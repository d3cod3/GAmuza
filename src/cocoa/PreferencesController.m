//
//  PreferencesController.m
//  GAmuza
//
//  Created by n3m3da on 10/06/13.
//
//

#import "PreferencesController.h"

@implementation PreferencesController

- (void)awakeFromNib{
    [customWidth setDelegate:self];
    [customHeight setDelegate:self];
}

- (void)controlTextDidChange:(NSNotification *)notification{
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
    NSMutableArray* item = [[NSMutableArray alloc] initWithCapacity:1];
    
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
    
    
    itemArray = [root nodesForXPath:@"//host_port" error:nil];
    for(NSXMLElement* xmlElement in itemArray){
        [receivingAtPORT setStringValue:[xmlElement stringValue]];
    }
    
    [xmlDoc release];
    [item release];
    
    [mainPanel makeKeyAndOrderFront:mainPanel];
    
}

- (IBAction) saveDataToXml:(id)sender{
    
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

- (IBAction) setOutputRes:(id)sender{
    
}

- (void) getCaptureRes:(NSString*)_w height:(NSString*)_h{
    
}

- (IBAction) setCaptureRes:(id)sender{
    
}

- (IBAction) closePreferences:(id)sender{
    [mainPanel orderOut:mainPanel];
}

@end
