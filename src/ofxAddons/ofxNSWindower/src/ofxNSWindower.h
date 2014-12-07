/*
 *  ofxNSWindower.h
 *
 *  Created by Will Gallia on 15/04/2012.
 *  Copyright 2012 . All rights reserved.
 *
 */

//this is a singleton class that handles all the windows
//windows are added with addWindow()
//pointers to the apps of the windows can be retrieved with getAppPtr()

#pragma once

#include "ofxNSWindow.h"
#include "OpenGLContext.h"

#include <map>
#include <string>

#include "ofTypes.h"

class ofxNSWindow;
class ofxNSWindowApp;

class ofxNSWindower {

public:
	static ofxNSWindower* instance();
	static void destroy();
	
	
	//it is recommended that a name is used for each window, but this 
	//is optional...
	void addWindow(ofxNSWindowApp *app, string name="", int options=NSTitledWindowMask, int frameRate=30);
	
	void deleteWindow(ofxNSWindowApp *app);

	ofxNSWindowApp* getAppPtr(string name);
	ofPtr<ofxNSWindow> getWindowPtr(string name);
	
	vector<string> getAppNames();
	
private:
	ofxNSWindower();
	~ofxNSWindower();

	
	void loop(); //this isn't currently used...saf
	
	map<string, ofPtr<ofxNSWindow> > windows;
	
};


//////////////////////////////////////////////////////////////////
// used for view syncronising, which we aren't doing at the moment

typedef void (ofxNSWindower::*func)();


@interface Timer : NSObject { 
	func callback;
	ofxNSWindower *window_object;
}

- (void) setCallbackWithObject: (ofxNSWindower*) obj function: (func) cb;
- (void) startTimer: (float) frameRate;
- (void) loop;

@end