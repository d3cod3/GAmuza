//
//  GASketchFile.h
//  GAmuza
//
//  Created by n3m3da on 16/05/13.
//
//

#import <Cocoa/Cocoa.h>

#import "GASketchFileViewController.h"
#import "GATextView.h"
#import "GAConstants.h"

static BOOL			sketchSyntaxColoredTextDocPrefsInited = NO;

static NSMutableArray*		GASketchSyntaxDefinitionFiles = NULL;	// Array of syntax definition file paths in NSStrings.
static NSMutableDictionary*	GASketchSuffixToTagMappings = NULL;

@interface GASketchFile : NSDocument{
    
    IBOutlet GATextView             *textView;
    IBOutlet NSView                 *view;
    
    GASketchFileViewController      *ctrl;
    
    NSString*                       syntaxDefinitionFilename;
    NSString*						sourceCode;
    NSString*                       gaSourceCode;
    NSString*                       localStatus;
    NSTimer*						recolorTimer;
    NSRange							affectedCharRange;
    NSString*						replacementString;
    BOOL							autoSyntaxColoring;
    BOOL							syntaxColoringBusy;
    BOOL							maintainIndentation;
    
    NSString*                       filename;
    NSString*                       fileCode;
    
}

@property (nonatomic,assign) NSString     *filename;
@property (nonatomic,assign) NSString     *fileCode;
@property (nonatomic,assign) GATextView   *textView;


-(NSViewController *)newPrimaryViewController;

+ (void) makeSurePrefsAreInited;
- (void) resetNewDocument;
- (void) setScriptContent: (NSString*)code;

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
-(void) recolorRange: (NSRange) range inStorage:(NSTextStorage*)tS;

-(void)	colorOneLineComment: (NSString*) startCh inString: (NSMutableAttributedString*) s
                  withColor: (NSColor*) col andMode:(NSString*)attr;
-(void)	colorCommentsFrom: (NSString*) startCh to: (NSString*) endCh inString: (NSMutableAttributedString*) s
				withColor: (NSColor*) col andMode:(NSString*)attr;
-(void)	colorIdentifier: (NSString*) ident inString: (NSMutableAttributedString*) s
              withColor: (NSColor*) col andMode:(NSString*)attr charset: (NSCharacterSet*)cset;
-(void)	colorStringsFrom: (NSString*) startCh to: (NSString*) endCh inString: (NSMutableAttributedString*) s
               withColor: (NSColor*) col andMode:(NSString*)attr andEscapeChar: (NSString*)vStringEscapeCharacter;

@end
