#include "ofxAUPlugin.h"
#include "ofUtils.h"

#import <CoreAudioKit/CoreAudioKit.h>
#import <CoreAudioKit/AUGenericView.h>
#import <AudioUnit/AUCocoaUIView.h>

#include <iostream>

vector<CAComponent*> ofxAUPlugin::components;
vector<string*> ofxAUPlugin::pluginsList;
map<string, ofVec2f> ofxAUPlugin::_paramsInfo;
CAComponent* ofxAUPlugin::infoloadedComponent;
CAAUProcessor* ofxAUPlugin::infoProcessor;
bool ofxAUPlugin::inited = false;

int ofxAUPlugin::sampleRate = 44100;
int ofxAUPlugin::bufferSize = 1024;

void ofxAUPlugin::loadPlugins(){
    
	for (unsigned int i = 0; i < components.size(); i++){
		delete components[i];
	}

	components.clear();
    
    for (unsigned int i = 0; i < pluginsList.size(); i++){
		delete pluginsList[i];
	}
    
	pluginsList.clear();

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    ///////////////////////////////////////////////////////////
	ComponentDescription cd;
	Component comp;

	cd.componentType = kAudioUnitType_Effect;
	cd.componentSubType = 0;
	cd.componentManufacturer = 0;
	cd.componentFlags = 0;
	cd.componentFlagsMask = 0;

	comp = FindNextComponent(NULL, &cd);

    int c = 0;
	while (comp != NULL){
		components.push_back(new CAComponent(comp));
        pluginsList.push_back(new string([(NSString*)components[c]->GetCompName() UTF8String]));
		comp = FindNextComponent(comp, &cd);
        c++;
	}
    
    cd.componentType = kAudioUnitType_MusicEffect;
	cd.componentSubType = 0;
	cd.componentManufacturer = 0;
	cd.componentFlags = 0;
	cd.componentFlagsMask = 0;
    
	comp = FindNextComponent(NULL, &cd);
    
	while (comp != NULL){
		components.push_back(new CAComponent(comp));
        pluginsList.push_back(new string([(NSString*)components[c]->GetCompName() UTF8String]));
		comp = FindNextComponent(comp, &cd);
        c++;
	}
    ///////////////////////////////////////////////////////////

	[pool release];
}

vector<string *> ofxAUPlugin::getPluginsList(){
    return pluginsList;
}

map<string, ofVec2f> ofxAUPlugin::getPluginParams(string name){
    
    for (unsigned int i = 0; i < components.size(); i++){
		string n = [(NSString*)components[i]->GetCompName() UTF8String];
		if (n == name){
			infoloadedComponent = components[i];
            
            _paramsInfo.clear();
            
            infoProcessor = new CAAUProcessor(*infoloadedComponent);
            
            // get parameter size
            UInt32 size;
            AudioUnitGetPropertyInfo(infoProcessor->AU().AU(),
                                     kAudioUnitProperty_ParameterList,
                                     kAudioUnitScope_Global,
                                     0,
                                     &size,
                                     NULL);
            
            int numOfParams = size / sizeof(AudioUnitParameterID);
            
            vector<AudioUnitParameterID> paramList(numOfParams, 0);
            
            // get parameter id list
            AudioUnitGetProperty(infoProcessor->AU().AU(),
                                 kAudioUnitProperty_ParameterList,
                                 kAudioUnitScope_Global,
                                 0,
                                 &paramList[0],
                                 &size);
            
            // get parameters info
            for (unsigned int i = 0; i < paramList.size(); i++){
                AudioUnitParameterInfo paramInfo;
                UInt32 size = sizeof(AudioUnitParameterInfo);
                
                AudioUnitGetProperty(infoProcessor->AU().AU(),
                                     kAudioUnitProperty_ParameterInfo,
                                     kAudioUnitScope_Global,
                                     paramList[i],
                                     &paramInfo,
                                     &size);
                
                ofVec2f info;
                info.x = paramInfo.minValue;
                info.y = paramInfo.maxValue;
                
                _paramsInfo[paramInfo.name] = info;
                
                //printf("%s\n",paramInfo.name);
            }
            
            return _paramsInfo;
		}
	}
}

void ofxAUPlugin::init(int sampleRate, int bufferSize){
	if (inited == false){
		inited = true;
		ofxAUPlugin::sampleRate = sampleRate;
		ofxAUPlugin::bufferSize = bufferSize;

		loadPlugins();
	}
    
}

void ofxAUPlugin::listPlugins(){
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	for (unsigned int i = 0; i < components.size(); i++){
		printf("[%i] - %s\n", i, [(NSString*)components[i]->GetCompName() UTF8String]);
	}

	[pool release];
}

ofxAUPlugin::ofxAUPlugin(){
	outputBuffer = NULL;
	processor = NULL;
	numInputCh = numOutputCh = 0;

	clear();
    
}

ofxAUPlugin::~ofxAUPlugin()
{
	clear();
}

void ofxAUPlugin::clear(){
	if (outputBuffer){
		delete outputBuffer;
		outputBuffer = NULL;
	}

	if (processor){
		delete processor;
		processor = NULL;
	}
    
}

void ofxAUPlugin::clearPluginUI(){
    [windowController dealloc];
}

void ofxAUPlugin::initProcessor(CAComponent comp){
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	clear();

	processor = new CAAUProcessor(comp);

	CAStreamBasicDescription input_format, output_format;

	assert(processor->AU().GetFormat(kAudioUnitScope_Input, 0, input_format) == noErr);
	assert(processor->AU().GetFormat(kAudioUnitScope_Output, 0, output_format) == noErr);

	numInputCh = input_format.NumberChannels();
	numOutputCh = output_format.NumberChannels();

	assert(numInputCh > 0 || numOutputCh > 0);

	assert(processor->Initialize(input_format, output_format, 0) == noErr);
	assert(processor->Preflight() == noErr);

	AURenderCallbackStruct cb;
	cb.inputProc = ofxAUPlugin::inputCallback;
	cb.inputProcRefCon = this;

	assert(processor->EstablishInputCallback(cb) == noErr);

	outputBuffer = new AUOutputBL(output_format, bufferSize);
	outputBuffer->Allocate(bufferSize);
	outputBuffer->Prepare();

	[pool release];

	initParameter(comp);
}

void ofxAUPlugin::initParameter(CAComponent comp){
	CAAudioUnit &au = processor->AU();

	// get parameter size

	UInt32 size;
	AudioUnitGetPropertyInfo(au.AU(),
		kAudioUnitProperty_ParameterList,
		kAudioUnitScope_Global,
		0,
		&size,
		NULL);

	int numOfParams = size / sizeof(AudioUnitParameterID);

	vector<AudioUnitParameterID> paramList(numOfParams, 0);

	// get parameter id list

	AudioUnitGetProperty(au.AU(),
		kAudioUnitProperty_ParameterList,
		kAudioUnitScope_Global,
		0,
		&paramList[0],
		&size);

	paramsInfo.clear();

	// get parameters info

	for (unsigned int i = 0; i < paramList.size(); i++){
		AudioUnitParameterInfo paramInfo;
		UInt32 size = sizeof(AudioUnitParameterInfo);

		AudioUnitGetProperty(au.AU(),
			kAudioUnitProperty_ParameterInfo,
			kAudioUnitScope_Global,
			paramList[i],
			&paramInfo,
			&size);

		ParamInfo info;
		info.paramID = paramList[i];
		info.name = paramInfo.name;
		info.minValue = paramInfo.minValue;
		info.maxValue = paramInfo.maxValue;

		paramsInfo[paramInfo.name] = info;
	}
    
    // Load Plugin UI View
    pluginName = [(NSString*)comp.GetCompName() UTF8String];
    NSString* _AUname = [[(NSString*)comp.GetCompName() componentsSeparatedByString: @":"] objectAtIndex:1];
    windowController = [[AUWindowController alloc] initWithAudioUnit:processor->AU().AU() forceGeneric:NO delegate:nil];
    [windowController loadAUView:_AUname];
    
}

void ofxAUPlugin::loadPlugin(string name){
    
	//ofxAUPlugin::init();

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	for (unsigned int i = 0; i < components.size(); i++){
		string n = [(NSString*)components[i]->GetCompName() UTF8String];

		if (n == name){
			loadedComponent = components[i];
		}
	}

	if (loadedComponent == NULL){
		ofLog(OF_LOG_ERROR, "plugin not found: %s", name.c_str());
	}

	clear();

	initProcessor(*loadedComponent);

	[pool release];
}

string ofxAUPlugin::loadPreset(string path){
	//ofxAUPlugin::init();
    
    string pName;

	path = ofToDataPath(path, true);

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	NSDictionary *data = [NSDictionary dictionaryWithContentsOfFile:[NSString stringWithUTF8String:path.c_str()]];

	int type = [[data objectForKey:@"type"] intValue];
	int subtype = [[data objectForKey:@"subtype"] intValue];
	int manufacturer = [[data objectForKey:@"manufacturer"] intValue];

	for (unsigned int i = 0; i < components.size(); i++){
        
		CAComponent comp = CAComponent(type, subtype, manufacturer);

		if (components[i]->Comp() == comp.Comp()){
			loadedComponent = components[i];
            pName = [(NSString*)components[i]->GetCompName() UTF8String];
			break;
		}
	}

	clear();

	initProcessor(*loadedComponent);

	assert(processor->SetAUPreset(data) == noErr);

	[pool release];
    
    CFURLRef presetURL = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault,
                                                           (const UInt8*)path.c_str(),
                                                           path.length(),
                                                           NULL);
    
    
    CFDataRef         presetData;
	CFPropertyListRef presetPList;
	Boolean           presetReadSuccess;
	SInt32            presetReadErrorCode;
	OSStatus          presetSetStatus;
    
    presetReadSuccess = CFURLCreateDataAndPropertiesFromResource(kCFAllocatorDefault,
																 presetURL,
																 &presetData,
																 NULL,
																 NULL,
																 &presetReadErrorCode);
	if(presetReadSuccess){
		presetPList = CFPropertyListCreateWithData(kCFAllocatorDefault,
												   presetData,
												   kCFPropertyListImmutable,
												   NULL,
												   NULL);
		
		presetSetStatus = AudioUnitSetProperty(processor->AU().AU(),
											   kAudioUnitProperty_ClassInfo,
											   kAudioUnitScope_Global,
											   0,
											   &presetPList,
											   sizeof(presetPList));
		CFRelease(presetData);
		CFRelease(presetPList);
	}else{
		cout << "Couldn't read preset" << endl;
	}
    
    
    CFRelease(presetURL);
    
    return pName;
    
}

void ofxAUPlugin::savePreset(string path, string presetName){
    
    string finalPath = path.append("/").append(presetName).append(".aupreset");
    
    CFURLRef fileURL = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault,
                                                           (const UInt8*)finalPath.c_str(),
                                                           finalPath.length(),
                                                           NULL);
    
    //NSURL *fileURL = [NSURL fileURLWithPath:nsPath];
    
    CFPropertyListRef  myClassData;
    UInt32 size = sizeof(myClassData);
    
    AudioUnitGetProperty(processor->AU().AU(),
                         kAudioUnitProperty_ClassInfo,
                         kAudioUnitScope_Global,
                         0,
                         &myClassData,
                         &size);
    
    if(!CFPropertyListIsValid(myClassData, kCFPropertyListXMLFormat_v1_0)) return false;
    
    // if succesful, writing it to a file
	CFDataRef presetData = CFPropertyListCreateXMLData(kCFAllocatorDefault, myClassData);
    
    // Write the XML data to the file.
    SInt32 errorCode;
    Boolean status = CFURLWriteDataAndPropertiesToResource(fileURL, presetData, NULL, &errorCode);
    
    CFRelease(presetData);
    
    if (!status) {
        cout << "Error " << errorCode << " writing preset file" << endl;
    }
    
    CFRelease(fileURL);

}


OSStatus ofxAUPlugin::inputCallback(void *inRefCon,AudioUnitRenderActionFlags *ioActionFlags,const AudioTimeStamp *inTimeStamp,UInt32 inBusNumber,UInt32 inNumberFrames,AudioBufferList *ioData){
    
	ofxAUPlugin *self = (ofxAUPlugin*)inRefCon;

	for (unsigned int c = 0; c < ioData->mNumberBuffers; c++){
		AudioBuffer &buffer = ioData->mBuffers[c];
		const float *src = &self->inputBuffer[0] + c;
		float *dst = (float*)buffer.mData;

		for (int i = 0; i < bufferSize; i++){
			*dst = *src;
			src += self->numInputCh;
			dst += 1;
		}
	}

	return noErr;
}

void ofxAUPlugin::process(const float *input, float *output){
    
	if (processor == NULL || outputBuffer == NULL){
		//ofLog(OF_LOG_ERROR, "ofxAUPlugin: not initialized yet");
		return;
	}

	AudioTimeStamp time;
	memset (&time, 0, sizeof(time));
	time.mSampleTime = ofGetElapsedTimef() * sampleRate;
	time.mFlags = kAudioTimeStampSampleTimeValid;

	inputBuffer.assign(input, input + (bufferSize * numInputCh));

	bool outIsSilence = false;
	UInt32 frames = bufferSize;
	bool outOLCompleted = false, outOLRequiresPostProcess = false, outDone = false;

	assert(processor->Render(outputBuffer->ABL(), frames, outIsSilence, &outOLCompleted, &outOLRequiresPostProcess) == noErr);
    

	if (outOLRequiresPostProcess){
		while (!outDone){
			assert(processor->PostProcess(outputBuffer->ABL(), frames, outIsSilence, outDone) == noErr);
		}
	}

	for (int c = 0; c < numOutputCh; c++){
		AudioBuffer &buffer = outputBuffer->ABL()->mBuffers[c];
		float *src = (float*)buffer.mData;
		float *dst = output + c;

		for (int i = 0; i < bufferSize; i++)
		{
			*dst = *src++;
			dst += numOutputCh;
		}
	}
}

void ofxAUPlugin::listParamInfo(){
	map<string, ParamInfo>::iterator it = paramsInfo.begin();
	
	while (it != paramsInfo.end()){
		const ParamInfo &param = (*it).second;
		cout << "#" << param.paramID << ": " << param.name << " [" << param.minValue << " ~ " << param.maxValue << "]" << endl;		
		it++;
	}
}

float ofxAUPlugin::getParam(const string& name){
    
	if (paramsInfo.find(name) == paramsInfo.end()) return 0;
	
	float result;
	ParamInfo &info = paramsInfo[name];
	
	AudioUnitGetParameter(processor->AU().AU(),
						  info.paramID,
						  kAudioUnitScope_Global,
						  0,
						  &result);
	
	return result;
}

void ofxAUPlugin::setParam(const string& name, float value){
    
	if (paramsInfo.find(name) == paramsInfo.end()) return;
	
	ParamInfo &info = paramsInfo[name];
	CAAudioUnit &au = processor->AU();
	
	value = ofClamp(value, info.minValue, info.maxValue);
	
	AudioUnitSetParameter(au.AU(),
						  info.paramID,
						  kAudioUnitScope_Global,
						  0,
						  value,
						  0);
}

void ofxAUPlugin::bypass(bool yn){
	if (processor->AU().CanBypass()){
		processor->AU().SetBypass(yn);
    }
}


//////////////////////////////////////////////////////////////
// AU window controller implementation

static OSStatus WindowClosedHandler (EventHandlerCallRef myHandler, EventRef theEvent, void* userData){
	AUWindowController* me = (AUWindowController*)userData;
	[me AU_editwindowClosed];
	return noErr;
}

@implementation AUWindowController

+ (id) editorForAudioUnit:(AudioUnit)unit forceGeneric:(BOOL)forceGeneric delegate:(id)delegate{
	return [[[[self class] alloc] initWithAudioUnit:unit forceGeneric:forceGeneric delegate:delegate] autorelease];
}

- (void) AU_editwindowClosed{
    NSLog(@"Closing audio unit editor.");
    if(_carbonWindow){
        DisposeWindow(_carbonWindow);
    }
    if(_editView){
		CloseComponent(_editView);
    }
}

- (BOOL) AU_error:(NSString*)errString status:(OSStatus)err{
	NSString* errorString = [NSString stringWithFormat: @"%@ failed; %i / %4.4s",
                             errString, (int)err, (char*)&err];
	NSLog(@"%@",errorString);
	return NO;
}

- (BOOL) installWindowCloseHandler{
	OSStatus err;
	EventHandlerUPP handlerUPP;
	EventTypeSpec eventList[] = {{kEventClassWindow, kEventWindowClose}};
	
	handlerUPP = NewEventHandlerUPP(WindowClosedHandler);
	
	err = InstallWindowEventHandler(_carbonWindow, handlerUPP, GetEventTypeCount(eventList), eventList, self, NULL);
	if (err) return [self AU_error: @"Install close window handler" status: err];
	return YES;
}

- (void)initializeEditViewComponentDescription:(BOOL)forceGeneric{
	OSStatus err;
	
	// set up to use generic UI component
	_editUnitCD.componentType         = kAudioUnitCarbonViewComponentType;
	_editUnitCD.componentSubType      = 'gnrc';
	_editUnitCD.componentManufacturer = 'appl';
	_editUnitCD.componentFlags        = 0;
	_editUnitCD.componentFlagsMask    = 0;
	
	if(forceGeneric) return;
    
	// ask the AU for its first editor component
	UInt32 propertySize;
	err = AudioUnitGetPropertyInfo(
                                   _editUnit, kAudioUnitProperty_GetUIComponentList, kAudioUnitScope_Global, 0, &propertySize, NULL);
	
	// An error occured so we will just have to use the generic control.
	if(err) return;
    
	ComponentDescription *editors = (ComponentDescription*) malloc(propertySize);
	err = AudioUnitGetProperty(
                               _editUnit, kAudioUnitProperty_GetUIComponentList, kAudioUnitScope_Global, 0, editors, &propertySize);
	if(!err)
		_editUnitCD = editors[0];	// just pick the first one for now
	free(editors);
}

+ (BOOL)plugInClassIsValid:(Class) pluginClass{
	if ([pluginClass conformsToProtocol:@protocol(AUCocoaUIBase)]) {
		if ([pluginClass instancesRespondToSelector:@selector(interfaceVersion)] &&
			[pluginClass instancesRespondToSelector:@selector(uiViewForAudioUnit:withSize:)]) {
			return YES;
		}
	}
    return NO;
}

- (BOOL) hasCocoaView{
	UInt32 dataSize   = 0;
	Boolean isWritable = 0;
	OSStatus err = AudioUnitGetPropertyInfo(_editUnit,
                                            kAudioUnitProperty_CocoaUI,
                                            kAudioUnitScope_Global,
                                            0,
                                            &dataSize,
                                            &isWritable);
    
	return dataSize > 0 && err == noErr;
}

- (NSView *) getCocoaView{
	// get AU's Cocoa view property
    UInt32 						dataSize;
    Boolean 					isWritable;
    AudioUnitCocoaViewInfo *	cocoaViewInfo = NULL;
    UInt32						numberOfClasses;
    
    OSStatus result = AudioUnitGetPropertyInfo(	_editUnit,
                                               kAudioUnitProperty_CocoaUI,
                                               kAudioUnitScope_Global,
                                               0,
                                               &dataSize,
                                               &isWritable );
    
    numberOfClasses = (dataSize - sizeof(CFURLRef)) / sizeof(CFStringRef);
    
    NSURL 	 *	CocoaViewBundlePath = nil;
    NSString *	factoryClassName = nil;
    
	// Does view have custom Cocoa UI?
    if ((result == noErr) && (numberOfClasses > 0) ) {
        cocoaViewInfo = (AudioUnitCocoaViewInfo *)malloc(dataSize);
        if(AudioUnitGetProperty(		_editUnit,
                                kAudioUnitProperty_CocoaUI,
                                kAudioUnitScope_Global,
                                0,
                                cocoaViewInfo,
                                &dataSize) == noErr) {
            CocoaViewBundlePath	= (NSURL *)cocoaViewInfo->mCocoaAUViewBundleLocation;
			
			// we only take the first view in this example.
            factoryClassName	= (NSString *)cocoaViewInfo->mCocoaAUViewClass[0];
        } else {
            if (cocoaViewInfo != NULL) {
				free (cocoaViewInfo);
				cocoaViewInfo = NULL;
			}
        }
    }
	
	NSView *AUView = nil;
	BOOL wasAbleToLoadCustomView = NO;
	
	// [A] Show custom UI if view has it
	if (CocoaViewBundlePath && factoryClassName) {
		NSBundle *viewBundle  	= [NSBundle bundleWithPath:[CocoaViewBundlePath path]];
		if (viewBundle == nil) {
			NSLog (@"Error loading AU view's bundle");
		} else {
			Class factoryClass = [viewBundle classNamed:factoryClassName];
			NSAssert (factoryClass != nil, @"Error getting AU view's factory class from bundle");
			
			// make sure 'factoryClass' implements the AUCocoaUIBase protocol
			NSAssert(	[AUWindowController plugInClassIsValid:factoryClass],
                     @"AU view's factory class does not properly implement the AUCocoaUIBase protocol");
			
			// make a factory
			id factoryInstance = [[[factoryClass alloc] init] autorelease];
			NSAssert (factoryInstance != nil, @"Could not create an instance of the AU view factory");
			// make a view
			AUView = [factoryInstance	uiViewForAudioUnit:_editUnit withSize:_defaultViewSize];
			
			// cleanup
			[CocoaViewBundlePath release];
			if (cocoaViewInfo) {
				UInt32 i;
				for (i = 0; i < numberOfClasses; i++)
					CFRelease(cocoaViewInfo->mCocoaAUViewClass[i]);
				
				free (cocoaViewInfo);
			}
			wasAbleToLoadCustomView = YES;
		}
	}
	
	if (!wasAbleToLoadCustomView) {
        // [C] Otherwise show generic Cocoa view
        AUView = [[AUGenericView alloc] initWithAudioUnit:_editUnit];
        [(AUGenericView *)AUView setShowsExpertParameters:YES];
        [AUView autorelease];
    }
	
	// Finally return created view
	return AUView;
}

- (BOOL) createCarbonWindow{
	Component editComponent = FindNextComponent(NULL, &_editUnitCD);
	OpenAComponent(editComponent, &_editView);
	if (!_editView)
		[NSException raise:NSGenericException format:@"Could not open audio unit editor component"];
	
	Rect bounds = { 100, 100, 100, 100 }; // Generic resized later
	OSStatus res = CreateNewWindow(kUtilityWindowClass,
                                   kWindowCloseBoxAttribute | kWindowCollapseBoxAttribute | kWindowStandardHandlerAttribute | kWindowSideTitlebarAttribute |
                                   kWindowCompositingAttribute, &bounds, &_carbonWindow);
    
	if(res != noErr)
		return [self AU_error:@"Create new carbon window" status:res];
	
	// create the edit view
	ControlRef rootControl;
	res = GetRootControl(_carbonWindow, &rootControl);
	if(!rootControl)
		return [self AU_error:@"Get root control of carbon window" status:res];
    
	ControlRef viewPane;
	Float32Point loc  = { 0.0, 0.0 };
	Float32Point size = { 0.0, 0.0 } ;
	AudioUnitCarbonViewCreate(_editView, _editUnit, _carbonWindow,
                              rootControl, &loc, &size, &viewPane);
    
	// resize and move window
	GetControlBounds(viewPane, &bounds);
	size.x = bounds.right-bounds.left;
	size.y = bounds.bottom-bounds.top;
	SizeWindow(_carbonWindow, (short) (size.x + 0.5), (short) (size.y + 0.5),  true);
	RepositionWindow(_carbonWindow, NULL, kWindowCenterOnMainScreen);
	
	return YES;
}

- (BOOL) createCocoaWindow{
	if([self hasCocoaView]){
		NSView * res = [self getCocoaView];
		if(res) {
			NSWindow * window = [[[NSWindow alloc] initWithContentRect:
                                  NSMakeRect(100, 400, [res frame].size.width, [res frame].size.height) styleMask:
                                  NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
                                                               backing:NSBackingStoreBuffered defer:NO] autorelease];
			[window setContentView:res];
			[window setIsVisible:YES];
			_cocoaWindow = [window retain];
			return YES;
		}
	}
	return NO;
}

- (void) showWindow: (id) sender{
	if(_cocoaWindow)
		[super showWindow:sender];
	else SelectWindow(_carbonWindow);
}

- (void) closeWindow: (id) sender{
	if(_cocoaWindow){
		[super close];
    }
}

- (id) initWithAudioUnit: (AudioUnit) unit forceGeneric: (BOOL) forceGeneric delegate: (id) delegate{
	_editUnit = unit;
	_delegate = delegate;
	_defaultViewSize = NSMakeSize(400, 300);
	
	if([self hasCocoaView]) {
		[self createCocoaWindow];
		self = [super initWithWindow:[_cocoaWindow autorelease]];
	}
	else self = [super initWithWindow:nil];
	
	if(!self)
		return nil;
	
	// Run only if we did not create a cocoa window
	if(!_cocoaWindow) {
		[self initializeEditViewComponentDescription: forceGeneric];
		
		if(![self createCarbonWindow])  {
			[self release];
			return nil;
		}
        
		if(![self installWindowCloseHandler]) {
			[self release];
			return nil;
		}
        
		// create the cocoa window for the carbon one and make it visible
		NSWindow *cocoaWindow = [[NSWindow alloc] initWithWindowRef:_carbonWindow];
		[self setWindow:cocoaWindow];
		[cocoaWindow setIsVisible:YES];
	}
	return self;
}

/*- (id) initWithWindowNibName:(NSString *)nibFile{
    self = [super initWithWindowNibName:nibFile];
    if (self) {        
        // make this the app. delegate
        [NSApp setDelegate:self];
    }
    
    return self;
}*/

- (void)cleanup {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void) loadAUView:(NSString*)_name{
    [[self window] setTitle:_name];
}

- (void) dealloc{
    //[self cleanup];
	
	if(_editView)
		CloseComponent(_editView);
	if(_carbonWindow)
		DisposeWindow(_carbonWindow);
    
	[super dealloc];
}

@end

