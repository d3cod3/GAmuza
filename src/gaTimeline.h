
#pragma once

#include "ofMain.h"
#include "ofxNSWindowApp.h"

#include "ofxTimeline.h"
#include "ofxTLEmptyTrack.h"
#include "ofxTLEmptyKeyframes.h"

class gaTimeline : public ofxNSWindowApp {
	
public:
    
	gaTimeline(int screenW, int screenH);
    ~gaTimeline();
	
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
    
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
	
	void mouseScrolled(float x, float y);
    
    void bangFired(ofxTLBangEventArgs& args);
    
    void undoTimeline();
    void redoTimeline();
    void copyTimeline();
    void cutTimeline();
    void pasteTimeline();
    
    ofxTimeline timeline;
    string      actualBang;
    
    int scrW, scrH;
	
};