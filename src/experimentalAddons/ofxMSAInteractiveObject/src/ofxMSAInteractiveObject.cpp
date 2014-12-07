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


#include "ofxMSAInteractiveObject.h"
#include "ofMain.h"

//--------------------------------------------------------------
ofxMSAInteractiveObject::ofxMSAInteractiveObject() {
	_isMouseOver	= false;
	enabled		= true;
	verbose		= false;
    _stateChangeTimestampMillis = 0;
	
	enableAppEvents();
	disableMouseEvents();
	disableKeyEvents();
}

//--------------------------------------------------------------
ofxMSAInteractiveObject::~ofxMSAInteractiveObject() {
	disableAllEvents();
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::enableAllEvents() {
	enableMouseEvents();
	enableKeyEvents();
	enableAppEvents();
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::disableAllEvents() {
	disableMouseEvents();
	disableKeyEvents();
	disableAppEvents();
}


//--------------------------------------------------------------
void ofxMSAInteractiveObject::enableMouseEvents() {
	ofAddListener(ofEvents().mousePressed, this, &ofxMSAInteractiveObject::_mousePressed);
	ofAddListener(ofEvents().mouseMoved, this, &ofxMSAInteractiveObject::_mouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &ofxMSAInteractiveObject::_mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &ofxMSAInteractiveObject::_mouseReleased);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::disableMouseEvents() {
	ofRemoveListener(ofEvents().mousePressed, this, &ofxMSAInteractiveObject::_mousePressed);
	ofRemoveListener(ofEvents().mouseMoved, this, &ofxMSAInteractiveObject::_mouseMoved);
	ofRemoveListener(ofEvents().mouseDragged, this, &ofxMSAInteractiveObject::_mouseDragged);
	ofRemoveListener(ofEvents().mouseReleased, this, &ofxMSAInteractiveObject::_mouseReleased);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::enableKeyEvents() {
	ofAddListener(ofEvents().keyPressed, this, &ofxMSAInteractiveObject::_keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &ofxMSAInteractiveObject::_keyReleased);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::disableKeyEvents() {
	ofRemoveListener(ofEvents().keyPressed, this, &ofxMSAInteractiveObject::_keyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &ofxMSAInteractiveObject::_keyReleased);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::enableAppEvents() {
	ofAddListener(ofEvents().setup, this, &ofxMSAInteractiveObject::_setup);
	ofAddListener(ofEvents().update, this, &ofxMSAInteractiveObject::_update);
	ofAddListener(ofEvents().draw, this, &ofxMSAInteractiveObject::_draw);
	ofAddListener(ofEvents().exit, this, &ofxMSAInteractiveObject::_exit);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::disableAppEvents() {
	ofRemoveListener(ofEvents().setup, this, &ofxMSAInteractiveObject::_setup);
	ofRemoveListener(ofEvents().update, this, &ofxMSAInteractiveObject::_update);
	ofRemoveListener(ofEvents().draw, this, &ofxMSAInteractiveObject::_draw);
	ofRemoveListener(ofEvents().exit, this, &ofxMSAInteractiveObject::_exit);
}


//--------------------------------------------------------------
//void ofxMSAInteractiveObject::setPosition(float _x, float _y) {
//	x = _x;
//	y = _y;
//}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::setSize(float _w, float _h) {
	width = _w;
	height = _h;
}

//--------------------------------------------------------------
//void ofxMSAInteractiveObject::setPosAndSize(float _x, float _y, float _w, float _h) {
//	setPosition(_x, _y);
//	setSize(_w, _h);
//}

//--------------------------------------------------------------
bool ofxMSAInteractiveObject::isMouseOver() const {
	return _isMouseOver;
}

//--------------------------------------------------------------
bool ofxMSAInteractiveObject::isMousePressed(int mouseButton) const {
    if(_isMousePressed.find(mouseButton) == _isMousePressed.end()) return false;
    return _isMousePressed.at(mouseButton);
}


//--------------------------------------------------------------
int ofxMSAInteractiveObject::getMouseX() const {
    return ofGetMouseX();
}

//--------------------------------------------------------------
int ofxMSAInteractiveObject::getMouseY() const {
    return ofGetMouseY();
}

//--------------------------------------------------------------
unsigned long ofxMSAInteractiveObject::getStateChangeMillis() const {
    return ofGetElapsedTimeMillis() - _stateChangeTimestampMillis;
}

//--------------------------------------------------------------
bool ofxMSAInteractiveObject::hitTest(int tx, int ty) const {
	return ((tx > x) && (tx < x + width) && (ty > y) && (ty < y + height));
}



//--------------------------------------------------------------
void ofxMSAInteractiveObject::_setup(ofEventArgs &e) {
	if(!enabled) return;
	setup();
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::_update(ofEventArgs &e) {
	if(!enabled) return;
	
	// check to see if object has moved, and if so update mouse events
    //	if(oldRect.x != this->x || oldRect.y != this->y || oldRect.width != this->width ||oldRect.height != this->height) {
    //		ofMouseEventArgs e;
    //		e.button = _mouseButton;
    //		e.x = _mouseX;
    //		e.y = _mouseY;
    //		if(_isMousePressed) _mouseDragged(e);
    //		else _mouseMoved(e);
    //
    //		oldRect =  (ofRectangle) (*this);
    //	}
	update();
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::_draw(ofEventArgs &e) {
	if(!enabled) return;
	draw();
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::_exit(ofEventArgs &e) {
	if(!enabled) return;
	exit();
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::_mouseMoved(ofMouseEventArgs &e) {
	//int x = (int)externMouseX;
	//int y = (int)externMouseY;
	//int button = e.button;
    int x = e.x;
	int y = e.y;
	int button = e.button;
	//printf("ofxMSAInteractiveObject::_mouseMoved(x: %i, y: %i)\n", x, y);
	if(!enabled) return;
	
	//	_mouseX = x;
    //	_mouseY = y;
	
	if(hitTest(x, y)) {						// if mouse is over the object
		if(!_isMouseOver) {						// if wasn't over previous frame
			_isMouseOver = true;						// update flag
			onRollOver(x, y);						// call onRollOver
		}
		onMouseMove(x, y);						// and trigger onMouseMove
	} else if(_isMouseOver) {					// if mouse is not over the object, but the flag is true (From previous frame)
		onRollOut();							// call onRollOut
		_isMouseOver = false;						// update flag
	}
    
    _stateChangeTimestampMillis = ofGetElapsedTimeMillis();
    
    mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::_mousePressed(ofMouseEventArgs &e) {
	//int x = (int)externMouseX;
	//int y = (int)externMouseY;
	//int button = e.button;
    int x = e.x;
	int y = e.y;
	int button = e.button;
	
	//if(verbose) printf("ofxMSAInteractiveObject::_mousePressed(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;

	//_mouseX = x;
	//_mouseY = y;
	//_mouseButton = button;
	
	if(hitTest(x, y)) {						// if mouse is over
		if(!isMousePressed(button)) {						 // if wasn't down previous frame
			_isMousePressed[button] = true;						// update flag
			onPress(x, y, button);					// call onPress
		}
	} else {								// if mouse is not over
		onPressOutside(x, y, button);
	}
    
    _stateChangeTimestampMillis = ofGetElapsedTimeMillis();
    
    mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::_mouseDragged(ofMouseEventArgs &e) {
	//int x = (int)externMouseX;
	//int y = (int)externMouseY;
	//int button = e.button;
    int x = e.x;
	int y = e.y;
	int button = e.button;
	
	//if(verbose) printf("ofxMSAInteractiveObject::_mouseDragged(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;
    
    //	_mouseX = x;
    //	_mouseY = y;
    //	_mouseButton = button;
    
	if(hitTest(x, y)) {						// if mouse is over the object
		if(!_isMouseOver) {						// if wasn't over previous frame
			//				onPress(x, y);							// call onPress - maybe not
			_isMouseOver = true;						// update flag
			onRollOver(x, y);						// call onRollOver
		}
		onDragOver(x, y, button);				// and trigger onDragOver
	} else {
		if(_isMouseOver) {					// if mouse is not over the object, but the flag is true (From previous frame)
			onRollOut();							// call onRollOut
			_isMouseOver = false;						// update flag
		}
		if(isMousePressed(button)) {
			onDragOutside(x, y, button);
		}
	}
    
    _stateChangeTimestampMillis = ofGetElapsedTimeMillis();
    
    mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::_mouseReleased(ofMouseEventArgs &e) {
	//int x = (int)externMouseX;
	//int y = (int)externMouseY;
	//int button = e.button;
    int x = e.x;
	int y = e.y;
	int button = e.button;
	
	//if(verbose) printf("ofxMSAInteractiveObject::_mouseReleased(x: %i, y: %i, button: %i)\n", x, y, button);
	if(!enabled) return;
    
    //	_mouseX = x;
    //	_mouseY = y;
    //	_mouseButton = button;
	
	if(hitTest(x, y)) {
		onRelease(x, y, button);
	} else {
		if(isMousePressed(button)) onReleaseOutside(x, y, button);
	}
	_isMousePressed[button] = false;
    
    _stateChangeTimestampMillis = ofGetElapsedTimeMillis();
    
    mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofxMSAInteractiveObject::_keyPressed(ofKeyEventArgs &e) {
	int key = e.key;
	if(verbose) printf("ofxMSAInteractiveObject::_keyPressed(key: %i)\n", key);
	if(!enabled) return;
    if(isMouseOver()) onKeyPress(key);
    keyPressed(key);
}


//--------------------------------------------------------------
void ofxMSAInteractiveObject::_keyReleased(ofKeyEventArgs &e) {
	int key = e.key;
	if(verbose) printf("ofxMSAInteractiveObject::_keyReleased(key: %i)\n", key);
	if(!enabled) return;
	if(isMouseOver()) onKeyRelease(key);
    keyReleased(key);
}
