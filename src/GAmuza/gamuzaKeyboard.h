#ifndef _GAMUZAKEYBOARD
#define _GAMUZAKEYBOARD

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::keyPressed(int key){
    
    bool alt = gamuzaKmap.isAltDown();
    
    ///////////////////////////////////////////
    // MAPPING keyboard control
    if(!activateMouseMapping){
        if(alt && key == OF_KEY_RETURN){
            manualEditMappingPoint = true;
            
        }
        
        if(alt && key == OF_KEY_BACKSPACE){
            manualEditMappingPoint = false;
            
        }
        
        if(alt && key == OF_KEY_LEFT){
            if(!manualEditMappingPoint){
                if(actualMappingPoint > 0){
                    actualMappingPoint--;
                }else{
                    actualMappingPoint = totalMappingPoints-1;
                }
            }else{
                finalTextureMapping.points[actualMappingPoint].x--;
            }
        }else if(alt && key == OF_KEY_RIGHT){
            if(!manualEditMappingPoint){
                if(actualMappingPoint < totalMappingPoints){
                    actualMappingPoint++;
                }else{
                    actualMappingPoint = 0;
                }
            }else{
                finalTextureMapping.points[actualMappingPoint].x++;
            }
        }else if(alt && key == OF_KEY_UP){
            if(manualEditMappingPoint){
                finalTextureMapping.points[actualMappingPoint].y--;
            }else{
                if(actualMappingPoint > gridRes){
                    actualMappingPoint -= (gridRes+1);
                }else{
                    actualMappingPoint += (gridRes+1)*gridRes;
                }
            }
        }else if(alt && key == OF_KEY_DOWN){
            if(manualEditMappingPoint){
                finalTextureMapping.points[actualMappingPoint].y++;
            }else{
                if(actualMappingPoint < ((gridRes+1)*(gridRes+1))-(gridRes+1)){
                    actualMappingPoint += (gridRes+1);
                }else{
                    actualMappingPoint -= (gridRes+1)*gridRes;
                }
            }
        }
    }
    ///////////////////////////////////////////
    
    // Live Coding
    lua.scriptKeyPressed(key);
    liveKey = key;
	
}

//--------------------------------------------------------------
void gamuzaMain::keyReleased(int key){
    
    bool alt = gamuzaKmap.isAltDown();
    
    // switch between mouse/keyboard Mapping points control
    if(alt && (key == 'm' || key == 'M')){
        activateMouseMapping = !activateMouseMapping;
    }
    
	switch (key){
        case ' ':
            break;
        case 'g':
            break;
        case 's':
            break;
        default:
            break;
    }
    
    // Live Coding
    lua.scriptKeyReleased(key);
    liveKey = key;
    
}

#endif
