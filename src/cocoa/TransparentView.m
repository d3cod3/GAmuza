//
//  TransparentView.m
//  GAmuza0424
//
//  Created by n3m3da on 06/05/13.
//
//

#import "TransparentView.h"

@implementation TransparentView

@synthesize _splashImg;

- (void)awakeFromNib {
    // Load the images from the bundle's Resources directory
    self._splashImg = [NSImage imageNamed:@"gamuza04_splash"];
}

- (void)dealloc {
    [_splashImg release];
    [super dealloc];
}

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    // Clear the drawing rect.
    [[NSColor clearColor] set];
    NSRectFill([self frame]);
    
    // Draw the splash image
    [_splashImg compositeToPoint:NSZeroPoint operation:NSCompositeSourceOver];
}

@end
