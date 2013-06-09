//
//  GATextView.m
//  ScriptEditor
//
//  Created by n3m3da on 01/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GATextView.h"
#import "GATextViewContainer.h"

@implementation GATextView

- (id)initWithCoder:(NSCoder *)aDecoder;
{
	if (self = [super initWithCoder:aDecoder])
	{
		[self initLineMargin: [self frame]];
	}
    
    return self;
}

-(id)initWithFrame:(NSRect)frame
{
    if (self = [super initWithFrame:frame])
    {
		[self initLineMargin: frame];
    }
	
    return self;
}



- (void) initLineMargin:(NSRect) frame
{
	NSSize				contentSize;
	GATextViewContainer	*myContainer;
    
    [self loadCompletionDict];
    
    // create a subclass of NSTextContainer that specifies the textdraw area. 
    // This will allow for a left margin for numbering.
    
	contentSize = [[self enclosingScrollView] contentSize];
	frame = NSMakeRect(0, 0, contentSize.width, contentSize.height);
	myContainer = [[GATextViewContainer allocWithZone:[self zone]] 
                   initWithContainerSize:NSMakeSize(frame.size.width, 100000)];
    
	[myContainer setWidthTracksTextView:NO];
	[myContainer setHeightTracksTextView:NO];
    
    // This controls the inset of our text away from the margin.
	[myContainer setLineFragmentPadding:6];
    
	[self replaceTextContainer:myContainer];
	[myContainer release];
    
	[self setMinSize:frame.size];
	[self setMaxSize:NSMakeSize(100000, 100000)];
	
	[self setHorizontallyResizable:YES];
	[self setVerticallyResizable:YES];
	
	[self setAutoresizingMask:FLEX_WIDTH];
	[self setAllowsUndo:YES];
	
	//[self setFont:[NSFont fontWithName: @"Monaco" size:10.0]];
    
    // listen to updates from the window to force a redraw - eg when the window resizes.
    
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowDidUpdate:)
                                                 name:NSWindowDidUpdateNotification object:[self window]];
	
	marginAttributes = [[NSMutableDictionary alloc] init];
    
    [marginAttributes setObject:[NSFont boldSystemFontOfSize:9] forKey: NSFontAttributeName];
	[marginAttributes setObject:[NSColor darkGrayColor] forKey: NSForegroundColorAttributeName];
    
	drawNumbersInMargin = YES;
	drawLineNumbers = YES;
    
}

- (void)drawRect:(NSRect)aRect 
{
    [super drawRect:aRect];
    
    [self drawEmptyMargin: [self marginRect]];
    
    if ( drawNumbersInMargin )
    {
        [self drawNumbersInMargin: [self marginRect]];
    }
}


- (void)windowDidUpdate:(NSNotification *)notification
{
    [self updateMargin];
}

- (void)updateLayout
{
    [self updateMargin];
}


-(void)updateMargin
{
    [self setNeedsDisplayInRect:[self marginRect] avoidAdditionalLayout:NO];
}


-(NSRect)marginRect
{
    NSRect  r;
    
    r = [self bounds];
    r.size.width = left_margin_width;
    
    return r;
}

-(void)drawEmptyMargin:(NSRect)aRect
{
    /*
     These values control the color of our margin. Giving the rect the 'clear' 
     background color is accomplished using the windowBackgroundColor.  Change 
     the color here to anything you like to alter margin contents.
     */
    [[NSColor controlHighlightColor] set];
    //[[NSColor colorWithCalibratedRed:0.12 green:0.12 blue:0.12 alpha:1.0f] set];
    [NSBezierPath fillRect: aRect]; 
    
    // These points should be set to the left margin width.
    NSPoint top = NSMakePoint(aRect.size.width, [self bounds].size.height);
    NSPoint bottom = NSMakePoint(aRect.size.width, 0);
    
    // This draws the dark line separating the margin from the text area.
    [[NSColor grayColor] set];
    [NSBezierPath setDefaultLineWidth:0.75];
    [NSBezierPath strokeLineFromPoint:top toPoint:bottom];
}


-(void) drawNumbersInMargin:(NSRect)aRect;
{
	UInt64		index;
    UInt32      lineNumber;
	NSRange		lineRange;
	NSRect		lineRect;
    
	NSLayoutManager* layoutManager = [self layoutManager];
	NSTextContainer* textContainer = [self textContainer];
    
	// Only get the visible part of the scroller view
	NSRect documentVisibleRect = [[self enclosingScrollView] documentVisibleRect];
    
	// Find the glyph range for the visible glyphs
	NSRange glyphRange = [layoutManager glyphRangeForBoundingRect: documentVisibleRect inTextContainer: textContainer];
    
	// Calculate the start and end indexes for the glyphs	
	unsigned long start_index = glyphRange.location;
	unsigned long end_index = glyphRange.location + glyphRange.length;
    
	index = 0;
	lineNumber = 1;
    
	// Skip all lines that are visible at the top of the text view (if any)
	while (index < start_index)
	{
		lineRect = [layoutManager lineFragmentRectForGlyphAtIndex:index effectiveRange:&lineRange];
		index = NSMaxRange( lineRange );
		++lineNumber;
	}
    
	for ( index = start_index; index < end_index; lineNumber++ )
	{
		lineRect = [layoutManager lineFragmentRectForGlyphAtIndex:index effectiveRange:&lineRange];
		index = NSMaxRange( lineRange );
        
		if ( drawLineNumbers )
        {
            [self drawOneNumberInMargin:lineNumber inRect:lineRect];
        }
        else    // draw character numbers
        {
            [self drawOneNumberInMargin:(UInt32)index inRect:lineRect];
        }
    }
    
    if ( drawLineNumbers )
    {
        lineRect = [layoutManager extraLineFragmentRect];
        [self drawOneNumberInMargin:lineNumber inRect:lineRect];
    }
}


-(void)drawOneNumberInMargin:(unsigned) aNumber inRect:(NSRect)r{
    
    NSColor  *normalNumbersColor = [NSColor colorWithCalibratedRed:0.4 green:0.4 blue:0.4 alpha:1.0f];
    NSColor  *highlightNumbersColor = [NSColor colorWithCalibratedRed:0.6 green:0.2 blue:0.2 alpha:1.0f];
    
    NSString            *s;
    NSSize              stringSize;
    
    s = [NSString stringWithFormat:@"%d", aNumber, nil];
    stringSize = [s sizeWithAttributes:marginAttributes];
    
    // Simple algorithm to center the line number next to the glyph.
    if(aNumber%5 != 0){
        [marginAttributes setObject: normalNumbersColor forKey: NSForegroundColorAttributeName];
        [s drawAtPoint: NSMakePoint( r.origin.x - stringSize.width - 1, 
                                r.origin.y + ((r.size.height / 2) - (stringSize.height / 2))) 
        withAttributes:marginAttributes];
    }else{
        [marginAttributes setObject: highlightNumbersColor forKey: NSForegroundColorAttributeName];
        [s drawAtPoint: NSMakePoint( r.origin.x - stringSize.width - 1, 
                                    r.origin.y + ((r.size.height / 2) - (stringSize.height / 2))) 
        withAttributes:marginAttributes];
    }
}

//------------------------------------------------------------------------------
-(void)keyUp:(NSEvent *)event{
    /*int keyCode = [event.characters characterAtIndex:0];
    if(keyCode != 10 && keyCode != 13 && keyCode != 9 && keyCode != 127 && keyCode != NSLeftArrowFunctionKey && keyCode != NSRightArrowFunctionKey){
        [self complete:self];
    }*/
    [super keyUp:event];
}

-(void)insertCompletion:(NSString *)word forPartialWordRange:(NSRange)charRange movement:(NSInteger)movement isFinal:(BOOL)flag{
    // suppress completion if user types a space
    if (movement == NSRightTextMovement) return;
    
    [super insertCompletion:word forPartialWordRange:charRange movement:movement isFinal:flag];
    
}

- (NSArray*)completionsForPartialWordRange:(NSRange)charRange indexOfSelectedItem:(NSInteger*)index{
	if(completionDict != NULL){
        NSString*   finalQuery;
        NSString*   preQuery;
        NSString* queryStr = [(NSAttributedString *)[self attributedSubstringFromRange:charRange] string];
        if([queryStr rangeOfString:@":"].location != NSNotFound){
            preQuery = [[[queryStr componentsSeparatedByString:@":"] objectAtIndex:0] stringByAppendingString:@":"];
            finalQuery = [[queryStr componentsSeparatedByString:@":"] objectAtIndex:1];
        }else{
            finalQuery = queryStr;
        }
        
        NSSortDescriptor *sort = [NSSortDescriptor sortDescriptorWithKey:@"description" ascending:YES];
        NSArray *sortedArray = [[completionDict allObjects] sortedArrayUsingDescriptors:[NSArray arrayWithObject:sort]];
        // create an NSArray containing all object names which match the query
        NSMutableArray* completions;
        completions = [[NSMutableArray alloc] init];
        NSEnumerator * enumerator = [sortedArray objectEnumerator];
        NSString* element;
        while(element = (NSString*)[enumerator nextObject]){
            if([element hasPrefix: finalQuery]){
                if([queryStr rangeOfString:@":"].location != NSNotFound && [[element componentsSeparatedByString:@":"] count] > 1){
                    NSString* finalElement = [preQuery stringByAppendingString:[[element componentsSeparatedByString:@":"] objectAtIndex:1]];
                    [completions addObject: finalElement];
                }else{
                    [completions addObject: element];
                }
            }
        }
		return completions;
	}else{
		// no dict file, or failure - pass through to standard non-GA suggestions.
		return [super completionsForPartialWordRange: charRange indexOfSelectedItem: index];
	}
}

- (void) loadCompletionDict{
    completionDict = [[NSMutableSet alloc] init];
    
	NSString *path = [[NSBundle mainBundle] pathForResource:@"gaAutocompletion" ofType:@"txt"];
    NSString *contents = [NSString stringWithContentsOfFile:path encoding:NSASCIIStringEncoding error:nil];
    NSArray *lines = [contents componentsSeparatedByCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"\r\n"]];
    int i = 0;
    for (NSString* line in lines) {
        if(line.length) {
            [completionDict addObject:(NSString*)line];
        }
    }
}

//------------------------------------------------------------------------------
- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver: self];
    
    [marginAttributes release];
    
    [super dealloc];
}

@end
