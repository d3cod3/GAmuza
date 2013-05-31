//
//  GAButton.h
//  ScriptEditor
//
//  Created by n3m3da on 10/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface GAButton : NSButton
{
    NSTrackingArea      *trackingArea;
    NSImage             *outImage;
    NSImage             *onImage;
    NSString            *butLabel;
    
    IBOutlet NSTextField*			buttonStatus;
}

- (void)setLabel: (NSString*)lab;
- (void)setButtonImages: (NSImage*)outImg rollOver: (NSImage*)onImg;

@end
