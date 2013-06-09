//
//  GATextView.h
//  ScriptEditor
//
//  Created by n3m3da on 01/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "GAConstants.h"

@interface GATextView : NSTextView{
    
    // script lines lateral numbering
    BOOL                    drawNumbersInMargin;
    BOOL                    drawLineNumbers;
    NSMutableDictionary     *marginAttributes;
    // Auto completion
    NSMutableSet            *completionDict;
    
}

//------------------------------------------------------------------------------
// Public
//------------------------------------------------------------------------------
// script lines lateral numbering
-(void)initLineMargin:(NSRect)frame;

-(void)updateMargin;
-(void)updateLayout;

-(void)drawEmptyMargin:(NSRect)aRect;
-(void)drawNumbersInMargin:(NSRect)aRect;
-(void)drawOneNumberInMargin:(unsigned) aNumber inRect:(NSRect)aRect;

-(NSRect)marginRect;

// Auto completion
-(void)insertCompletion:(NSString *)word forPartialWordRange:(NSRange)charRange movement:(NSInteger)movement isFinal:(BOOL)flag;
-(NSArray*)completionsForPartialWordRange:(NSRange)charRange indexOfSelectedItem:(NSInteger*)index;
-(void)loadCompletionDict;

@end

struct SelectionRange{
	short   unused1;	// 0 (not used)
	short   lineNum;	// line to select (< 0 to specify range)
	short	startRange; // start of selection range (if line < 0)
	short	endRange;   // end of selection range (if line < 0)
	long	unused2;	// 0 (not used)
	long	theDate;	// modification date/time
};
