//
//  NSScanner+SkipUpToCharset.m
//  ScriptEditor
//
//  Created by n3m3da on 02/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "NSScanner+SkipUpToCharset.h"


@implementation NSScanner (SkipUpToCharset)

-(BOOL) skipUpToCharactersFromSet:(NSCharacterSet*)set
{
	NSString*		vString = [self string];
	double				x = [self scanLocation];
	
	while( x < [vString length] )
	{
		if( ![set characterIsMember: [vString characterAtIndex: x]] )
			x++;
		else
			break;
	}
	
	if( x > [self scanLocation] )
	{
		[self setScanLocation: x];
		return YES;
	}
	else
		return NO;
}

@end
