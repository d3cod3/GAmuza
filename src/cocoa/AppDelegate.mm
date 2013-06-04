
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
    
    [self sendScreenResToGA];
    
    isPreviewON = false;
    [gappWindow->getWindow() makeKeyAndOrderFront:self];
    
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
    gaVPWindow->setWindowPosition(screenX-330,screenY-30);
    [gaVPWindow->getWindow() orderOut:self];
    
    // START GAmuza TIMELINE Panel
    gaTL = new gaTimeline(screenX,screenY);
    ofxNSWindower::instance()->addWindow(gaTL,"Timeline", NSTitledWindowMask|NSResizableWindowMask, 0);
    gaTLWindow = ofxNSWindower::instance()->getWindowPtr("Timeline");
    gaTLWindow->setWindowTitle("Timeline");
    gaTLWindow->setWindowShape(screenX,screenY-30);
    gaTLWindow->setWindowPosition(0,0);
    //[gaTLWindow->getWindow() setContentSize:NSMakeSize(800,400)];
    [gaTLWindow->getWindow() orderOut:self];
    
    
    // START GAmuza render window
    gapp = new gamuzaMain();
	ofxNSWindower::instance()->addWindow(gapp,"gamuza", NSTitledWindowMask, 0);
    gappWindow = ofxNSWindower::instance()->getWindowPtr("gamuza");
    gappWindow->setWindowTitle(gapp->_windowTitle);
    gappWindow->setWindowPosition(screenX - MAIN_WINDOW_W,screenY - MAIN_WINDOW_H);
    [gappWindow->getWindow() orderOut:self];
    gaVP->setFboDim(gapp->projectionScreenW,gapp->projectionScreenH);
    
    
    // Splash window
    [_splash makeKeyAndOrderFront:self];
    NSTimer *t = [NSTimer scheduledTimerWithTimeInterval:3.6
                                    target:self
                                    selector:@selector(terminateSplashWindow:)
                                    userInfo:NULL
                                    repeats:NO];
    
    applicationHasStarted = YES;
    
    NSString *tempRelease = [NSString stringWithFormat:@" GAmuza %@ | Hybrid Live OF Sketching IDE",[NSString stringWithCString:GAMUZA_RELEASE encoding:[NSString defaultCStringEncoding]]];
    [self sendGALog:tempRelease];
    [self sendGALog:@"----------------------------------------------------------"];
    [self sendGALog:@" "];
    [self sendGALog:@"   Powered  by OF           <http://www.openframeworks.cc>"];
    [self sendGALog:@"   Inspired by Processing   <http://www.processing.org>"];
    [self sendGALog:@" "];
    [self sendGALog:@"   Created  by Emanuele Mazza aka n3m3da"];
    [self sendGALog:@"----------------------------------------------------------"];
    [self sendGALog:@" "];
    
    [self sendGALog:@"GAmuza Started"];
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
    
    NSString *tempMessage = [NSString stringWithFormat:@"GAmuza Sketchbook directory: %@",documentsDirectory];
    [self sendGALog:@""];
    [self sendGALog:tempMessage];
    
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
- (void) screenResolution {
    
    NSRect screenRect;
    NSArray *screenArray = [NSScreen screens];
    unsigned screenCount = [screenArray count];
    unsigned index  = 0;
    numScreen = screenCount;
    
    for (index; index < screenCount; index++){
        NSScreen *screen = [screenArray objectAtIndex: index];
        screenRect = [screen visibleFrame];
        
        NSString *tempMessage = [NSString stringWithFormat:@"Screen %i @ %ix%i", index+1, (int)screenRect.size.width, (int)screenRect.size.height];
        [self sendGALog:tempMessage];
    }
    
    screenX = screenRect.size.width;
    screenY = screenRect.size.height;
    
}

//------------------------------------------------------------------------------
- (void) sendScreenResToGA {
    gapp->getScreenInfo(screenX,screenY);
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
            gaVPWindow->setWindowPosition(screenX-330,screenY-30);
            [sender setState: NSOnState];
            break;
            
        case 1:
            gaVP->setPreviewDim(640,360);
            gaVPWindow->setWindowShape(640,360);
            gaVPWindow->setWindowPosition(screenX-650,screenY-30);
            [sender setState: NSOnState];
            break;
            
        case 2:
            gaVP->setPreviewDim(640,480);
            gaVPWindow->setWindowShape(640,480);
            gaVPWindow->setWindowPosition(screenX-650,screenY-30);
            [sender setState: NSOnState];
            break;
            
        case 3:
            gaVP->setPreviewDim(800,600);
            gaVPWindow->setWindowShape(800,600);
            gaVPWindow->setWindowPosition(screenX-810,screenY-30);
            [sender setState: NSOnState];
            break;
            
        case 4:
            gaVP->setPreviewDim(854,480);
            gaVPWindow->setWindowShape(854,480);
            gaVPWindow->setWindowPosition(screenX-864,screenY-30);
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


@end
