//
//  ofxBox2dPrismaticJoint.cpp
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#include "ofxBox2dPrismaticJoint.h"

//----------------------------------------
ofxBox2dPrismaticJoint::ofxBox2dPrismaticJoint(){
    
}

//----------------------------------------
void ofxBox2dPrismaticJoint::destroy(){
    if (world == NULL || joint == NULL) return;
	world->DestroyJoint(joint);
	joint       = NULL;
    alive       = false;
}

//----------------------------------------
void ofxBox2dPrismaticJoint::setup(b2World *w, b2Body *body1, b2Body *body2, b2Vec2 anchor, b2Vec2 axis, float angle,
                                   float lowerTransition, float upperTransition, bool bEnableLimit,
                                   float maxMotorForce, float motorSpeed, bool bEnableMotor,
                                   bool bCollideConnected){
    
    setWorld(w);
    
    b2PrismaticJointDef jointDef;
    jointDef.Initialize(body1, body2, anchor, axis);
    jointDef.referenceAngle     = angle;
    jointDef.lowerTranslation   = lowerTransition;
    jointDef.upperTranslation   = upperTransition;
    jointDef.enableLimit        = bEnableLimit;
    jointDef.maxMotorForce      = maxMotorForce;
    jointDef.motorSpeed         = motorSpeed;
    jointDef.enableMotor        = bEnableMotor;
    jointDef.collideConnected   = bCollideConnected;
    
    joint = (b2PrismaticJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
    
}

//----------------------------------------
b2PrismaticJoint* ofxBox2dPrismaticJoint::getJoint(){
    return joint;
}

//----------------------------------------
float ofxBox2dPrismaticJoint::getLowerLimit(){
    return (float)joint->GetLowerLimit();
}

//----------------------------------------
float ofxBox2dPrismaticJoint::getUpperLimit(){
    return (float)joint->GetUpperLimit();
}

//----------------------------------------
void ofxBox2dPrismaticJoint::setLimits(float lower, float upper){
    joint->SetLimits((float32)lower, (float32)upper);
}

//----------------------------------------
void ofxBox2dPrismaticJoint::setEnableLimit(bool flag){
    joint->EnableLimit(flag);
}

//----------------------------------------
bool ofxBox2dPrismaticJoint::isLimitEnabled(){
    return joint->IsLimitEnabled();
}

//----------------------------------------
void ofxBox2dPrismaticJoint::setEnableMotor(bool flag){
    joint->EnableMotor(flag);
}

//----------------------------------------
bool ofxBox2dPrismaticJoint::isMotorEnabled(){
    return joint->IsMotorEnabled();
}

//----------------------------------------
void ofxBox2dPrismaticJoint::setMotorSpeed(float val){
    joint->SetMotorSpeed((float32)val);
}

//----------------------------------------
float ofxBox2dPrismaticJoint::getMotorSpeed(){
    return joint->GetMotorSpeed();
}

//----------------------------------------
void ofxBox2dPrismaticJoint::setMaxMotorForce(float val){
    joint->SetMaxMotorForce(val);
}

//----------------------------------------
float ofxBox2dPrismaticJoint::getMotorForce(){
    return joint->GetMotorForce();
}

//----------------------------------------
ofVec2f ofxBox2dPrismaticJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dPrismaticJoint::getReactionForceB2D(float inv_dt) const {
	return joint->GetReactionForce(inv_dt);
}

float ofxBox2dPrismaticJoint::getReactionTorque(float inv_dt) const {
	return (float)joint->GetReactionTorque(inv_dt);
}




