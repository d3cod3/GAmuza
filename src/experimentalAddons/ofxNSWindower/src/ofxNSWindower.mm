/*
 *  ofxNSWindower.cpp
 *
 *  Created by Will Gallia on 15/04/2012.
 *  Copyright 2012 . All rights reserved.
 *
 */

#include "ofxNSWindower.h"

static ofxNSWindower* windower = NULL;

ofxNSWindower* ofxNSWindower::instance() {
	if (windower == NULL) {
		windower = new ofxNSWindower();
	}
	return windower;
}

ofxNSWindower::ofxNSWindower() {
	
	//get the context fired up...
	//this will also load oF stuff
	[OpenGLContext instance];
	
	//ofSetDataPathRoot("../../../data/");
	ofSeedRandom();
	ofSetBackgroundAuto(false);	
	
}

void ofxNSWindower::destroy() {
	if (windower != NULL) {
		delete windower;
		windower = NULL;
	}
}

ofxNSWindower::~ofxNSWindower() {
	for (map<string, ofPtr<ofxNSWindow> >::iterator it = windows.begin(); it != windows.end(); it++) {
		delete it->second->getApp();
		//windows.erase(it);
	}
}

//all but the first arguments are optional...
//if no name is given then a random number between 0 and 1000 is given...
//default option is just a title, no buttons, with a framerate of 30
void ofxNSWindower::addWindow(ofxNSWindowApp *app, string name, int options, int frameRate) {

	//if a window isn't given a name, give it a random one..
	if (name == "") {
		string randomstring;
		do {
			randomstring = ofToString((int) ofRandom(1000));
		} while (windows.count(randomstring));
		name = randomstring;
	}

	windows[name] = ofPtr<ofxNSWindow>(new ofxNSWindow(app, name, options, frameRate));
	ofSetAppWindow(windows[name]);
	windows[name]->setup();
    
}


void ofxNSWindower::deleteWindow(ofxNSWindowApp *app) {

	//this is a bit rubbish, but i think it's ok, ideally we should have the name of the app,
	//but apps don't have names, windows do so it's a bit of weird situation.
	//this is just a quick fix without changing ofxNSWindowApp...
	for (map<string, ofPtr<ofxNSWindow> >::iterator it = windows.begin(); it != windows.end(); it++) {
		if (it->second->getApp() == app) {
            windows.erase(it);
			delete app;
			break;
		}
	}
}


//this is the equivalent to ofGetAppPtr() only we now pass a name for the specific app

ofxNSWindowApp*  ofxNSWindower::getAppPtr(string name) {
	if (windows.count(name)) {
		return windows[name]->getApp();
	}
	return NULL;
}

ofPtr<ofxNSWindow> ofxNSWindower::getWindowPtr(string name) {
	
	if (windows.count(name)) {
		return windows[name];
	}
}

//just a nice utility to see what apps we have running...
vector<string> ofxNSWindower::getAppNames() {
	vector<string> names;
	for (map<string, ofPtr<ofxNSWindow> >::iterator it = windows.begin(); it != windows.end(); it++) {
		names.push_back(it->first);
	}
	return names;
}

//tried syncronising all views at one point....

//void ofxNSWindower::loop() {
//
//	for (map<string, ofxNSWindow*>::iterator it = windows.begin(); it != windows.end(); ++it) {
//
//		[(*it).second->getView() renderLoop];
//
//	}
//	
//	[[[OpenGLContext instance] context] flushBuffer];
//	
//}

//not used...

////////////////////////////////////////////////////////////////////////

//implementation of Objective-C timer...
//is passed an ofxNSWindower object and a callback function
//fuck! i just realised that i could have hard coded it to call 
//the loop function of ofxNSWindower!!! damn!!!

//anyway, sets up a NSTimer to fire a C++ function

@implementation Timer

- (void) setCallbackWithObject: (ofxNSWindower*) obj function: (func) cb {
	callback = cb;
	window_object = obj;
}

- (void) startTimer: (float) frameRate {

		NSTimer *timer = [NSTimer timerWithTimeInterval: 1/frameRate
																		target:self 
																	selector:@selector(loop)
																	userInfo:nil 
																	 repeats:YES];
		
		
		[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
		
}

- (void) loop {
	(window_object->*callback)();
}

@end