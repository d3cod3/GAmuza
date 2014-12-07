//
//  ofxOceanCamera.h
//  VSOcean
//
//  Created by James George on 7/27/13.
//
//

#include "ofMain.h"

#pragma once

class ofxOcean;
class ofxOceanCamera : public ofCamera {
  public:
	
	ofxOceanCamera();
	
	ofxOcean* ocean;
	void update();
	float baseWidth;
	float lift;
	float heading;
	
	void drawDebug();
	float dampening;

  protected:
	
	ofVec3f frontBuoyant;
	ofVec3f backBuoyant;
	ofVec3f leftBuoyant;
	ofVec3f rightBuoyant;
	ofVec3f middleBuoyant;
	ofVec3f upDirection;
	
};