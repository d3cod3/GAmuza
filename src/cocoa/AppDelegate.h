
#include "gamuzaMain.h"
#include "gaVideoPreview.h"
#include "ofxNSWindower.h"

#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>

#import "SplashWindow.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSOutlineViewDelegate, NSOutlineViewDataSource, NSMenuDelegate> {
    
	BOOL                        applicationHasStarted;
    
    NSFileManager               *filemgr;
    NSString                    *resPath;
    NSString                    *documentsDirectory;
    NSArray                     *filelist; // filelist from GAmuza script folder
    NSMutableArray              *GAExampleFiles;
    NSMutableArray              *GASketchbookFiles;
    
    IBOutlet SplashWindow       *_splash;
    IBOutlet NSTextView         *logger;
    
    int                         numScreen;
    float                       screenX, screenY;
    
    bool                        isPreviewON;
    
}


// -----------------------------------------------------------------------------

- (void)terminateSplashWindow: (NSTimer *)timer;

- (void)createGAmuzaDirectory;

- (void)getGAmuzaFolderContents:(NSString*)path;

- (void)getSketchbookFolderContents:(NSString*)path;

- (void)checkForLogMessages: (NSNotification *) notification;

- (void)checkForLogErrors: (NSNotification *) notification;

// -----------------------------------------------------------------------------

- (void) screenResolution;

- (void) sendScreenResToGA;

- (NSString *) runCommand:(NSString *)commandToRun;

- (void)sendGALog:(NSString *)msg;


// -----------------------------------------------------------------------------
//	Menu Actions
// -----------------------------------------------------------------------------
- (IBAction) togglePreviewWindow:(id)sender;

- (IBAction) setPreviewDimensions:(id)sender;

- (IBAction) openOFReference:(id)sender;

- (IBAction) openOfxAddonsPage:(id)sender;

- (IBAction) showGettingStartedPage:(id)sender;

- (IBAction) gotoGAWeb:(id)sender;

- (IBAction) openOnlineReference:(id)sender;

- (IBAction) openItemFromGAmuzaFolder:(id)sender;

- (IBAction) openItemFromSketchbookFolder:(id)sender;

- (IBAction) restartGAmuzaWindow: (id)sender;

- (IBAction) sendScriptToGAmuza:(id)sender;

- (IBAction) cleanScriptToGAmuza:(id)sender;

- (IBAction) toggleGAmuzaFullscreen:(id)sender;

- (IBAction) resetMapping:(id)sender;

- (IBAction) loadMapping:(id)sender;

- (IBAction) saveMapping:(id)sender;

- (IBAction) drawMappingGrid:(id)sender;


// GAmuza render window reference
gamuzaMain      *gapp;
ofPtr<ofxNSWindow> gappWindow;
// GAmuza video preview
gaVideoPreview  *gaVP;
ofPtr<ofxNSWindow> gaVPWindow;

@end
