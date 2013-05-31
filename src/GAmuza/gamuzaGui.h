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
	emptyTexture.allocate(workingW,workingH,GL_RGB);
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
	
    //ofToggleFullscreen();
	if(isFullscreen){
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
	}else{
		isFullscreen = true;
        if(projectionScreenW < mainScreenW){
			fboDrawingW         = (projectionScreenW*mainScreenH)/projectionScreenH;
			fboDrawingH         = mainScreenH;
			fboDrawingPosX      = (mainScreenW-fboDrawingW)/2.0;
			fboDrawingPosY      = 0;
		}else{
			fboDrawingW         = mainScreenW;
			fboDrawingH         = (projectionScreenH*mainScreenW)/projectionScreenW;
			fboDrawingPosX      = 0;
			fboDrawingPosY      = (mainScreenH-fboDrawingH)/2.0;
		}
	}
	
}

//--------------------------------------------------------------
void gamuzaMain::resetWarpingPoints(int actualPanel){
	
	
	
}

#endif
