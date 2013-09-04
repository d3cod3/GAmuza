//
//  GAmuzaDocument.m
//  GAmuza0424
//
//  Created by n3m3da on 14/05/13.
//
//

#import "GAMultiTextDocument.h"
#import "GASketchFile.h"

#include "gamuzaConstants.h"

@implementation GAMultiTextDocument

-(NSString*)    generateDateFileName: (NSInteger*)num isTab:(BOOL)it{
    
    NSString *s = [alphabet substringWithRange:NSMakeRange((NSInteger)num, 1)];
    NSDateFormatter *df = [[NSDateFormatter alloc] init];
    [df setDateFormat:@"dd"];
    NSString *myDayString = [NSString stringWithFormat:@"%@",[df stringFromDate:[NSDate date]]];
    [df setDateFormat:@"MM"];
    NSString *myMonthString = [NSString stringWithFormat:@"%@",[df stringFromDate:[NSDate date]]];
    [df setDateFormat:@"yy"];
    NSString *myYearString = [NSString stringWithFormat:@"%@",[df stringFromDate:[NSDate date]]];
    [df release];
    
    NSString*   tempName = @"";
    if(it){
        tempName = [NSString stringWithFormat:@"sketch_%@%@%@%@",myYearString,myMonthString,myDayString,s];
    }else{
        tempName = [NSString stringWithFormat:@"sketch_%@%@%@%@ | GAmuza %@",myYearString,myMonthString,myDayString,s,[NSString stringWithCString:GAMUZA_RELEASE encoding:[NSString defaultCStringEncoding]]];
    }
    
    return tempName;
}

-(id)	init{
    
    self = [super init];
    if( self ){
        // [NSFont userFixedPitchFontOfSize:10] - [NSFont fontWithName:@"Monaco" size:10]
        consoleFont = [NSFont userFixedPitchFontOfSize:10];
        aDocNum = (NSInteger*)[[[NSDocumentController sharedDocumentController] documents] count];
        alphabet  = @"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXZY";
        sketchFiles = [[NSMutableSet alloc] initWithCapacity:3];
        SFviewControllers = [[NSMutableSet alloc] initWithCapacity:3];
	}
    return self;
}

- (void)restoreDocumentWindowWithIdentifier:(NSString *)identifier state:(NSCoder *)state completionHandler:(void (^)(NSWindow *, NSError *))completionHandler{
    // customize initial windows restore
    [super restoreDocumentWindowWithIdentifier:identifier state:state completionHandler:completionHandler];
    
    GAMultiTextDocument *currentDoc = (GAMultiTextDocument*)[[NSDocumentController sharedDocumentController] currentDocument];
    NSString* directoryName = @"";
    if([[[currentDoc fileURL] absoluteString] rangeOfString:@"localhost"].location != NSNotFound){
        directoryName = [[[[[currentDoc fileURL] absoluteString] stringByDeletingPathExtension] substringFromIndex:15] stringByDeletingLastPathComponent];
    }else{
        directoryName = [[[[[currentDoc fileURL] absoluteString] stringByDeletingPathExtension] substringFromIndex:5] stringByDeletingLastPathComponent];
    }
    
    // add sketch files (if we have)
    NSArray                 *contents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:directoryName error:NULL];
    NSEnumerator            *enm = [contents objectEnumerator];
    NSString                *importFile;
    NSString                *mainFile = [[[[[NSDocumentController sharedDocumentController] currentDocument] fileURL] absoluteString] lastPathComponent];
    
    while ((importFile = [enm nextObject])){
        // eliminate from listing hidden files and .DS_Store files
        if([importFile hasPrefix:@"."] || [importFile rangeOfString:@".DS_Store"].location != NSNotFound){
            continue;
        }
        if ([[importFile pathExtension] isEqualToString:@"ga"] && [importFile isEqualToString:mainFile] == NO){
            NSString *actualFilePath = [NSString stringWithFormat:@"%@/%@", directoryName, importFile];
            NSString *fileContent = [[NSString alloc] initWithContentsOfFile:actualFilePath encoding:NSUTF8StringEncoding error:NULL];
            if (fileContent != nil) {
                GASketchFile* doc = [[GASketchFile alloc] init];
                [[[NSDocumentController sharedDocumentController] currentDocument] addDocument:doc withName:[importFile stringByDeletingPathExtension] andCode:fileContent];
            }
        }
    }
    
}

-(NSString*)	windowNibName{
    return @"GAMultiTextDocument";
}

- (NSString *)displayName {
    
    NSString *windowTitle = @" ";
    if([[self fileURL] absoluteString] != nil){
        NSString * tempFileName = [[[[self fileURL] absoluteString] lastPathComponent] stringByDeletingPathExtension];
        windowTitle = [NSString stringWithFormat:@"%@%@%@", tempFileName, @" | GAmuza ",[NSString stringWithCString:GAMUZA_RELEASE encoding:[NSString defaultCStringEncoding]]];
    }else{
        windowTitle = [self generateDateFileName:aDocNum isTab:FALSE];
    }
    
    return windowTitle;
}

-(void) dealloc{
    [super dealloc];
}

-(void) windowControllerDidLoadNib:(NSWindowController *)windowController{
	
	[super windowControllerDidLoadNib: windowController];
    
    ////////////////////////////////////////////////
    // init document interface
    [[newFileMenu cell] setUsesItemFromMenu:NO];
    [newFileView setHidden:TRUE];
    [newFileMenu setAutoenablesItems:NO];
    [[newFileMenu menu] setDelegate:self];
    
    [self addLogMsg:@" "];
    NSString *tempRelease = [NSString stringWithFormat:@" GAmuza %@ | Hybrid Live OF Sketching IDE",[NSString stringWithCString:GAMUZA_RELEASE encoding:[NSString defaultCStringEncoding]]];
    [self addLogMsg:tempRelease];
    
    ////////////////////////////////////////////////
    // custom buttons
    [sendToBut setLabel:@"Compile Script"];
    [sendToBut setButtonImages:[NSImage imageNamed:@"gotoG_out"] rollOver:[NSImage imageNamed:@"gotoG_over"]];
    
    [emptyBut setLabel:@"Clear Script"];
    [emptyBut setButtonImages:[NSImage imageNamed:@"empty_out"] rollOver:[NSImage imageNamed:@"empty_over"]];
    
    [newBut setLabel:@"New Script"];
    [newBut setButtonImages:[NSImage imageNamed:@"new_out"] rollOver:[NSImage imageNamed:@"new_over"]];
    
    [openBut setLabel:@"Open Script"];
    [openBut setButtonImages:[NSImage imageNamed:@"open_out"] rollOver:[NSImage imageNamed:@"open_over"]];
    
    [saveBut setLabel:@"Save Script As"];
    [saveBut setButtonImages:[NSImage imageNamed:@"save_out"] rollOver:[NSImage imageNamed:@"save_over"]];
    
    [cleanBut setLabel:@"Clear Console"];
    [cleanBut setButtonImages:[NSImage imageNamed:@"clean_out"] rollOver:[NSImage imageNamed:@"clean_over"]];
    
    [newFileBut setLabel:@" "];
    [newFileBut setButtonImages:[NSImage imageNamed:@"wm_out"] rollOver:[NSImage imageNamed:@"wm_over"]];
    
    [resizeBut setLabel:@" "];
    [resizeBut setButtonImages:[NSImage imageNamed:@"resize"] rollOver:[NSImage imageNamed:@"resize"]];
    
    ////////////////////////////////////////////////
    // Set up the tab controller
    NSString *tempFileName = @" ";
    if([[self fileURL] absoluteString] != nil){
        tempFileName = [[[[self fileURL] absoluteString] lastPathComponent] stringByDeletingPathExtension];
    }else{
        tempFileName = [self generateDateFileName:aDocNum isTab:TRUE];
    }
    
    [[tabView tabViewItemAtIndex:0] setLabel:tempFileName];
    [tabView selectTabViewItem: [tabView tabViewItemAtIndex:0]];
    
}

#pragma mark -
#pragma mark Manage/Sketch Files

-(void)setDocument:(GASketchFile *)document{
    NSLog(@"Will not set document to: %@",document);
}

-(void)addViewWithDocument:(GASketchFile *) document withName:(NSString*)fName {
    
    if ([document respondsToSelector:@selector(newPrimaryViewController)]) {
        NSViewController* addedCtrl = [(id)document newPrimaryViewController];
        [SFviewControllers addObject: addedCtrl];
        
        [document resetNewDocument];
        document.filename = fName;
        
        [self updateChangeCount:NSChangeDone];
        
        NSTabViewItem* tabViewItem = [[[NSTabViewItem alloc]initWithIdentifier: addedCtrl] autorelease];
        [tabViewItem setView: addedCtrl.view];
        [tabViewItem setLabel: fName];
        
        NSUInteger tabIndex = [tabView numberOfTabViewItems];
        [tabView insertTabViewItem:tabViewItem atIndex:tabIndex];
    }
}

-(void)addDocument:(GASketchFile *)docToAdd withName:(NSString*)fName{
    
    NSMutableSet* documents = sketchFiles;
    if ([documents containsObject:docToAdd]) {
        return;
    }
    
    [documents addObject:docToAdd];
    
    [self addViewWithDocument:docToAdd withName:fName];
}

-(void)addViewWithDocument:(GASketchFile *) document withName:(NSString*)fName andCode:(NSString*)code{
    
    if ([document respondsToSelector:@selector(newPrimaryViewController)]) {
        NSViewController* addedCtrl = [(id)document newPrimaryViewController];
        [SFviewControllers addObject: addedCtrl];
        
        [document resetNewDocument];
        document.filename = fName;
        [document setScriptContent:code];
        
        [self updateChangeCount:NSChangeDone];
        
        NSTabViewItem* tabViewItem = [[[NSTabViewItem alloc]initWithIdentifier: addedCtrl] autorelease];
        [tabViewItem setView: addedCtrl.view];
        [tabViewItem setLabel: fName];
        
        NSUInteger tabIndex = [tabView numberOfTabViewItems];
        [tabView insertTabViewItem:tabViewItem atIndex:tabIndex];
        
        
    }
}

-(void)addDocument:(GASketchFile *)docToAdd withName:(NSString*)fName andCode:(NSString*)code{
    
    NSMutableSet* documents = sketchFiles;
    if ([documents containsObject:docToAdd]) {
        return;
    }
    
    [documents addObject:docToAdd];
    
    [self addViewWithDocument:docToAdd withName:fName andCode:code];
}

-(void)removeDocument:(GASketchFile *)docToRemove attachedToViewController:(NSViewController*)ctrl{
    NSMutableSet* documents = sketchFiles;
    if (![documents containsObject:docToRemove]) {
        return;
    }
    
    // remove the document's view controller and view
    [ctrl.view removeFromSuperview];
    if ([ctrl respondsToSelector:@selector(setDocument:)]) {
        [(id)ctrl setDocument: nil];
    }
    [ctrl release];
    
    // remove the view from the tab item
    NSTabViewItem* tabViewItem = [tabView tabViewItemAtIndex: [tabView indexOfTabViewItemWithIdentifier: ctrl]];
    [tabView removeTabViewItem:tabViewItem];
    [tabViewItem setView: nil];
    
    // remove the control from the view controllers set
    [SFviewControllers removeObject: ctrl];
    
    // Delete file.
    NSString *directoryPath = [[NSDocumentController sharedDocumentController] currentDirectory];
    for (NSString *filename in [[NSFileManager defaultManager] contentsOfDirectoryAtPath:directoryPath error:NULL]) {
        if ([[filename stringByDeletingPathExtension] isEqualToString:docToRemove.filename]) {
            NSString *fullPath = [directoryPath stringByAppendingPathComponent:filename];
            //NSLog(@"%@",fullPath);
            [[NSFileManager defaultManager] removeItemAtPath:fullPath error:NULL];
            break;
        }
    }
    
    [documents removeObject:docToRemove];
    [self updateChangeCount:NSChangeDone];
    
}


#pragma mark -
#pragma mark New Tab Menu

-(void) menuWillOpen:(NSMenu *) menu {
    if(menu == [newFileMenu menu]){
        [self checkingWhichTab];
    }
}

//------------------------------------------------------------------------------
-(void)	checkingWhichTab{
    if([[tabView selectedTabViewItem] isEqualTo:[tabView tabViewItemAtIndex:0]]){
        [[newFileMenu itemAtIndex:1] setEnabled:YES];
        [[newFileMenu itemAtIndex:2] setEnabled:NO];
        [[newFileMenu itemAtIndex:3] setEnabled:NO];
    }else{
        [[newFileMenu itemAtIndex:1] setEnabled:YES];
        [[newFileMenu itemAtIndex:2] setEnabled:YES];
        [[newFileMenu itemAtIndex:3] setEnabled:YES];
    }
}

//------------------------------------------------------------------------------
-(void)saveGAFile:(GASketchFile*) document withName:(NSString *)fName{
    
    NSString * urlName = [NSString stringWithFormat:@"%@/%@.ga",
                          [[NSDocumentController sharedDocumentController] currentDirectory], fName];
    // save sketch file
    NSData *data = [document.fileCode dataUsingEncoding:NSUTF8StringEncoding];
    [data writeToFile:urlName atomically:YES];
    
}

-(IBAction)	addNewFile: (id)sender{
    [newFileView setHidden:FALSE];
    isNewFile = TRUE;
    addFileTextField.stringValue = @"untitled";
}

-(IBAction)	cancelAddNewFile: (id)sender{
    [newFileView setHidden:TRUE];
    addFileTextField.stringValue = @"";
}

-(IBAction)	saveNewFile: (id)sender{
    [newFileView setHidden:TRUE];
    
    NSString *filename = [addFileTextField stringValue];
    if(isNewFile){
        if(filename.length > 0) {
            GASketchFile* doc = [[GASketchFile alloc] init];
            [self addDocument:doc withName:filename];
            // saving
            [self saveGAFile:doc withName:filename];
            // update tabs
            [tabView selectTabViewItem: [tabView tabViewItemAtIndex:[tabView numberOfTabViewItems]-1]];
        }
    }else{
        NSString *oldFilename = [[tabView selectedTabViewItem] label];
        if(filename.length > 0) {
            NSString *newPath = [NSString stringWithFormat:@"%@/%@.ga",[[NSDocumentController sharedDocumentController] currentDirectory],filename];
            NSString *oldPath = [NSString stringWithFormat:@"%@/%@.ga",[[NSDocumentController sharedDocumentController] currentDirectory],oldFilename];
            [[NSFileManager defaultManager] movePath:oldPath toPath:newPath handler:nil];
            // update tabs
            [[tabView selectedTabViewItem] setLabel:[addFileTextField stringValue]];
            // update internal document
            NSMutableSet* _temp = sketchFiles;
            NSArray* groupsArray = [_temp allObjects];
            for(GASketchFile* document in groupsArray){
                if([document.filename isEqualToString:oldFilename]){
                    document.filename = filename;
                    break;
                }
            }
            
        }
    }
    addFileTextField.stringValue = @"";
}

-(IBAction)	renameCurrentFile: (id)sender{
    [newFileView setHidden:FALSE];
    isNewFile = FALSE;
    [addFileTextField setStringValue:[[tabView selectedTabViewItem] label]];
    [addFileTextField selectText:self];
}

-(IBAction)	deleteCurrentFile: (id)sender{
    // delete it
    NSViewController* ctrl = (NSViewController*)[[tabView selectedTabViewItem] identifier];
    if ([ctrl respondsToSelector:@selector(document)]) {
        GASketchFile* doc = [(id) ctrl document];
        [self removeDocument:doc attachedToViewController:ctrl];
    }
}

-(IBAction) openGADocument:(id)sender{
    NSString        *sketchbookLocation = [@"~/Documents/GAmuza" stringByExpandingTildeInPath];
    
    // Custom Open Panel
    NSOpenPanel                 *oPan;
    oPan = [NSOpenPanel openPanel];
    [oPan setTitle:@"Open a GAmuza Sketch"];
    [oPan setDirectoryURL:[NSURL fileURLWithPath:sketchbookLocation]];
    [oPan setAllowsOtherFileTypes:NO];
    [oPan setCanCreateDirectories:NO];
    
    NSInteger tvarNSInteger	= [oPan runModalForTypes:nil];
    
    if(tvarNSInteger == NSOKButton){
        NSString * tvarFilename = [NSString stringWithFormat:@"%@%@", @"file:", [oPan filename]];
        NSURL *url = [NSURL URLWithString:tvarFilename];
        
        // add GAmuza document
        [[NSDocumentController sharedDocumentController] openDocumentWithContentsOfURL:url display:YES error:nil];
        
        NSString* directoryName = [[oPan directory] lastPathComponent];
        if ([ [[[oPan filename] lastPathComponent] stringByDeletingPathExtension] isEqualToString:directoryName]) {
            // add sketch files (if we have)
            NSArray                 *contents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:[oPan directory] error:NULL];
            NSEnumerator            *enm = [contents objectEnumerator];
            NSString                *importFile;
            NSString                *mainFile = [[oPan filename] lastPathComponent];
            
            while ((importFile = [enm nextObject])){
                // eliminate from listing hidden files and .DS_Store files
                if([importFile hasPrefix:@"."] || [importFile rangeOfString:@".DS_Store"].location != NSNotFound){
                    continue;
                }
                if ([[importFile pathExtension] isEqualToString:@"ga"] && [importFile isEqualToString:mainFile] == NO){
                    NSString *actualFilePath = [NSString stringWithFormat:@"%@/%@", [oPan directory], importFile];
                    NSString *fileContent = [[NSString alloc] initWithContentsOfFile:actualFilePath encoding:NSUTF8StringEncoding error:NULL];
                    if (fileContent != nil) {
                        GASketchFile* doc = [[GASketchFile alloc] init];
                        [[[NSDocumentController sharedDocumentController] currentDocument] addDocument:doc withName:[importFile stringByDeletingPathExtension] andCode:fileContent];
                    }
                }
            }
        }
        
    }else{
        return;
    }
}

-(IBAction) saveGAAll:(id)sender{
    if([self fileURL] != NULL){
        // save Main File
        [self saveToURL:[self fileURL] ofType:@"GAmuza Source Code" forSaveOperation:NSSaveOperation error:nil];
    
        // Save the other sketch files (if any)
        NSMutableSet* _temp = sketchFiles;
        NSArray* groupsArray = [_temp allObjects];
        for(GASketchFile* document in groupsArray){
            [self saveGAFile:document withName:document.filename];
        }
    }else{
        [self saveGADocument:sender];
    }
}

-(IBAction) saveGADocument:(id)sender{
    
    NSArray         *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString        *sketchbookLocation = [NSString stringWithFormat:@"%@/%@/", [paths objectAtIndex:0], @"GAmuza"];
    
    // Custom Save Panel
    NSSavePanel                 *sPan;
    
    sPan = [NSSavePanel savePanel];
    [sPan setTitle:@"Save GAmuza Sketch As"];
    [sPan setDirectoryURL:[NSURL fileURLWithPath:sketchbookLocation]];
    [sPan setAllowsOtherFileTypes:NO];
    [sPan setCanCreateDirectories:YES];
    
    long tvar = [sPan runModalForDirectory:[[[[self fileURL] absoluteString] lastPathComponent] stringByDeletingPathExtension]
                                      file:[[[[self fileURL] absoluteString] lastPathComponent] stringByDeletingPathExtension]];
    
    if(tvar == NSOKButton){
        NSFileManager               *filemgr;
        filemgr = [NSFileManager defaultManager];
        
        NSString * fName = [[sPan filename] lastPathComponent];
        
     	NSString * newDirName = [NSString stringWithFormat:@"%@", [[sPan filename] stringByDeletingPathExtension]];
        NSString * urlName = [NSString stringWithFormat:@"%@/%@.ga", newDirName, fName];
        
        NSURL *temp = [NSURL fileURLWithPath:urlName];
        
        // create new script directory
        [filemgr createDirectoryAtPath: newDirName withIntermediateDirectories:YES attributes: nil error:nil];
        // create data folder
        [filemgr createDirectoryAtPath: [NSString stringWithFormat:@"%@%@", newDirName, @"/data"] withIntermediateDirectories:YES attributes: nil error:nil];
        
        // save script inside created directory
        [self saveToURL:temp ofType:@"GAmuza Source Code" forSaveOperation:NSSaveAsOperation error:nil];
        // Save the other sketch files (if any)
        NSMutableSet* _temp = sketchFiles;
        NSArray* groupsArray = [_temp allObjects];
        for(GASketchFile* document in groupsArray){
            [self saveGAFile:document withName:document.filename];
        }
        
        [[tabView tabViewItemAtIndex:0] setLabel:[[[sPan filename] lastPathComponent] stringByDeletingPathExtension]];
        
        [filemgr release];
        
    }else{
        return;
    }
    
    // After saving recolor script
    [self recolorCompleteFile:nil];
    
}

#pragma mark -
#pragma mark Manage Console Logs

-(IBAction)clearLog:(id)sender {
    [console setEditable:YES];
    [console setString:@""];
    [console setEditable:NO];
}

//------------------------------------------------------------------------------
- (void)addLogMsg:(NSString *)msg attributes:(NSDictionary *)attrs {
    NSTextStorage *storage = [console textStorage];
    NSString *wrapped = [NSString stringWithFormat:@"%@\n", msg];
    NSAttributedString *attrStr = [[NSAttributedString alloc] initWithString:wrapped attributes:attrs];
    
    [console setEditable:YES];
    [storage beginEditing];
    [storage appendAttributedString:attrStr];
    
    [storage endEditing];
    [attrStr release];
    [console setEditable:NO];
    
    unsigned long len = [storage length];
    
    if (len > 0)
        [console scrollRangeToVisible:NSMakeRange(len - 1, 1)];
}

//------------------------------------------------------------------------------
- (void)addErrorMsg:(NSString *)msg {
    NSDictionary *attrs = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor colorWithDeviceRed:1 green:0.2 blue:0.2 alpha:1.0], NSForegroundColorAttributeName, consoleFont, NSFontAttributeName, nil];
    
    [self addLogMsg:msg attributes:attrs];
}

//------------------------------------------------------------------------------
- (void)addLogMsg:(NSString *)msg {
    NSDictionary *attrs = [NSDictionary dictionaryWithObjectsAndKeys:[NSColor colorWithDeviceRed:1 green:1 blue:1 alpha:1.0], NSForegroundColorAttributeName, consoleFont, NSFontAttributeName, nil];
    [self addLogMsg:msg attributes:attrs];
}

// ----------------------------------------------------------------

-(NSString*) sendToGAmuza{
    // send source code to LUA engine
    gaSourceCode = @"";
    
    NSMutableSet* _temp = sketchFiles;
    NSArray* groupsArray = [_temp allObjects];
    for(GASketchFile* document in groupsArray){
        gaSourceCode = [gaSourceCode stringByAppendingString:@"\n\n"];
        gaSourceCode = [gaSourceCode stringByAppendingString:document.fileCode];
    }
    
    if([[[textView textStorage] string] isEqualToString:@""]){
        gaSourceCode = @"function draw() gaBackground(0.0,1.0) end";
    }else{
        gaSourceCode = [gaSourceCode stringByAppendingString:@"\n\n"];
        gaSourceCode = [gaSourceCode stringByAppendingString:[[textView textStorage] string]];
    }
    
    return gaSourceCode;
    
}

@end
