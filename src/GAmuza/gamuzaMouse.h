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
    
    // External mouse
    if(!isFullscreen){
        externMouseX = scaledMouseX;
        externMouseY = scaledMouseY;
    }else{
        externMouseX = scaledMouseX-fboDrawingPosX;
        externMouseY = scaledMouseY-fboDrawingPosY;
    }
    
    // MAPPING
	if(drawGrid){
        if(!isFullscreen){
            finalTextureMapping.mouseMoved(scaledMouseX, scaledMouseY);
        }else{
            finalTextureMapping.mouseMoved(externMouseX, externMouseY);
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
    
    // External mouse
    if(!isFullscreen){
        externMouseX = scaledMouseX;
        externMouseY = scaledMouseY;
    }else{
        externMouseX = scaledMouseX-fboDrawingPosX;
        externMouseY = scaledMouseY-fboDrawingPosY;
    }
    
    // MAPPING
	if(drawGrid){
        if(!isFullscreen){
            finalTextureMapping.mouseDragged(scaledMouseX, scaledMouseY);
        }else{
            finalTextureMapping.mouseDragged(externMouseX, externMouseY);
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
    
    // External mouse
    if(!isFullscreen){
        externMouseX = scaledMouseX;
        externMouseY = scaledMouseY;
    }else{
        externMouseX = scaledMouseX-fboDrawingPosX;
        externMouseY = scaledMouseY-fboDrawingPosY;
    }
    
	// MAPPING
    if(drawGrid){
        if(!isFullscreen){
            finalTextureMapping.mousePressed(scaledMouseX, scaledMouseY);
        }else{
            finalTextureMapping.mousePressed(externMouseX, externMouseY);
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
    
    // External mouse
    if(!isFullscreen){
        externMouseX = scaledMouseX;
        externMouseY = scaledMouseY;
    }else{
        externMouseX = scaledMouseX-fboDrawingPosX;
        externMouseY = scaledMouseY-fboDrawingPosY;
    }
    
    // MAPPING
	if(drawGrid){
        if(!isFullscreen){
            finalTextureMapping.mouseReleased(scaledMouseX, scaledMouseY);
        }else{
            finalTextureMapping.mouseReleased(externMouseX, externMouseY);
        }
	}
    
    // Live Coding
    lua.scriptMouseReleased(x, y, button);
    
}

//--------------------------------------------------------------
void gamuzaMain::mouseScrolled(float x, float y) {
    
}

#endif
