
#pragma once

#include "ofMain.h"
#include "ofxNSWindowApp.h"

#include "ofxMtlMapping2D.h"

#include "gamuzaMain.h"

extern gamuzaMain   *gapp; // external reference to gamuza app, declared in AppDelegate.h


class gaMapperModule : public ofxNSWindowApp {
	
public:
    
	gaMapperModule(int windowW, int windowH);
    ~gaMapperModule();
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	void mouseReleased(int x, int y, int button);
	
	void mouseScrolled(float x, float y);
    
    void setModuleON(bool onOff);
    
    void resetPreview();
    void setFboDim(int w, int h);
    void getPreview(ofFbo p);
    
    
    ofxMtlMapping2D         *mapping;
	
    ofTexture				previewFbo;
    int                     fboW,fboH;
    float                   fboDrawingW;
    float                   fboDrawingH;
    float                   fboDrawingPosX;
    float                   fboDrawingPosY;
    
    float                   fboBoxW;
    float                   fboBoxH;
    float                   xMargin;
    float                   yMargin;
    
    int                     winW, winH;
    
    bool                    isON;
    
    
    
	
};