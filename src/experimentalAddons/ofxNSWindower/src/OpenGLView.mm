//
//  OpenGLView.m
//
//  Created by Will Gallia on 14/04/2012.
//  Copyright 2012 . All rights reserved.
//

#import "OpenGLView.h"
#include "ofxNSWindow.h"

#include <OpenGL/OpenGL.h>

static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime,
																		CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext);

@interface OpenGLView ()

- (void) renderLoop;
- (void) setOfWindow;

@end

@implementation OpenGLView


- (id) initWithFrame: (NSRect) frame: (ofxNSWindowApp*) app : (int) fr {
	
	windowApp = app;
	frameRate = fr;
	[self initWithFrame:frame];
}


- (id) initWithFrame: (NSRect)frame {
	
	self = [super initWithFrame:frame];
	
	if (self) {
		
		pixelFormat = [[OpenGLContext instance] pixelFormat];

		if (pixelFormat == nil) {
			NSLog(@"OpenGLView: no pixel format");
		}
		
		context = nil;

	}
	
	//we need to do this to enable mouseMoved events
	NSTrackingArea *trackingArea;
	trackingArea = [[NSTrackingArea alloc] initWithRect:frame
																							options:NSTrackingMouseMoved | NSTrackingInVisibleRect | NSTrackingActiveInKeyWindow
																								owner:self
																						 userInfo:nil];
	
	[self addTrackingArea:trackingArea];
	[trackingArea release];
	
	
	lastFrameTime = 0;
	
	if (frameRate) {
		[self startTimer];
	}
	
	//framerate is 0 so we sync with the screen's refresh rate
	else {
		//the following has been copied and adjusted from:
		//http://developer.apple.com/library/mac/#documentation/graphicsimaging/conceptual/OpenGL-MacProgGuide/opengl_designstrategies/opengl_designstrategies.html
		
		// Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
		
    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
		
    // Set the renderer output callback function
    CVDisplayLinkSetOutputCallback(displayLink, &displayLinkCallback, self);
		
    // Set the display link for the current renderer
    CGLContextObj cglContext = (CGLContextObj) [[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj) [pixelFormat CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
		
    // Activate the display link
    CVDisplayLinkStart(displayLink);
	}
	
	//dragging stuff, basically just allow us to register dragging...
	[self registerForDraggedTypes:[NSArray arrayWithObjects: NSFilenamesPboardType, nil]];

	
	
	return self;
}



///////////////////////////////////////////////////////////
//screen refresh stuff....

//again... taken from the URL above...
// This is the renderer output callback function
static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime,
																			CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext) {
	
	 return [(OpenGLView*)displayLinkContext getFrameForTime:outputTime];
}

- (CVReturn) getFrameForTime: (const CVTimeStamp*) outputTime {
	
	//getFrameForTime gets called on a high priority thread, so let's call renderLoop on the main thread
    //BUG FIX: waitUntilDone: needs to be YES, or other nswindows can freeze...
	[self performSelectorOnMainThread:@selector(renderLoop) withObject:nil waitUntilDone:YES];

	return kCVReturnSuccess;
}

//////////////////////////////////////////////////////////////

- (void) setup {
	windowApp->setup();
    ofNotifySetup();
}

- (void) setApp: (ofxNSWindowApp*) app {
	windowApp = app;
}

//returns pointer to shared GL context
- (NSOpenGLContext*) openGLContext {
	
	if (context == nil) {
		
		context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat 
                                             shareContext:[[OpenGLContext instance] context]];
		
		if (context == nil) {
			NSLog(@"OpenGLView: can't create context");
		}
	}

	return context;
}

- (void) prepareOpenGL {
	
	//really basic OpenGL initialisation...
	glViewport(0, 0, (GLsizei) self.frame.size.width, (GLsizei) self.frame.size.height);
	
	//this is taken from oF's ofGLRenderer::setupScreenPerspective()
		
	float viewW = self.frame.size.width;
	float viewH = self.frame.size.height;
	
	float fov = 60;
	float eyeX = viewW / 2;
	float eyeY = viewH / 2;
	float halfFov = PI * fov / 360;
	float theTan = tanf(halfFov);
	float dist = eyeY / theTan;
	float aspect = (float) viewW / viewH;
	
	float nearDist = dist / 10.0f;
	float farDist = dist * 10.0f;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, aspect, nearDist, farDist);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0, 0, 1, 0);
	
	//put the origin in the top left corner...
	glScalef(1, -1, 1);
	glTranslatef(0, -self.frame.size.height, 0);
	

	[[self openGLContext] update];
}

- (void) lockFocus {
	
	//make sure we are ready to draw
	[super lockFocus];
	
	NSOpenGLContext *ctx = [self openGLContext];
	
	//as far as i can understand, just make 
	//the context draw into this view
	if ([ctx view] != self) {
		[ctx setView:self];
	}
	
	//make this the current context
	//we only have one...
	[ctx makeCurrentContext];
}

- (void) renderLoop {
	
	realFrameRate = 1.0/((ofGetElapsedTimeMicros() - lastFrameTime)*0.000001);
	
//	[self setOfWindow];
	
	//VERY IMPORTANT!!!
	//we need to lock focus so that things are drawn here
	//this won't make a difference with just one window
	//but with multiple ones only one window will redraw
	[self lockFocus];
	
	
	windowApp->update();
    ofNotifyUpdate();
	
	windowApp->draw();
    ofNotifyDraw();

	[[self openGLContext] flushBuffer];	


	//now unlock so we can draw to others...
	[self unlockFocus];
	
	frameCounter++;
	lastFrameTime = ofGetElapsedTimeMicros();

}

- (void) setOfWindow {
	// wow, what a mess
	ofSetAppWindow(ofxNSWindower::instance()->getWindowPtr(windowApp->getParent()->getWindowTitle()));
}

- (void) setFrameRate: (float) fr {
	
	[self eraseTimer];
	frameRate = fr;
	[self startTimer];
	
}

- (int) getFrameNum {
	return frameCounter;
}

- (float) getFrameRate {
	return frameRate;
}

- (float) getRealFrameRate {
	return realFrameRate;
}

- (void) startTimer {
	timer = [NSTimer timerWithTimeInterval: 1.0/frameRate
																	target:self 
																selector:@selector(renderLoop) 
																userInfo:nil 
																 repeats:YES];
	
	[[NSRunLoop mainRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	
	//also add a timer for tracking run loop so the the app doesn't freeze when
	//the menu is being used...
	[[NSRunLoop mainRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];
}

- (void) eraseTimer {
	
	[timer invalidate];
}

- (void) drawRect: (NSRect) rect {
	//do nothing here...
}


- (BOOL) acceptsFirstResponder {
	return YES;
}

// - - - - LEFT MOUSE BUTTON - - - - 


- (void) mouseDown: (NSEvent*) event {
	
	NSPoint p = [self convertPoint:[event locationInWindow] fromView:nil];
	windowApp->mousePressed(p.x, self.frame.size.height - p.y, 0);
    ofNotifyMousePressed(p.x, self.frame.size.height - p.y, 0);
    
}

- (void) mouseDragged: (NSEvent*) event {
	
	NSPoint p = [self convertPoint:[event locationInWindow] fromView:nil];
	windowApp->mouseDragged(p.x, self.frame.size.height - p.y, 0);
    ofNotifyMouseDragged(p.x, self.frame.size.height - p.y, 0);

}

- (void) mouseUp: (NSEvent*) event {
	
	NSPoint p = [self convertPoint:[event locationInWindow] fromView:nil];
	windowApp->mouseReleased(p.x, self.frame.size.height - p.y, 0);
	windowApp->mouseReleased();
    ofNotifyMouseReleased(p.x, self.frame.size.height - p.y, 0);
}

// - - - - RIGHT MOUSE BUTTON - - - - 

- (void) rightMouseDown: (NSEvent*) event {
	
	NSPoint p = [self convertPoint:[event locationInWindow] fromView:nil];
	windowApp->mousePressed(p.x, self.frame.size.height - p.y, 2);
    ofNotifyMousePressed(p.x, self.frame.size.height - p.y, 2);
}

- (void) rightMouseDragged: (NSEvent*) event {
	
	NSPoint p = [self convertPoint:[event locationInWindow] fromView:nil];
	windowApp->mouseDragged(p.x, self.frame.size.height - p.y, 2);
    ofNotifyMouseDragged(p.x, self.frame.size.height - p.y, 2);
}

- (void) rightMouseUp: (NSEvent*) event {
	
	NSPoint p = [self convertPoint:[event locationInWindow] fromView:nil];
	windowApp->mouseReleased(p.x, self.frame.size.height - p.y, 2);
	windowApp->mouseReleased();
    ofNotifyMouseReleased(p.x, self.frame.size.height - p.y, 2);
}

- (void) mouseMoved: (NSEvent*) event {
	
	NSPoint p = [self convertPoint:[event locationInWindow] fromView:nil];
	windowApp->mouseX = p.x;
	windowApp->mouseY = self.frame.size.height - p.y;
	windowApp->mouseMoved(p.x, self.frame.size.height - p.y);
    ofNotifyMouseMoved(p.x, self.frame.size.height - p.y);
}

// - - - - KEYS - - - - 

- (void) keyDown: (NSEvent*) event {
	
	unichar c = [[event characters] characterAtIndex:0];
	windowApp->keyPressed(c);
    ofNotifyKeyPressed(c);
}

- (void) keyUp: (NSEvent*) event {
	
	unichar c = [[event characters] characterAtIndex:0];
	windowApp->keyReleased(c);
    ofNotifyKeyReleased(c);
}

// - - - - SCROLLWHEEL - - - -

- (void) scrollWheel: (NSEvent*) event {
	
	windowApp->mouseScrolled(event.deltaX, event.deltaY);
}


// - - - - DRAGGING - - - - 

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender {
	
	//return drag operation copy, so that the cursor and the plus sign...
	//i think this makes the most sense...
	return NSDragOperationCopy;
}


- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender {
	
	NSPasteboard *pasteboard = [sender draggingPasteboard];
	
	//get the array of filenames, these are absolute file paths
	NSArray *files = [pasteboard propertyListForType: NSFilenamesPboardType];
	
	
	NSPoint p = [sender draggingLocation];
	
	[self setOfWindow];
	ofDragInfo dragInfo;
	dragInfo.position = ofPoint(p.x, ofGetHeight() - p.y);//flip positive y direction
	
	//now we can differentiate between links and data and other stuff like that
	//but for our application, i don't think we need to, so
	
	for (NSString *o in files) {
		dragInfo.files.push_back([o UTF8String]);
	}
	
	windowApp->dragEvent(dragInfo);
    ofNotifyDragEvent(dragInfo);
	
	return YES;
}

- (void)viewDidMoveToWindow{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(windowResized:) name:NSWindowDidResizeNotification
                                               object:[self window]];
}


- (void)windowResized:(NSNotification *)notification;{
    NSSize size = [[self window] frame].size;
    windowApp->windowResized(size.width,size.height);
}


- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
	[timer invalidate];
	
	[super dealloc];
}

@end
