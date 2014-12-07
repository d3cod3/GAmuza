/*
 * VideoPlayer.h
 *
 *  Created on: 08/04/2012
 *      Author: arturo
 */

#pragma once

#include "ofConstants.h"
#include "ofVideoPlayer.h"
#include "ofxPBO.h"
#include "ofFbo.h"

class ofxPBOVideoPlayer {
public:
    
    ofxPBOVideoPlayer() {}
    
	void load(string path);
	void play();
	void update();
	void draw();

	bool isFrameNew();
	ofVideoPlayer player;

private:
        void newFrame(ofPixels & pixels);

		ofxPBO pbo;
        ofTexture tex;
        ofFbo fbo;
        bool usePBO;
        bool updateTex;
};

