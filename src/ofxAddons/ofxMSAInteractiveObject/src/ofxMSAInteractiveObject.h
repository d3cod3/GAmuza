//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//


#pragma once

#include "ofMain.h"

extern float externMouseX; // external reference to gamuza scaled mouse pos, declared in main.mm
extern float externMouseY; // external reference to gamuza scaled mouse pos, declared in main.mm

class ofxMSAInteractiveObject : public ofRectangle {
public:
	bool		enabled;				// set this to false to temporarily disable all events
	bool		verbose;
    
	ofxMSAInteractiveObject();			// constructor
	virtual ~ofxMSAInteractiveObject();	// destructor
    
	void enableAllEvents();				// enable all event callbacks
	void disableAllEvents();			// disable all event callbacks
    
	void enableMouseEvents();			// call this if object should receive mouse events
	void disableMouseEvents();			// call this if object doesn't need to receive mouse events (default)
    
	void enableKeyEvents();				// call this if object should receive key events
	void disableKeyEvents();			// call this if object doesn't need to receive key events (default)
    
	void enableAppEvents();				// call this if object should update/draw automatically	(default)
	void disableAppEvents();			// call this if object doesn't need to update/draw automatically
    
    
    //	void setPosition(float _x, float _y);	// replaced with ofRectangle::setPosition
	void setSize(float _w, float _h);	// set size of object
    //	void setPosAndSize(float _x, float _y, float _w, float _h);		// replaced with ofRectangle::set
    
    
	bool isMouseOver() const;                     // returns true if mouse is over object (based on position and size)
	bool isMousePressed(int mouseButton=0) const;    // returns true if mouse button is down and was pressed over object (based on position and size)
    
    
	int	 getMouseX() const;                       // returns mouse X (in screen coordinates)
	int  getMouseY() const;                       // returns mouse Y (in screen coordinates)
    
    unsigned long getStateChangeMillis() const;   // returns milliseconds since last state change
    
	virtual bool hitTest(int tx, int ty) const;		// returns true if given (x, y) coordinates (in screen space) are over the object (based on position and size)
    
	// extend ofxMSAInteractiveObject and override all or any of the following methods
	virtual void setup() {}     // called when app starts
	virtual void update() {}	// called every frame to update object
    virtual void draw() {}      // called every frame to draw object
	virtual void exit() {}      // called when app quites
    
	// these behave very similar to those in flash
	virtual void onRollOver(int x, int y) {}                    // called when mouse enters object x, y, width, height
	virtual void onRollOut() {}                                 // called when mouse leaves object x, y, width, height
	virtual void onMouseMove(int x, int y) {}                   // called when mouse moves while over object x, y, width, height
	virtual void onDragOver(int x, int y, int button) {}        // called when mouse moves while over object and button is down
	virtual void onDragOutside(int x, int y, int button) {}     // called when mouse moves while outside the object after being clicked on it
	virtual void onPress(int x, int y, int button) {}           // called when mouse presses while over object
	virtual void onPressOutside(int x, int y, int button) {}    // called when mouse presses while outside object
	virtual void onRelease(int x, int y, int button) {}         // called when mouse releases while over object
	virtual void onReleaseOutside(int x, int y, int button) {}  // called when mouse releases outside of object after being pressed on object
	virtual void onKeyPress(int key) {}                         // called when keypressed while mouse over the object
	virtual void onKeyRelease(int key) {}                        // called when keyreleased while mouse over the object
    
    
    // these are called when the relevant event occurs without caring where it actually happened
    // i.e. its the raw event
    virtual void mouseMoved(int x, int y) {}                     // called when mouse moves anywhere
	virtual void mousePressed(int x, int y, int button) {}       // called when mouse pressed anywhere
	virtual void mouseDragged(int x, int y, int button) {}       // called when mouse dragged anywhere
	virtual void mouseReleased(int x, int y, int button) {}      // called when mouse released anywhere
    
	virtual void keyPressed(int key) {}                          // called when keypressed anywhere
	virtual void keyReleased(int key) {}                         // called when keyreleased anywhere
    
    
	// you shouldn't need access to any of these unless you know what you are doing
	// (i.e. disable auto updates and call these manually)
	void _setup(ofEventArgs &e);
	void _update(ofEventArgs &e);
    void _draw(ofEventArgs &e);
	void _exit(ofEventArgs &e);
    
	void _mouseMoved(ofMouseEventArgs &e);
	void _mousePressed(ofMouseEventArgs &e);
	void _mouseDragged(ofMouseEventArgs &e);
	void _mouseReleased(ofMouseEventArgs &e);
    
	void _keyPressed(ofKeyEventArgs &e);
	void _keyReleased(ofKeyEventArgs &e);
    
    bool            _isMouseOver;       // is mouse over the rect
	map<int, bool>    _isMousePressed;       // is mouse down over the rect (for any given mouse button)
    unsigned long   _stateChangeTimestampMillis;
    
private:
	
	ofRectangle	oldRect;
};

