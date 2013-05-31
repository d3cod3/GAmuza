#include "ofxKeyMap.h"

ofxKeyMap::ofxKeyMap() {
	ofAddListener(ofEvents().keyPressed, this, &ofxKeyMap::_keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &ofxKeyMap::_keyReleased);
	for (int i=0; i<NUM_KEYS; i++) keys[i]=false;
}

void ofxKeyMap::_keyPressed(ofKeyEventArgs &e) {
	assert(e.key<NUM_KEYS);
    keys[e.key]=true;
}

void ofxKeyMap::_keyReleased(ofKeyEventArgs &e) {
    assert(e.key<NUM_KEYS);
    keys[e.key]=false;
}

bool ofxKeyMap::isKeyDown(int key) {
    return keys[key];
}

bool ofxKeyMap::isAltDown() {
    #ifdef TARGET_WIN32
    return ((GetKeyState( VK_MENU ) & 0x80) > 0);
    #else
    return (glutGetModifiers() & GLUT_ACTIVE_ALT);
    #endif
}

bool ofxKeyMap::isShiftDown() {
    #ifdef TARGET_WIN32
    return ((GetKeyState( VK_SHIFT ) & 0x80) > 0);
    #else
    return (glutGetModifiers() & GLUT_ACTIVE_SHIFT);
    #endif
}

bool ofxKeyMap::isControlDown() {
    #ifdef TARGET_WIN32
    return ((GetKeyState( VK_CONTROL ) & 0x80) > 0);
    #else
    return (glutGetModifiers() & GLUT_ACTIVE_CTRL);
    #endif
}

