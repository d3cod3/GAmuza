
#pragma once

#include "ofMain.h"
#include "ofxNSWindowApp.h"
#include "ofxControlPanel.h"
#include "gamuzaMain.h"

extern gamuzaMain   *gapp; // external reference to gamuza app, declared in AppDelegate.h

class gaOSCModule : public ofxNSWindowApp {
	
public:
    
	gaOSCModule(int windowW, int windowH);
    ~gaOSCModule();
	
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
    
    void setupGui();
    void updateGui();
    void drawGui();
    
    void restart();
    
    ofxControlPanel             gui;
    simpleColor					gamuzaMainColor;
    simpleColor					gamuzaWhiteColor;
    simpleColor					gamuzaMarkColor;
    simpleColor					gamuzaChartBackColor;
    ofTrueTypeFont				fontSmall;
    
    int                         winW, winH;
	
};