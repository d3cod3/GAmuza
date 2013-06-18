//
//  PreferencesController.h
//  GAmuza
//
//  Created by n3m3da on 10/06/13.
//
//

#import <Cocoa/Cocoa.h>
#import <QTKit/QTkit.h>

@interface PreferencesController : NSObject<NSTextFieldDelegate>{
    
    IBOutlet NSPanel*       mainPanel;
    
    // VIDEO OUTPUT
    IBOutlet NSPopUpButton* videoTextureRes;
    IBOutlet NSTextField*   mappingGridRes;
    IBOutlet NSTextField*   customWidth;
    IBOutlet NSTextField*   customHeight;
    IBOutlet NSTextField*   aspectRatio;
    
    // AUTOMATION
    IBOutlet NSPopUpButton* screensList;
    IBOutlet NSButton*      autoFullscreen;
    IBOutlet NSButton*      autoloadSketch;
    IBOutlet NSButton*      autoloadMapping;
    IBOutlet NSTextField*   autoSketchFile;
    IBOutlet NSTextField*   autoMappingFile;
    IBOutlet NSButton*      chooseSketchFile;
    IBOutlet NSButton*      chooseMappingFile;
    
    // COMPUTER VISION
    IBOutlet QTCaptureView* deviceCaptureView;
    IBOutlet NSPopUpButton* videoDevices;
    IBOutlet NSPopUpButton* captureRes;
    IBOutlet NSTextField*   testingVideoFile;
    IBOutlet NSButton*      chooseVideoFile;
    IBOutlet NSTextField*   haarFile;
    IBOutlet NSButton*      chooseHaarFile;
    
    // AUDIO STREAMING
    IBOutlet NSPopUpButton* audioDevices;
    IBOutlet NSPopUpButton* samplingRate;
    IBOutlet NSPopUpButton* bufferSize;
    IBOutlet NSPopUpButton* fftWindowing;
    
    // ARDUINO
    IBOutlet NSPopUpButton* serialDevices;
    IBOutlet NSPopUpButton* baudrate;
    
    // MIDI
    IBOutlet NSPopUpButton* midiDevices;
    
    // OSC
    IBOutlet NSTextField*   sendingToIP;
    IBOutlet NSTextField*   sendingToPORT;
    IBOutlet NSTextField*   receivingAtPORT;
    
    
    NSString*   outputWidth;
    NSString*   outputHeight;
    NSString*   captureWidth;
    NSString*   captureHeight;
    
}

- (void) reduceToAspectRatio;

- (IBAction) updateScreenResolution:(id)sender;

- (IBAction) getDataFromXml:(id)sender;
- (IBAction) saveDataToXml:(id)sender;

- (void) getOutputRes:(NSString*)_w height:(NSString*)_h;
- (IBAction) setOutputRes:(id)sender;

- (void) getCaptureRes:(NSString*)_w height:(NSString*)_h;
- (IBAction) setCaptureRes:(id)sender;

- (IBAction) closePreferences:(id)sender;



@end
