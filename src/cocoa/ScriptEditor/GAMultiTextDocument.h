//
//  GAmuzaDocument.h
//  GAmuza0424
//
//  Created by n3m3da on 14/05/13.
//
//

#import <Cocoa/Cocoa.h>
#import <BWToolkitFramework/BWToolkitFramework.h>

#import "GATextDocument.h"
#import "GASketchFile.h"
#import "GAButton.h"
#import "PSMTabBarControl.h"

@class PSMTabBarControl;

@interface GAMultiTextDocument : GATextDocument <NSMenuDelegate> {
    
    NSMutableSet            * sketchFiles;
    NSMutableSet            * SFviewControllers;
    
    NSInteger               *aDocNum;
    NSString                *alphabet;
    BOOL                    isNewFile;
    NSFont                  *consoleFont;
    
    IBOutlet NSTabView              *tabView;
    IBOutlet PSMTabBarControl       *tabBar;
    
    IBOutlet NSView                 *newFileView;
    IBOutlet NSTextField            *addFileTextField;
    IBOutlet NSPopUpButton          *newFileMenu;
    
    IBOutlet GAButton               *sendToBut;
    IBOutlet GAButton               *emptyBut;
    IBOutlet GAButton               *newBut;
    IBOutlet GAButton               *openBut;
    IBOutlet GAButton               *saveBut;
    IBOutlet GAButton               *cleanBut;
    IBOutlet GAButton               *newFileBut;
    IBOutlet GAButton               *resizeBut;
    
    IBOutlet NSTextView             *console;
    IBOutlet NSTextField            *status;
    
    
    
}

- (void)restoreDocumentWindowWithIdentifier:(NSString *)identifier state:(NSCoder *)state completionHandler:(void (^)(NSWindow *, NSError *))completionHandler NS_AVAILABLE_MAC(10_7);

// ---------------------------------------------------------------
-(void)addViewWithDocument:(GASketchFile*) document withName:(NSString*)fName;
-(void)addDocument:(GASketchFile *)docToAdd withName:(NSString*)fName;
-(void)addViewWithDocument:(GASketchFile*) document withName:(NSString*)fName andCode:(NSString*)code;
-(void)addDocument:(GASketchFile *)docToAdd withName:(NSString*)fName andCode:(NSString*)code;
-(void)removeDocument:(GASketchFile *)docToRemove attachedToViewController:(NSViewController*)ctrl;

-(void)saveGAFile:(GASketchFile*) document withName:(NSString *)fName;

// ---------------------------------------------------------------

-(IBAction)	addNewFile: (id)sender;
-(IBAction)	cancelAddNewFile: (id)sender;
-(IBAction)	saveNewFile: (id)sender;
-(IBAction)	renameCurrentFile: (id)sender;
-(IBAction)	deleteCurrentFile: (id)sender;

// ---------------------------------------------------------------

-(IBAction) clearLog:(id)sender;

-(IBAction) openGADocument:(id)sender;
-(IBAction) saveGADocument:(id)sender;
-(IBAction) saveGAAll:(id)sender;

// ---------------------------------------------------------------

-(NSString*)    generateDateFileName: (NSInteger*)num isTab:(BOOL)it;
-(NSString*)    sendToGAmuza;

-(void)         addLogMsg:(NSString *)msg;
-(void)         addErrorMsg:(NSString *)msg;

-(void)         checkingWhichTab;

@end