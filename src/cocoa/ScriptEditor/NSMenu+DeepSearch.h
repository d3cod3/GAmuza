//
//  NSMenu+DeepSearch.h
//  ScriptEditor
//
//  Created by n3m3da on 11/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSMenu (DeepSearch)
    // Perform a deep search on a menu and its submenus: (returns NIL if the item couldn't be found)
    -(NSMenuItem*)  findItemWithTarget: (id)targ andAction: (SEL)action;
@end
