
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
- (BOOL)restoreWindowWithIdentifier:(NSString *)identifier state:(NSCoder *)state completionHandler:(void (^)(NSWindow *, NSError *))completionHandler{
    return NO;
}

//------------------------------------------------------------------------------
- (void)terminateSplashWindow:(NSTimer *)timer {
    [_splash orderOut:self];
    
    isMouseON           = true;
    isPreviewON         = false;
    isTimelineON        = false;
    isAudioModuleON     = false;
    isArduinoModuleON   = false;
    gaARM->setModuleON(true);
    [gappWindow->getWindow() makeKeyAndOrderFront:self];
    
    if(prefPanel._autoFullscreen == 1){
        [self getScreenXPosition:prefPanel._fullscreenScreen];
        gappWindow->setWindowPosition(fullscreenWinPosX,screenH-60);
        gappWindow->toggleFullscreen();
        gapp->gamuzaFullscreen(gappWindow->getActualScreen());
    }
    
}

//------------------------------------------------------------------------------
- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename{
    
    return [self processFile:filename];
}

//------------------------------------------------------------------------------
- (BOOL)processFile:(NSString *)file{
    // open arbitrary file
    NSString * tvarFilename = [NSString stringWithFormat:@"%@%@", @"file:", file];
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
    return YES;
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
    ofxNSWindower::instance()->addWindow(gaVP,"Preview", NSBorderlessWindowMask);
    gaVPWindow = ofxNSWindower::instance()->getWindowPtr("Preview");
    gaVPWindow->setWindowTitle("Preview");
    gaVPWindow->setWindowShape(320,240);
    gaVPWindow->setWindowPosition(screenW-330,screenH-30);
    [gaVPWindow->getWindow() orderOut:self];
    
    // START GAmuza TIMELINE Panel
    gaTL = new gaTimeline(screenW,screenH);
    ofxNSWindower::instance()->addWindow(gaTL,"Timeline", NSTitledWindowMask|NSResizableWindowMask,20);
    gaTLWindow = ofxNSWindower::instance()->getWindowPtr("Timeline");
    gaTLWindow->setWindowTitle("Timeline");
    gaTLWindow->setWindowShape(screenW,screenH-30);
    gaTLWindow->setWindowPosition(0,0);
    [gaTLWindow->getWindow() orderOut:self];
    
    
    // START GAmuza render window
    gapp = new gamuzaMain();
	ofxNSWindower::instance()->addWindow(gapp,"gamuza", NSBorderlessWindowMask);
    gappWindow = ofxNSWindower::instance()->getWindowPtr("gamuza");
    gappWindow->setWindowTitle(gapp->_windowTitle);
    gappWindow->setWindowPosition(screenW - MAIN_WINDOW_W,screenH - MAIN_WINDOW_H);
    [gappWindow->getWindow() orderOut:self];
    gaVP->setFboDim(gapp->projectionScreenW,gapp->projectionScreenH);
    [self sendScreenResToGA];
    gapp->sendHardwareInfo(aInD,aInDID,aOutD,aOutDID,mD,sD,aInputCH,aOutputCH);
    [self sendDataToPreferences];
    
    // START GAmuza Audio Analysis Module
    gaAM = new gaAudioModule(810,470);
    ofxNSWindower::instance()->addWindow(gaAM,"GA Audio Analysis", NSTitledWindowMask,20);
    gaAMWindow = ofxNSWindower::instance()->getWindowPtr("GA Audio Analysis");
    gaAMWindow->setWindowTitle("GA Audio Analysis");
    [gaAMWindow->getWindow() orderOut:self];
    
    // START GAmuza Arduino Module
    gaARM = new gaArduinoModule(1260,720);
    ofxNSWindower::instance()->addWindow(gaARM,"GA Arduino", NSTitledWindowMask,20);
    gaARMWindow = ofxNSWindower::instance()->getWindowPtr("GA Arduino");
    gaARMWindow->setWindowTitle("GA Arduino");
    [gaARMWindow->getWindow() orderOut:self];
    
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
    
    // Remove all old menu items from our menu:
    /*NSMenuItem          *foundItem  = [[NSApp mainMenu] findItemWithTarget:NULL andAction:@selector(openItemFromSketchbookFolder:)];
	NSMenuItem          *currMItem = foundItem;
    NSMenu              *syntaxMenu = [foundItem menu];
	double				currItemNum = [syntaxMenu indexOfItem: currMItem];
    NSMenuItem          *thisFile   = NULL;
	
	while( [currMItem action] == @selector(openItemFromSketchbookFolder:)){
		[syntaxMenu removeItem: currMItem];
		if( currItemNum < [syntaxMenu numberOfItems] )
			currMItem = [syntaxMenu itemAtIndex: currItemNum];
		else
			break;
	}
    
    // Populate Examples menu
    int x = 0;
    NSFileManager *fileManager = [[[NSFileManager alloc] init] autorelease];
    NSURL *directoryURL = [NSURL URLWithString:path];
    NSArray *keys = [NSArray arrayWithObject:NSURLIsDirectoryKey];
    NSDirectoryEnumerator *enumerator = [fileManager enumeratorAtURL:directoryURL includingPropertiesForKeys:keys options:0 errorHandler:NULL];
    
    for (NSURL *url in enumerator) {
        NSString *actualPath = [[url absoluteString] substringFromIndex:16];
        NSString *mainSketch = [actualPath lastPathComponent];
        NSString *sketchFolder = [[actualPath stringByDeletingLastPathComponent] lastPathComponent];
        if([[mainSketch stringByDeletingPathExtension] isEqualToString:sketchFolder]){
            NSLog(@"%@ - %@",actualPath,mainSketch);
            [GASketchbookFiles addObject:actualPath];
            
            thisFile = [[NSMenuItem alloc] initWithTitle:sketchFolder action:@selector(openItemFromSketchbookFolder:) keyEquivalent:@""];
            [thisFile setRepresentedObject:actualPath];
            [thisFile setTag:x];
            [syntaxMenu addItem:thisFile];
            
        }
        x++;
    }*/
    
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
-(IBAction) archiveSketch:(id)sender{
    GAMultiTextDocument *currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    NSString* directoryName = @"";
    if([[[currentDoc fileURL] absoluteString] rangeOfString:@"localhost"].location != NSNotFound){
        directoryName = [[[[[currentDoc fileURL] absoluteString] stringByDeletingPathExtension] substringFromIndex:15] stringByDeletingLastPathComponent];
    }else{
        directoryName = [[[[[currentDoc fileURL] absoluteString] stringByDeletingPathExtension] substringFromIndex:5] stringByDeletingLastPathComponent];
    }
    
    NSString* sketchName = [[[[currentDoc fileURL] absoluteString] lastPathComponent] stringByDeletingPathExtension];
    
    if(currentDoc != NULL){
        // Custom Save Panel
        NSSavePanel                 *sPan;
        
        sPan = [NSSavePanel savePanel];
        [sPan setTitle:@"Archive GAmuza Sketch As"];
        [sPan setDirectoryURL:[NSURL fileURLWithPath:directoryName]];
        [sPan setAllowsOtherFileTypes:NO];
        [sPan setCanCreateDirectories:NO];
        
        long tvar = [sPan runModalForDirectory:sketchName file:sketchName];
        
        if(tvar == NSOKButton){
            NSFileManager *fileManager = [[[NSFileManager alloc] init] autorelease];
            NSURL *directoryURL = [NSURL URLWithString:directoryName];
            NSArray *keys = [NSArray arrayWithObject:NSURLIsDirectoryKey];
            NSDirectoryEnumerator *enumerator = [fileManager
                                                 enumeratorAtURL:directoryURL
                                                 includingPropertiesForKeys:keys
                                                 options:0
                                                 errorHandler:NULL];
            
            NSString *stringPath = [[sPan filename] stringByAppendingFormat:@".zip"];
            ZipFile *zipFile = [[ZipFile alloc]initWithFileName:stringPath mode:ZipFileModeCreate];
        
            for (NSURL *url in enumerator) {
                NSNumber    *isDirectory = NULL;
                NSString    *_actualFile = [[url absoluteString] lastPathComponent];
                
                [url getResourceValue:&isDirectory forKey:NSURLIsDirectoryKey error:NULL];
                
                if([_actualFile hasPrefix:@"."] || [_actualFile rangeOfString:@".DS_Store"].location != NSNotFound){
                    continue;
                }
                
                if(![isDirectory boolValue]){
                    NSString* tempPath = [NSString stringWithFormat:@"file://localhost%@/", [[directoryURL absoluteString] stringByDeletingLastPathComponent]];
                    NSString *difference = [[[url absoluteString] substringFromIndex:tempPath.length] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
                    
                    NSString* zipElement = [[NSString stringWithFormat:@"/%@",difference] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
                    
                    NSLog(@"%@",difference);
                    
                    id elem = difference;                    
                    NSString *path = [[directoryName stringByDeletingLastPathComponent] stringByAppendingString:zipElement];
                    
                    NSDictionary *attributes = [fileManager attributesOfItemAtPath:path error:NULL];
                    NSDate *Date = [attributes objectForKey:NSFileCreationDate];
                    
                    ZipWriteStream *stream = [zipFile writeFileInZipWithName:elem fileDate:Date compressionLevel:ZipCompressionLevelDefault];
                    NSData *data = [NSData dataWithContentsOfFile:path];
                    [stream writeData:data];
                    [stream finishedWriting];
                }
            }
            [zipFile close];
            
        }else{
            return;
        }
    }
}

-(IBAction) exportSketchToHTML:(id)sender{
    
    [self sendScriptToGAmuza:NULL];
    
    GAMultiTextDocument *currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    NSString* _tempCode = [currentDoc sendToGAmuza];
    NSString* sketchName = [[[[currentDoc fileURL] absoluteString] lastPathComponent] stringByDeletingPathExtension];
    NSString* directoryName = @"";
    if([[[currentDoc fileURL] absoluteString] rangeOfString:@"localhost"].location != NSNotFound){
        directoryName = [[[[[currentDoc fileURL] absoluteString] stringByDeletingPathExtension] substringFromIndex:15] stringByDeletingLastPathComponent];
    }else{
        directoryName = [[[[[currentDoc fileURL] absoluteString] stringByDeletingPathExtension] substringFromIndex:5] stringByDeletingLastPathComponent];
    }
    NSString* finalFilePath = @"";
    
    if(currentDoc != NULL){
        
        // Custom Save Panel
        NSSavePanel                 *sPan;
        
        sPan = [NSSavePanel savePanel];
        [sPan setTitle:@"Export GAmuza Sketch to HTML"];
        [sPan setDirectoryURL:[NSURL fileURLWithPath:directoryName]];
        [sPan setAllowsOtherFileTypes:NO];
        [sPan setCanCreateDirectories:NO];
        
        long tvar = [sPan runModalForDirectory:sketchName file:sketchName];
        
        if(tvar == NSOKButton){
            
            // extract header comment for description
            NSRange rr2 = [_tempCode rangeOfString:@"/*"];
            NSRange rr3 = [_tempCode rangeOfString:@"*/"];
            int lengt = rr3.location - rr2.location - rr2.length;
            int location = rr2.location + rr2.length;
            NSRange aa;
            aa.location = location;
            aa.length = lengt;
            _tempCode = [_tempCode substringWithRange:aa];
            NSArray *headerCodeLinesNm = [_tempCode componentsSeparatedByString:@"\n"];
            
            // create documentation directories
            NSString* docDirectory = [NSString stringWithFormat:@"%@", [sPan filename]];
            [filemgr createDirectoryAtPath:docDirectory withIntermediateDirectories:YES attributes: NULL error:NULL];
            docDirectory = [NSString stringWithFormat:@"%@/img", [sPan filename]];
            [filemgr createDirectoryAtPath:docDirectory withIntermediateDirectories:YES attributes: NULL error:NULL];
            
            // capture one jpg from sketch output window
            ofImage             _img;
            ofPixels 			_pix;
            ofTexture           _tex = gapp->gamuzaFbo.getTextureReference();
            _tex.readToPixels(_pix);
            _img.setFromPixels(_pix);
            
            // save jpg inside img/ folder
            NSString* _imageUrl = [NSString stringWithFormat:@"%@/img/frame0.jpg", [sPan filename]];
            string _name = [_imageUrl UTF8String];
            _img.saveImage(_name.c_str());
            
            //compose html file
            NSMutableString *htmlText = [[NSMutableString alloc] init];
            [htmlText appendFormat: @"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"];
            [htmlText appendFormat: @"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"];
            [htmlText appendFormat: @"\t<head>\n"];
            [htmlText appendFormat: @"\t\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\n"];
            NSString* temp_skName = [NSString stringWithFormat:@"\t\t<title>%@ | GAmuza 1.0 sketch documentation</title>\n",sketchName];
            [htmlText appendFormat: temp_skName];
            [htmlText appendFormat: @"\t\t<style type=\"text/css\">\n"];
            [htmlText appendFormat: @"\t\t\tbody{ \n"];
            [htmlText appendFormat: @"\t\t\t\tbackground-color:#FFFFFF;\n"];
            [htmlText appendFormat: @"\t\t\t\tfont-family: Helvetica, Arial;\n"];
            [htmlText appendFormat: @"\t\t\t\tfont-size: 11px;\n"];
            [htmlText appendFormat: @"\t\t\t\tcolor: #111;\n"];
            [htmlText appendFormat: @"\t\t\t\t-webkit-font-smoothing: antialiased;\n"];
            [htmlText appendFormat: @"\t\t\t}\n"];
            [htmlText appendFormat: @"\t\t\ta{color:#ee3987;}\n"];
            [htmlText appendFormat: @"\t\t\ta:link{color:#ee3987; text-decoration:underline;}\n"];
            [htmlText appendFormat: @"\t\t\ta:visited{color:#ee3987; text-decoration:underline;}\n"];
            [htmlText appendFormat: @"\t\t\ta:active{color:#ee3987; text-decoration:underline;}\n"];
            [htmlText appendFormat: @"\t\t\ta:hover{color:#ee3987; text-decoration:underline;}\n"];
            [htmlText appendFormat: @"\t\t\t.mainContent{\n"];
            [htmlText appendFormat: @"\t\t\t\tbackground: url(\"img/frame0.jpg\") transparent;\n"];
            [htmlText appendFormat: @"\t\t\t\topacity: 0.18;\n"];
            [htmlText appendFormat: @"\t\t\t\tfilter: alpha(opacity = 18);\n"];
            [htmlText appendFormat: @"\t\t\t\tbottom: 0;\n"];
            [htmlText appendFormat: @"\t\t\t\tleft: 0;\n"];
            [htmlText appendFormat: @"\t\t\t\tposition: absolute;\n"];
            [htmlText appendFormat: @"\t\t\t\tright: 0;\n"];
            [htmlText appendFormat: @"\t\t\t\ttop: 0;\n"];
            [htmlText appendFormat: @"\t\t\t\tz-index: 0;\n"];
            [htmlText appendFormat: @"\t\t\t\tbackground-repeat: repeat;\n"];
            [htmlText appendFormat: @"\t\t\t\tbackground-size: cover;\n"];
            [htmlText appendFormat: @"\t\t\t\t-o-background-size: cover;\n"];
            [htmlText appendFormat: @"\t\t\t\t-webkit-background-size: cover;\n"];
            [htmlText appendFormat: @"\t\t\t}\n"];
            [htmlText appendFormat: @"\t\t</style>\n"];
            [htmlText appendFormat: @"\n"];
            [htmlText appendFormat: @"\t</head>\n"];
            [htmlText appendFormat: @"\n"];
            [htmlText appendFormat: @"<body>\n"];
            [htmlText appendFormat: @"\t<div class=\"mainContent\"></div>\n"];
            [htmlText appendFormat: @"\t<div>\n"];
            temp_skName = [NSString stringWithFormat:@"\t\t<span style=\"font-size:28px;position:absolute;left:66px;top:10px;\"><p>%@</p></span>\n",sketchName];
            [htmlText appendFormat: temp_skName];
            [htmlText appendFormat: @"\t</div>\n"];
            [htmlText appendFormat: @"\t<div class=\"header_comment\">\n"];
            [htmlText appendFormat: @"\t\t<span style=\"color:#666;font-size:13px;font-style:italic;position:absolute;left:66px;top:50px;\"><p>\n"];
            
            for(int i=0;i<headerCodeLinesNm.count;i++){
                [htmlText appendFormat:[NSString stringWithFormat:@"%@<br \\>", [headerCodeLinesNm objectAtIndex:i]]];
            }
            int _topSlide = headerCodeLinesNm.count*14;
            
            [htmlText appendFormat: @"\t\t</p></span>\n"];
            [htmlText appendFormat: @"\t</div>\n"];
            [htmlText appendFormat: @"\t<div>\n"];
            
            _topSlide += 70;
            int _exportWidth = gapp->projectionScreenW*360 / gapp->projectionScreenH;
            temp_skName = [NSString stringWithFormat:@"\t\t<span style=\"position:absolute;top:%ipx;left:66px;\"><p><img src=\"img/frame0.jpg\" width=\"%i\" height=\"360\"/></p></span>\n",_topSlide,_exportWidth];
            [htmlText appendFormat:temp_skName];
            [htmlText appendFormat: @"\t</div>\n"];
            [htmlText appendFormat: @"\t<div>\n"];
            
            _topSlide += 370;
            temp_skName = [NSString stringWithFormat:@"\t\t<span style=\"position:absolute;left:26px;top:%ipx;\"><p><ul>\n",_topSlide];
            [htmlText appendFormat:temp_skName];
            [htmlText appendFormat: @"\t\t\tSource Code: \n"];
            temp_skName = [NSString stringWithFormat:@"\t\t\t<li style=\"display:inline;list-style-type:none;padding-right:20px;\"><a href=\"%@.ga\">%@</a></li>\n",sketchName,sketchName];
            [htmlText appendFormat: temp_skName];
            
            // save all the sketch files to main folder
            [[NSFileManager defaultManager] copyItemAtURL:[currentDoc fileURL] toURL:[NSURL URLWithString:[NSString stringWithFormat:@"file://localhost%@/%@.ga", [sPan filename],sketchName]] error:NULL];
            NSArray * sketchFiles = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:directoryName error:NULL];
            if(sketchFiles){
                for(int index=0;index<sketchFiles.count;index++){
                    NSString * file = [sketchFiles objectAtIndex:index];
                    if( [[file pathExtension] compare: @"ga"] == NSOrderedSame && [[file stringByDeletingPathExtension]  compare:sketchName] != NSOrderedSame){
                        [[NSFileManager defaultManager] copyItemAtURL:[NSURL URLWithString:[NSString stringWithFormat:@"file://localhost%@/%@",directoryName,file]] toURL:[NSURL URLWithString:[NSString stringWithFormat:@"file://localhost%@/%@", [sPan filename],file]] error:NULL];
                        temp_skName = [NSString stringWithFormat:@"\t\t\t<li style=\"display:inline;list-style-type:none;padding-right:20px;\"><a href=\"%@\">%@</a></li>\n",file,[file stringByDeletingPathExtension]];
                        [htmlText appendFormat: temp_skName];
                    }
                }
            }
            
            [htmlText appendFormat: @"\t\t</ul></p></span>\n"];
            [htmlText appendFormat: @"\t</div>\n"];
            [htmlText appendFormat: @"\t<div>\n"];
            
            _topSlide += 40;
            temp_skName = [NSString stringWithFormat:@"\t\t<span style=\"position:absolute;left:66px;top:%ipx;\"><p>\n",_topSlide];
            [htmlText appendFormat:temp_skName];
            temp_skName = [NSString stringWithFormat:@"\t\t\tBuilt with <a href=\"http://www.gamuza.cc\" title=\"GAmuza\">GAmuza 1.0 Rel. %@</a>\n",[NSString stringWithCString:GAMUZA_RELEASE encoding:[NSString defaultCStringEncoding]]];
            [htmlText appendFormat:temp_skName];
            [htmlText appendFormat: @"\t\t</p></span>\n"];
            [htmlText appendFormat: @"\t</div>\n"];
            [htmlText appendFormat: @"</body>\n"];
            [htmlText appendFormat: @"</html>"];
            
            // create & save the html file
            finalFilePath = [[NSString stringWithFormat:@"%@/index", [sPan filename]] stringByAppendingFormat:@".html"];
            [htmlText writeToFile:finalFilePath atomically:YES encoding: NSUTF8StringEncoding error:NULL];
            
        }else{
            return;
        }
    }
    
    [self cleanScriptToGAmuza:NULL];
    
    [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"file://localhost%@", finalFilePath]]];
    
}

-(IBAction) getColorCorrection:(id)sender{
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

-(IBAction) saveColorCorrection:(id)sender{
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

-(IBAction) resetColorCorrection:(id)sender{
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

-(IBAction) applyColorCorrection:(id)sender{
    gapp->setColorCorrection([gammaS floatValue],[brightS floatValue],[satS floatValue],[contrS floatValue],[filmBS floatValue],[techS floatValue],[whiteDS floatValue],[exposS floatValue],[diffS floatValue]);
}

-(IBAction) applyPreferences:(id)sender{
    [prefPanel saveDataToXml];
    
    gapp->cleanMemory();
    gapp->resetApp();
    gappWindow->setWindowTitle(gapp->_windowTitle);
    
    gaAM->restart();
    gaARM->restart();
    
    gaVP->setFboDim(gapp->projectionScreenW,gapp->projectionScreenH);
    [self sendScreenResToGA];
    [prefPanel.mainPanel orderOut:NULL];
}

-(IBAction) hideAllModules:(id)sender{
    if(isArduinoModuleON){
        isArduinoModuleON = false;
        [gaARMWindow->getWindow() orderOut:self];
    }
    if(isAudioModuleON){
        isAudioModuleON = false;
        [gaAMWindow->getWindow() orderOut:self];
    }
    if(isTimelineON){
        isTimelineON = false;
        [gaTLWindow->getWindow() orderOut:self];
    }
    if(isPreviewON){
        isPreviewON = false;
        [gaVPWindow->getWindow() orderOut:self];
    }
}

-(IBAction) toggleArduinoModule:(id)sender{
    if(isArduinoModuleON){
        isArduinoModuleON = false;
        gaARM->setModuleON(false);
        [gaARMWindow->getWindow() orderOut:self];
        [sender setState: NSOffState];
    }else{
        isArduinoModuleON = true;
        gaARM->setModuleON(true);
        [gaARMWindow->getWindow() makeKeyAndOrderFront:self];
        [sender setState: NSOnState];
    }
}

-(IBAction) toggleAudioModule:(id)sender{
    if(isAudioModuleON){
        gaAM->setModuleON(false);
        isAudioModuleON = false;
        [gaAMWindow->getWindow() orderOut:self];
        [sender setState: NSOffState];
    }else{
        isAudioModuleON = true;
        gaAM->setModuleON(true);
        [gaAMWindow->getWindow() makeKeyAndOrderFront:self];
        [sender setState: NSOnState];
    }
}

-(IBAction) toggleTimelinePanel:(id)sender{
    if(isTimelineON){
        isTimelineON = false;
        gaTL->setModuleON(false);
        [gaTLWindow->getWindow() orderOut:self];
        [sender setState: NSOffState];
    }else{
        isTimelineON = true;
        gaTL->setModuleON(true);
        [gaTLWindow->getWindow() makeKeyAndOrderFront:self];
        [sender setState: NSOnState];
    }
}

-(IBAction) togglePreviewWindow:(id)sender{
    if(isPreviewON){
        isPreviewON = false;
        gaVP->setModuleON(false);
        [gaVPWindow->getWindow() orderOut:self];
        [sender setState: NSOffState];
    }else{
        isPreviewON = true;
        gaVP->setModuleON(true);
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
    
    GAMultiTextDocument * prevcurrentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    
    if(![[[prevcurrentDoc fileURL] absoluteString] isEqualToString:tvarFilename]){
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
}

-(IBAction) openItemFromSketchbookFolder: (id)sender{
	// open file from Sketchbook menu items
    NSString * tvarFilename = [NSString stringWithFormat:@"%@%@", @"file:", [GASketchbookFiles objectAtIndex:[sender tag]]];
    NSURL *url = [NSURL URLWithString:tvarFilename];
    
    GAMultiTextDocument * prevcurrentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    
    if(![[[prevcurrentDoc fileURL] absoluteString] isEqualToString:tvarFilename]){
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
}

-(IBAction) openGAMUZADocument:(id)sender{
    NSString        *sketchbookLocation = [@"~/Documents/GAmuza" stringByExpandingTildeInPath];
    
    // Custom Open Panel
    NSOpenPanel                 *oPan;
    oPan = [NSOpenPanel openPanel];
    [oPan setTitle:@"Open a GAmuza Sketch"];
    [oPan setDirectoryURL:[NSURL fileURLWithPath:sketchbookLocation]];
    [oPan setAllowsOtherFileTypes:NO];
    [oPan setCanCreateDirectories:NO];
    
    NSInteger tvarNSInteger	= [oPan runModalForTypes:NULL];
    
    if(tvarNSInteger == NSOKButton){
        NSString * tvarFilename = [NSString stringWithFormat:@"%@%@", @"file:", [oPan filename]];
        NSURL *url = [NSURL URLWithString:tvarFilename];
        
        GAMultiTextDocument * prevcurrentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
        
        if(![[[prevcurrentDoc fileURL] absoluteString] isEqualToString:tvarFilename]){
            // add GAmuza document
            [[NSDocumentController sharedDocumentController] openDocumentWithContentsOfURL:url display:YES error:NULL];
            
            NSString* directoryName = [[oPan directory] lastPathComponent];
            if ([ [[[oPan filename] lastPathComponent] stringByDeletingPathExtension] isEqualToString:directoryName]) {
                // add sketch files (if we have)
                NSArray                 *contents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[oPan directory] error:NULL];
                NSEnumerator            *enm = [contents objectEnumerator];
                NSString                *importFile;
                NSString                *mainFile = [[oPan filename] lastPathComponent];
                
                while ((importFile = [enm nextObject])){
                    // eliminate from listing hidden files and .DS_Store files
                    if([importFile hasPrefix:@"."] || [importFile rangeOfString:@".DS_Store"].location != NSNotFound){
                        continue;
                    }
                    if ([[importFile pathExtension] isEqualToString:@"ga"] && [importFile isEqualToString:mainFile] == NO){
                        NSString *actualFilePath = [NSString stringWithFormat:@"%@/%@", [oPan directory], importFile];
                        NSString *fileContent = [[NSString alloc] initWithContentsOfFile:actualFilePath encoding:NSUTF8StringEncoding error:NULL];
                        if (fileContent != NULL) {
                            GASketchFile* doc = [[GASketchFile alloc] init];
                            [[[NSDocumentController sharedDocumentController] currentDocument] addDocument:doc withName:[importFile stringByDeletingPathExtension] andCode:fileContent];
                        }
                    }
                }
            }
        }
        
    }else{
        return;
    }
}

-(IBAction) sendScriptToGAmuza: (id)sender{
    GAMultiTextDocument * currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    
    if(currentDoc != NULL){
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
        //[currentDoc saveGAAll:sender];
    }
}

-(IBAction) cleanScriptToGAmuza: (id)sender{
	string text = "function draw() gaBackground(0.0,1.0) end";
	gapp->receiveScript(text);
}

-(IBAction) toggleGAmuzaFullscreen: (id)sender{
    gappWindow->toggleFullscreen();
	gapp->gamuzaFullscreen(gappWindow->getActualScreen());
}

-(IBAction) toggleHideCursor:(id)sender{
    if(isMouseON){
        isMouseON = false;
        gappWindow->hideCursor();
    }else{
        isMouseON = true;
        gappWindow->showCursor();
    }
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
