#ifndef _GAMUZAKEYBOARD
#define _GAMUZAKEYBOARD

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::keyPressed(int key){
    
    // Live Coding
    lua.scriptKeyPressed(key);
    liveKey = key;
	
}

//--------------------------------------------------------------
void gamuzaMain::keyReleased(int key){
    
    // Live Coding
    lua.scriptKeyReleased(key);
    liveKey = key;
    
}

#endif
