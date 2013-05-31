/*
 *  ofxNSWindowApp.h
 *
 *  Created by Will Gallia on 14/04/2012.
 *  Copyright 2012 . All rights reserved.
 *
 */

//this is the equivalent to oF's ofBaseApp
//only now we can have stuff like mouseScrolled (woohoo!)
//also as this is a window, we inherit from ofAppBaseWindow too
//haven't implemented a great deal of the functions

#pragma once


#include "ofxNSWindow.h"
#include "ofAppBaseWindow.h"
#include "ofMain.h"

class ofxNSWindow;

class ofxNSWindowApp : public ofBaseSoundInput, public ofBaseSoundOutput {
	
public:
	ofxNSWindowApp() {
		mouseX = mouseY = 0;
		parent = NULL;
	};
	
	virtual ~ofxNSWindowApp() {}
	
	virtual void setup() {}
	virtual void update() {}
	virtual void draw() {}
	virtual void close() {}
	
	virtual void keyPressed(int key) {}
	virtual void keyReleased(int key) {}
	
	virtual void mouseMoved(int x, int y) {}
	virtual void mouseDragged(int x, int y, int button) {}
	virtual void mousePressed(int x, int y, int button) {}
	virtual void mouseReleased() {}
	virtual void mouseReleased(int x, int y, int button) {}
	
	virtual void mouseScrolled(float x, float y) {}
	
	virtual void dragEvent(ofDragInfo dragInfo) {}
	
	int mouseX, mouseY;	//for processing heads, and i like processing so let's keep it
	
	
	///////////////////////////////////////////////////////
	void setParent(ofxNSWindow *p) { parent = p; }
	ofxNSWindow* getParent() { return parent; }
	
	
private:
		ofxNSWindow *parent;
};

