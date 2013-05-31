//
//  OpenGLView.h
//
//  Created by Will Gallia on 14/04/2012.
//  Copyright 2012 . All rights reserved.
//

//this is a custom NSView that draws openFrameworks stuff...

//the code is based on the examples in the book:
//OpenGL Programming on Mac OS X p.133 & 147


#include "ofMain.h"
#include "ofxNSWindowApp.h"

#import <Cocoa/Cocoa.h>
#import "OpenGLContext.h"

class ofxNSWindowApp;

@interface OpenGLView : NSView <NSDraggingDestination> {
	
	float realFrameRate;
	int frameRate; //this also serves a boolean for the screen sync
	int lastFrameTime;
	
	CVDisplayLinkRef displayLink; //display link for managing rendering thread
	
@private
	NSOpenGLContext *context;
	NSOpenGLPixelFormat *pixelFormat;
	
	NSTimer *timer;
	unsigned long frameCounter;
	
	ofxNSWindowApp *windowApp;
	
}

- (id) initWithFrame : (NSRect)frame : (ofxNSWindowApp*) app : (int) fr;
- (void) setup;

- (NSOpenGLContext*) openGLContext;
- (void) prepareOpenGL;

- (void) setApp: (ofxNSWindowApp*) app;


- (void) setFrameRate: (float) fr;
- (void) startTimer;
- (void) eraseTimer;

- (int) getFrameNum;
- (float) getFrameRate;
- (float) getRealFrameRate;

- (CVReturn) getFrameForTime: (const CVTimeStamp*) outputTime;

@end

