
#import <IOKit/graphics/IOGraphicsLib.h>

#import "AppDelegate.h"
#import "NSMenu+DeepSearch.h"
#import "GAMultiTextDocument.h"

@implementation AppDelegate

//------------------------------------------------------------------------------
- (id)init{
    applicationHasStarted = NO;
    GAExampleFiles       = [[NSMutableArray alloc] init];
    GASketchbookFiles    = [[NSMutableArray alloc] init];
    return self;
}

//------------------------------------------------------------------------------
- (void)terminateSplashWindow:(NSTimer *)timer {
    [_splash orderOut:self];
    
    isPreviewON = false;
    [gappWindow->getWindow() makeKeyAndOrderFront:self];
    
    if(prefPanel._autoFullscreen == 1){
        [self getScreenXPosition:prefPanel._fullscreenScreen];
        gappWindow->setWindowPosition(fullscreenWinPosX,screenH-60);
        gappWindow->toggleFullscreen();
        gapp->gamuzaFullscreen();
    }
    
}

//------------------------------------------------------------------------------
- (void) applicationDidFinishLaunching: (NSNotification*) notification {
    
    //fire up ofxNSWindower
    ofxNSWindower::instance();
    
    // Create and populate gamuza's folders
    BOOL isDir;
    [self screenResolution];
    [self createGAmuzaDirectory];
    [self getGAmuzaFolderContents:resPath];
    if ([filemgr fileExistsAtPath:documentsDirectory isDirectory:&isDir] && isDir){
        [self getSketchbookFolderContents:documentsDirectory];
    }
    
    // Register notification for console logs & errors
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(checkForGALog:) name:@"GAConsoleLog" object:NULL ];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(checkForLogMessages:) name:@"GALogMessageEvent" object:NULL ];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(checkForLogErrors:) name:@"GALogErrorEvent" object:NULL ];
    
    // START GAmuza video preview
    gaVP = new gaVideoPreview();
    ofxNSWindower::instance()->addWindow(gaVP,"Preview", NSBorderlessWindowMask, 0);
    gaVPWindow = ofxNSWindower::instance()->getWindowPtr("Preview");
    gaVPWindow->setWindowTitle("Preview");
    gaVPWindow->setWindowShape(320,240);
    gaVPWindow->setWindowPosition(screenW-330,screenH-30);
    [gaVPWindow->getWindow() orderOut:self];
    
    // START GAmuza TIMELINE Panel
    gaTL = new gaTimeline(screenW,screenH);
    ofxNSWindower::instance()->addWindow(gaTL,"Timeline", NSTitledWindowMask|NSResizableWindowMask, 0);
    gaTLWindow = ofxNSWindower::instance()->getWindowPtr("Timeline");
    gaTLWindow->setWindowTitle("Timeline");
    gaTLWindow->setWindowShape(screenW,screenH-30);
    gaTLWindow->setWindowPosition(0,0);
    //[gaTLWindow->getWindow() setContentSize:NSMakeSize(800,400)];
    [gaTLWindow->getWindow() orderOut:self];
    
    
    // START GAmuza render window
    gapp = new gamuzaMain();
	ofxNSWindower::instance()->addWindow(gapp,"gamuza", NSTitledWindowMask, 0);
    gappWindow = ofxNSWindower::instance()->getWindowPtr("gamuza");
    gappWindow->setWindowTitle(gapp->_windowTitle);
    gappWindow->setWindowPosition(screenW - MAIN_WINDOW_W,screenH - MAIN_WINDOW_H);
    [gappWindow->getWindow() orderOut:self];
    gaVP->setFboDim(gapp->projectionScreenW,gapp->projectionScreenH);
    [self sendScreenResToGA];
    gapp->sendHardwareInfo(aInD,aInDID,aOutD,aOutDID,mD,sD,aInputCH,aOutputCH);
    [self sendDataToPreferences];
    
    // Splash window
    [_splash makeKeyAndOrderFront:self];
    NSTimer *t = [NSTimer scheduledTimerWithTimeInterval:3.1
                                    target:self
                                    selector:@selector(terminateSplashWindow:)
                                    userInfo:NULL
                                    repeats:NO];
    
    applicationHasStarted = YES;
    
    NSString *tempRelease = [NSString stringWithFormat:@"GAmuza %@ | Hybrid Live OF Sketching IDE",[NSString stringWithCString:GAMUZA_RELEASE encoding:[NSString defaultCStringEncoding]]];
    [self sendGALog:tempRelease];
    [self sendGALog:@"----------------------------------------------------------"];
    [self sendGALog:@" "];
    [self sendGALog:@"   Powered  by OF           <http://www.openframeworks.cc>"];
    [self sendGALog:@"   Inspired by Processing   <http://www.processing.org>"];
    [self sendGALog:@" "];
    [self sendGALog:@"   Created  by Emanuele Mazza aka n3m3da"];
    [self sendGALog:@"----------------------------------------------------------"];
    [self sendGALog:@" "];
    
    [self sendGALog:@"GAmuza STARTED"];
    [self sendGALog:@" "];
    

}

//------------------------------------------------------------------------------
- (void) createGAmuzaDirectory{
    
    // if not exist create the GAmuza script directory inside /Users/user_@@@/Documents/ folder
    filemgr = [NSFileManager defaultManager];
    
    NSURL           *newDir;
    NSArray         *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    
    resPath = [[NSBundle mainBundle] pathForResource: @"GAmuza" ofType: @""];
    
    newDir = [NSURL fileURLWithPath:[NSString stringWithFormat:@"%@/%@", [paths objectAtIndex:0], @"GAmuza"]];
    documentsDirectory = [NSString stringWithFormat:@"%@/%@/", [paths objectAtIndex:0], @"GAmuza"];
    
    // create GAmuza directory
    [filemgr createDirectoryAtPath:documentsDirectory withIntermediateDirectories:YES attributes: NULL error:NULL];
    
    //NSString *tempMessage = [NSString stringWithFormat:@"GAmuza Sketchbook directory: %@",documentsDirectory];
    //[self sendGALog:@""];
    //[self sendGALog:tempMessage];
    
}

//------------------------------------------------------------------------------
- (void) getGAmuzaFolderContents:(NSString*)path{
    
    BOOL isDir;
    NSString*   importFile;
    NSMenu*     lastFolder;
    NSString*   actualPath;
    NSDirectoryEnumerator *dirEnum =[filemgr enumeratorAtPath:path];
    
    int x = 0;
    NSMenuItem  *foundItem  = NULL;
    NSMenu      *syntaxMenu = NULL;
    NSMenuItem  *thisFile   = NULL;
    NSMenuItem  *tempItem   = NULL;
    foundItem = [[NSApp mainMenu] findItemWithTarget:NULL andAction:@selector(openItemFromGAmuzaFolder:)];
    syntaxMenu = [foundItem menu];
    
    // Remove all old menu items from our menu:
	NSMenuItem*         currMItem = foundItem;
	double				currItemNum = [syntaxMenu indexOfItem: currMItem];
	
	while( [currMItem action] == @selector(openItemFromGAmuzaFolder:) )
	{
		[syntaxMenu removeItem: currMItem];
		if( currItemNum < [syntaxMenu numberOfItems] )
			currMItem = [syntaxMenu itemAtIndex: currItemNum];
		else
			break;
	}
    
    // Populate Examples menu
    bool        lastOneIsDir = false;
    bool        insideData;
    while (importFile = [dirEnum nextObject]){
        // eliminate from listing hidden files and .DS_Store files
        if([importFile hasPrefix:@"."] || [importFile rangeOfString:@".DS_Store"].location != NSNotFound){
            continue;
        }
        
        actualPath = [path stringByAppendingPathComponent:importFile];
        [GAExampleFiles addObject:actualPath];
        
        NSString*   lpComponent = [importFile lastPathComponent];
        NSString*   dName = [lpComponent stringByDeletingPathExtension];
        NSString*   actualDir = [[importFile stringByDeletingLastPathComponent] lastPathComponent];
        
        insideData = false;
        
        if([importFile rangeOfString:@"/data"].location != NSNotFound){
            insideData = true;
        }
        
        if([filemgr fileExistsAtPath:actualPath isDirectory:&isDir] && isDir && [importFile rangeOfString:@"/"].location == NSNotFound){
            if(!lastOneIsDir){
                NSMenu      *subFolder  = [[NSMenu alloc] init];
                tempItem = [syntaxMenu addItemWithTitle:importFile action:NULL keyEquivalent:@""];
                [tempItem setSubmenu:subFolder];
                lastFolder = subFolder;
                lastOneIsDir = true;
            }else{
                NSMenu      *subSubFolder  = [[NSMenu alloc] init];
                tempItem = [lastFolder addItemWithTitle:importFile action:NULL keyEquivalent:@""];
                [tempItem setSubmenu:subSubFolder];
                lastFolder = subSubFolder;
                lastOneIsDir = true;
            }
        }else if([importFile hasSuffix:@".ga"] && [importFile rangeOfString:dName].location != NSNotFound && insideData == false){
            if([actualDir isEqualToString:dName]){
                thisFile = [lastFolder addItemWithTitle:dName action: @selector(openItemFromGAmuzaFolder:) keyEquivalent:@""];
                [thisFile setTag: x];
                lastOneIsDir = false;
            }
        }
        
        x++;
        
    }
}

//------------------------------------------------------------------------------
- (void) getSketchbookFolderContents:(NSString*)path{
    
    BOOL isDir;
    NSString*   importFile;
    NSMenu*     lastFolder;
    NSString*   actualPath;
    NSDirectoryEnumerator *dirEnum =[filemgr enumeratorAtPath:path];
    
    int x = 0;
    NSMenuItem  *foundItem  = NULL;
    NSMenu      *syntaxMenu = NULL;
    NSMenuItem  *thisFile   = NULL;
    NSMenuItem  *tempItem   = NULL;
    foundItem = [[NSApp mainMenu] findItemWithTarget:NULL andAction:@selector(openItemFromSketchbookFolder:)];
    syntaxMenu = [foundItem menu];
    
    // Remove all old menu items from our menu:
	NSMenuItem*         currMItem = foundItem;
	double				currItemNum = [syntaxMenu indexOfItem: currMItem];
	
	while( [currMItem action] == @selector(openItemFromSketchbookFolder:) )
	{
		[syntaxMenu removeItem: currMItem];
		if( currItemNum < [syntaxMenu numberOfItems] )
			currMItem = [syntaxMenu itemAtIndex: currItemNum];
		else
			break;
	}
    
    // Populate Examples menu
    bool        lastOneIsDir = false;
    bool        insideData;
    while (importFile = [dirEnum nextObject]){
        // eliminate from listing hidden files and .DS_Store files
        if([importFile hasPrefix:@"."] || [importFile rangeOfString:@".DS_Store"].location != NSNotFound){
            continue;
        }
        
        actualPath = [path stringByAppendingPathComponent:importFile];
        [GASketchbookFiles addObject:actualPath];
        
        NSString*   lpComponent = [importFile lastPathComponent];
        NSString*   dName = [lpComponent stringByDeletingPathExtension];
        NSString*   actualDir = [[importFile stringByDeletingLastPathComponent] lastPathComponent];
        
        insideData = false;
        
        if([importFile rangeOfString:@"/data"].location != NSNotFound){
            insideData = true;
        }
        
        if([filemgr fileExistsAtPath:actualPath isDirectory:&isDir] && isDir && [importFile rangeOfString:@"/"].location == NSNotFound){
            if(!lastOneIsDir){
                NSMenu      *subFolder  = [[NSMenu alloc] init];
                tempItem = [syntaxMenu addItemWithTitle:importFile action:NULL keyEquivalent:@""];
                [tempItem setSubmenu:subFolder];
                lastFolder = subFolder;
                lastOneIsDir = true;
            }else{
                NSMenu      *subSubFolder  = [[NSMenu alloc] init];
                tempItem = [lastFolder addItemWithTitle:importFile action:NULL keyEquivalent:@""];
                [tempItem setSubmenu:subSubFolder];
                lastFolder = subSubFolder;
                lastOneIsDir = true;
            }
        }else if([importFile hasSuffix:@".ga"] && [importFile rangeOfString:dName].location != NSNotFound && insideData == false){
            if([actualDir isEqualToString:dName]){
                thisFile = [lastFolder addItemWithTitle:dName action: @selector(openItemFromSketchbookFolder:) keyEquivalent:@""];
                [thisFile setTag: x];
                lastOneIsDir = false;
            }
        }
        
        x++;
        
    }
}

//------------------------------------------------------------------------------
- (void) applicationWillTerminate: (NSNotification*) notification {
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
	ofxNSWindower::destroy();
}

//------------------------------------------------------------------------------
- (void) checkForGALog: (NSNotification *) notification{
    NSString *gaString = [NSString stringWithUTF8String:gapp->currentGlobalLog.c_str()];
    [self sendGALog:gaString];
}

//------------------------------------------------------------------------------
- (void) checkForLogMessages: (NSNotification *) notification{
    GAMultiTextDocument * currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    NSString *gaString = [NSString stringWithUTF8String:gapp->currentLog.c_str()];
    
    [currentDoc addLogMsg:gaString];
}

//------------------------------------------------------------------------------
- (void) checkForLogErrors: (NSNotification *) notification{
    GAMultiTextDocument * currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    NSString *gaString = [NSString stringWithUTF8String:gapp->currentErrorLog.c_str()];
    
    [currentDoc addErrorMsg:gaString];
}

//------------------------------------------------------------------------------
- (NSString*) screenNameFromID:(CGDirectDisplayID)displayID{
    NSString *screenName = NULL;
    
    NSDictionary *deviceInfo = (NSDictionary *)IODisplayCreateInfoDictionary(CGDisplayIOServicePort(displayID), kIODisplayOnlyPreferredName);
    NSDictionary *localizedNames = [deviceInfo objectForKey:[NSString stringWithUTF8String:kDisplayProductName]];
    
    if ([localizedNames count] > 0) {
    	screenName = [[localizedNames objectForKey:[[localizedNames allKeys] objectAtIndex:0]] retain];
    }
    
    [deviceInfo release];
    return [screenName autorelease];
}

//------------------------------------------------------------------------------
- (void) getScreenXPosition:(int)screenNum{
    int xPos = 20;
    
    unsigned i = 0;
    for(NSString *s in screensINFO){
        NSRect nsr = NSRectFromString(s);
        if(i < screenNum){
            xPos += (int)nsr.size.width;
        }
        i++;
    }
    
    fullscreenWinPosX = xPos;
    
}

//------------------------------------------------------------------------------
- (void) screenResolution{
    
    NSRect              screenRect;
    NSDictionary*       screenDescription;
    CGDirectDisplayID   theCGDisplayID;
    NSArray*            screenArray = [NSScreen screens];
    
    unsigned screenCount = [screenArray count];
    screensINFO = [[NSMutableArray alloc] initWithCapacity:screenCount];
    
    unsigned i = 0;
    
    [self sendGALog:@""];
    [self sendGALog:@" ------------------------------------------------ SCREENS CONNECTED"];
    for(i;i < screenCount;i++){
        NSScreen *screen = [screenArray objectAtIndex: i];
        screenRect = [screen visibleFrame];
        screenDescription = [screen deviceDescription];
        
        theCGDisplayID = (CGDirectDisplayID) [[screenDescription valueForKey:@"NSScreenNumber"] intValue];
        
        NSRect      tempRect = NSMakeRect((float)CGRectGetMinX(CGDisplayBounds(theCGDisplayID)),(float)CGRectGetMinY(CGDisplayBounds(theCGDisplayID)),(float)CGDisplayPixelsWide(theCGDisplayID),(float)CGDisplayPixelsHigh(theCGDisplayID));
        [screensINFO addObject:NSStringFromRect(tempRect)];
        
        NSString *tempMessage = [NSString stringWithFormat:@" Screen %i: %@  %ix%i", i+1,[self screenNameFromID:theCGDisplayID],(int)tempRect.size.width,(int)tempRect.size.height];
        [self sendGALog:tempMessage];
        [self sendGALog:@""];
        
        if(i==0){ // main screen
            screenW = (int)tempRect.size.width;
            screenH = (int)tempRect.size.height;
        }
    }
    
}

//------------------------------------------------------------------------------
- (void) sendScreenResToGA{
    gapp->getScreenInfo(screenW,screenH);
    
    vector<ofRectangle>  _tempScreens;
    for(NSString *s in screensINFO){
        NSRect nsr = NSRectFromString(s);
        ofRectangle _r = ofRectangle(nsr.origin.x,nsr.origin.y,nsr.size.width,nsr.size.height);
        _tempScreens.push_back(_r);
    }
    gapp->getScreensData(_tempScreens);
}

//------------------------------------------------------------------------------
- (void) sendDataToPreferences{
    unsigned i = 0;
    NSString        *_tempDev;
    int             _tI;
    
    // AUDIO IN DEVICES
    [prefPanel.audioInDevices removeItemAtIndex:0];
    for(i;i<aInD.size();i++){
        _tempDev = [NSString stringWithCString:aInD[i].c_str() encoding:[NSString defaultCStringEncoding]];
        _tI = aInDID[i];
        [prefPanel.audioInDevices addItemWithTitle:_tempDev];
        [[prefPanel.audioInDevices itemAtIndex:i] setTag:_tI];
    }
    
    // AUDIO OUT DEVICES
    i = 0;
    [prefPanel.audioOutDevices removeItemAtIndex:0];
    for(i;i<aOutD.size();i++){
        _tempDev = [NSString stringWithCString:aOutD[i].c_str() encoding:[NSString defaultCStringEncoding]];
        _tI = aOutDID[i];
        [prefPanel.audioOutDevices addItemWithTitle:_tempDev];
        [[prefPanel.audioOutDevices itemAtIndex:i] setTag:_tI];
    }
    
    prefPanel.aInCh = [[NSMutableArray alloc] initWithCapacity:aInputCH.size()];
    i = 0;
    for(i;i<aInputCH.size();i++){
        _tempDev = [NSString stringWithCString:aInputCH[i].c_str() encoding:[NSString defaultCStringEncoding]];
        [prefPanel.aInCh addObject:_tempDev];
    }
    
    prefPanel.aOutCh = [[NSMutableArray alloc] initWithCapacity:aOutputCH.size()];
    i = 0;
    for(i;i<aOutputCH.size();i++){
        _tempDev = [NSString stringWithCString:aOutputCH[i].c_str() encoding:[NSString defaultCStringEncoding]];
        [prefPanel.aOutCh addObject:_tempDev];
    }
    
    // MIDI DEVICES
    i = 0;
    [prefPanel.midiDevices removeItemAtIndex:0];
    for(i;i<mD.size();i++){
        _tempDev = [NSString stringWithCString:mD[i].c_str() encoding:[NSString defaultCStringEncoding]];
        [prefPanel.midiDevices addItemWithTitle:_tempDev];
        [[prefPanel.midiDevices itemAtIndex:i] setTag:i];
    }
    
    // SERIAL DEVICES
    i = 0;
    [prefPanel.serialDevices removeItemAtIndex:0];
    for(i;i<sD.size();i++){
        _tempDev = [NSString stringWithCString:sD[i].c_str() encoding:[NSString defaultCStringEncoding]];
        [prefPanel.serialDevices addItemWithTitle:_tempDev];
        [[prefPanel.serialDevices itemAtIndex:i] setTag:i];
    }
    
}

//------------------------------------------------------------------------------
- (NSString*) runCommand:(NSString *)commandToRun{
    // NSString *output = runCommand(@"ps -A | grep mysql");
    NSTask *task;
    task = [[NSTask alloc] init];
    [task setLaunchPath: @"/bin/sh"];
    
    NSArray *arguments = [NSArray arrayWithObjects:
                          @"-c" ,
                          [NSString stringWithFormat:@"%@", commandToRun],
                          NULL];
    NSLog(@"run command: %@",commandToRun);
    [task setArguments: arguments];
    
    NSPipe *pipe;
    pipe = [NSPipe pipe];
    [task setStandardOutput: pipe];
    
    NSFileHandle *file;
    file = [pipe fileHandleForReading];
    
    [task launch];
    
    NSData *data;
    data = [file readDataToEndOfFile];
    
    NSString *output;
    output = [[NSString alloc] initWithData: data encoding: NSUTF8StringEncoding];
    return output;
}

//------------------------------------------------------------------------------
- (NSXMLNode *)childNamed:(NSString *)name fromNode:(NSXMLNode *)fNode{
    NSEnumerator *e = [[fNode children] objectEnumerator];
    
    NSXMLNode *node;
    while (node = [e nextObject])
        if ([[node name] isEqualToString:name])
            return node;
    
    return NULL;
}

//------------------------------------------------------------------------------
- (void)sendGALog:(NSString *)msg{
    
    NSDictionary *attrs = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor colorWithDeviceRed:1 green:1 blue:1 alpha:1.0], NSForegroundColorAttributeName, [NSFont userFixedPitchFontOfSize:10], NSFontAttributeName, NULL];
    NSTextStorage *storage = [logger textStorage];
    
    NSDateFormatter *formatter;
    NSString        *dateString;
    
    formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"dd-MM-yyyy HH:mm:ss "];
    dateString = [formatter stringFromDate:[NSDate date]];
    [formatter release];
    
    NSString *wrapped = [NSString stringWithFormat:@"%@ %@\n", dateString, msg];
    NSAttributedString *attrStr = [[NSAttributedString alloc] initWithString:wrapped attributes:attrs];
    
    [logger setEditable:YES];
    [storage beginEditing];
    [storage appendAttributedString:attrStr];
    
    [storage endEditing];
    [attrStr release];
    [logger setEditable:NO];
    
    unsigned long len = [storage length];
    
    if (len > 0)
        [logger scrollRangeToVisible:NSMakeRange(len - 1, 1)];
}


// -----------------------------------------------------------------------------
//	Menu Actions
// -----------------------------------------------------------------------------
- (IBAction) getColorCorrection:(id)sender{
    NSXMLDocument *xmlDoc;
    NSArray* itemArray;
    NSString *path = [[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/settings/gamuzaSettings.xml"];
    NSURL *furl = [NSURL fileURLWithPath:path];
    if (!furl) {
        NSLog(@"Can't create an URL from file gamuzaSettings.xml.");
        return;
    }
    xmlDoc = [[NSXMLDocument alloc] initWithContentsOfURL:furl
                                                  options:(NSXMLNodePreserveWhitespace|NSXMLNodePreserveCDATA)
                                                    error:NULL];
    if (xmlDoc == NULL) {
        xmlDoc = [[NSXMLDocument alloc] initWithContentsOfURL:furl
                                                      options:NSXMLDocumentTidyXML
                                                        error:NULL];
    }
    
    NSXMLElement* root  = [xmlDoc rootElement];
    
    itemArray = [root nodesForXPath:@"//gamma_correction" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [gammaS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    itemArray = [root nodesForXPath:@"//brightness" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [brightS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    itemArray = [root nodesForXPath:@"//saturation" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [satS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    itemArray = [root nodesForXPath:@"//contrast" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [contrS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    itemArray = [root nodesForXPath:@"//film_bleach" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [filmBS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    itemArray = [root nodesForXPath:@"//technicolor" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [techS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    itemArray = [root nodesForXPath:@"//force_bw" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [whiteDS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    itemArray = [root nodesForXPath:@"//white_exposure" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [exposS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    itemArray = [root nodesForXPath:@"//white_diffusion" error:NULL];
    for(NSXMLElement* xmlElement in itemArray){
        [diffS setFloatValue:[[xmlElement stringValue] floatValue]];
    }
    
    [xmlDoc release];
    
    [colorCorrectionPanel makeKeyAndOrderFront:NULL];
    
    [self applyColorCorrection:NULL];
    
}

- (IBAction) saveColorCorrection:(id)sender{
    NSXMLDocument   *xmlDoc;
    NSData          *data;
    NSArray         *itemArray;
    NSXMLNode       *node;
    
    NSString *path = [[[NSBundle mainBundle] resourcePath] stringByAppendingString:@"/settings/gamuzaSettings.xml"];
    NSURL *furl = [NSURL fileURLWithPath:path];
    
    if (!furl) {
        NSLog(@"Can't create an URL from file gamuzaSettings.xml.");
        return;
    }
    xmlDoc = [[NSXMLDocument alloc] initWithContentsOfURL:furl
                                                  options:(NSXMLNodePreserveWhitespace|NSXMLNodePreserveCDATA)
                                                    error:NULL];
    if (xmlDoc == NULL) {
        xmlDoc = [[NSXMLDocument alloc] initWithContentsOfURL:furl
                                                      options:NSXMLDocumentTidyXML
                                                        error:NULL];
    }
    
    NSXMLNode *rootNode = [xmlDoc rootElement];
	
    //////////////////////////////////////////////////////////////////////
    // SAVE DATA
    node = [self childNamed:@"gamma_correction" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[gammaS stringValue]]];
    
    node = [self childNamed:@"brightness" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[brightS stringValue]]];
    
    node = [self childNamed:@"saturation" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[satS stringValue]]];
    
    node = [self childNamed:@"contrast" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[contrS stringValue]]];
    
    node = [self childNamed:@"film_bleach" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[filmBS stringValue]]];
    
    node = [self childNamed:@"technicolor" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[techS stringValue]]];
    
    node = [self childNamed:@"force_bw" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[whiteDS stringValue]]];
    
    node = [self childNamed:@"white_exposure" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[exposS stringValue]]];
    
    node = [self childNamed:@"white_diffusion" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[diffS stringValue]]];
    
    
    // WRITE TO XML
    data = [xmlDoc XMLData];
    [data writeToURL:furl atomically:YES];
    
    [xmlDoc release];
    
    [colorCorrectionPanel orderOut:NULL];
}

- (IBAction) resetColorCorrection:(id)sender{
    [gammaS setFloatValue:1.0];
    [brightS setFloatValue:1.0];
    [satS setFloatValue:1.0];
    [contrS setFloatValue:1.0];
    [filmBS setFloatValue:0.0];
    [techS setFloatValue:0.0];
    [whiteDS setFloatValue:0.0];
    [exposS setFloatValue:0.0];
    [diffS setFloatValue:0.0];
    
    gapp->setColorCorrection([gammaS floatValue],[brightS floatValue],[satS floatValue],[contrS floatValue],[filmBS floatValue],[techS floatValue],[whiteDS floatValue],[exposS floatValue],[diffS floatValue]);
}

- (IBAction) applyColorCorrection:(id)sender{
    gapp->setColorCorrection([gammaS floatValue],[brightS floatValue],[satS floatValue],[contrS floatValue],[filmBS floatValue],[techS floatValue],[whiteDS floatValue],[exposS floatValue],[diffS floatValue]);
}

- (IBAction) applyPreferences:(id)sender{
    [prefPanel saveDataToXml];
    gapp->resetApp();
    gappWindow->setWindowTitle(gapp->_windowTitle);
    gaVP->setFboDim(gapp->projectionScreenW,gapp->projectionScreenH);
    [prefPanel.mainPanel orderOut:NULL];
}

-(IBAction) toggleTimelinePanel:(id)sender{
    if(isTimelineON){
        isTimelineON = false;
        [gaTLWindow->getWindow() orderOut:self];
        [sender setState: NSOffState];
    }else{
        isTimelineON = true;
        [gaTLWindow->getWindow() makeKeyAndOrderFront:self];
        [sender setState: NSOnState];
    }
}

-(IBAction) togglePreviewWindow:(id)sender{
    if(isPreviewON){
        isPreviewON = false;
        [gaVPWindow->getWindow() orderOut:self];
        [sender setState: NSOffState];
    }else{
        isPreviewON = true;
        [gaVPWindow->getWindow() makeKeyAndOrderFront:self];
        [sender setState: NSOnState];
    }
}

-(IBAction) setPreviewDimensions:(id)sender{
    NSMenu      *syntaxMenu = [sender menu];
    NSMenuItem  *currItem = sender;
	double		currItemNum = 0;
	
	while(currItemNum < [syntaxMenu numberOfItems]){
        currItem = [syntaxMenu itemAtIndex:currItemNum];
		[currItem setState: NSOffState];
        currItemNum++;
	}
    
    switch ([sender tag]) {
        case 0:
            gaVP->setPreviewDim(320,240);
            gaVPWindow->setWindowShape(320,240);
            gaVPWindow->setWindowPosition(screenW-330,screenH-30);
            [sender setState: NSOnState];
            break;
            
        case 1:
            gaVP->setPreviewDim(640,360);
            gaVPWindow->setWindowShape(640,360);
            gaVPWindow->setWindowPosition(screenW-650,screenH-30);
            [sender setState: NSOnState];
            break;
            
        case 2:
            gaVP->setPreviewDim(640,480);
            gaVPWindow->setWindowShape(640,480);
            gaVPWindow->setWindowPosition(screenW-650,screenH-30);
            [sender setState: NSOnState];
            break;
            
        case 3:
            gaVP->setPreviewDim(800,600);
            gaVPWindow->setWindowShape(800,600);
            gaVPWindow->setWindowPosition(screenW-810,screenH-30);
            [sender setState: NSOnState];
            break;
            
        case 4:
            gaVP->setPreviewDim(854,480);
            gaVPWindow->setWindowShape(854,480);
            gaVPWindow->setWindowPosition(screenW-864,screenH-30);
            [sender setState: NSOnState];
            break;
            
        default:
            break;
    }
}

-(IBAction) openOFReference:(id)sender{
    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://www.openframeworks.cc/documentation/"]];
}

-(IBAction) openOfxAddonsPage:(id)sender{
    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://ofxaddons.com/"]];
}

-(IBAction) showGettingStartedPage:(id)sender {
    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://gamuza.d3cod3.org/downloads/manual/GAmuza_HLC_MA_Introduction.pdf"]];
}

-(IBAction) gotoGAWeb: (id)sender{
    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://gamuza.d3cod3.org/"]];
}


-(IBAction) openOnlineReference: (id)sender{
    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:@"http://gamuza.d3cod3.org/reference"]];
}

-(IBAction) openItemFromGAmuzaFolder: (id)sender{
	// open file from Examples menu items
    NSString * tvarFilename = [NSString stringWithFormat:@"%@%@", @"file:", [GAExampleFiles objectAtIndex:[sender tag]]];
    NSURL *url = [NSURL URLWithString:tvarFilename];
    
    [[NSDocumentController sharedDocumentController] openDocumentWithContentsOfURL:url display:YES error:NULL];
    
    GAMultiTextDocument * currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    NSString* directoryName = [[[[[currentDoc fileURL] absoluteString] stringByDeletingPathExtension] substringFromIndex:5] stringByDeletingLastPathComponent];
    
    // add sketch files (if we have)
    NSArray                 *contents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:directoryName error:NULL];
    NSEnumerator            *enm = [contents objectEnumerator];
    NSString                *importFile;
    NSString                *mainFile = [[[currentDoc fileURL] absoluteString] lastPathComponent];
    
    while ((importFile = [enm nextObject])){
        // eliminate from listing hidden files and .DS_Store files
        if([importFile hasPrefix:@"."] || [importFile rangeOfString:@".DS_Store"].location != NSNotFound){
            continue;
        }
        if ([[importFile pathExtension] isEqualToString:@"ga"] && [importFile isEqualToString:mainFile] == NO){
            NSString *actualFilePath = [NSString stringWithFormat:@"%@/%@", directoryName, importFile];
            NSString *fileContent = [[NSString alloc] initWithContentsOfFile:actualFilePath encoding:NSUTF8StringEncoding error:NULL];
            if (fileContent != NULL) {
                GASketchFile* doc = [[GASketchFile alloc] init];
                [currentDoc addDocument:doc withName:[importFile stringByDeletingPathExtension] andCode:fileContent];
            }
        }
    }
}

-(IBAction) openItemFromSketchbookFolder: (id)sender{
	// open file from Sketchbook menu items
    NSString * tvarFilename = [NSString stringWithFormat:@"%@%@", @"file:", [GASketchbookFiles objectAtIndex:[sender tag]]];
    NSURL *url = [NSURL URLWithString:tvarFilename];
    
    [[NSDocumentController sharedDocumentController] openDocumentWithContentsOfURL:url display:YES error:NULL];
    
    GAMultiTextDocument * currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    NSString* directoryName = [[[[[currentDoc fileURL] absoluteString] stringByDeletingPathExtension] substringFromIndex:5] stringByDeletingLastPathComponent];
    
    // add sketch files (if we have)
    NSArray                 *contents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:directoryName error:NULL];
    NSEnumerator            *enm = [contents objectEnumerator];
    NSString                *importFile;
    NSString                *mainFile = [[[currentDoc fileURL] absoluteString] lastPathComponent];
    
    while ((importFile = [enm nextObject])){
        // eliminate from listing hidden files and .DS_Store files
        if([importFile hasPrefix:@"."] || [importFile rangeOfString:@".DS_Store"].location != NSNotFound){
            continue;
        }
        if ([[importFile pathExtension] isEqualToString:@"ga"] && [importFile isEqualToString:mainFile] == NO){
            NSString *actualFilePath = [NSString stringWithFormat:@"%@/%@", directoryName, importFile];
            NSString *fileContent = [[NSString alloc] initWithContentsOfFile:actualFilePath encoding:NSUTF8StringEncoding error:NULL];
            if (fileContent != NULL) {
                GASketchFile* doc = [[GASketchFile alloc] init];
                [currentDoc addDocument:doc withName:[importFile stringByDeletingPathExtension] andCode:fileContent];
            }
        }
    }
}

-(IBAction) restartGAmuzaWindow: (id)sender{
    gapp->resetApp();
    gappWindow->setWindowTitle(gapp->_windowTitle);
}

-(IBAction) sendScriptToGAmuza: (id)sender{
    GAMultiTextDocument * currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    
    // send source code to LUA engine
    NSString* _temp = [currentDoc sendToGAmuza];
    NSString * _sUrl = [[currentDoc fileURL] path];

    if(_sUrl != NULL){
        string _path = [_sUrl UTF8String];
        gapp->setScriptPath(_path);
    }
    
    string text = [_temp UTF8String];
    gapp->receiveScript(text);
	
    
    // save file if isn't
    [currentDoc saveGAAll:sender];
}

-(IBAction) cleanScriptToGAmuza: (id)sender{
	string text = "function draw() gaBackground(0.0,1.0) end";
	gapp->receiveScript(text);
}

-(IBAction) toggleGAmuzaFullscreen: (id)sender{
    gappWindow->toggleFullscreen();
	gapp->gamuzaFullscreen();
}

///////////////////////////////////////////// MAPPING

-(IBAction) resetMapping: (id)sender{
	gapp->resetMappingPoints();
}

-(IBAction) loadMapping: (id)sender{
	gapp->loadMappingPoints();
}

-(IBAction) saveMapping: (id)sender{
	gapp->saveMappingPoints();
}

-(IBAction) drawMappingGrid:(id)sender{
    gapp->toggleDrawGrid();
}

- (IBAction) switchMouseKeyControl:(id)sender{
    if(gapp->switchMouseKeyControl()){
        [sender setTitle:@"Keyboard Control"];
    }else{
        [sender setTitle:@"Mouse Control"];
    }
}

- (IBAction) mappingManualEditON:(id)sender{
    gapp->manualPointEditON();
}

- (IBAction) mappingManualEditOFF:(id)sender{
    gapp->manualPointEditOFF();
}

- (IBAction) goToNorthMappingPoint:(id)sender{
    gapp->northMappingPoint();
}

- (IBAction) goToSouthMappingPoint:(id)sender{
    gapp->southMappingPoint();
}

- (IBAction) goToEastMappingPoint:(id)sender{
    gapp->eastMappingPoint();
}

- (IBAction) goToWestMappingPoint:(id)sender{
    gapp->westMappingPoint();
}

///////////////////////////////////////////// TIMELINE

- (IBAction) undoOnTimeline:(id)sender{
    if(isTimelineON){
        gaTL->undoTimeline();
    }
}

- (IBAction) redoOnTimeline:(id)sender{
    if(isTimelineON){
        gaTL->redoTimeline();
    }
}

- (IBAction) copyOnTimeline:(id)sender{
    if(isTimelineON){
        gaTL->copyTimeline();
    }
}

- (IBAction) cutOnTimeline:(id)sender{
    if(isTimelineON){
        gaTL->cutTimeline();
    }
}

- (IBAction) pasteOnTimeline:(id)sender{
    if(isTimelineON){
        gaTL->pasteTimeline();
    }
}


@end
