/*
 *  ofxGameCamera.cpp
 *
 *  Created by James George on 1/19/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#include "ofxGameCamera.h"

static float ClampAngle (float angle, float min, float max) {
	if (angle < -360.0f)
		angle += 360.f;
	if (angle > 360.0f)
		angle -= 360.0f;
	return ofClamp(angle, min, max);
}


ofxGameCamera::ofxGameCamera() {
	dampen = false;
	sensitivityX = 0.15f;
	sensitivityY = 0.15f;

	minimumX = -360.0f;
	maximumX =  360.0f;

	minimumY = -60.0f;
	maximumY =  60.0f;

	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;

	targetXRot = 0.0f;
	targetYRot = 0.0f;
	targetZRot = 0.0f;
	
	speed = 10.0f;
	
	lastMouse = ofVec2f(0,0);
	
	invertControls = false;
	usemouse = true;
	autosavePosition = false;
	useArrowKeys = false;

	applyRotation = true;
	applyTranslation = true;

	rollSpeed = 2;
	justResetAngles = false;

	positionChanged = false;
	rotationChanged = false;

	cameraPositionFile =  "_gameCameraPosition.xml";
}

void ofxGameCamera::setup(){
	ofAddListener(ofEvents().update, this, &ofxGameCamera::update);
	ofAddListener(ofEvents().keyPressed, this, &ofxGameCamera::keyPressed);
}

void ofxGameCamera::update(ofEventArgs& args){	
	rotationChanged = false;
	positionChanged = false;
	if(applyTranslation){
		int multiplier = invertControls ? -1 : 1;
		if(ofGetKeyPressed('w') || (useArrowKeys && ofGetKeyPressed(OF_KEY_UP)) ){
			if(dampen){
				targetNode.dolly(-speed);
			}else{
				dolly(-speed);
			}
			positionChanged = true;
		}
		
		if(ofGetKeyPressed('s') || (useArrowKeys && ofGetKeyPressed(OF_KEY_DOWN)) ){
			if(dampen){
				targetNode.dolly(speed);
			}else{
				dolly(speed);
			}
			positionChanged = true;
		}
		
		if(ofGetKeyPressed('a') || (useArrowKeys && ofGetKeyPressed(OF_KEY_LEFT)) ){
			if(dampen){
				targetNode.truck(-speed);
			}else{
				truck(-speed);
			}
			positionChanged = true;
		}
		
		if(ofGetKeyPressed('d') || (useArrowKeys && ofGetKeyPressed(OF_KEY_RIGHT)) ){
			if(dampen){
				targetNode.truck(speed);
			}
			else{
				truck(speed);
			}
			positionChanged = true;
		}
		
		if(ofGetKeyPressed('c') || (useArrowKeys && ofGetKeyPressed(OF_KEY_PAGE_DOWN)) ){
			if(dampen){
				targetNode.boom(-speed*multiplier);
			}
			else{
				boom(-speed*multiplier);
			}
			positionChanged = true;
		}
		
		if(ofGetKeyPressed('e') || (useArrowKeys && ofGetKeyPressed(OF_KEY_PAGE_UP)) ){
			if(dampen){
				targetNode.boom(speed*multiplier);
			}
			else{
				boom(speed*multiplier);
			}
			positionChanged = true;
		}
	}
	
	if(applyRotation){
		if(ofGetKeyPressed('r')){
			targetZRot += rollSpeed;
			rotationChanged = true;
		}
		if(ofGetKeyPressed('q')){
			targetZRot -= rollSpeed;
			rotationChanged = true;
		}
	}
	
	if(dampen){
		setPosition(getPosition() + (targetNode.getPosition() - getPosition()) *.2);
	}
	ofVec2f mouse( ofGetMouseX(), ofGetMouseY() );
	if(usemouse && applyRotation && ofGetMousePressed(0)){
        if(!justResetAngles){

			float dx = (mouse.x - lastMouse.x) * sensitivityX;
			float dy = (mouse.y - lastMouse.y) * sensitivityY;
//			cout << "b4 DX DY! " << dx << " " << dy << " " << targetXRot << " " << targetYRot << endl;
			targetXRot += dx * (invertControls ? -1 : 1);
			targetYRot += dy * (invertControls ? -1 : 1);
//			targetYRot = ClampAngle(targetYRot, minimumY, maximumY);
//			targetXRot = ClampAngle(targetXRot, minimumX, maximumX);
//			cout << "after DX DY! " << dx << " " << dy << " " << targetXRot << " " << targetYRot << endl;
			rotationChanged = true;
		}
		justResetAngles = false;
	}
	
	if(rotationChanged){
		updateRotation();		
	}
	
	lastMouse = mouse;
    
	if(!ofGetMousePressed(0) && autosavePosition && (rotationChanged || positionChanged)){
		saveCameraPosition();
	}
}

void ofxGameCamera::keyPressed(ofKeyEventArgs& args){
	
   
}

void ofxGameCamera::begin(ofRectangle rect) { 
	ofCamera::begin(rect);
}

void ofxGameCamera::setAnglesFromOrientation(){
	ofVec3f rotation = getOrientationEuler();
	rotationX = targetXRot = -rotation.y;
	rotationY = targetYRot = -rotation.z;
	rotationZ = targetZRot = -rotation.x;
//	cout << "rotation is " << ofVec3f(rotationX,rotationY,rotationZ) << endl;;
	justResetAngles = true;
}

void ofxGameCamera::updateRotation(){
	
	if(!applyRotation) return;
	
//	cout << "update rotation!" << endl;
	if(dampen){
		rotationX += (targetXRot - rotationX) *.2;
		rotationY += (targetYRot - rotationY) *.2;
		rotationZ += (targetZRot - rotationZ) *.2;
	}
	else{
		rotationX = targetXRot;
		rotationY = targetYRot;
		rotationZ = targetZRot;
	}
	
	setOrientation(ofQuaternion(0,0,0,1)); //reset
	setOrientation(getOrientationQuat() * ofQuaternion(-rotationZ, getZAxis()));
	setOrientation(getOrientationQuat() * ofQuaternion(-rotationX, getYAxis()));
	setOrientation(getOrientationQuat() * ofQuaternion(-rotationY, getXAxis()));
		
	targetNode.setOrientation(getOrientationQuat());
}

void ofxGameCamera::saveCameraPosition()
{
	ofxXmlSettings savePosition;
	savePosition.addTag("camera");
	savePosition.pushTag("camera");

	savePosition.addTag("position");
	savePosition.pushTag("position");

	savePosition.addValue("X", getPosition().x);
	savePosition.addValue("Y", getPosition().y);
	savePosition.addValue("Z", getPosition().z);

	savePosition.popTag(); //pop position

	savePosition.addTag("rotation");
	savePosition.pushTag("rotation");

	savePosition.addValue("X", rotationX);
	savePosition.addValue("Y", rotationY);
	savePosition.addValue("Z", rotationZ);

	savePosition.popTag(); //pop rotation

	savePosition.popTag(); //camera;

	savePosition.saveFile(cameraPositionFile);
}

void ofxGameCamera::loadCameraPosition()
{
	ofxXmlSettings loadPosition;
	if(loadPosition.loadFile(cameraPositionFile)){
		bool apply = applyRotation;
		applyRotation = true;
		loadPosition.pushTag("camera");
		loadPosition.pushTag("position");
		// tig: defaulting with floats so as to get floats back.
		setPosition(ofVec3f(loadPosition.getValue("X", 0.),
							loadPosition.getValue("Y", 0.),
							loadPosition.getValue("Z", 0.)));
		targetNode.setPosition(getPosition());
		
		loadPosition.popTag();

		loadPosition.pushTag("rotation");
		targetXRot = rotationX = loadPosition.getValue("X", 0.);
		targetYRot = rotationY = loadPosition.getValue("Y", 0.);
		targetZRot = rotationZ = loadPosition.getValue("Z", 0.);
		float fov = loadPosition.getValue("FOV", -1);
		if(fov != -1){
			setFov(fov);
		}
		
		loadPosition.popTag();

		loadPosition.popTag(); //pop camera;

		updateRotation();
		applyRotation = apply;
	}
	else{
		ofLog(OF_LOG_ERROR, "ofxGameCamera: couldn't load position!");
	}

}

void ofxGameCamera::reset(){
 	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;
    
	targetXRot = 0.0f;
	targetYRot = 0.0f;
	targetZRot = 0.0f;
    
    targetNode.setPosition(ofVec3f(0,0,0));
    targetNode.setOrientation(ofQuaternion());

}
