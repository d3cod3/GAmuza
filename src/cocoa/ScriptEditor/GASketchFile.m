//
//  GASketchFile.m
//  GAmuza
//
//  Created by n3m3da on 16/05/13.
//
//

#import "GASketchFile.h"
#import "NSArray+Color.h"
#import "NSScanner+SkipUpToCharset.h"


@implementation GASketchFile
@synthesize filename, fileCode, textView;

-(NSArray*) syntaxDefinitionFiles
{
	if( !GASketchSyntaxDefinitionFiles )
	{
		GASketchSyntaxDefinitionFiles = [[NSMutableArray alloc] init];
		GASketchSuffixToTagMappings = [[NSMutableDictionary alloc] init];
        
		// Load from folder in app bundle:
		NSString* fpath = [[NSBundle mainBundle] pathForResource: @"Syntax Definitions" ofType: @""];
		[self addSyntaxFilesFromFolderToArray: fpath];
		
	}
	
	return GASketchSyntaxDefinitionFiles;
}

-(void) addSyntaxFilesFromFolderToArray: (NSString*)fpath
{
	NSDirectoryEnumerator*  enny = [[NSFileManager defaultManager] enumeratorAtPath: fpath];
	NSString*				currPath = nil;
	NSString*				currName = nil;
	
	while( (currName = [enny nextObject]) )
	{
		if( [currName characterAtIndex: 0] == '.' )
			continue;
		
		currPath = [fpath stringByAppendingPathComponent: currName];
		[GASketchSyntaxDefinitionFiles addObject: currPath];
	}
}

- (id)init{
    self = [super init];
    if (self) {
        sourceCode = nil;
        gaSourceCode = nil;
        localStatus = nil;
		autoSyntaxColoring = YES;
		maintainIndentation = YES;
		recolorTimer = nil;
		syntaxColoringBusy = NO;
        filename = @"";
        fileCode = @"";
        syntaxDefinitionFilename = [[[self syntaxDefinitionFiles] objectAtIndex: 0] retain];
    }
    return self;
}

-(void) dealloc{
    [syntaxDefinitionFilename release];
    syntaxDefinitionFilename = nil;
	[super dealloc];
}

-(NSViewController *)newPrimaryViewController{
    ctrl = [[GASketchFileViewController alloc] initWithNibName:@"SketchView" bundle:nil];
    ctrl.document = self;
    view = [ctrl view];
    textView = ctrl.tV;
    return ctrl;
}

- (NSString *)windowNibName{
    assert(false);
    return @"";
}

+(void) makeSurePrefsAreInited{
	if( !sketchSyntaxColoredTextDocPrefsInited ){
        
		NSUserDefaults*	prefs = [NSUserDefaults standardUserDefaults];
		[prefs registerDefaults: [NSDictionary dictionaryWithContentsOfFile: [[NSBundle mainBundle] pathForResource: @"SyntaxColorDefaults" ofType: @"plist"]]];
        
		sketchSyntaxColoredTextDocPrefsInited = YES;
	}
}

-(void) resetNewDocument{
    
    // Set up some sensible defaults for syntax coloring:
	[[self class] makeSurePrefsAreInited];
    
    if( sourceCode != nil ){
        [sourceCode release];
        sourceCode = nil;
    }
	
	// Register for "text changed" notifications of our text storage:
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(processEditing:) name: NSTextStorageDidProcessEditingNotification object: [textView textStorage]];
	
	[textView setSelectedRange: NSMakeRange(0,0)];
	// Make sure text isn't wrapped:
	[self turnOffWrapping:textView];
    
	// Do initial syntax coloring of our file:
	[self recolorCompleteFile:nil];
	
}

- (void) setScriptContent: (NSString*)code{
    [textView setString:code];
}


-(NSData*)	dataRepresentationOfType: (NSString*)aType{
    return [[textView string] dataUsingEncoding: NSUTF8StringEncoding allowLossyConversion:YES];
}

-(BOOL)	loadDataRepresentation: (NSData*)data ofType: (NSString*)aType
{
	// sourceCode is a member variable:
	if( sourceCode )
	{
		[sourceCode release];   // Release any old text.
		sourceCode = nil;
	}
	sourceCode = [[NSString alloc] initWithData:data encoding: NSMacOSRomanStringEncoding]; // Load the new text.
	
	/* Try to load it into textView and syntax colorize it:
     Since this may be called before the NIB has been loaded, we keep around
     sourceCode as a data member and try these two calls again in windowControllerDidLoadNib: */
	[textView setString: sourceCode];
	[self recolorCompleteFile:nil];
    
	// Try to get selection info if possible:
	NSAppleEventDescriptor*  evt = [[NSAppleEventManager sharedAppleEventManager] currentAppleEvent];
	if( evt )
	{
		NSAppleEventDescriptor*  param = [evt paramDescriptorForKeyword: keyAEPosition];
		if( param )		// This is always false when xCode calls us???
		{
			NSData*					data = [param data];
			struct SelectionRange   range;
			
			memmove( &range, [data bytes], sizeof(range) );
			
		}
	}
	
	return YES;
}

/* -----------------------------------------------------------------------------
 processEditing:
 Part of the text was changed. Recolor it.
 -------------------------------------------------------------------------- */

-(void) processEditing: (NSNotification*)notification{
    
    NSTextStorage	*textStorage = [notification object];
	NSRange			range = [textStorage editedRange];
	double				changeInLen = [textStorage changeInLength];
	BOOL			wasInUndoRedo = [[self undoManager] isUndoing] || [[self undoManager] isRedoing];
	BOOL			textLengthMayHaveChanged = NO;
	
	// Was delete op or undo that could have changed text length?
	if( wasInUndoRedo )
	{
		textLengthMayHaveChanged = YES;
		range = [textView selectedRange];
	}
	if( changeInLen <= 0 )
		textLengthMayHaveChanged = YES;
	
	//	Try to get chars around this to recolor any identifier we're in:
	if( textLengthMayHaveChanged )
	{
		if( range.location > 0 )
			range.location--;
		if( (range.location +range.length +2) < [textStorage length] )
			range.length += 2;
		else if( (range.location +range.length +1) < [textStorage length] )
			range.length += 1;
	}
	
	NSRange						currRange = range;
    
	// Perform the syntax coloring:
	if( autoSyntaxColoring && range.length > 0 )
	{
		NSRange			effectiveRange;
		NSString*		rangeMode;
		
		
		rangeMode = [textStorage attribute: GA_SYNTAX_COLORING_MODE_ATTR
                                   atIndex: currRange.location
                            effectiveRange: &effectiveRange];
		
		unsigned long		x = range.location;
		
		
		// Scan up to prev line break:
		while( x > 0 )
		{
			unichar theCh = [[textStorage string] characterAtIndex: x];
			if( theCh == '\n' || theCh == '\r' )
				break;
			--x;
		}
		
		currRange.location = x;
		
		// Scan up to next line break:
		x = range.location +range.length;
		
		while( x < [textStorage length] )
		{
			unichar theCh = [[textStorage string] characterAtIndex: x];
			if( theCh == '\n' || theCh == '\r' )
				break;
			++x;
		}
		
		currRange.length = x -currRange.location;
		
		// Open identifier, comment etc.? Make sure we include the whole range.
		if( rangeMode != nil )
			currRange = NSUnionRange( currRange, effectiveRange );
		
		// Actually recolor the changed part:
		[self recolorRange: currRange inStorage:textStorage];
        
        fileCode = [textStorage string];
        
	}
    
}


/* -----------------------------------------------------------------------------
 textView:shouldChangeTextinRange:replacementString:
 Perform indentation-maintaining if we're supposed to.
 -------------------------------------------------------------------------- */

-(BOOL) textView:(NSTextView *)tv shouldChangeTextInRange:(NSRange)afcr replacementString:(NSString *)rps{
    
	if( maintainIndentation )
	{
		affectedCharRange = afcr;
		if( replacementString )
		{
			[replacementString release];
			replacementString = nil;
		}
		replacementString = [rps retain];
		
		[self performSelector: @selector(didChangeText) withObject: nil afterDelay: 0.0];
	}
	
	return YES;
}


-(void)	didChangeText{
    
	if( maintainIndentation && replacementString && ([replacementString isEqualToString:@"\n"]
                                                     || [replacementString isEqualToString:@"\r"]) )
	{
		NSMutableAttributedString*  textStore = [textView textStorage];
		BOOL						hadSpaces = NO;
		unsigned long				lastSpace = affectedCharRange.location,prevLineBreak = 0;
        
		NSRange						spacesRange = { 0, 0 };
		unichar						theChar = 0;
		unsigned long				x = (affectedCharRange.location == 0) ? 0 : affectedCharRange.location -1;
		NSString*					tsString = [textStore string];
		
		while( true )
		{
			if( x > ([tsString length] -1) )
				break;
			
			theChar = [tsString characterAtIndex: x];
			
			switch( theChar )
			{
				case '\n':
				case '\r':
					prevLineBreak = x +1;
					x = 0;  // Terminate the loop.
					break;
                    
				case ' ':
				case '\t':
					if( !hadSpaces )
					{
						lastSpace = x;
						hadSpaces = YES;
					}
					break;
                    
				default:
					hadSpaces = NO;
					break;
			}
			
			if( x == 0 )
				break;
			
			x--;
		}
		
		if( hadSpaces )
		{
			spacesRange.location = prevLineBreak;
			spacesRange.length = lastSpace -prevLineBreak +1;
			if( spacesRange.length > 0 )
				[textView insertText: [tsString substringWithRange:spacesRange]];
		}
	}
}

/* -----------------------------------------------------------------------------
 goToLine:
 This selects the specified line of the document.
 -------------------------------------------------------------------------- */

-(void)	goToLine: (unsigned int)lineNum inView:(NSTextView *)tv{
    
	NSRange			theRange = { 0, 0 };
	NSString*		vString = [tv string];
	unsigned		currLine = 1;
	NSCharacterSet* vSet = [NSCharacterSet characterSetWithCharactersInString: @"\n\r"];
	unsigned		x;
	unsigned		lastBreakOffs = 0;
	unichar			lastBreakChar = 0;
	
	for( x = 0; x < [vString length]; x++ )
	{
		unichar		theCh = [vString characterAtIndex: x];
		
		// Skip non-linebreak chars:
		if( ![vSet characterIsMember: theCh] )
			continue;
		
		// If this is the LF in a CRLF sequence, only count it as one line break:
		if( theCh == '\n' && lastBreakOffs == (x-1)
           && lastBreakChar == '\r' )
		{
			lastBreakOffs = 0;
			lastBreakChar = 0;
			theRange.location++;
			continue;
		}
		
		// Calc range and increase line number:
		theRange.length = x -theRange.location +1;
		if( currLine >= lineNum )
			break;
		currLine++;
		theRange.location = theRange.location +theRange.length;
		lastBreakOffs = x;
		lastBreakChar = theCh;
	}
    localStatus = [NSString stringWithFormat: @"Characters %u to %u", theRange.location +1, theRange.location +theRange.length];
	
	[tv scrollRangeToVisible: theRange];
	[tv setSelectedRange: theRange];
}

/* -----------------------------------------------------------------------------
 turnOffWrapping:
 Makes the view so wide that text won't wrap anymore.
 -------------------------------------------------------------------------- */

-(void) turnOffWrapping:(NSTextView *)tv{
    
	const double			LargeNumberForText = 1.0e7;
	NSTextContainer*	textContainer = [tv textContainer];
	NSRect				frame;
	NSScrollView*		scrollView = [tv enclosingScrollView];
	
	// Make sure we can see right edge of line:
    [scrollView setHasHorizontalScroller:NO];
	
	// Make text container so wide it won't wrap:
	[textContainer setContainerSize: NSMakeSize(LargeNumberForText, LargeNumberForText)];
	[textContainer setWidthTracksTextView:YES];
    [textContainer setHeightTracksTextView:NO];
    
	// Make sure text view is wide enough:
	frame.origin = NSMakePoint(0.0, 0.0);
    frame.size = [scrollView contentSize];
	
    [tv setMaxSize:NSMakeSize(LargeNumberForText, LargeNumberForText)];
    [tv setHorizontallyResizable:YES];
    [tv setVerticallyResizable:YES];
    [tv setAutoresizingMask:NSViewNotSizable];
    [tv setAllowsUndo:YES];
    
}

-(void)	goToCharacter: (unsigned int)charNum inView:(NSTextView *)tv{
	[self goToRangeFrom: charNum toChar: charNum +1 inView:tv];
}


-(void) goToRangeFrom: (unsigned int)startCh toChar: (unsigned int)endCh inView:(NSTextView *)tv{
    
	NSRange		theRange = { 0, 0 };
    
	theRange.location = startCh -1;
	theRange.length = endCh -startCh;
	
	if( startCh == 0 || startCh > [[tv string] length] )
		return;
	
	localStatus =  [NSString stringWithFormat: @"Characters %u to %u",theRange.location +1, theRange.location +theRange.length];
	[tv scrollRangeToVisible: theRange];
	[tv setSelectedRange: theRange];
}

-(NSString*) getLocalStatus{
    return localStatus;
}

-(IBAction) indentSelection: (id)sender{
    
	[[self undoManager] registerUndoWithTarget: self selector: @selector(unindentSelection:) object: nil];
	
	NSRange				selRange = [textView selectedRange],
    nuSelRange = selRange;
	unsigned long			x;
	NSMutableString*	str = [[textView textStorage] mutableString];
	
	// Unselect any trailing returns so we don't indent the next line after a full-line selection.
	if( selRange.length > 1 && ([str characterAtIndex: selRange.location +selRange.length -1] == '\n'
                                || [str characterAtIndex: selRange.location +selRange.length -1] == '\r') )
		selRange.length--;
	
	for( x = selRange.location +selRange.length -1; x >= selRange.location; x-- )
	{
		if( [str characterAtIndex: x] == '\n'
           || [str characterAtIndex: x] == '\r' )
		{
			[str insertString: @"\t" atIndex: x+1];
			nuSelRange.length++;
		}
		
		if( x == 0 )
			break;
	}
	
	[str insertString: @"\t" atIndex: nuSelRange.location];
	nuSelRange.length++;
	[textView setSelectedRange: nuSelRange];
}


-(IBAction) unindentSelection: (id)sender{
    
	NSRange				selRange = [textView selectedRange],
    nuSelRange = selRange;
	unsigned long			x, n;
	unsigned long			lastIndex = selRange.location +selRange.length -1;
	NSMutableString*	str = [[textView textStorage] mutableString];
	
	// Unselect any trailing returns so we don't indent the next line after a full-line selection.
	if( selRange.length > 1 && ([str characterAtIndex: selRange.location +selRange.length -1] == '\n'
                                || [str characterAtIndex: selRange.location +selRange.length -1] == '\r') )
		selRange.length--;
	
	if( selRange.length == 0 )
		return;
	
	[[self undoManager] registerUndoWithTarget: self selector: @selector(indentSelection:) object: nil];
	
	for( x = lastIndex; x >= selRange.location; x-- )
	{
		if( [str characterAtIndex: x] == '\n'
           || [str characterAtIndex: x] == '\r' )
		{
			if( (x +1) <= lastIndex)
			{
				if( [str characterAtIndex: x+1] == '\t' )
				{
					[str deleteCharactersInRange: NSMakeRange(x+1,1)];
					nuSelRange.length--;
				}
				else
				{
					for( n = x+1; (n <= (x+4)) && (n <= lastIndex); n++ )
					{
						if( [str characterAtIndex: x+1] != ' ' )
							break;
						[str deleteCharactersInRange: NSMakeRange(x+1,1)];
						nuSelRange.length--;
					}
				}
			}
		}
		
		if( x == 0 )
			break;
	}
	
	if( [str characterAtIndex: nuSelRange.location] == '\t' )
	{
		[str deleteCharactersInRange: NSMakeRange(nuSelRange.location,1)];
		nuSelRange.length--;
	}
	else
	{
		for( n = 1; (n <= 4) && (n <= lastIndex); n++ )
		{
			if( [str characterAtIndex: nuSelRange.location] != ' ' )
				break;
			[str deleteCharactersInRange: NSMakeRange(nuSelRange.location,1)];
			nuSelRange.length--;
		}
	}
	
	[textView setSelectedRange: nuSelRange];
}


/* -----------------------------------------------------------------------------
 recolorCompleteFile:
 IBAction to do a complete recolor of the whole friggin' document.
 This is called once after the document's been loaded and leaves some
 custom styles in the document which are used by recolorRange to properly
 perform recoloring of parts.
 -------------------------------------------------------------------------- */

-(IBAction)	recolorCompleteFile: (id)sender{
	NSRange		range = NSMakeRange(0,[[textView textStorage] length]);
    [self recolorRange: range inStorage:[textView textStorage]];
}


-(void) recolorRange: (NSRange) range inStorage:(NSTextStorage*)tS{
    
	if( syntaxColoringBusy ){	// Prevent endless loop when recoloring's replacement of text causes processEditing to fire again.
		return;
    }
    
	if( tS == nil || range.length == 0 || recolorTimer ){
		return;
    }
	
	// Kludge fix for case where we sometimes exceed text length:range
	double diff = [tS length] -(range.location +range.length);
	if( diff < 0 )
		range.length += diff;
	
	NS_DURING
    syntaxColoringBusy = YES;
    
    
    
    // Get the text we'll be working with:
    //NSRange						vOldSelection = [textView selectedRange];
    NSMutableAttributedString*	vString = [[NSMutableAttributedString alloc] initWithString: [[tS string] substringWithRange: range]];
    [vString autorelease];
    
    // Load colors and fonts to use from preferences:
    
    // Load our dictionary which contains info on coloring this language:
    NSDictionary*				vSyntaxDefinition = [self syntaxDefinitionDictionary];
    NSEnumerator*				vComponentsEnny = [[vSyntaxDefinition objectForKey: @"Components"] objectEnumerator];
    
    if( vComponentsEnny == nil )	// No new-style list of components to colorize? Use old code.
    {
        NS_VOIDRETURN;
    }
    
    // Loop over all available components:
    NSDictionary*				vCurrComponent = nil;
    NSDictionary*				vStyles = [self defaultTextAttributes];
    NSUserDefaults*				vPrefs = [NSUserDefaults standardUserDefaults];
    
    while( (vCurrComponent = [vComponentsEnny nextObject]) )
    {
        NSString*   vComponentType = [vCurrComponent objectForKey: @"Type"];
        NSString*   vComponentName = [vCurrComponent objectForKey: @"Name"];
        NSString*   vColorKeyName = [@"SyntaxColoring:Color:" stringByAppendingString: vComponentName];
        NSColor*	vColor = [[vPrefs arrayForKey: vColorKeyName] colorValue];
        
        if( !vColor )
            vColor = [[vCurrComponent objectForKey: @"Color"] colorValue];
        
        if( [vComponentType isEqualToString: @"BlockComment"] )
        {
            [self colorCommentsFrom: [vCurrComponent objectForKey: @"Start"]
                                 to: [vCurrComponent objectForKey: @"End"] inString: vString
                          withColor: vColor andMode: vComponentName];
        }
        else if( [vComponentType isEqualToString: @"OneLineComment"] )
        {
            [self colorOneLineComment: [vCurrComponent objectForKey: @"Start"]
                             inString: vString withColor: vColor andMode: vComponentName];
        }
        
        else if( [vComponentType isEqualToString: @"Constants"] )
        {
            NSArray* vIdents = [vCurrComponent objectForKey: @"Keywords"];
            if( !vIdents )
                vIdents = [[NSUserDefaults standardUserDefaults] objectForKey: [@"SyntaxColoring:Keywords:" stringByAppendingString: vComponentName]];
            if( vIdents )
            {
                NSCharacterSet*		vIdentCharset = nil;
                NSString*			vCurrIdent = nil;
                NSString*			vCsStr = [vCurrComponent objectForKey: @"Charset"];
                if( vCsStr )
                    vIdentCharset = [NSCharacterSet characterSetWithCharactersInString: vCsStr];
                
                NSEnumerator*	vItty = [vIdents objectEnumerator];
                while( vCurrIdent = [vItty nextObject] )
                    [self colorIdentifier: vCurrIdent inString: vString withColor: vColor
                                  andMode: vComponentName charset: vIdentCharset];
            }
        }
        else if( [vComponentType isEqualToString: @"Keywords"] )
        {
            NSArray* vIdents = [vCurrComponent objectForKey: @"Keywords"];
            if( !vIdents )
                vIdents = [[NSUserDefaults standardUserDefaults] objectForKey: [@"SyntaxColoring:Keywords:" stringByAppendingString: vComponentName]];
            if( vIdents )
            {
                NSCharacterSet*		vIdentCharset = nil;
                NSString*			vCurrIdent = nil;
                NSString*			vCsStr = [vCurrComponent objectForKey: @"Charset"];
                if( vCsStr )
                    vIdentCharset = [NSCharacterSet characterSetWithCharactersInString: vCsStr];
                
                NSEnumerator*	vItty = [vIdents objectEnumerator];
                while( vCurrIdent = [vItty nextObject] )
                    [self colorIdentifier: vCurrIdent inString: vString withColor: vColor
                                  andMode: vComponentName charset: vIdentCharset];
            }
        }
        // Strings
        else if( [vComponentType isEqualToString: @"String"] )
        {
            [self colorStringsFrom: [vCurrComponent objectForKey: @"Start"]
                                to: [vCurrComponent objectForKey: @"End"]
                          inString: vString withColor: vColor andMode: vComponentName
                     andEscapeChar: [vCurrComponent objectForKey: @"EscapeChar"]];
        }
        
        if( [vComponentType isEqualToString: @"BlockComment"] )
        {
            [self colorCommentsFrom: [vCurrComponent objectForKey: @"Start"]
                                 to: [vCurrComponent objectForKey: @"End"] inString: vString
                          withColor: vColor andMode: vComponentName];
        }
        else if( [vComponentType isEqualToString: @"OneLineComment"] )
        {
            [self colorOneLineComment: [vCurrComponent objectForKey: @"Start"]
                             inString: vString withColor: vColor andMode: vComponentName];
        }
    }
    
    // Replace the range with our recolored part:
    [vString addAttributes: vStyles range: NSMakeRange( 0, [vString length] )];
    [tS replaceCharactersInRange: range withAttributedString: vString];
    
    syntaxColoringBusy = NO;
	NS_HANDLER
    syntaxColoringBusy = NO;
    [localException raise];
	NS_ENDHANDLER
    
}

/* -----------------------------------------------------------------------------
 textView:willChangeSelectionFromCharacterRange:toCharacterRange:
 Delegate method called when our selection changes. Updates our status
 display to indicate which characters are selected.
 -------------------------------------------------------------------------- */

-(NSRange)  textView: (NSTextView*)theTextView willChangeSelectionFromCharacterRange: (NSRange)oldSelectedCharRange
    toCharacterRange:(NSRange)newSelectedCharRange
{
	unsigned long		startCh = newSelectedCharRange.location +1,
    endCh = newSelectedCharRange.location +newSelectedCharRange.length;
	unsigned long		lineNo = 1,
    lastLineStart = 0,
    x;
	unsigned long		startChLine, endChLine;
	unichar			lastBreakChar = 0;
	unsigned long		lastBreakOffs = 0;
    
	// Calc line number:
	for( x = 0; (x < startCh) && (x < [[theTextView string] length]); x++ )
	{
		unichar		theCh = [[theTextView string] characterAtIndex: x];
		switch( theCh )
		{
			case '\n':
				if( lastBreakOffs == (x-1) && lastBreakChar == '\r' )   // LF in CRLF sequence? Treat this as a single line break.
				{
					lastBreakOffs = 0;
					lastBreakChar = 0;
					continue;
				}
				// Else fall through!
				
			case '\r':
				lineNo++;
				lastLineStart = x +1;
				lastBreakOffs = x;
				lastBreakChar = theCh;
				break;
		}
	}
	
	startChLine = (newSelectedCharRange.location -lastLineStart) +1;
	endChLine = (newSelectedCharRange.location -lastLineStart) +newSelectedCharRange.length;
	
	
	// Display info:
	if( startCh > endCh )   // Insertion mark!
	{
		localStatus =  [NSString stringWithFormat: @"char %u, line %u (char %u in document)", startChLine, lineNo, startCh];
	}
	else					// Selection
	{
        localStatus =  [NSString stringWithFormat: @"char %u to %u, line %u (char %u to %u in document)", startChLine, endChLine, lineNo, startCh, endCh];
	}
	
	return newSelectedCharRange;
}


/* -----------------------------------------------------------------------------
 colorStringsFrom:
 Apply syntax coloring to all strings. This is basically the same code
 as used for multi-line comments, except that it ignores the end
 character if it is preceded by a backslash.
 -------------------------------------------------------------------------- */

-(void)	colorStringsFrom: (NSString*) startCh to: (NSString*) endCh inString: (NSMutableAttributedString*) s
               withColor: (NSColor*) col andMode:(NSString*)attr andEscapeChar: (NSString*)vStringEscapeCharacter
{
	NS_DURING
    NSScanner*					vScanner = [NSScanner scannerWithString: [s string]];
    NSDictionary*				vStyles = [NSDictionary dictionaryWithObjectsAndKeys:
                                           col, NSForegroundColorAttributeName,
                                           attr, GA_SYNTAX_COLORING_MODE_ATTR,
                                           nil];
    BOOL						vIsEndChar = NO;
    unichar						vEscChar = '\\';
    
    if( vStringEscapeCharacter )
    {
        if( [vStringEscapeCharacter length] != 0 )
            vEscChar = [vStringEscapeCharacter characterAtIndex: 0];
    }
    
    while( ![vScanner isAtEnd] )
    {
        double		vStartOffs,
        vEndOffs;
        vIsEndChar = NO;
        
        // Look for start of string:
        [vScanner scanUpToString: startCh intoString: nil];
        vStartOffs = [vScanner scanLocation];
        if( ![vScanner scanString:startCh intoString:nil] )
            NS_VOIDRETURN;
        
        while( !vIsEndChar && ![vScanner isAtEnd] )	// Loop until we find end-of-string marker or our text to color is finished:
        {
            [vScanner scanUpToString: endCh intoString: nil];
            if( ([vStringEscapeCharacter length] == 0) || [[s string] characterAtIndex: ([vScanner scanLocation] -1)] != vEscChar )	// Backslash before the end marker? That means ignore the end marker.
                vIsEndChar = YES;	// A real one! Terminate loop.
            if( ![vScanner scanString:endCh intoString:nil] )	// But skip this char before that.
                NS_VOIDRETURN;
            
        }
        
        vEndOffs = [vScanner scanLocation];
        
        // Now mess with the string's styles:
        [s setAttributes: vStyles range: NSMakeRange( vStartOffs, vEndOffs -vStartOffs )];
    }
	NS_HANDLER
    // Just ignore it, syntax coloring isn't that important.
	NS_ENDHANDLER
}


/* -----------------------------------------------------------------------------
 colorCommentsFrom:
 Colorize block-comments in the text view.
 
 REVISIONS:
 2004-05-18  witness Documented.
 -------------------------------------------------------------------------- */

-(void)	colorCommentsFrom: (NSString*) startCh to: (NSString*) endCh inString: (NSMutableAttributedString*) s
                withColor: (NSColor*) col andMode:(NSString*)attr
{
	NS_DURING
    NSScanner*					vScanner = [NSScanner scannerWithString: [s string]];
    NSDictionary*				vStyles = [NSDictionary dictionaryWithObjectsAndKeys:
                                           col, NSForegroundColorAttributeName,
                                           attr, GA_SYNTAX_COLORING_MODE_ATTR,
                                           nil];
    
    while( ![vScanner isAtEnd] )
    {
        double		vStartOffs,
        vEndOffs;
        
        // Look for start of multi-line comment:
        [vScanner scanUpToString: startCh intoString: nil];
        vStartOffs = [vScanner scanLocation];
        if( ![vScanner scanString:startCh intoString:nil] )
            NS_VOIDRETURN;
        
        // Look for associated end-of-comment marker:
        [vScanner scanUpToString: endCh intoString: nil];
        if( ![vScanner scanString:endCh intoString:nil] ){
            /*NS_VOIDRETURN*/;  // Don't exit. If user forgot trailing marker, indicate this by "bleeding" until end of string.
        }
        vEndOffs = [vScanner scanLocation];
        
        // Now mess with the string's styles:
        [s setAttributes: vStyles range: NSMakeRange( vStartOffs, vEndOffs -vStartOffs )];
        
    }
	NS_HANDLER
    // Just ignore it, syntax coloring isn't that important.
	NS_ENDHANDLER
}


/* -----------------------------------------------------------------------------
 colorOneLineComment:
 Colorize one-line-comments in the text view.
 
 REVISIONS:
 2004-05-18  witness Documented.
 -------------------------------------------------------------------------- */

-(void)	colorOneLineComment: (NSString*) startCh inString: (NSMutableAttributedString*) s
                  withColor: (NSColor*) col andMode:(NSString*)attr
{
	NS_DURING
    NSScanner*					vScanner = [NSScanner scannerWithString: [s string]];
    NSDictionary*				vStyles = [NSDictionary dictionaryWithObjectsAndKeys:
                                           col, NSForegroundColorAttributeName,
                                           attr, GA_SYNTAX_COLORING_MODE_ATTR,
                                           nil];
    
    unichar						vStartChar = ':';
    
    while( ![vScanner isAtEnd] )
    {
        double		vStartOffs,
        vEndOffs;
        
        // Look for start of one-line comment:
        [vScanner scanUpToString: startCh intoString: nil];
        vStartOffs = [vScanner scanLocation];
        if( ![vScanner scanString:startCh intoString:nil]) //   || [[s string] characterAtIndex: (vStartOffs -1)] == vStartChar
            NS_VOIDRETURN;
        
        // Look for associated line break:
        if( ![vScanner skipUpToCharactersFromSet:[NSCharacterSet characterSetWithCharactersInString: @"\n\r"]] ){
            
        }
        
        vEndOffs = [vScanner scanLocation];
        
        // Now mess with the string's styles:
        [s setAttributes: vStyles range: NSMakeRange( vStartOffs, vEndOffs -vStartOffs )];
        
    }
	NS_HANDLER
    // Just ignore it, syntax coloring isn't that important.
	NS_ENDHANDLER
}


/* -----------------------------------------------------------------------------
 colorIdentifier:
 Colorize keywords in the text view.
 
 REVISIONS:
 2004-05-18  witness Documented.
 -------------------------------------------------------------------------- */

-(void)	colorIdentifier: (NSString*) ident inString: (NSMutableAttributedString*) s
              withColor: (NSColor*) col andMode:(NSString*)attr charset: (NSCharacterSet*)cset
{
	NS_DURING
    NSScanner*					vScanner = [NSScanner scannerWithString: [s string]];
    NSDictionary*				vStyles = [NSDictionary dictionaryWithObjectsAndKeys:
                                           col, NSForegroundColorAttributeName,
                                           attr, GA_SYNTAX_COLORING_MODE_ATTR,
                                           nil];
    double							vStartOffs = 0;
    
    // Skip any leading whitespace chars, somehow NSScanner doesn't do that:
    if( cset )
    {
        while( vStartOffs < [[s string] length] )
        {
            if( [cset characterIsMember: [[s string] characterAtIndex: vStartOffs]] )
                break;
            vStartOffs++;
        }
    }
    
    [vScanner setScanLocation: vStartOffs];
    
    while( ![vScanner isAtEnd] )
    {
        // Look for start of identifier:
        [vScanner scanUpToString: ident intoString: nil];
        vStartOffs = [vScanner scanLocation];
        if( ![vScanner scanString:ident intoString:nil] )
            NS_VOIDRETURN;
        
        if( vStartOffs > 0 )	// Check that we're not in the middle of an identifier:
        {
            // Alphanum character before identifier start?
            if( [cset characterIsMember: [[s string] characterAtIndex: (vStartOffs -1)]] )  // If charset is NIL, this evaluates to NO.
                continue;
        }
        
        if( (vStartOffs +[ident length] +1) < [s length] )
        {
            // Alphanum character following our identifier?
            if( [cset characterIsMember: [[s string] characterAtIndex: (vStartOffs +[ident length])]] )  // If charset is NIL, this evaluates to NO.
                continue;
        }
        
        // Now mess with the string's styles:
        if([ident isEqualToString:[[s string] substringWithRange:NSMakeRange(vStartOffs,[ident length])]]){
            [s setAttributes: vStyles range: NSMakeRange( vStartOffs, [ident length] )];
        }
        
    }
    
	NS_HANDLER
    // Just ignore it, syntax coloring isn't that important.
	NS_ENDHANDLER
}


/* -----------------------------------------------------------------------------
 defaultTextAttributes:
 Return the text attributes to use for the text in our text view.
 
 REVISIONS:
 2004-05-18  witness Documented.
 -------------------------------------------------------------------------- */

-(NSDictionary*)	defaultTextAttributes{
	//return [NSDictionary dictionaryWithObject: [NSFont fontWithName:@"Monaco" size:11] forKey: NSFontAttributeName];
    return [NSDictionary dictionaryWithObject: [NSFont userFixedPitchFontOfSize:10.0] forKey: NSFontAttributeName];
}

// ----------------------------------------------------------------

-(NSDictionary*)	syntaxDefinitionDictionary
{
	NSString*   synDefName = [self syntaxDefinitionFilename];
	return [NSDictionary dictionaryWithContentsOfFile: synDefName];
}

-(NSString*)	syntaxDefinitionFilename
{
    return [[syntaxDefinitionFilename retain] autorelease];
}

@end
