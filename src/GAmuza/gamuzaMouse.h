#ifndef _GAMUZAMOUSE
#define _GAMUZAMOUSE

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::mouseMoved(int x, int y){
    if(x < fboDrawingPosX){
        scaledMouseX = 0;
    }else if(x > fboDrawingW + fboDrawingPosX){
        scaledMouseX = projectionScreenW;
    }else{
        scaledMouseX = x - fboDrawingPosX;
        scaledMouseX /= fboDrawingW;
        scaledMouseX *= projectionScreenW;
    }
    
    if(y < fboDrawingPosY){
        scaledMouseY = 0;
    }else if(y > fboDrawingH + fboDrawingPosY){
        scaledMouseY = projectionScreenH;
    }else{
        scaledMouseY = y - fboDrawingPosY;
        scaledMouseY /= fboDrawingH;
        scaledMouseY *= projectionScreenH;
    }
    
    // External mouse
    externMouseX = scaledMouseX;
    externMouseY = scaledMouseY;
    
    // MAPPING
	if(drawGrid){
        finalTextureMapping.mouseMoved(externMouseX, externMouseY);
	}
    
    // Live Coding
    lua.scriptMouseMoved(x,y);
}

//--------------------------------------------------------------
void gamuzaMain::mouseDragged(int x, int y, int button){
    if(x < fboDrawingPosX){
        scaledMouseX = 0;
    }else if(x > fboDrawingW + fboDrawingPosX){
        scaledMouseX = projectionScreenW;
    }else{
        scaledMouseX = x - fboDrawingPosX;
        scaledMouseX /= fboDrawingW;
        scaledMouseX *= projectionScreenW;
    }
    
    if(y < fboDrawingPosY){
        scaledMouseY = 0;
    }else if(y > fboDrawingH + fboDrawingPosY){
        scaledMouseY = projectionScreenH;
    }else{
        scaledMouseY = y - fboDrawingPosY;
        scaledMouseY /= fboDrawingH;
        scaledMouseY *= projectionScreenH;
    }
    
    // External mouse
    externMouseX = scaledMouseX;
    externMouseY = scaledMouseY;
    
    // MAPPING
	if(drawGrid){
        finalTextureMapping.mouseDragged(externMouseX, externMouseY);
	}
    
    // Live Coding
    lua.scriptMouseDragged(x,y, button);
}

//--------------------------------------------------------------
void gamuzaMain::mousePressed(int x, int y, int button){
    if(x < fboDrawingPosX){
        scaledMouseX = 0;
    }else if(x > fboDrawingW + fboDrawingPosX){
        scaledMouseX = projectionScreenW;
    }else{
        scaledMouseX = x - fboDrawingPosX;
        scaledMouseX /= fboDrawingW;
        scaledMouseX *= projectionScreenW;
    }
    
    if(y < fboDrawingPosY){
        scaledMouseY = 0;
    }else if(y > fboDrawingH + fboDrawingPosY){
        scaledMouseY = projectionScreenH;
    }else{
        scaledMouseY = y - fboDrawingPosY;
        scaledMouseY /= fboDrawingH;
        scaledMouseY *= projectionScreenH;
    }
    
    // External mouse
    externMouseX = scaledMouseX;
    externMouseY = scaledMouseY;
    
	// MAPPING
    if(drawGrid){
        finalTextureMapping.mousePressed(externMouseX, externMouseY);
	}
    
    // Live Coding
    lua.scriptMousePressed(x,y, button);
    
}

//--------------------------------------------------------------
void gamuzaMain::mouseReleased() {
    
}

//--------------------------------------------------------------
void gamuzaMain::mouseReleased(int x, int y, int button){
	if(x < fboDrawingPosX){
        scaledMouseX = 0;
    }else if(x > fboDrawingW + fboDrawingPosX){
        scaledMouseX = projectionScreenW;
    }else{
        scaledMouseX = x - fboDrawingPosX;
        scaledMouseX /= fboDrawingW;
        scaledMouseX *= projectionScreenW;
    }
    
    if(y < fboDrawingPosY){
        scaledMouseY = 0;
    }else if(y > fboDrawingH + fboDrawingPosY){
        scaledMouseY = projectionScreenH;
    }else{
        scaledMouseY = y - fboDrawingPosY;
        scaledMouseY /= fboDrawingH;
        scaledMouseY *= projectionScreenH;
    }
    
    // External mouse
    externMouseX = scaledMouseX;
    externMouseY = scaledMouseY;
    
    // MAPPING
	if(drawGrid){
        finalTextureMapping.mouseReleased(externMouseX, externMouseY);
	}
    
    // Live Coding
    lua.scriptMouseReleased(x, y, button);
    
}

//--------------------------------------------------------------
void gamuzaMain::mouseScrolled(float x, float y) {
    
}

#endif
