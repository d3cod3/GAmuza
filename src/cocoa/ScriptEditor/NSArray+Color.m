//
//  NSArray+Color.m
//  ScriptEditor
//
//  Created by n3m3da on 02/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "NSArray+Color.h"

@implementation NSArray (Color)

+(NSArray*)		arrayWithColor: (NSColor*) col
{
	CGFloat			fRed, fGreen, fBlue, fAlpha;
	
	col = [col colorUsingColorSpaceName: NSCalibratedRGBColorSpace];
	[col getRed: &fRed green: &fGreen blue: &fBlue alpha: &fAlpha];
	
	return [self arrayWithObjects: [NSNumber numberWithFloat:(float)fRed], [NSNumber numberWithFloat:(float)fGreen],
            [NSNumber numberWithFloat:(float)fBlue], [NSNumber numberWithFloat:(float)fAlpha], nil];
}

-(NSColor*)		colorValue
{
	double			fRed, fGreen, fBlue, fAlpha = 1.0;
	
	fRed = [[self objectAtIndex:0] floatValue];
	fGreen = [[self objectAtIndex:1] floatValue];
	fBlue = [[self objectAtIndex:2] floatValue];
	if( [self count] > 3 )	// Have alpha info?
		fAlpha = [[self objectAtIndex:3] floatValue];
	
	return [NSColor colorWithCalibratedRed: fRed green: fGreen blue: fBlue alpha: fAlpha];
}

@end
