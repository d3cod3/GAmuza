//
//  PreferencesController.m
//  GAmuza
//
//  Created by n3m3da on 10/06/13.
//
//

#import <IOKit/graphics/IOGraphicsLib.h>

#import "PreferencesController.h"

@implementation PreferencesController
@synthesize mainPanel, audioInDevices, audioOutDevices, midiDevices, serialDevices, aInCh, aOutCh, _autoFullscreen, _fullscreenScreen;


NSString* screenNameForDisplay(CGDirectDisplayID displayID){
    NSString *screenName = nil;
    
    NSDictionary *deviceInfo = (NSDictionary *)IODisplayCreateInfoDictionary(CGDisplayIOServicePort(displayID), kIODisplayOnlyPreferredName);
    NSDictionary *localizedNames = [deviceInfo objectForKey:[NSString stringWithUTF8String:kDisplayProductName]];
    
    if ([localizedNames count] > 0) {
    	screenName = [[localizedNames objectForKey:[[localizedNames allKeys] objectAtIndex:0]] retain];
    }
    
    [deviceInfo release];
    return [screenName autorelease];
}

- (void) awakeFromNib{
    [self getScreensInfo];
    [customWidth setDelegate:self];
    [customHeight setDelegate:self];
    [self getDataFromXml:nil];
    [mainPanel orderOut:nil];
}

- (void) controlTextDidChange:(NSNotification *)notification{
    if([notification object] == customWidth || [notification object] == customHeight){
        [self reduceToAspectRatio];
    }
}

- (void) reduceToAspectRatio{
    int arW = [customWidth intValue];
    int arH = [customHeight intValue];
    int temp = arW*arH;
    if (temp>0){
        for (temp; temp>1; temp--){
            if ((arW%temp==0) && (arH%temp==0)){
                arW/=temp;
                arH/=temp;
            }
        }
    }else if (temp<0){
        for (temp; temp<-1; temp++){
            if ((arW%temp==0) && (arH%temp==0)){
                arW/=temp;
                arH/=temp;
            }
        }
    }
    [aspectRatio setStringValue:[NSString stringWithFormat:@"%dx%d", arW, arH]];
}

- (void) getScreensInfo{
    NSRect              screenRect;
    NSDictionary*       screenDescription;
    CGDirectDisplayID   theCGDisplayID;
    NSArray*            screenArray = [NSScreen screens];
    
    unsigned screenCount = [screenArray count];
    unsigned i = 0;
    
    [screensList removeItemAtIndex:0];
    
    for(i;i < screenCount;i++){
        NSScreen *screen = [screenArray objectAtIndex: i];
        screenRect = [screen visibleFrame];
        screenDescription = [screen deviceDescription];
        
        theCGDisplayID = (CGDirectDisplayID) [[screenDescription valueForKey:@"NSScreenNumber"] intValue];
        
        NSString *tempMessage = [NSString stringWithFormat:@"%@  %ix%i",screenNameForDisplay(theCGDisplayID),(unsigned)CGDisplayPixelsWide(theCGDisplayID),(unsigned)CGDisplayPixelsHigh(theCGDisplayID)];
        [screensList addItemWithTitle:tempMessage];
        
    }
}

- (IBAction) updateScreenResolution:(id)sender{
    if([[sender selectedItem] tag] == 0){
        [self getOutputRes:@"160" height:@"120"];
    }else if([[sender selectedItem] tag] == 1){
        [self getOutputRes:@"320" height:@"240"];
    }else if([[sender selectedItem] tag] == 2){
        [self getOutputRes:@"400" height:@"240"];
    }else if([[sender selectedItem] tag] == 3){
        [self getOutputRes:@"640" height:@"350"];
    }else if([[sender selectedItem] tag] == 4){
        [self getOutputRes:@"640" height:@"360"];
    }else if([[sender selectedItem] tag] == 5){
        [self getOutputRes:@"640" height:@"480"];
    }else if([[sender selectedItem] tag] == 6){
        [self getOutputRes:@"768" height:@"480"];
    }else if([[sender selectedItem] tag] == 7){
        [self getOutputRes:@"800" height:@"480"];
    }else if([[sender selectedItem] tag] == 8){
        [self getOutputRes:@"854" height:@"480"];
    }else if([[sender selectedItem] tag] == 9){
        [self getOutputRes:@"800" height:@"600"];
    }else if([[sender selectedItem] tag] == 10){
        [self getOutputRes:@"960" height:@"540"];
    }else if([[sender selectedItem] tag] == 11){
        [self getOutputRes:@"960" height:@"640"];
    }else if([[sender selectedItem] tag] == 12){
        [self getOutputRes:@"1024" height:@"576"];
    }else if([[sender selectedItem] tag] == 13){
        [self getOutputRes:@"1024" height:@"600"];
    }else if([[sender selectedItem] tag] == 14){
        [self getOutputRes:@"1024" height:@"768"];
    }else if([[sender selectedItem] tag] == 15){
        [self getOutputRes:@"1280" height:@"720"];
    }else if([[sender selectedItem] tag] == 16){
        [self getOutputRes:@"1280" height:@"800"];
    }else if([[sender selectedItem] tag] == 17){
        [self getOutputRes:@"1280" height:@"960"];
    }else if([[sender selectedItem] tag] == 18){
        [self getOutputRes:@"1280" height:@"1024"];
    }else if([[sender selectedItem] tag] == 19){
        [self getOutputRes:@"1366" height:@"768"];
    }else if([[sender selectedItem] tag] == 20){
        [self getOutputRes:@"1440" height:@"900"];
    }else if([[sender selectedItem] tag] == 21){
        [self getOutputRes:@"1440" height:@"1080"];
    }else if([[sender selectedItem] tag] == 22){
        [self getOutputRes:@"1600" height:@"900"];
    }else if([[sender selectedItem] tag] == 23){
        [self getOutputRes:@"1600" height:@"1200"];
    }else if([[sender selectedItem] tag] == 24){
        [self getOutputRes:@"1680" height:@"1050"];
    }else if([[sender selectedItem] tag] == 25){
        [self getOutputRes:@"1920" height:@"1080"];
    }else if([[sender selectedItem] tag] == 26){
        [self getOutputRes:@"1920" height:@"1200"];
    }else if([[sender selectedItem] tag] == 27){
        [self getOutputRes:@"2048" height:@"1152"];
    }else if([[sender selectedItem] tag] == 28){
        [self getOutputRes:@"4096" height:@"2304"];
    }else if([[sender selectedItem] tag] == 29){
        [self getOutputRes:@"1600" height:@"600"];
    }else if([[sender selectedItem] tag] == 30){
        [self getOutputRes:@"2048" height:@"768"];
    }else if([[sender selectedItem] tag] == 31){
        [self getOutputRes:@"2560" height:@"720"];
    }else if([[sender selectedItem] tag] == 32){
        [self getOutputRes:@"2560" height:@"800"];
    }else if([[sender selectedItem] tag] == 33){
        [self getOutputRes:@"2560" height:@"960"];
    }else if([[sender selectedItem] tag] == 34){
        [self getOutputRes:@"2560" height:@"1024"];
    }else if([[sender selectedItem] tag] == 35){
        [self getOutputRes:@"2720" height:@"768"];
    }else if([[sender selectedItem] tag] == 36){
        [self getOutputRes:@"2800" height:@"1050"];
    }else if([[sender selectedItem] tag] == 37){
        [self getOutputRes:@"2880" height:@"900"];
    }else if([[sender selectedItem] tag] == 38){
        [self getOutputRes:@"3200" height:@"900"];
    }else if([[sender selectedItem] tag] == 39){
        [self getOutputRes:@"3200" height:@"1200"];
    }else if([[sender selectedItem] tag] == 40){
        [self getOutputRes:@"3360" height:@"1050"];
    }else if([[sender selectedItem] tag] == 41){
        [self getOutputRes:@"3840" height:@"1080"];
    }else if([[sender selectedItem] tag] == 42){
        [self getOutputRes:@"3840" height:@"1200"];
    }else if([[sender selectedItem] tag] == 43){
        [self getOutputRes:@"4096" height:@"1152"];
    }else if([[sender selectedItem] tag] == 44){
        [self getOutputRes:@"1920" height:@"480"];
    }else if([[sender selectedItem] tag] == 45){
        [self getOutputRes:@"2400" height:@"480"];
    }else if([[sender selectedItem] tag] == 46){
        [self getOutputRes:@"2400" height:@"600"];
    }else if([[sender selectedItem] tag] == 47){
        [self getOutputRes:@"1920" height:@"1080"];
    }else if([[sender selectedItem] tag] == 48){
        [self getOutputRes:@"3840" height:@"720"];
    }else if([[sender selectedItem] tag] == 49){
        [self getOutputRes:@"3840" height:@"768"];
    }else if([[sender selectedItem] tag] == 50){
        [self getOutputRes:@"3840" height:@"800"];
    }else if([[sender selectedItem] tag] == 51){
        [self getOutputRes:@"3840" height:@"960"];
    }else if([[sender selectedItem] tag] == 52){
        [self getOutputRes:@"3840" height:@"1024"];
    }else if([[sender selectedItem] tag] == 53){
        [self getOutputRes:@"4080" height:@"768"];
    }else if([[sender selectedItem] tag] == 54){
        [self getOutputRes:@"4098" height:@"768"];
    }else if([[sender selectedItem] tag] == 55){
        [self getOutputRes:@"4200" height:@"1050"];
    }else if([[sender selectedItem] tag] == 56){
        [self getOutputRes:@"4320" height:@"900"];
    }else if([[sender selectedItem] tag] == 57){
        [self getOutputRes:@"4800" height:@"900"];
    }else if([[sender selectedItem] tag] == 58){
        [self getOutputRes:@"5040" height:@"1050"];
    }else if([[sender selectedItem] tag] == 59){
        [self getOutputRes:@"5760" height:@"1080"];
    }
}

- (IBAction) updateSamplingRate:(id)sender{
    if([[sender selectedItem] tag] == 0){
        _samplingRate = @"22050";
    }else if([[sender selectedItem] tag] == 1){
        _samplingRate = @"44100";
    }else if([[sender selectedItem] tag] == 2){
        _samplingRate = @"48000";
    }else if([[sender selectedItem] tag] == 3){
        _samplingRate = @"96000";
    }else if([[sender selectedItem] tag] == 4){
        _samplingRate = @"192000";
    }
}

- (IBAction) updateBufferSize:(id)sender{
    if([[sender selectedItem] tag] == 0){
        _bufferSize = @"32";
    }else if([[sender selectedItem] tag] == 1){
        _bufferSize = @"64";
    }else if([[sender selectedItem] tag] == 2){
        _bufferSize = @"128";
    }else if([[sender selectedItem] tag] == 3){
        _bufferSize = @"256";
    }else if([[sender selectedItem] tag] == 4){
        _bufferSize = @"512";
    }else if([[sender selectedItem] tag] == 5){
        _bufferSize = @"1024";
    }else if([[sender selectedItem] tag] == 6){
        _bufferSize = @"2048";
    }else if([[sender selectedItem] tag] == 7){
        _bufferSize = @"4096";
    }
}

- (IBAction) updateBaudrate:(id)sender{
    if([[sender selectedItem] tag] == 0){
        _baudRate = @"300";
    }else if([[sender selectedItem] tag] == 1){
        _baudRate = @"600";
    }else if([[sender selectedItem] tag] == 2){
        _baudRate = @"1200";
    }else if([[sender selectedItem] tag] == 3){
        _baudRate = @"2400";
    }else if([[sender selectedItem] tag] == 4){
        _baudRate = @"4800";
    }else if([[sender selectedItem] tag] == 5){
        _baudRate = @"9600";
    }else if([[sender selectedItem] tag] == 6){
        _baudRate = @"14400";
    }else if([[sender selectedItem] tag] == 7){
        _baudRate = @"19200";
    }else if([[sender selectedItem] tag] == 8){
        _baudRate = @"28800";
    }else if([[sender selectedItem] tag] == 9){
        _baudRate = @"38400";
    }else if([[sender selectedItem] tag] == 10){
        _baudRate = @"57600";
    }else if([[sender selectedItem] tag] == 11){
        _baudRate = @"115200";
    }
}

- (IBAction) updateAudioInDevice:(id)sender{
    _audioInDev = [[sender selectedItem] tag];
    
}

- (IBAction) updateAudioOutDevice:(id)sender{
    _audioOutDev = [[sender selectedItem] tag];
    
}

- (IBAction) updateMidiDevice:(id)sender{
    _midiDev = [[sender selectedItem] tag];
   
}

- (IBAction) updateSerialDevice:(id)sender{
     _serialDev = [[sender selectedItem] title];
}

- (IBAction) getDataFromXml:(id)sender{
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
                                                    error:nil];
    if (xmlDoc == nil) {
        xmlDoc = [[NSXMLDocument alloc] initWithContentsOfURL:furl
                                                      options:NSXMLDocumentTidyXML
                                                        error:nil];
    }
    
    NSXMLElement* root  = [xmlDoc rootElement];
    
    ////////////////////////////////////////////////////////////////////// VIDEO OUTPUT
    
    // OUTPUT RESOLUTION
    itemArray = [root nodesForXPath:@"//ps_width" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        outputWidth = [xmlElement stringValue];
    }
    
    itemArray = [root nodesForXPath:@"//ps_height" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        outputHeight = [xmlElement stringValue];
    }
    [self getOutputRes:outputWidth height:outputHeight];
    
    // MAPPING RESOLUTION
    itemArray = [root nodesForXPath:@"//grid_res" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        [mappingGridRes setStringValue:[xmlElement stringValue]];
        [mappingSliderRes setIntValue:[mappingGridRes intValue]];
    }
    
    ////////////////////////////////////////////////////////////////////// AUTOMATION
    NSString *_tempA;
    itemArray = [root nodesForXPath:@"//auto_pilot" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _tempA = [xmlElement stringValue];
        _autoFullscreen = [_tempA intValue];
        [autoFullscreen setState:_autoFullscreen];
    }
    itemArray = [root nodesForXPath:@"//auto_pilot_screen" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _tempA = [xmlElement stringValue];
        _fullscreenScreen = [_tempA intValue];
        [screensList selectItemWithTag:_fullscreenScreen];
    }
    itemArray = [root nodesForXPath:@"//autoload_script" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _tempA = [xmlElement stringValue];
        [autoloadSketch setState:[_tempA intValue]];
    }
    itemArray = [root nodesForXPath:@"//autoload_mapping" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _tempA = [xmlElement stringValue];
        [autoloadMapping setState:[_tempA intValue]];
    }
    itemArray = [root nodesForXPath:@"//script_file" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        [autoSketchFile setStringValue:[xmlElement stringValue]];
    }
    
    itemArray = [root nodesForXPath:@"//mapping_file" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        [autoMappingFile setStringValue:[xmlElement stringValue]];
    }
    
    ////////////////////////////////////////////////////////////////////// AUDIO STREAMING
    itemArray = [root nodesForXPath:@"//audioIn_Dev_ID" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _audioInDev = [[xmlElement stringValue] intValue];
        [audioInDevices selectItemWithTag:_audioInDev];
    }
    itemArray = [root nodesForXPath:@"//audioOut_Dev_ID" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _audioOutDev = [[xmlElement stringValue] intValue];
        [audioOutDevices selectItemWithTag:_audioOutDev];
    }
    
    itemArray = [root nodesForXPath:@"//sampling_rate" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _samplingRate = [xmlElement stringValue];
        if([_samplingRate isEqualToString:@"22050"]){
            [samplingRate selectItemWithTag:0];
        }else if([_samplingRate isEqualToString:@"44100"]){
            [samplingRate selectItemWithTag:1];
        }else if([_samplingRate isEqualToString:@"48000"]){
            [samplingRate selectItemWithTag:2];
        }else if([_samplingRate isEqualToString:@"96000"]){
            [samplingRate selectItemWithTag:3];
        }else if([_samplingRate isEqualToString:@"192000"]){
            [samplingRate selectItemWithTag:4];
        }
    }
    
    itemArray = [root nodesForXPath:@"//buffer_size" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _bufferSize = [xmlElement stringValue];
        if([_bufferSize isEqualToString:@"32"]){
            [bufferSize selectItemWithTag:0];
        }else if([_bufferSize isEqualToString:@"64"]){
            [bufferSize selectItemWithTag:1];
        }else if([_bufferSize isEqualToString:@"128"]){
            [bufferSize selectItemWithTag:2];
        }else if([_bufferSize isEqualToString:@"256"]){
            [bufferSize selectItemWithTag:3];
        }else if([_bufferSize isEqualToString:@"512"]){
            [bufferSize selectItemWithTag:4];
        }else if([_bufferSize isEqualToString:@"1024"]){
            [bufferSize selectItemWithTag:5];
        }else if([_bufferSize isEqualToString:@"2048"]){
            [bufferSize selectItemWithTag:6];
        }else if([_bufferSize isEqualToString:@"4096"]){
            [bufferSize selectItemWithTag:7];
        }
    }
    
    itemArray = [root nodesForXPath:@"//fft_window" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _fftWindowing = [[xmlElement stringValue] intValue];
        [fftWindowing selectItemWithTag:_fftWindowing];
    }
    
    ////////////////////////////////////////////////////////////////////// ARDUINO
    itemArray = [root nodesForXPath:@"//serial_device_name" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _serialDev = [xmlElement stringValue];
        [serialDevices selectItemWithTitle:_serialDev];
    }
    
    itemArray = [root nodesForXPath:@"//baud_rate" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _baudRate = [xmlElement stringValue];
        if([_baudRate isEqualToString:@"300"]){
            [baudrate selectItemWithTag:0];
        }else if([_baudRate isEqualToString:@"600"]){
            [baudrate selectItemWithTag:1];
        }else if([_baudRate isEqualToString:@"1200"]){
            [baudrate selectItemWithTag:2];
        }else if([_baudRate isEqualToString:@"2400"]){
            [baudrate selectItemWithTag:3];
        }else if([_baudRate isEqualToString:@"4800"]){
            [baudrate selectItemWithTag:4];
        }else if([_baudRate isEqualToString:@"9600"]){
            [baudrate selectItemWithTag:5];
        }else if([_baudRate isEqualToString:@"14400"]){
            [baudrate selectItemWithTag:6];
        }else if([_baudRate isEqualToString:@"19200"]){
            [baudrate selectItemWithTag:7];
        }else if([_baudRate isEqualToString:@"28800"]){
            [baudrate selectItemWithTag:8];
        }else if([_baudRate isEqualToString:@"38400"]){
            [baudrate selectItemWithTag:9];
        }else if([_baudRate isEqualToString:@"57600"]){
            [baudrate selectItemWithTag:10];
        }else if([_baudRate isEqualToString:@"115200"]){
            [baudrate selectItemWithTag:11];
        }
    }
    
    ////////////////////////////////////////////////////////////////////// MIDI
    itemArray = [root nodesForXPath:@"//midi_port" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        _midiDev = [[xmlElement stringValue] intValue];
        [midiDevices selectItemWithTag:_midiDev];
    }
    
    ////////////////////////////////////////////////////////////////////// OSC
    itemArray = [root nodesForXPath:@"//host_ip" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        [sendingToIP setStringValue:[xmlElement stringValue]];
    }
    
    itemArray = [root nodesForXPath:@"//host_port" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        [sendingToPORT setStringValue:[xmlElement stringValue]];
    }
    
    itemArray = [root nodesForXPath:@"//server_port" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        [receivingAtPORT setStringValue:[xmlElement stringValue]];
    }
    
    
    [xmlDoc release];
    
    [mainPanel makeKeyAndOrderFront:mainPanel];
    
}

- (void) saveDataToXml{
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
                                                    error:nil];
    if (xmlDoc == nil) {
        xmlDoc = [[NSXMLDocument alloc] initWithContentsOfURL:furl
                                                      options:NSXMLDocumentTidyXML
                                                        error:nil];
    }
    
    NSXMLNode *rootNode = [xmlDoc rootElement];
	
    //////////////////////////////////////////////////////////////////////
    // SAVE DATA
    ////////////////////////////////////////////////////////////////////// VIDEO OUTPUT
    node = [self childNamed:@"ps_width" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[customWidth stringValue]]];
    
    node = [self childNamed:@"ps_height" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[customHeight stringValue]]];
    
    node = [self childNamed:@"grid_res" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[mappingGridRes stringValue]]];
    
    ////////////////////////////////////////////////////////////////////// AUTOMATION
    node = [self childNamed:@"auto_pilot" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%d",[autoFullscreen state]]];
    
    node = [self childNamed:@"auto_pilot_screen" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%d",[screensList indexOfSelectedItem]]];
    
    node = [self childNamed:@"autoload_script" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%d",[autoloadSketch state]]];
    
    node = [self childNamed:@"autoload_mapping" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%d",[autoloadMapping state]]];
    
    node = [self childNamed:@"script_file" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[autoSketchFile stringValue]]];
    
    node = [self childNamed:@"mapping_file" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[autoMappingFile stringValue]]];
    
    ////////////////////////////////////////////////////////////////////// AUDIO STREAMING
    node = [self childNamed:@"audioIn_Dev_ID" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%d",[[audioInDevices selectedItem] tag]]];
    
    node = [self childNamed:@"audioOut_Dev_ID" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%d",[[audioOutDevices selectedItem] tag]]];
    
    // CHANNELS
    node = [self childNamed:@"input_ch" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%@",[aInCh objectAtIndex:[audioInDevices indexOfSelectedItem]]]];
    node = [self childNamed:@"output_ch" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%@",[aOutCh objectAtIndex:[audioOutDevices indexOfSelectedItem]]]];
    
    node = [self childNamed:@"sampling_rate" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%@",[samplingRate titleOfSelectedItem]]];
    
    node = [self childNamed:@"buffer_size" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%@",[bufferSize titleOfSelectedItem]]];
    
    node = [self childNamed:@"fft_window" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%d",[fftWindowing indexOfSelectedItem]]];
    
    ////////////////////////////////////////////////////////////////////// ARDUINO
    node = [self childNamed:@"serial_device_name" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%@",[serialDevices titleOfSelectedItem]]];
    
    node = [self childNamed:@"baud_rate" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%@",[baudrate titleOfSelectedItem]]];
    
    ////////////////////////////////////////////////////////////////////// MIDI
    node = [self childNamed:@"midi_port" fromNode:rootNode];
    [node setStringValue:[NSString stringWithFormat:@"%d",[midiDevices indexOfSelectedItem]]];
    
    ////////////////////////////////////////////////////////////////////// OSC
    node = [self childNamed:@"host_ip" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[sendingToIP stringValue]]];
    
    node = [self childNamed:@"host_port" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[sendingToPORT stringValue]]];
    
    node = [self childNamed:@"server_port" fromNode:rootNode];
    [node setStringValue:[NSString stringWithString:[receivingAtPORT stringValue]]];
    
    
    // WRITE TO XML
    data = [xmlDoc XMLData];
    [data writeToURL:furl atomically:YES];
    
    [xmlDoc release];
    
}

- (NSXMLNode *)childNamed:(NSString *)name fromNode:(NSXMLNode *)fNode{
    NSEnumerator *e = [[fNode children] objectEnumerator];
    
    NSXMLNode *node;
    while (node = [e nextObject])
        if ([[node name] isEqualToString:name])
            return node;
    
    return nil;
}

- (void) getOutputRes:(NSString*)_w height:(NSString*)_h{
    if([_w isEqualToString:@"160"] && [_h isEqualToString:@"120"]){
        [videoTextureRes selectItemWithTag:0];
        [customWidth setStringValue:@"160"];
        [customHeight setStringValue:@"120"];
    }else if([_w isEqualToString:@"320"] && [_h isEqualToString:@"240"]){
        [videoTextureRes selectItemWithTag:1];
        [customWidth setStringValue:@"320"];
        [customHeight setStringValue:@"240"];
    }else if([_w isEqualToString:@"400"] && [_h isEqualToString:@"240"]){
        [videoTextureRes selectItemWithTag:2];
        [customWidth setStringValue:@"400"];
        [customHeight setStringValue:@"240"];
    }else if([_w isEqualToString:@"640"] && [_h isEqualToString:@"350"]){
        [videoTextureRes selectItemWithTag:3];
        [customWidth setStringValue:@"640"];
        [customHeight setStringValue:@"350"];
    }else if([_w isEqualToString:@"640"] && [_h isEqualToString:@"360"]){
        [videoTextureRes selectItemWithTag:4];
        [customWidth setStringValue:@"640"];
        [customHeight setStringValue:@"360"];
    }else if([_w isEqualToString:@"640"] && [_h isEqualToString:@"480"]){
        [videoTextureRes selectItemWithTag:5];
        [customWidth setStringValue:@"640"];
        [customHeight setStringValue:@"480"];
    }else if([_w isEqualToString:@"768"] && [_h isEqualToString:@"480"]){
        [videoTextureRes selectItemWithTag:6];
        [customWidth setStringValue:@"768"];
        [customHeight setStringValue:@"480"];
    }else if([_w isEqualToString:@"800"] && [_h isEqualToString:@"480"]){
        [videoTextureRes selectItemWithTag:7];
        [customWidth setStringValue:@"800"];
        [customHeight setStringValue:@"480"];
    }else if([_w isEqualToString:@"854"] && [_h isEqualToString:@"480"]){
        [videoTextureRes selectItemWithTag:8];
        [customWidth setStringValue:@"854"];
        [customHeight setStringValue:@"480"];
    }else if([_w isEqualToString:@"800"] && [_h isEqualToString:@"600"]){
        [videoTextureRes selectItemWithTag:9];
        [customWidth setStringValue:@"800"];
        [customHeight setStringValue:@"600"];
    }else if([_w isEqualToString:@"960"] && [_h isEqualToString:@"540"]){
        [videoTextureRes selectItemWithTag:10];
        [customWidth setStringValue:@"960"];
        [customHeight setStringValue:@"540"];
    }else if([_w isEqualToString:@"960"] && [_h isEqualToString:@"640"]){
        [videoTextureRes selectItemWithTag:11];
        [customWidth setStringValue:@"960"];
        [customHeight setStringValue:@"640"];
    }else if([_w isEqualToString:@"1024"] && [_h isEqualToString:@"576"]){
        [videoTextureRes selectItemWithTag:12];
        [customWidth setStringValue:@"1024"];
        [customHeight setStringValue:@"576"];
    }else if([_w isEqualToString:@"1024"] && [_h isEqualToString:@"600"]){
        [videoTextureRes selectItemWithTag:13];
        [customWidth setStringValue:@"1024"];
        [customHeight setStringValue:@"600"];
    }else if([_w isEqualToString:@"1024"] && [_h isEqualToString:@"768"]){
        [videoTextureRes selectItemWithTag:14];
        [customWidth setStringValue:@"1024"];
        [customHeight setStringValue:@"768"];
    }else if([_w isEqualToString:@"1280"] && [_h isEqualToString:@"720"]){
        [videoTextureRes selectItemWithTag:15];
        [customWidth setStringValue:@"1280"];
        [customHeight setStringValue:@"720"];
    }else if([_w isEqualToString:@"1280"] && [_h isEqualToString:@"800"]){
        [videoTextureRes selectItemWithTag:16];
        [customWidth setStringValue:@"1280"];
        [customHeight setStringValue:@"800"];
    }else if([_w isEqualToString:@"1280"] && [_h isEqualToString:@"960"]){
        [videoTextureRes selectItemWithTag:17];
        [customWidth setStringValue:@"1280"];
        [customHeight setStringValue:@"960"];
    }else if([_w isEqualToString:@"1280"] && [_h isEqualToString:@"1024"]){
        [videoTextureRes selectItemWithTag:18];
        [customWidth setStringValue:@"1280"];
        [customHeight setStringValue:@"1024"];
    }else if([_w isEqualToString:@"1366"] && [_h isEqualToString:@"768"]){
        [videoTextureRes selectItemWithTag:19];
        [customWidth setStringValue:@"1366"];
        [customHeight setStringValue:@"768"];
    }else if([_w isEqualToString:@"1440"] && [_h isEqualToString:@"900"]){
        [videoTextureRes selectItemWithTag:20];
        [customWidth setStringValue:@"1440"];
        [customHeight setStringValue:@"900"];
    }else if([_w isEqualToString:@"1440"] && [_h isEqualToString:@"1080"]){
        [videoTextureRes selectItemWithTag:21];
        [customWidth setStringValue:@"1440"];
        [customHeight setStringValue:@"1080"];
    }else if([_w isEqualToString:@"1600"] && [_h isEqualToString:@"900"]){
        [videoTextureRes selectItemWithTag:22];
        [customWidth setStringValue:@"1600"];
        [customHeight setStringValue:@"900"];
    }else if([_w isEqualToString:@"1600"] && [_h isEqualToString:@"1200"]){
        [videoTextureRes selectItemWithTag:23];
        [customWidth setStringValue:@"1600"];
        [customHeight setStringValue:@"1200"];
    }else if([_w isEqualToString:@"1680"] && [_h isEqualToString:@"1050"]){
        [videoTextureRes selectItemWithTag:24];
        [customWidth setStringValue:@"1680"];
        [customHeight setStringValue:@"1050"];
    }else if([_w isEqualToString:@"1920"] && [_h isEqualToString:@"1080"]) {
        [videoTextureRes selectItemWithTag:25];
        [customWidth setStringValue:@"1920"];
        [customHeight setStringValue:@"1080"];
    }else if([_w isEqualToString:@"1920"] && [_h isEqualToString:@"1200"]){
        [videoTextureRes selectItemWithTag:26];
        [customWidth setStringValue:@"1920"];
        [customHeight setStringValue:@"1200"];
    }else if([_w isEqualToString:@"2048"] && [_h isEqualToString:@"1152"]){
        [videoTextureRes selectItemWithTag:27];
        [customWidth setStringValue:@"2048"];
        [customHeight setStringValue:@"1152"];
    }else if([_w isEqualToString:@"4096"] && [_h isEqualToString:@"2304"]){
        [videoTextureRes selectItemWithTag:28];
        [customWidth setStringValue:@"4096"];
        [customHeight setStringValue:@"2304"];
    }else if([_w isEqualToString:@"1600"] && [_h isEqualToString:@"600"]){
        [videoTextureRes selectItemWithTag:29];
        [customWidth setStringValue:@"1600"];
        [customHeight setStringValue:@"600"];
    }else if([_w isEqualToString:@"2048"] && [_h isEqualToString:@"768"]){
        [videoTextureRes selectItemWithTag:30];
        [customWidth setStringValue:@"2048"];
        [customHeight setStringValue:@"768"];
    }else if([_w isEqualToString:@"2560"] && [_h isEqualToString:@"720"]){
        [videoTextureRes selectItemWithTag:31];
        [customWidth setStringValue:@"2560"];
        [customHeight setStringValue:@"720"];
    }else if([_w isEqualToString:@"2560"] && [_h isEqualToString:@"800"]){
        [videoTextureRes selectItemWithTag:32];
        [customWidth setStringValue:@"2560"];
        [customHeight setStringValue:@"800"];
    }else if([_w isEqualToString:@"2560"] && [_h isEqualToString:@"960"]){
        [videoTextureRes selectItemWithTag:33];
        [customWidth setStringValue:@"2560"];
        [customHeight setStringValue:@"960"];
    }else if([_w isEqualToString:@"2560"] && [_h isEqualToString:@"1024"]){
        [videoTextureRes selectItemWithTag:34];
        [customWidth setStringValue:@"2560"];
        [customHeight setStringValue:@"1024"];
    }else if([_w isEqualToString:@"2720"] && [_h isEqualToString:@"768"]){
        [videoTextureRes selectItemWithTag:35];
        [customWidth setStringValue:@"2720"];
        [customHeight setStringValue:@"768"];
    }else if([_w isEqualToString:@"2800"] && [_h isEqualToString:@"1050"]){
        [videoTextureRes selectItemWithTag:36];
        [customWidth setStringValue:@"2800"];
        [customHeight setStringValue:@"1050"];
    }else if([_w isEqualToString:@"2880"] && [_h isEqualToString:@"900"]){
        [videoTextureRes selectItemWithTag:37];
        [customWidth setStringValue:@"2880"];
        [customHeight setStringValue:@"900"];
    }else if([_w isEqualToString:@"3200"] && [_h isEqualToString:@"900"]){
        [videoTextureRes selectItemWithTag:38];
        [customWidth setStringValue:@"3200"];
        [customHeight setStringValue:@"900"];
    }else if([_w isEqualToString:@"3200"] && [_h isEqualToString:@"1200"]){
        [videoTextureRes selectItemWithTag:39];
        [customWidth setStringValue:@"3200"];
        [customHeight setStringValue:@"1200"];
    }else if([_w isEqualToString:@"3360"] && [_h isEqualToString:@"1050"]){
        [videoTextureRes selectItemWithTag:40];
        [customWidth setStringValue:@"3360"];
        [customHeight setStringValue:@"1050"];
    }else if([_w isEqualToString:@"3840"] && [_h isEqualToString:@"1080"]){
        [videoTextureRes selectItemWithTag:41];
        [customWidth setStringValue:@"3840"];
        [customHeight setStringValue:@"1080"];
    }else if([_w isEqualToString:@"3840"] && [_h isEqualToString:@"1200"]){
        [videoTextureRes selectItemWithTag:42];
        [customWidth setStringValue:@"3840"];
        [customHeight setStringValue:@"1200"];
    }else if([_w isEqualToString:@"4096"] && [_h isEqualToString:@"1152"]){
        [videoTextureRes selectItemWithTag:43];
        [customWidth setStringValue:@"4096"];
        [customHeight setStringValue:@"1152"];
    }else if([_w isEqualToString:@"1920"] && [_h isEqualToString:@"480"]){
        [videoTextureRes selectItemWithTag:44];
        [customWidth setStringValue:@"1920"];
        [customHeight setStringValue:@"480"];
    }else if([_w isEqualToString:@"2400"] && [_h isEqualToString:@"480"]){
        [videoTextureRes selectItemWithTag:45];
        [customWidth setStringValue:@"2400"];
        [customHeight setStringValue:@"480"];
    }else if([_w isEqualToString:@"2400"] && [_h isEqualToString:@"600"]){
        [videoTextureRes selectItemWithTag:46];
        [customWidth setStringValue:@"2400"];
        [customHeight setStringValue:@"600"];
    }else if([_w isEqualToString:@"3072"] && [_h isEqualToString:@"768"]){
        [videoTextureRes selectItemWithTag:47];
        [customWidth setStringValue:@"1920"];
        [customHeight setStringValue:@"1080"];
    }else if([_w isEqualToString:@"3840"] && [_h isEqualToString:@"720"]){
        [videoTextureRes selectItemWithTag:48];
        [customWidth setStringValue:@"3840"];
        [customHeight setStringValue:@"720"];
    }else if([_w isEqualToString:@"3840"] && [_h isEqualToString:@"768"]){
        [videoTextureRes selectItemWithTag:49];
        [customWidth setStringValue:@"3840"];
        [customHeight setStringValue:@"768"];
    }else if([_w isEqualToString:@"3840"] && [_h isEqualToString:@"800"]){
        [videoTextureRes selectItemWithTag:50];
        [customWidth setStringValue:@"3840"];
        [customHeight setStringValue:@"800"];
    }else if([_w isEqualToString:@"3840"] && [_h isEqualToString:@"960"]){
        [videoTextureRes selectItemWithTag:51];
        [customWidth setStringValue:@"3840"];
        [customHeight setStringValue:@"960"];
    }else if([_w isEqualToString:@"3840"] && [_h isEqualToString:@"1024"]){
        [videoTextureRes selectItemWithTag:52];
        [customWidth setStringValue:@"3840"];
        [customHeight setStringValue:@"1024"];
    }else if([_w isEqualToString:@"4080"] && [_h isEqualToString:@"768"]){
        [videoTextureRes selectItemWithTag:53];
        [customWidth setStringValue:@"4080"];
        [customHeight setStringValue:@"768"];
    }else if([_w isEqualToString:@"4098"] && [_h isEqualToString:@"768"]){
        [videoTextureRes selectItemWithTag:54];
        [customWidth setStringValue:@"4098"];
        [customHeight setStringValue:@"768"];
    }else if([_w isEqualToString:@"4200"] && [_h isEqualToString:@"1050"]){
        [videoTextureRes selectItemWithTag:55];
        [customWidth setStringValue:@"4200"];
        [customHeight setStringValue:@"1050"];
    }else if([_w isEqualToString:@"4320"] && [_h isEqualToString:@"900"]){
        [videoTextureRes selectItemWithTag:56];
        [customWidth setStringValue:@"4320"];
        [customHeight setStringValue:@"900"];
    }else if([_w isEqualToString:@"4800"] && [_h isEqualToString:@"900"]){
        [videoTextureRes selectItemWithTag:57];
        [customWidth setStringValue:@"4800"];
        [customHeight setStringValue:@"900"];
    }else if([_w isEqualToString:@"5040"] && [_h isEqualToString:@"1050"]){
        [videoTextureRes selectItemWithTag:58];
        [customWidth setStringValue:@"5040"];
        [customHeight setStringValue:@"1050"];
    }else if([_w isEqualToString:@"5760"] && [_h isEqualToString:@"1080"]){
        [videoTextureRes selectItemWithTag:59];
        [customWidth setStringValue:@"5760"];
        [customHeight setStringValue:@"1080"];
    }
    
    [self reduceToAspectRatio];
    
}

- (IBAction) openPanelForSketch:(id)sender{
    NSString        *sketchbookLocation = [@"~/Documents/GAmuza" stringByExpandingTildeInPath];
    NSArray         *fileTypes = [[NSArray alloc] initWithObjects:@"ga", nil];
    
    // Custom Open Panel
    NSOpenPanel                 *oPan;
    oPan = [NSOpenPanel openPanel];
    [oPan setTitle:@"Choose a GAmuza Sketch"];
    [oPan setDirectoryURL:[NSURL fileURLWithPath:sketchbookLocation]];
    [oPan setAllowsOtherFileTypes:NO];
    [oPan setAllowsMultipleSelection:NO];
    [oPan setCanChooseDirectories:NO];
    [oPan setCanCreateDirectories:NO];
    [oPan setAllowedFileTypes:fileTypes];
    
    NSInteger tvarNSInteger	= [oPan runModal];
    
    if(tvarNSInteger == NSOKButton){
        [autoSketchFile setStringValue:[oPan filename]];
    }else{
        return;
    }
}

- (IBAction) openPanelForMapping:(id)sender{
    NSString        *sketchbookLocation = [@"~/Documents/GAmuza" stringByExpandingTildeInPath];
    NSArray         *fileTypes = [[NSArray alloc] initWithObjects:@"xml", @"XML", nil];
    
    // Custom Open Panel
    NSOpenPanel                 *oPan;
    oPan = [NSOpenPanel openPanel];
    [oPan setTitle:@"Choose a Mapping File"];
    [oPan setDirectoryURL:[NSURL fileURLWithPath:sketchbookLocation]];
    [oPan setAllowsOtherFileTypes:NO];
    [oPan setAllowsMultipleSelection:NO];
    [oPan setCanChooseDirectories:NO];
    [oPan setCanCreateDirectories:NO];
    [oPan setAllowedFileTypes:fileTypes];
    
    NSInteger tvarNSInteger	= [oPan runModal];
    
    if(tvarNSInteger == NSOKButton){
        [autoMappingFile setStringValue:[oPan filename]];
    }else{
        return;
    }
}

@end
