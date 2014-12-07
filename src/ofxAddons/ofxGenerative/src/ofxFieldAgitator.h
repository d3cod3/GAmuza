
#pragma once

#include "ofPoint.h"

class ofxFieldAgitator : public ofPoint {

public:
	
	ofxFieldAgitator() : ofPoint(){
		
		init();
	}
	
	ofxFieldAgitator(ofPoint p) : ofPoint(p){
		
		init();
	}
	
	void init(){
	
		angle = 0;
		distance = 0;
	}
	
	void update(){
	
		angle += angleRate;
		distance += distanceRate;
	}
	
	float getAngle(){
	
		return angle;
	}
	
	ofPoint getDistance(){
		
		ofPoint result;
		result.x = this->x + cos(angle) * distance;
		result.y = this->y + sin(angle) * distance;
	
		return result;
	}
	
	void draw(){
	
		ofSetColor(0, 0, 255);
		
		ofPushMatrix();
		
		ofTranslate(*this);
		
		ofRotate(angle*RAD_TO_DEG, 0, 0, 1);
		
		ofCircle(0, 0, 4);
		
		ofLine(0, 0, distance, 0);
		
		ofPopMatrix();
	}
	
	float angle;
	float distance;
	
	float angleRate;
	float distanceRate;
	
};