//
//  GAColorPanel.m
//  ScriptEditor
//
//  Created by n3m3da on 31/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GAColorPanel.h"

@implementation GAColorPanel

-(void)updateNumbers{
    
    NSColor *wColor = [colorWell color];
    
    float redFloat = (float)wColor.redComponent * 25500;
	float greenFloat = (float)wColor.greenComponent * 25500;
	float blueFloat = (float)wColor.blueComponent * 25500;
    
    float hFloat = (float)wColor.hueComponent * 25500;
	float sFloat = (float)wColor.saturationComponent * 25500;
	float bFloat = (float)wColor.brightnessComponent * 25500;
    
    int redInt = redFloat / 100;
	int greenInt = greenFloat / 100;
	int blueInt = blueFloat / 100;
    
    int hInt = hFloat / 100;
	int sInt = sFloat / 100;
	int bInt = bFloat / 100;
    
    [redField setStringValue: [NSString stringWithFormat: @"%d", redInt]];
    [greenField setStringValue: [NSString stringWithFormat: @"%d", greenInt]];
    [blueField setStringValue: [NSString stringWithFormat: @"%d", blueInt]];
    
    [hField setStringValue: [NSString stringWithFormat: @"%d", hInt]];
    [sField setStringValue: [NSString stringWithFormat: @"%d", sInt]];
    [bField setStringValue: [NSString stringWithFormat: @"%d", bInt]];
    
}


-(IBAction)updateColorFromSlider:(id)sender {
    
    NSColor *aColor;
    
    if ([self sliderIsRGBSlider:sender]) {
        
        aColor = [NSColor colorWithCalibratedRed:rSlider.floatValue green:gSlider.floatValue blue:bSlider.floatValue alpha:1.0];
        
        hSlider.floatValue = (float)aColor.hueComponent;
        sSlider.floatValue = (float)aColor.saturationComponent;
        brighSlider.floatValue = (float)aColor.brightnessComponent;
        
    }else{
        aColor = [NSColor colorWithCalibratedHue:hSlider.floatValue+0.001 saturation:sSlider.floatValue+0.001 brightness:brighSlider.floatValue+0.001 alpha:1.0];
        
        rSlider.floatValue = (float)aColor.redComponent;
        gSlider.floatValue = (float)aColor.greenComponent;    
        bSlider.floatValue = (float)aColor.blueComponent;
    }
    
    [redWell setColor:[NSColor colorWithCalibratedRed:rSlider.floatValue green:0.0 blue:0.0 alpha:1.0]];
    [greenWell setColor:[NSColor colorWithCalibratedRed:0.0 green:gSlider.floatValue blue:0.0 alpha:1.0]];
    [blueWell setColor:[NSColor colorWithCalibratedRed:0.0 green:0.0 blue:bSlider.floatValue alpha:1.0]];
    
    [hWell setColor:[NSColor colorWithCalibratedHue:hSlider.floatValue saturation:1.0 brightness:1.0 alpha:1.0]];
    [sWell setColor:[NSColor colorWithCalibratedHue:hSlider.floatValue saturation:sSlider.floatValue brightness:1.0 alpha:1.0]];
    [bWell setColor:[NSColor colorWithCalibratedHue:hSlider.floatValue saturation:1.0 brightness:brighSlider.floatValue alpha:1.0]];
    
    [colorWell setColor:aColor];
    [self updateNumbers];
    
}

-(BOOL)sliderIsRGBSlider:(id)theSlider {
    
    if (theSlider == rSlider) {
        return YES;
    } else if (theSlider == gSlider) {
        return YES;
        
    } else if (theSlider == bSlider) {
        return YES;
        
    } else {
        return NO;
    }
    
    
}

@end
