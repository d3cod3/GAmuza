/*
 *  ofxNSWindow.h
 *
 *  Created by Will Gallia on 14/04/2012.
 *  Copyright 2012 . All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxNSWindower.h"
#include "ofAppBaseWindow.h"

#import "OpenGLView.h"
#import <Cocoa/Cocoa.h>

class ofxNSWindowApp;
class ofxNSWindow;
class ofxNSWindower;
@class OpenGLView;
@class DraggingWindow;
@class WindowDelegate;

class ofxNSWindow : public ofAppBaseWindow {
	
public:
	ofxNSWindow() {}
	ofxNSWindow(ofxNSWindowApp *app, string name="", int options=NSTitledWindowMask, float frameRate=30);
	void setup();
	
	~ofxNSWindow();
		
	DraggingWindow* getWindow() { return window; }
	OpenGLView* getView() { return glview; }
	ofxNSWindowApp* getApp() { return app; }
	
	void hideCursor();
	void showCursor();
	
	void setWindowPosition(int x, int y);
	void setWindowShape(int w, int h);
	
	int getFrameNum();
	float getFrameRate();
	void setFrameRate(float fr);
	float getSetFrameRate(); //yes, weird name but might be useful

	ofPoint	getWindowPosition() { return ofPoint(frame.x, frame.y); }
	ofPoint	getWindowSize(){ return ofPoint(frame.width, frame.height); }
	ofRectangle getFrame() { return frame; }

	int getWidth() { return getWindowSize().x; }
	int getHeight() { return getWindowSize().y; }
	
	void setPos(int x, int y) { [window setFrameOrigin:NSMakePoint(x, y)]; }
	
	void	setFullscreen(bool fullscreen);
	void	toggleFullscreen();
	
	void setWindowTitle(string title);
	string getWindowTitle();

private:
	
	ofRectangle frame, oframe;
	string name;
	float frameRate;
	bool isFullscreen;
	
	DraggingWindow *window;
	OpenGLView *glview;
	
	WindowDelegate *windowDelegate;
	
	ofxNSWindowApp *app;
	
};

/////////////////////////////////////////////////
//window to handle borderless windows dragging
@interface DraggingWindow : NSWindow {
    BOOL        shouldDrag;
    BOOL        shouldRedoInitials;
    NSPoint     initialLocation;
    NSPoint     initialLocationOnScreen;
    NSRect      initialFrame;
    NSPoint     currentLocation;
    NSPoint     newOrigin;
    NSRect      screenFrame;
    NSRect      windowFrame;
    float       minY;
}

- (void) mouseUp: (NSEvent*) event;
- (void) mouseDown: (NSEvent*) event;
- (void) mouseDragged: (NSEvent*) event;

@end

/////////////////////////////////////////////////
//window delegate to handle close events

@interface WindowDelegate : NSObject<NSWindowDelegate> { 
	ofxNSWindowApp *app;
	OpenGLView *view;
}

@property (assign) ofxNSWindowApp* app;
@property (retain) OpenGLView* view;

- (BOOL) windowShouldClose: (id) sender;

@end

