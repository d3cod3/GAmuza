//
//  GAColorPanel.h
//  ScriptEditor
//
//  Created by n3m3da on 31/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GAColorPanel : NSObject{
 
    // color wells
    IBOutlet NSColorWell *colorWell;
    IBOutlet NSColorWell *redWell, *greenWell, *blueWell, *hWell, *sWell, *bWell;
	// controls
    IBOutlet NSSlider *rSlider, *gSlider, *bSlider, *hSlider, *sSlider, *brighSlider;
    IBOutlet NSTextField *redField, *greenField, *blueField, *hField, *sField, *bField;
    
}

/* The Color Well */
-(void)     updateNumbers;


/* Color generation. */
-(IBAction) updateColorFromSlider:(id)sender;


/* Sliders */
-(BOOL)     sliderIsRGBSlider:(NSSlider *)theSlider;

@end
