//
//  GASketchFileViewController.h
//  GAmuza
//
//  Created by n3m3da on 16/05/13.
//
//

#import <Cocoa/Cocoa.h>
#import "GATextView.h"


@interface GASketchFileViewController : NSViewController{
    
    NSDocument            *document;
    IBOutlet GATextView   *tV;
    
}

@property (nonatomic,assign) NSDocument     *document;
@property (nonatomic,assign) GATextView     *tV;

@end
