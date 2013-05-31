//
//  NSArray+Color.h
//  ScriptEditor
//
//  Created by n3m3da on 02/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSArray (Color)

+(NSArray*)		arrayWithColor: (NSColor*) col;
-(NSColor*)		colorValue;

@end
