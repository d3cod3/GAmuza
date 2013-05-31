//
//  NSMenu+DeepSearch.m
//  ScriptEditor
//
//  Created by n3m3da on 11/08/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "NSMenu+DeepSearch.h"

@implementation NSMenu (DeepSearch)

// -----------------------------------------------------------------------------
//	findItemWithTarget:andAction:
//		Calls indexOfItemWithTarget:andAction: on the menu, and if it doesn't
//		find an item, calls itself recursively on the submenus of all items
//		in the specified menu.
//
//  REVISIONS:
//		2004-05-18  witness Created.
// -----------------------------------------------------------------------------

-(NSMenuItem*)  findItemWithTarget: (id)targ andAction: (SEL)action
{
	// Look in this menu:
	double itemIndex = [self indexOfItemWithTarget: targ andAction: action];
	if( itemIndex >= 0 )
		return [self itemAtIndex: itemIndex];   // Return the item we found in this menu.
	
	// If not found, search our items' submenus:
	NSArray*		items = [self itemArray];
	NSEnumerator*   enny = [items objectEnumerator];
	NSMenuItem*  	currItem = nil;
	
	while( (currItem = [enny nextObject]) )
	{
		if( [currItem hasSubmenu] )
		{
			currItem = [[currItem submenu] findItemWithTarget: targ andAction: action]; // Recurse deeper.
			if( currItem )
				return currItem;	// Found, exit & return item from submenu.
		}
	}
	
	// Nothing found? Report failure:
	return nil;
}

@end
