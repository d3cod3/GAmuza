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
    IBOutlet NSSlider*      mappingSliderRes;
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
    
    // AUDIO STREAMING
    IBOutlet NSPopUpButton*     audioInDevices;
    IBOutlet NSPopUpButton*     audioOutDevices;
    IBOutlet NSPopUpButton*     samplingRate;
    IBOutlet NSPopUpButton*     bufferSize;
    IBOutlet NSPopUpButton*     fftWindowing;
    
    // ARDUINO
    IBOutlet NSPopUpButton*     serialDevices;
    IBOutlet NSPopUpButton*     baudrate;
    
    // MIDI
    IBOutlet NSPopUpButton*     midiDevices;
    
    // OSC
    IBOutlet NSTextField*   sendingToIP;
    IBOutlet NSTextField*   sendingToPORT;
    IBOutlet NSTextField*   receivingAtPORT;
    
    
    int         _autoFullscreen;
    int         _fullscreenScreen;
    NSString*   outputWidth;
    NSString*   outputHeight;
    NSString*   _samplingRate;
    NSString*   _bufferSize;
    int         _fftWindowing;
    int         _audioInDev;
    int         _audioOutDev;
    int         _midiDev;
    NSString*   _baudRate;
    NSString*   _serialDev;
    
    NSMutableArray*     aInCh;
    NSMutableArray*     aOutCh;
    
}

@property (nonatomic,assign) NSPanel*           mainPanel;
@property (nonatomic,assign) NSPopUpButton*     audioInDevices;
@property (nonatomic,assign) NSPopUpButton*     audioOutDevices;
@property (nonatomic,assign) NSPopUpButton*     midiDevices;
@property (nonatomic,assign) NSPopUpButton*     serialDevices;
@property (nonatomic,assign) NSMutableArray*    aInCh;
@property (nonatomic,assign) NSMutableArray*    aOutCh;
@property (nonatomic,assign) int                _autoFullscreen;
@property (nonatomic,assign) int                _fullscreenScreen;

NSString* screenNameForDisplay(CGDirectDisplayID displayID);

- (NSXMLNode *)childNamed:(NSString *)name fromNode:(NSXMLNode *)fNode;

- (void) reduceToAspectRatio;
- (void) getScreensInfo;

- (IBAction) updateScreenResolution:(id)sender;
- (IBAction) updateSamplingRate:(id)sender;
- (IBAction) updateBufferSize:(id)sender;
- (IBAction) updateBaudrate:(id)sender;

- (IBAction) updateAudioInDevice:(id)sender;
- (IBAction) updateAudioOutDevice:(id)sender;
- (IBAction) updateMidiDevice:(id)sender;
- (IBAction) updateSerialDevice:(id)sender;

- (IBAction) getDataFromXml:(id)sender;
- (void) saveDataToXml;

- (void) getOutputRes:(NSString*)_w height:(NSString*)_h;

- (IBAction) openPanelForSketch:(id)sender;
- (IBAction) openPanelForMapping:(id)sender;



@end
