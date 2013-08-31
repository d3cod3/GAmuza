
#pragma once

#include "ofMain.h"
#include "ofxNSWindowApp.h"


class gaVideoPreview : public ofxNSWindowApp {
	
public:
    
	gaVideoPreview();
    ~gaVideoPreview();
	
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
    
    void resetPreview();
    void setFboDim(int w, int h);
    void setPreviewDim(int w, int h);
    void getPreview(ofFbo p);
    
    void setModuleON(bool onOff); 
	
	
    ofTexture				previewFbo;
    int                     fboW,fboH;
    int                     previewW, previewH;
    
    float                   fboDrawingW;
    float                   fboDrawingH;
    float                   fboDrawingPosX;
    float                   fboDrawingPosY;
    
    bool                    isON;
	
};