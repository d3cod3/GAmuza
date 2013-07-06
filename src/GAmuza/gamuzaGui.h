#ifndef _GAMUZAGUI
#define _GAMUZAGUI

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupGui(){
	
    isFullscreen = false;
    if(projectionScreenW > MAIN_WINDOW_W){
        fboDrawingW         = (projectionScreenW*MAIN_WINDOW_H)/projectionScreenH;
        fboDrawingH         = MAIN_WINDOW_H;
        fboDrawingPosX      = (MAIN_WINDOW_W-fboDrawingW)/2.0;
        fboDrawingPosY      = 0;
    }else{
        fboDrawingW         = MAIN_WINDOW_W;
        fboDrawingH         = (projectionScreenH*MAIN_WINDOW_W)/projectionScreenW;
        fboDrawingPosX      = 0;
        fboDrawingPosY      = (MAIN_WINDOW_H-fboDrawingH)/2.0;
    }
    //////////////////////////////////////////////
    // empty containers
	emptyTexture.allocate(320,240,GL_RGB);
	//////////////////////////////////////////////
}

//--------------------------------------------------------------
void gamuzaMain::updateGui(){
	
    
}

//--------------------------------------------------------------
void gamuzaMain::drawGui(){
	
}

//--------------------------------------------------------------
void gamuzaMain::gamuzaFullscreen(){
	
	if(isFullscreen){
		isFullscreen = false;
        externIsFullscreen = false;
        if(projectionScreenW > MAIN_WINDOW_W){
			fboDrawingW         = (projectionScreenW*MAIN_WINDOW_H)/projectionScreenH;
			fboDrawingH         = MAIN_WINDOW_H;
			fboDrawingPosX      = (MAIN_WINDOW_W-fboDrawingW)/2.0;
			fboDrawingPosY      = 0;
		}else{
			fboDrawingW         = MAIN_WINDOW_W;
			fboDrawingH         = (projectionScreenH*MAIN_WINDOW_W)/projectionScreenW;
			fboDrawingPosX      = 0;
			fboDrawingPosY      = (MAIN_WINDOW_H-fboDrawingH)/2.0;
		}
	}else{
		isFullscreen = true;
        externIsFullscreen = true;
        if(projectionScreenW < _mainScreenW){
			fboDrawingW         = (projectionScreenW*_mainScreenH)/projectionScreenH;
			fboDrawingH         = _mainScreenH;
			fboDrawingPosX      = (_mainScreenW-fboDrawingW)/2.0;
			fboDrawingPosY      = 0;
		}else{
			fboDrawingW         = _mainScreenW;
			fboDrawingH         = (projectionScreenH*_mainScreenW)/projectionScreenW;
			fboDrawingPosX      = 0;
			fboDrawingPosY      = (_mainScreenH-fboDrawingH)/2.0;
		}
	}
	
}

//--------------------------------------------------------------
void gamuzaMain::resetWarpingPoints(int actualPanel){
	
	
	
}

#endif
