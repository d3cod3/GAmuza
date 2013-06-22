//
//  ofxBox2dGearJoint.cpp
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#include "ofxBox2dGearJoint.h"


//----------------------------------------
ofxBox2dGearJoint::ofxBox2dGearJoint(){
    
}

//----------------------------------------
void ofxBox2dGearJoint::destroy(){
    if (world == NULL || joint == NULL) return;
	world->DestroyJoint(joint);
	joint       = NULL;
    alive       = false;
}

//----------------------------------------
void ofxBox2dGearJoint::setup(b2World* w,
                              ofxBox2dRevoluteJoint *revoluteJoint, ofxBox2dPrismaticJoint *prismaticJoint,
                              float ratio, bool bCollideConnected){
    
    setWorld(w);
    
    b2GearJointDef jointDef;
    jointDef.joint1             = revoluteJoint->getJoint();
    jointDef.joint2             = prismaticJoint->getJoint();
    jointDef.ratio              = ratio;
    jointDef.collideConnected   = bCollideConnected;
    
    joint = (b2GearJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
    
}

//----------------------------------------
void ofxBox2dGearJoint::setRatio(float val){
    joint->SetRatio((float32)val);
}

//----------------------------------------
float ofxBox2dGearJoint::getRatio(){
    return (float)joint->GetRatio();
}

//----------------------------------------
ofVec2f ofxBox2dGearJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec =  getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}

b2Vec2 ofxBox2dGearJoint::getReactionForceB2D(float inv_dt) const {
	return joint->GetReactionForce(inv_dt);
}

float ofxBox2dGearJoint::getReactionTorque(float inv_dt) const {
	return (float)joint->GetReactionTorque(inv_dt);
}

