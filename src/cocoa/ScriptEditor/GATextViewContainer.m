//
//  GATextViewContainer.m
//  ScriptEditor
//
//  Created by n3m3da on 01/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GATextViewContainer.h"

@implementation GATextViewContainer

- (NSRect)lineFragmentRectForProposedRect:(NSRect)proposedRect 
                           sweepDirection:(NSLineSweepDirection)sweepDirection 
                        movementDirection:(NSLineMovementDirection)movementDirection 
                            remainingRect:(NSRect *)remainingRect
{
    proposedRect.origin.x = left_margin_width;
    
    return [super lineFragmentRectForProposedRect:proposedRect sweepDirection:sweepDirection
                                movementDirection:movementDirection remainingRect:remainingRect];
}

@end
