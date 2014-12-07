#pragma once

#include <AudioToolbox/AudioToolbox.h>
#include <AudioUnit/AudioUnit.h>
#include <AudioUnit/AudioUnitCarbonView.h>
#include <Carbon/Carbon.h>

#include "ofMain.h"

#include <Cocoa/Cocoa.h>
#include <CoreFoundation/CoreFoundation.h>
#import <AppKit/AppKit.h>

#include "CAAUProcessor.h"

@class AUWindowController;

class ofxAUPlugin
{
protected:
	
	static vector<CAComponent *> components;
    static vector<string *> pluginsList;
    static map<string, ofVec2f> _paramsInfo;
	static bool inited;
	static int sampleRate, bufferSize;
	static void loadPlugins();

	static OSStatus inputCallback(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags, const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);

	vector<float> inputBuffer;
	AUOutputBL *outputBuffer;
	CAAUProcessor *processor;
    static CAAUProcessor *infoProcessor;

	int numInputCh, numOutputCh;
    
	void initProcessor(CAComponent comp);
	void initParameter(CAComponent comp);

public:
    
    struct ParamInfo
	{
		int paramID;
		string name;
		float minValue, maxValue;
	};

	static void init(int sampleRate = 44100, int bufferSize = 512);
	static void listPlugins();
    static vector<string *> getPluginsList();
    static map<string, ofVec2f> getPluginParams(string name);

	ofxAUPlugin();
	virtual ~ofxAUPlugin();

	void loadPlugin(string name);
	string loadPreset(string path);
    void savePreset(string path, string presetName);

	const int numInput() const { return numInputCh; }
	const int numOutput() const { return numOutputCh; }
	
	void listParamInfo();
	
	float getParam(const string& name);
	void setParam(const string& name, float value);

	void process(const float *input, float *output);
	
	void bypass(bool yn);
    
    void clear();
    void clearPluginUI();
    
    string                              pluginName;
    
    map<string, ParamInfo> paramsInfo;
    
    
private:

    AUWindowController  *windowController;
    CAComponent         *loadedComponent;
    static CAComponent         *infoloadedComponent;
};


/////////////////////////////////////////////////
// AU window controller
@interface AUWindowController : NSWindowController{
    IBOutlet NSBox *				uiAUViewContainer;
    IBOutlet NSView *               mView;
    IBOutlet NSScrollView *			mScrollView;
    
    // Carbon View Stuff
    ComponentDescription            _editUnitCD;
	AudioUnit                       _editUnit;
	AudioUnitCarbonView             _editView;
	WindowRef                       _carbonWindow;
	NSWindow                        *_cocoaWindow;
	NSSize                          _defaultViewSize;
    id                              _delegate;
    
}

- (void) AU_editwindowClosed;
- (BOOL) AU_error:(NSString*)errString status:(OSStatus)err;
+ (BOOL) plugInClassIsValid:(Class) pluginClass;

+ (id) editorForAudioUnit:(AudioUnit)unit forceGeneric:(BOOL)forceGeneric delegate:(id)delegate;
- (id) initWithAudioUnit: (AudioUnit)unit forceGeneric:(BOOL)forceGeneric delegate:(id)delegate;

- (void) showWindow:(id)sender;
- (void) closeWindow:(id)sender;

-(void) loadAUView:(NSString*)_name;

-(void) cleanup;


@end


