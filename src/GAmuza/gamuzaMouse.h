#ifndef _GAMUZAMOUSE
#define _GAMUZAMOUSE

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::mouseMoved(int x, int y){
    scaledMouseX = x;
    scaledMouseY = y;
    if(!isFullscreen){
        scaledMouseX /= MAIN_WINDOW_W;
        scaledMouseX *= projectionScreenW;
        scaledMouseY /= MAIN_WINDOW_H;
        scaledMouseY *= projectionScreenH;
    }else{
        scaledMouseX /= fboDrawingW;
        scaledMouseX *= projectionScreenW;
        scaledMouseY /= fboDrawingH;
        scaledMouseY *= projectionScreenH;
    }
    scaledMouseX = ceil(scaledMouseX);
    scaledMouseY = ceil(scaledMouseY);
    externMouseX = scaledMouseX;
    externMouseY = scaledMouseY;
    
    // MAPPING
	if(drawGrid){
        if(!isFullscreen){
            finalTextureMapping.mouseMoved(scaledMouseX, scaledMouseY);
        }else{
            finalTextureMapping.mouseMoved(scaledMouseX-fboDrawingPosX-6, scaledMouseY-fboDrawingPosY-6);
        }
	}
    
    // Live Coding
    lua.scriptMouseMoved(x,y);
}

//--------------------------------------------------------------
void gamuzaMain::mouseDragged(int x, int y, int button){
    scaledMouseX = x;
    scaledMouseY = y;
    if(!isFullscreen){
        scaledMouseX /= MAIN_WINDOW_W;
        scaledMouseX *= projectionScreenW;
        scaledMouseY /= MAIN_WINDOW_H;
        scaledMouseY *= projectionScreenH;
    }else{
        scaledMouseX /= fboDrawingW;
        scaledMouseX *= projectionScreenW;
        scaledMouseY /= fboDrawingH;
        scaledMouseY *= projectionScreenH;
    }
    scaledMouseX = ceil(scaledMouseX);
    scaledMouseY = ceil(scaledMouseY);
    externMouseX = scaledMouseX;
    externMouseY = scaledMouseY;
    
    // MAPPING
	if(drawGrid){
        if(!isFullscreen){
            finalTextureMapping.mouseDragged(scaledMouseX, scaledMouseY);
        }else{
            finalTextureMapping.mouseDragged(scaledMouseX-fboDrawingPosX-6, scaledMouseY-fboDrawingPosY-6);
        }
	}
    
    // Live Coding
    lua.scriptMouseDragged(x,y, button);
}

//--------------------------------------------------------------
void gamuzaMain::mousePressed(int x, int y, int button){
    scaledMouseX = x;
    scaledMouseY = y;
    if(!isFullscreen){
        scaledMouseX /= MAIN_WINDOW_W;
        scaledMouseX *= projectionScreenW;
        scaledMouseY /= MAIN_WINDOW_H;
        scaledMouseY *= projectionScreenH;
    }else{
        scaledMouseX /= fboDrawingW;
        scaledMouseX *= projectionScreenW;
        scaledMouseY /= fboDrawingH;
        scaledMouseY *= projectionScreenH;
    }
    scaledMouseX = ceil(scaledMouseX);
    scaledMouseY = ceil(scaledMouseY);
    externMouseX = scaledMouseX;
    externMouseY = scaledMouseY;
    
	// MAPPING
    if(drawGrid){
        if(!isFullscreen){
            finalTextureMapping.mousePressed(scaledMouseX, scaledMouseY);
        }else{
            finalTextureMapping.mousePressed(scaledMouseX-fboDrawingPosX-6, scaledMouseY-fboDrawingPosY-6);
        }
	}
    
    // Live Coding
    lua.scriptMousePressed(x,y, button);
    
}

//--------------------------------------------------------------
void gamuzaMain::mouseReleased() {
    
}

//--------------------------------------------------------------
void gamuzaMain::mouseReleased(int x, int y, int button){
	scaledMouseX = x;
    scaledMouseY = y;
    if(!isFullscreen){
        scaledMouseX /= MAIN_WINDOW_W;
        scaledMouseX *= projectionScreenW;
        scaledMouseY /= MAIN_WINDOW_H;
        scaledMouseY *= projectionScreenH;
    }else{
        scaledMouseX /= fboDrawingW;
        scaledMouseX *= projectionScreenW;
        scaledMouseY /= fboDrawingH;
        scaledMouseY *= projectionScreenH;
    }
    scaledMouseX = ceil(scaledMouseX);
    scaledMouseY = ceil(scaledMouseY);
    externMouseX = scaledMouseX;
    externMouseY = scaledMouseY;
    
    // MAPPING
	if(drawGrid){
        if(!isFullscreen){
            finalTextureMapping.mouseReleased(scaledMouseX, scaledMouseY);
        }else{
            finalTextureMapping.mouseReleased(scaledMouseX-fboDrawingPosX-6, scaledMouseY-fboDrawingPosY-6);
        }
	}
    
    // Live Coding
    lua.scriptMouseReleased(x, y, button);
    
}

//--------------------------------------------------------------
void gamuzaMain::mouseScrolled(float x, float y) {
    
}

#endif
