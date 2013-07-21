/*
 *  ofxNSWindow.mm
 *
 *  Created by Will Gallia on 14/04/2012.
 *  Copyright 2012 . All rights reserved.
 *
 */



#include "ofxNSWindow.h"


ofxNSWindow::ofxNSWindow(ofxNSWindowApp *app, string name, int options, float frameRate):
name(name), frameRate(frameRate), isFullscreen(false) {

	frame = ofRectangle(100, 500, 320, 240);
	oframe = ofRectangle(100, 500, 320, 240); //used when we go fullscreen
	
	//set the parent so we can gain information 
	//about the window from inside the app
	app->setParent(this);
	this->app = app;
	
	//create the window...
	NSRect nsframe = NSMakeRect(frame.x, frame.y, frame.width, frame.height);
	
	window = [[DraggingWindow alloc] initWithContentRect:nsframe styleMask:options backing:NSBackingStoreBuffered defer:NO];
	
	[window setFrameTopLeftPoint:NSMakePoint(frame.x, frame.y)];

	glview = [[OpenGLView alloc] initWithFrame:nsframe :app :frameRate];

	//setup and display the window
	
	[window setContentView:glview];
	[window makeKeyAndOrderFront:nil];
	[glview release];
	
	windowDelegate = [[WindowDelegate alloc] init];
	[windowDelegate setApp:app];
	[windowDelegate setView:[window contentView]];
	[window setDelegate:windowDelegate];
	[window setReleasedWhenClosed:YES];

	setWindowTitle(name);
}

void ofxNSWindow::setup() {
	[glview setup];
}

//windows should be close with the close button
ofxNSWindow::~ofxNSWindow() {
//	[[window contentView] release];
//	[window close];
//	[window release];
	[windowDelegate release];
}

void ofxNSWindow::showCursor() {
	[NSCursor unhide];
}

void ofxNSWindow::hideCursor() {
	[NSCursor hide];
}

void ofxNSWindow::setWindowTitle(string title) {
	
	NSString *nstitle = [NSString	stringWithUTF8String:title.c_str()];
	[window setTitle:nstitle];
}

string ofxNSWindow::getWindowTitle() {
	return string([[window title] UTF8String]);
}

float ofxNSWindow::getFrameRate() { 
	return [glview getRealFrameRate];
}

void ofxNSWindow::setFrameRate(float fr) { 
	[glview setFrameRate: fr]; 
}

int ofxNSWindow::getFrameNum() { 

	return [glview getFrameNum]; 
}

float ofxNSWindow::getSetFrameRate() {
	return [glview getFrameRate];
}

void ofxNSWindow::setWindowShape(int w, int h) {

	[window setContentSize:NSMakeSize(w, h)];
	[glview setFrame:NSMakeRect(0, 0, w, h)];
	[glview prepareOpenGL];
	
	frame.width = w;
	frame.height = h;
	
}

void ofxNSWindow::setWindowPosition(int x, int y) {
	
	[window setFrameTopLeftPoint:NSMakePoint(x, y)];
	frame.x = x;
	frame.y = y;
}

int ofxNSWindow::getActualScreen(){
    NSPoint center;
    NSRect rect = [window frame];
    center.x = rect.origin.x + rect.size.width / 2;
    center.y = rect.origin.y + rect.size.height / 2;
    
    NSEnumerator *screenEnum = [[NSScreen screens] objectEnumerator];
    NSScreen *screen;
    
    int count = 0;
    while (screen = [screenEnum nextObject]){
        NSRect f = [screen frame]; // visibleFrame
        if(NSPointInRect(center,f)){
            return count;
        }
        count++;
    }
    
    return 0;
}

void ofxNSWindow::setFullscreen(bool fullscreen){
    NSMutableDictionary *opts = [NSMutableDictionary dictionary];
    [opts setObject:[NSNumber numberWithBool:NO] forKey:NSFullScreenModeAllScreens];
    
	NSPoint center;
    NSRect rect = [window frame];
    center.x = rect.origin.x + rect.size.width / 2;
    center.y = rect.origin.y + rect.size.height / 2;
    
	if(fullscreen) {
        NSEnumerator *screenEnum = [[NSScreen screens] objectEnumerator];
		NSScreen *screen;
        
        while (screen = [screenEnum nextObject]){
            NSRect f = [screen frame]; // visibleFrame
            if(NSPointInRect(center,f)){
                [glview enterFullScreenMode:screen withOptions:opts];
                //[glview setFrame:f];
                [window setFrame:f display:YES animate:NO];
                oframe.x = rect.origin.x;
                oframe.y = rect.origin.y;
                oframe.width = rect.size.width;
                oframe.height = rect.size.height;
                frame.set(0, 0, f.size.width, f.size.height);
                break;
            }
        }
	}
	else {
		[glview exitFullScreenModeWithOptions:opts];
		//[glview setFrame:NSMakeRect(0, 0, oframe.width, oframe.height)];
        [window setFrame:NSMakeRect(oframe.x, oframe.y, oframe.width, oframe.height) display:YES animate:NO];
		frame = oframe;
	}

	[glview prepareOpenGL];
	[window makeFirstResponder:glview];

	isFullscreen = fullscreen;
}

void	ofxNSWindow::toggleFullscreen(){

	setFullscreen(!isFullscreen);
}

//////////////////////////////////////////////////////////////
// NSWindow implementation to handle borderless windows dragging

@implementation DraggingWindow

- (id)initWithContentRect:(NSRect)contentRect
                styleMask:(NSUInteger)aStyle
                  backing:(NSBackingStoreType)bufferingType
                    defer:(BOOL)flag {
	self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    
    if(aStyle == NSBorderlessWindowMask){
        [self setMovableByWindowBackground:YES];
        [self setAcceptsMouseMovedEvents:YES];
        [self setBackgroundColor:[NSColor clearColor]];
        [self setLevel:NSNormalWindowLevel];
        [self setOpaque:NO];
        [self setHasShadow:YES];
    }
	return self;
}

- (BOOL) canBecomeKeyWindow {
    return YES;
}

- (void) mouseMoved: (NSEvent*) event {
    
}

- (void) mouseUp: (NSEvent*) event{
	shouldRedoInitials = YES;
}

- (void) mouseDown: (NSEvent*) event{
    //grab the mouse location in global coordinates
	initialLocation = [event locationInWindow];
	initialLocationOnScreen = [self convertBaseToScreen:[event locationInWindow]];
    
	initialFrame = [self frame];
    
}

- (void) mouseDragged: (NSEvent*) event{
	if (shouldRedoInitials){
		initialLocation = [event locationInWindow];
		initialLocationOnScreen = [self convertBaseToScreen:[event locationInWindow]];
        
		initialFrame = [self frame];
		shouldRedoInitials = NO;
        
		if (initialLocation.x > initialFrame.size.width - 20 && initialLocation.y < 20) {
			shouldDrag = NO;
		}
		else {
			shouldDrag = YES;
		}
        
		screenFrame = [[NSScreen mainScreen] frame];
		windowFrame = [self frame];
        
		minY = windowFrame.origin.y+(windowFrame.size.height-288);
	}
    
    
	// 1. Is the Event a resize drag (test for bottom right-hand corner)?
	if (shouldDrag == FALSE){
		// i. Remember the current downpoint
		/*NSPoint currentLocationOnScreen = [self convertBaseToScreen:[self mouseLocationOutsideOfEventStream]];
		currentLocation = [event locationInWindow];
        
		// ii. Adjust the frame size accordingly
		float heightDelta = (currentLocationOnScreen.y - initialLocationOnScreen.y);
        
		if ((initialFrame.size.height - heightDelta) < 289){
			windowFrame.size.height = 288;
			windowFrame.origin.y = minY;
		} else{
			windowFrame.size.height = (initialFrame.size.height - heightDelta);
			windowFrame.origin.y = (initialFrame.origin.y + heightDelta);
		}
        
		windowFrame.size.width = initialFrame.size.width + (currentLocation.x - initialLocation.x);
		if (windowFrame.size.width < 323){
			windowFrame.size.width = 323;
		}
        
		// iii. Set
		[self setFrame:windowFrame display:YES animate:NO];*/
	}
    else{
		//grab the current global mouse location; we could just as easily get the mouse location
		//in the same way as we do in -mouseDown:
		currentLocation = [self convertBaseToScreen:[self mouseLocationOutsideOfEventStream]];
		newOrigin.x = currentLocation.x - initialLocation.x;
		newOrigin.y = currentLocation.y - initialLocation.y;
        
		// Don't let window get dragged up under the menu bar
		if( (newOrigin.y+windowFrame.size.height) > (screenFrame.origin.y+screenFrame.size.height) ){
			newOrigin.y=screenFrame.origin.y + (screenFrame.size.height-windowFrame.size.height);
		}
        
		//go ahead and move the window to the new location
        if([self styleMask] == NSBorderlessWindowMask){
            [self setFrameOrigin:newOrigin];
        }
        
	}
}

@end

//////////////////////////////////////////////////////////////
//NSWindow delegate implementation for close events

@implementation WindowDelegate

@synthesize app;
@synthesize view;


- (BOOL) windowShouldClose: (id) sender {

	[view eraseTimer];
	app->close();

	ofxNSWindower::instance()->deleteWindow(app);

	return YES;
}


@end


