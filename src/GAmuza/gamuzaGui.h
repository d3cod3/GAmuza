#ifndef _GAMUZAGUI
#define _GAMUZAGUI

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupGui(){
	
    asRatio = reduceToAspectRatio(projectionScreenW,projectionScreenH);
    isFullscreen = false;
    externIsFullscreen = false;
    if(projectionScreenW > MAIN_WINDOW_W){
        fboDrawingW         = (projectionScreenW*MAIN_WINDOW_H)/projectionScreenH;
        fboDrawingH         = MAIN_WINDOW_H;
        fboDrawingPosX      = (MAIN_WINDOW_W-fboDrawingW)/2.0;
        fboDrawingPosY      = 0;
    }else{
        if(projectionScreenH < MAIN_WINDOW_H){
            fboDrawingW         = MAIN_WINDOW_W;
            fboDrawingH         = (projectionScreenH*MAIN_WINDOW_W)/projectionScreenW;
            fboDrawingPosX      = 0;
            fboDrawingPosY      = (MAIN_WINDOW_H-fboDrawingH)/2.0;
        }else{
            fboDrawingH = MAIN_WINDOW_H;
            fboDrawingW = (projectionScreenW*MAIN_WINDOW_H)/projectionScreenH;
            fboDrawingPosX      = (MAIN_WINDOW_W-fboDrawingW)/2.0;
            fboDrawingPosY      = 0;
        }
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
void gamuzaMain::gamuzaFullscreen(int actualScreen){
    
    _actualScreen = actualScreen;
    
	if(isFullscreen){ // go to window mode
		isFullscreen = false;
        externIsFullscreen = false;
        if(projectionScreenW > MAIN_WINDOW_W){
			fboDrawingW         = (projectionScreenW*MAIN_WINDOW_H)/projectionScreenH;
			fboDrawingH         = MAIN_WINDOW_H;
			fboDrawingPosX      = (MAIN_WINDOW_W-fboDrawingW)/2.0;
			fboDrawingPosY      = 0;
		}else{
            if(projectionScreenH < MAIN_WINDOW_H){
                fboDrawingW         = MAIN_WINDOW_W;
                fboDrawingH         = (projectionScreenH*MAIN_WINDOW_W)/projectionScreenW;
                fboDrawingPosX      = 0;
                fboDrawingPosY      = (MAIN_WINDOW_H-fboDrawingH)/2.0;
            }else{
                fboDrawingH         = MAIN_WINDOW_H;
                fboDrawingW         = (projectionScreenW*MAIN_WINDOW_H)/projectionScreenH;
                fboDrawingPosX      = (MAIN_WINDOW_W-fboDrawingW)/2.0;
                fboDrawingPosY      = 0;
            }
		}
	}else{ // go to fullscreen mode (at specified screen only, GAmuza do not span fullscreen over all screens)
        
        int theScreenX = 0;
        int theScreenY = 0;
        int theScreenW = _screensData[actualScreen].width;
        int theScreenH = _screensData[actualScreen].height;
        
        for(int i=0;i<actualScreen;i++){
            theScreenX += _screensData[i].x;
            theScreenY += _screensData[i].y;
        }
        
		isFullscreen = true;
        externIsFullscreen = true;
        if(projectionScreenW > theScreenW && projectionScreenH > theScreenH){ // width & height bigger than screen
            if(asRatio.x > asRatio.y){ // horizontal texture
                fboDrawingW         = theScreenW;
                fboDrawingH         = (asRatio.y*fboDrawingW)/asRatio.x;
                fboDrawingPosX      = 0;
                fboDrawingPosY      = (theScreenH-fboDrawingH)/2.0;
            }else{ // vertical texture
                fboDrawingH         = theScreenH;
                fboDrawingW         = (asRatio.x*fboDrawingH)/asRatio.y;
                fboDrawingPosX      = (theScreenW-fboDrawingW)/2.0;
                fboDrawingPosY      = 0;
            }
		}else if(projectionScreenW > theScreenW && projectionScreenH <= theScreenH){ // width bigger
            // horizontal texture only (due to landscape screens nature)
            fboDrawingW         = theScreenW;
            fboDrawingH         = (asRatio.y*fboDrawingW)/asRatio.x;
            fboDrawingPosX      = 0;
            fboDrawingPosY      = (theScreenH-fboDrawingH)/2.0;
        }else if(projectionScreenW <= theScreenW && projectionScreenH > theScreenH){ // height bigger
            fboDrawingH         = theScreenH;
            fboDrawingW         = (asRatio.x*fboDrawingH)/asRatio.y;
            fboDrawingPosX      = (theScreenW-fboDrawingW)/2.0;
            fboDrawingPosY      = 0;
        }else{ // smaller than screen
            if(asRatio.x > asRatio.y){ // horizontal texture
                if((asRatio.x/asRatio.y) < 1.5){
                    fboDrawingH         = theScreenH;
                    fboDrawingW         = (projectionScreenW*fboDrawingH)/projectionScreenH;
                    fboDrawingPosX      = (theScreenW-fboDrawingW)/2.0;
                    fboDrawingPosY      = 0;
                }else{
                    fboDrawingW         = theScreenW;
                    fboDrawingH         = (projectionScreenH*fboDrawingW)/projectionScreenW;
                    fboDrawingPosX      = 0;
                    fboDrawingPosY      = (theScreenH-fboDrawingH)/2.0;
                }
            }else{ // vertical texture
                fboDrawingW         = theScreenW;
                fboDrawingH         = (projectionScreenH*fboDrawingW)/projectionScreenW;
                fboDrawingPosX      = 0;
                fboDrawingPosY      = (theScreenH-fboDrawingH)/2.0;
            }
        }
        
	}
	
}

//--------------------------------------------------------------
ofVec2f gamuzaMain::reduceToAspectRatio(int _w, int _h){
    ofVec2f _res;
    int temp = _w*_h;
    if(temp>0){
        for(temp; temp>1; temp--){
            if((_w%temp==0) && (_h%temp==0)){
                _w/=temp;
                _h/=temp;
            }
        }
    }else if (temp<0){
        for (temp; temp<-1; temp++){
            if ((_w%temp==0) && (_h%temp==0)){
                _w/=temp;
                _h/=temp;
            }
        }
    }
    _res.set(_w,_h);
    return _res;
}

#endif
