//
//  GATextDocument.h
//  ScriptEditor
//
//  Created by n3m3da on 02/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "GAConstants.h"
#import "GATextView.h"

static BOOL			sSyntaxColoredTextDocPrefsInited = NO;

static NSMutableArray*		GASyntaxDefinitionFiles = NULL;	// Array of syntax definition file paths in NSStrings.
static NSMutableDictionary*	GASuffixToTagMappings = NULL;


@interface GATextDocument : NSDocument {
    
    IBOutlet GATextView             *textView;
    NSFont                          *viewFont;
    
    NSString*                       syntaxDefinitionFilename;
    NSString*						sourceCode;
    NSString*                       gaSourceCode; // Code buffer for sending to GAmuza GUI
    NSString*                       localStatus;
    NSTimer*						recolorTimer;
    NSRange							affectedCharRange;
    NSString*						replacementString;
    BOOL							autoSyntaxColoring;
    BOOL							syntaxColoringBusy;
    BOOL							maintainIndentation;
    
}

+ (void) makeSurePrefsAreInited;
- (void) resetNewDocument;

-(IBAction)	recolorCompleteFile: (id)sender;
-(IBAction) indentSelection: (id)sender;
-(IBAction) unindentSelection: (id)sender;

-(void)		goToLine: (unsigned int)lineNum inView:(NSTextView *)tv;
-(void)		goToCharacter: (unsigned int)charNum inView:(NSTextView *)tv;
-(void)		goToRangeFrom: (unsigned int)startCh toChar: (unsigned int)endCh inView:(NSTextView *)tv;
-(NSString*)		getLocalStatus;

// ---------------------------------------------------------------
// Override any of the following in one of your subclasses to customize this object further:
-(NSString*)		syntaxDefinitionFilename;   // Defaults to "SyntaxDefinition.plist" in the app bundle's "Resources" directory.
-(NSDictionary*)	syntaxDefinitionDictionary; // Defaults to loading from -syntaxDefinitionFilename.
-(NSDictionary*)	defaultTextAttributes;		// Style attributes dictionary for an NSAttributedString.

-(void)         addSyntaxFilesFromFolderToArray: (NSString*)fpath;

-(void) turnOffWrapping:(NSTextView *)tv;
-(void) recolorRange: (NSRange) range inView: (NSTextView *)tv;
-(void)	colorOneLineComment: (NSString*) startCh inString: (NSMutableAttributedString*) s
                  withColor: (NSColor*) col andMode:(NSString*)attr;
-(void)	colorCommentsFrom: (NSString*) startCh to: (NSString*) endCh inString: (NSMutableAttributedString*) s
				withColor: (NSColor*) col andMode:(NSString*)attr;
-(void)	colorIdentifier: (NSString*) ident inString: (NSMutableAttributedString*) s
              withColor: (NSColor*) col andMode:(NSString*)attr charset: (NSCharacterSet*)cset;
-(void)	colorStringsFrom: (NSString*) startCh to: (NSString*) endCh inString: (NSMutableAttributedString*) s
               withColor: (NSColor*) col andMode:(NSString*)attr andEscapeChar: (NSString*)vStringEscapeCharacter;

@end
