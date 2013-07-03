/*
 *  ofxGameCamera.h
 *
 *  Created by James George on 1/19/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */
#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"

class ofxGameCamera : public ofCamera {
  public:
	
	ofxGameCamera();

	void setup();
    bool dampen;
	bool invertControls;
    void update(ofEventArgs& args);
    void keyPressed(ofKeyEventArgs& args);
	
	float sensitivityX;
	float sensitivityY;
	
	float minimumX;
	float maximumX;

	float minimumY;
	float maximumY;
	
	float rotationX;
	float rotationY;
	float rotationZ;	
	
	float targetXRot;
	float targetYRot;
	float targetZRot;
	
	float rollSpeed;
	float speed;
	
	virtual void begin(ofRectangle rect = ofGetWindowRect());
	void updateRotation();
	ofNode targetNode;
	
	ofVec2f lastMouse;
	bool usemouse;
	bool justResetAngles;
	bool useArrowKeys;
	bool autosavePosition;
	bool applyRotation;
	bool applyTranslation;
	
	string cameraPositionFile;
	void saveCameraPosition();
	void loadCameraPosition();
	
	bool positionChanged;
	bool rotationChanged;
	void setAnglesFromOrientation();
    void reset();
};
