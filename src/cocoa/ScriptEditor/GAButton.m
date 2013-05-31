//
//  GAButton.m
//  ScriptEditor
//
//  Created by n3m3da on 10/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GAButton.h"

@implementation GAButton

//------------------------------------------------------------------------------
- (void)updateTrackingAreas
{
	[super updateTrackingAreas];
	
	if (trackingArea)
	{
		[self removeTrackingArea:trackingArea];
		[trackingArea release];
	}
	
	NSTrackingAreaOptions options = NSTrackingInVisibleRect | NSTrackingMouseEnteredAndExited | NSTrackingActiveInKeyWindow;
	trackingArea = [[NSTrackingArea alloc] initWithRect:NSZeroRect options:options owner:self userInfo:nil];
	[self addTrackingArea:trackingArea];
}

//------------------------------------------------------------------------------
- (void)setLabel: (NSString*)lab{
    butLabel = lab;
    [buttonStatus setStringValue:@""];
}

//------------------------------------------------------------------------------
- (void)setButtonImages: (NSImage*)outImg rollOver: (NSImage*)onImg{
    outImage = outImg;
    onImage = onImg;
}

//------------------------------------------------------------------------------
- (void)mouseEntered:(NSEvent *)theEvent{
    [buttonStatus setStringValue:butLabel];
    [self setImage:onImage];
    
}

//------------------------------------------------------------------------------
- (void)mouseExited:(NSEvent *)theEvent{
    [buttonStatus setStringValue:@" "];
    [self setImage:outImage];
    
}

@end
