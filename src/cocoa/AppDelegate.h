
#include "gamuzaMain.h"

#include "gaVideoPreview.h"
#include "gaTimeline.h"
#include "gaAudioModule.h"
#include "gaArduinoModule.h"
#include "gaCVModule.h"

#include "ofxNSWindower.h"

#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>

#import "SplashWindow.h"
#import "PreferencesController.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSOutlineViewDelegate, NSOutlineViewDataSource, NSMenuDelegate> {
    
	BOOL                        applicationHasStarted;
    
    NSFileManager               *filemgr;
    NSString                    *resPath;
    NSString                    *documentsDirectory;
    NSArray                     *filelist;
    NSMutableArray              *GAExampleFiles;
    NSMutableArray              *GASketchbookFiles;
    
    // SPLASH WINDOW
    IBOutlet SplashWindow           *_splash;
    // LOGGER
    IBOutlet NSTextView             *logger;
    // PREFERENCE PANEL
    IBOutlet PreferencesController  *prefPanel;
    
    // COLOR CORRECTION PANEL
    IBOutlet NSPanel                *colorCorrectionPanel;
    IBOutlet NSSlider               *gammaS;
    IBOutlet NSSlider               *brightS;
    IBOutlet NSSlider               *satS;
    IBOutlet NSSlider               *contrS;
    IBOutlet NSSlider               *filmBS;
    IBOutlet NSSlider               *techS;
    IBOutlet NSSlider               *whiteDS;
    IBOutlet NSSlider               *exposS;
    IBOutlet NSSlider               *diffS;
    
    int                         numScreen;
    int                         screenW, screenH;
    int                         fullscreenWinPosX;
    
    bool                        isPreviewON;
    bool                        isTimelineON;
    bool                        isAudioModuleON;
    bool                        isArduinoModuleON;
    bool                        isCVModuleON;
    
    NSMutableArray              *screensINFO;
    
    vector<string>              aInD;
    vector<int>                 aInDID;
    vector<string>              aOutD;
    vector<int>                 aOutDID;
    vector<string>				aInputCH;
    vector<string>				aOutputCH;
    vector<string>              mD;
    vector<string>              sD;
    
}


// -----------------------------------------------------------------------------

- (void)terminateSplashWindow: (NSTimer *)timer;

- (void)createGAmuzaDirectory;

- (void)getGAmuzaFolderContents:(NSString*)path;

- (void)getSketchbookFolderContents:(NSString*)path;

- (void)checkForGALog: (NSNotification *) notification;

- (void)checkForLogMessages: (NSNotification *) notification;

- (void)checkForLogErrors: (NSNotification *) notification;

// -----------------------------------------------------------------------------

- (void) getScreenXPosition:(int)screenNum;

- (void) screenResolution;

- (void) sendScreenResToGA;

- (void) sendDataToPreferences;

- (NSString *) runCommand:(NSString *)commandToRun;
- (NSXMLNode *)childNamed:(NSString *)name fromNode:(NSXMLNode *)fNode;

- (void)sendGALog:(NSString *)msg;


// -----------------------------------------------------------------------------
//	Menu Actions
// -----------------------------------------------------------------------------
- (IBAction) hideAllModules:(id)sender;

- (IBAction) applyPreferences:(id)sender;

- (IBAction) togglePreviewWindow:(id)sender;

- (IBAction) setPreviewDimensions:(id)sender;

- (IBAction) openOFReference:(id)sender;

- (IBAction) openOfxAddonsPage:(id)sender;

- (IBAction) showGettingStartedPage:(id)sender;

- (IBAction) gotoGAWeb:(id)sender;

- (IBAction) openOnlineReference:(id)sender;

- (IBAction) openItemFromGAmuzaFolder:(id)sender;

- (IBAction) openItemFromSketchbookFolder:(id)sender;

- (IBAction) openGAMUZADocument:(id)sender;

- (IBAction) sendScriptToGAmuza:(id)sender;

- (IBAction) cleanScriptToGAmuza:(id)sender;

- (IBAction) toggleGAmuzaFullscreen:(id)sender;

// COLOR CORRECTION
- (IBAction) getColorCorrection:(id)sender;
- (IBAction) saveColorCorrection:(id)sender;
- (IBAction) resetColorCorrection:(id)sender;
- (IBAction) applyColorCorrection:(id)sender;

// MAPPING
- (IBAction) resetMapping:(id)sender;
- (IBAction) loadMapping:(id)sender;
- (IBAction) saveMapping:(id)sender;
- (IBAction) drawMappingGrid:(id)sender;
- (IBAction) switchMouseKeyControl:(id)sender;
- (IBAction) mappingManualEditON:(id)sender;
- (IBAction) mappingManualEditOFF:(id)sender;
- (IBAction) goToNorthMappingPoint:(id)sender;
- (IBAction) goToSouthMappingPoint:(id)sender;
- (IBAction) goToEastMappingPoint:(id)sender;
- (IBAction) goToWestMappingPoint:(id)sender;

// TIMELINE
- (IBAction) toggleTimelinePanel:(id)sender;
- (IBAction) undoOnTimeline:(id)sender;
- (IBAction) redoOnTimeline:(id)sender;
- (IBAction) copyOnTimeline:(id)sender;
- (IBAction) cutOnTimeline:(id)sender;
- (IBAction) pasteOnTimeline:(id)sender;

// AUDIO MODULE
- (IBAction) toggleAudioModule:(id)sender;

// ARDUINO MODULE
- (IBAction) toggleArduinoModule:(id)sender;

// COMPUTER VISION MODULE
- (IBAction) toggleCVModule:(id)sender;

// GAmuza render window reference
gamuzaMain          *gapp;
ofPtr<ofxNSWindow>  gappWindow;
// GAmuza video preview
gaVideoPreview      *gaVP;
ofPtr<ofxNSWindow>  gaVPWindow;

//////////////////////////////// GAmuza GUI PANELS
// Timelne
gaTimeline          *gaTL;
ofPtr<ofxNSWindow>  gaTLWindow;
// Audio Module
gaAudioModule       *gaAM;
ofPtr<ofxNSWindow>  gaAMWindow;
// Arduino Module
gaArduinoModule     *gaARM;
ofPtr<ofxNSWindow>  gaARMWindow;
// Computer Vision Module
gaCVModule          *gaCVM;
ofPtr<ofxNSWindow>  gaCVMWindow;

@end
