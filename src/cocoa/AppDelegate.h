
#include "gamuzaMain.h"

#include "gaVideoPreview.h"
#include "gaTimeline.h"
#include "gaAudioModule.h"
#include "gaArduinoModule.h"
#include "gaMapperModule.h"

#include "ofxNSWindower.h"

#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>
#import <AppKit/NSApplication.h>

#import "ZipFile.h"
#import "ZipException.h"
#import "FileInZipInfo.h"
#import "ZipReadStream.h"
#import "ZipWriteStream.h"
#import "zlib.h"

#import "SplashWindow.h"
#import "PreferencesController.h"

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
// Mapper Module
gaMapperModule      *gaMM;
ofPtr<ofxNSWindow>  gaMMWindow;

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
    
    // GRID TOOL PANEL
    IBOutlet NSPanel                *gridToolPanel;
    IBOutlet NSButton*              goldenRatioBut;
    IBOutlet NSButton*              centerRatioBut;
    IBOutlet NSButton*              thirdRatiobut;
    IBOutlet NSButton*              standardGridBut;
    IBOutlet NSSlider               *standardCellWidth;
    IBOutlet NSSlider               *standardCellHeight;
    IBOutlet NSTextField*           cellWidthTextField;
    IBOutlet NSTextField*           cellHeightTextField;
    
    
    int                         numScreen;
    int                         screenW, screenH;
    int                         fullscreenWinPosX;
    
    bool                        isMouseON;
    bool                        isPreviewON;
    bool                        isTimelineON;
    bool                        isAudioModuleON;
    bool                        isArduinoModuleON;
    bool                        isMapperModuleON;
    bool                        isMapperOutputON;
    
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

- (BOOL)processFile:(NSString *)file;

- (void)setButtonTitleFor:(NSButton*)button toString:(NSString*)title withColor:(NSColor*)color;

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

// Archive Sketch (Zip it)
- (IBAction) archiveSketch:(id)sender;

// Export to HTML
- (IBAction) exportSketchToHTML:(id)sender;

// GRID Tool
- (IBAction) getGridTool:(id)sender;
- (IBAction) applyGridSettings:(id)sender;

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

// MAPPER MODULE
- (IBAction) toggleMapperModule:(id)sender;
- (IBAction) toggleActivateMapper:(id)sender;

// MAIN RENDER WINDOW
- (IBAction) toggleHideCursor:(id)sender;


@end
