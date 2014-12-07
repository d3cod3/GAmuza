//
//  ofxOceanCamera.cpp
//  VSOcean
//
//  Created by James George on 7/27/13.
//
//

#include "ofxOceanCamera.h"
#include "ofxOcean.h"

ofxOceanCamera::ofxOceanCamera(){
	ocean = NULL;
	baseWidth = 5;
	lift = 10;
	dampening = 0;
	heading = 0;
}

void ofxOceanCamera::update(){
	if(ocean == NULL){
		return;
	}

	
	//these vectors are to the front and to the side of the current camera
	ofVec3f frontDirection = ofVec3f(0, 0, 1).getRotated(heading, ofVec3f(0,1,0));
	ofVec3f sideDirection = ofVec3f(1, 0, 0).getRotated(heading, ofVec3f(0,1,0));
	
	// get aactual positions in each 4 directions, the wider the base the more stable the camera will feel
	ofVec3f middle = getPosition();
	ofVec3f front = middle + frontDirection * baseWidth;
	ofVec3f back  = middle - frontDirection * baseWidth;
	ofVec3f left  = middle - sideDirection  * baseWidth;
	ofVec3f right = middle + sideDirection  * baseWidth;
	
	//positions in height on the ocean
	middleBuoyant = ocean->floatingPosition(middle,false);
	frontBuoyant  = ocean->floatingPosition(front,false);
	backBuoyant   = ocean->floatingPosition(back,false);
	leftBuoyant   = ocean->floatingPosition(left,false);
	rightBuoyant  = ocean->floatingPosition(right,false);

	//based on the heights, find the orientation of the "raft"
	ofVec3f rollDirection = (rightBuoyant - leftBuoyant).normalized();
	ofVec3f dipDirection =  (frontBuoyant - backBuoyant).normalized();
	upDirection = (rollDirection).getCrossed(dipDirection).normalized();


	ofQuaternion sideRotation;
	//find the opposing angles
	float lrAngle = sideDirection.angle(rollDirection);
	if(lrAngle == lrAngle){ //check for NaN
		if(leftBuoyant.y > rightBuoyant.y) lrAngle *= -1;
		sideRotation.makeRotate(lrAngle, frontDirection);
	}

	ofQuaternion frontRotation;
	float fbAngle = frontDirection.angle(dipDirection);
	if(fbAngle == fbAngle){ //check for NaN
		if(backBuoyant.y < frontBuoyant.y) fbAngle *= -1;
		frontRotation.makeRotate(fbAngle, sideDirection);
	}
	
	//set the position based on the middle, consider dampening
	ofVec3f newPosition = middleBuoyant + ofVec3f(0,lift,0);
	setPosition(getPosition() + (newPosition - getPosition()) * (1.0-dampening) );

	//set the orientationb ased on the two angles
	setOrientation(frontRotation * sideRotation);
	rotate(heading, ofVec3f(0,1,0));
	
//	cout << "FRAME " << ofGetFrameNum() << endl;
//	cout << "	y rot " << heading << endl;
//	cout << "	sideDirection " << sideDirection << endl;
//	cout << "	rollDirection " << rollDirection << endl;
//	cout << "	frontDirection " << frontDirection << endl;
//	cout << "	dipDirection " << dipDirection << endl;
//	cout << "	sideRotation " << sideRotation.getEuler() << endl;
//	cout << "	frontRotation " << frontRotation.getEuler() << endl;
//	cout << "	final position  " << getPosition() << endl;
//	cout << "	final orientation  " << getOrientationEuler() << endl;

}

void ofxOceanCamera::drawDebug(){
	
	ofSphere(frontBuoyant, 2);
	ofSphere(backBuoyant, 2);
	ofSphere(leftBuoyant, 2);
	ofSphere(rightBuoyant,2);
	
	ofNode::draw();
}

