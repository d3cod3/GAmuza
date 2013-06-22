//
//  ofxBox2dRevoluteJoint.cpp
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//


#include "ofxBox2dRevoluteJoint.h"

//----------------------------------------
ofxBox2dRevoluteJoint::ofxBox2dRevoluteJoint(){
    
}

//----------------------------------------
void ofxBox2dRevoluteJoint::destroy(){
    if (world == NULL || joint == NULL) return;
	world->DestroyJoint(joint);
	joint       = NULL;
    alive       = false;
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setup(b2World *w, b2Body *body1, b2Body *body2, b2Vec2 anchor, float angle,
                                  float lowerLimitRadian, float upperLimitRadian, bool bEnableLimit,
                                  float motorSpeed, float maxMotorTorque, bool bEnableMotor,
                                  bool bCollideConnected){
    setWorld(w);
    
    b2RevoluteJointDef jointDef;
	jointDef.Initialize(body1, body2, anchor);
	jointDef.collideConnected	= bCollideConnected;
    jointDef.referenceAngle     = angle;
    jointDef.lowerAngle         = lowerLimitRadian;
    jointDef.upperAngle         = upperLimitRadian;
    jointDef.enableLimit        = bEnableLimit;
    jointDef.motorSpeed         = motorSpeed;
    jointDef.maxMotorTorque     = maxMotorTorque;
    jointDef.enableMotor        = bEnableMotor;
 
	joint						= (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    alive = true;
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setup(b2World *w, b2Body *body1, b2Body *body2, b2Vec2 anchor,
                                  float lowerLimitRadian, float upperLimitRadian, bool bEnableLimit,
                                  float motorSpeed, float maxMotorTorque, bool bEnableMotor,
                                  bool bCollideConnected){
    setWorld(w);
    
    b2RevoluteJointDef jointDef;
	jointDef.Initialize(body1, body2, anchor);
	jointDef.collideConnected	= bCollideConnected;
    jointDef.lowerAngle         = lowerLimitRadian;
    jointDef.upperAngle         = upperLimitRadian;
    jointDef.enableLimit        = bEnableLimit;
    jointDef.motorSpeed         = motorSpeed;
    jointDef.maxMotorTorque     = maxMotorTorque;
    jointDef.enableMotor        = bEnableMotor;
    
	joint						= (b2RevoluteJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
}

//----------------------------------------
b2RevoluteJoint* ofxBox2dRevoluteJoint::getJoint(){
    return joint;
}

//----------------------------------------
float ofxBox2dRevoluteJoint::getLowerLimit(){
    return (float)joint->GetLowerLimit();
}

//----------------------------------------
float ofxBox2dRevoluteJoint::getUpperLimit(){
    return (float)joint->GetUpperLimit();
}

//----------------------------------------
float ofxBox2dRevoluteJoint::getAngle(){
    return (float)joint->GetJointAngle();
}

void ofxBox2dRevoluteJoint::setLimits(float lower, float upper){
    joint->SetLimits((float32)lower, (float32)upper);
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setEnableLimit(bool flag){
    joint->EnableLimit(flag);
}

//----------------------------------------
bool ofxBox2dRevoluteJoint::isLimitEnabled(){
    return (float)joint->IsLimitEnabled();
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setMotorSpeed(float val){
    joint->SetMotorSpeed((float32)val);
}

//----------------------------------------
float ofxBox2dRevoluteJoint::getMotorSpeed(){
    joint->GetMotorSpeed();
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setMaxMotorTorque(float val){
    joint->SetMaxMotorTorque((float32)val);
}

//----------------------------------------
float ofxBox2dRevoluteJoint::getMotorTorque(){
    return (float)joint->GetMotorTorque();
}

//----------------------------------------
void ofxBox2dRevoluteJoint::setEnableMotor(bool flag){
    joint->EnableMotor(flag);
}

//----------------------------------------
bool ofxBox2dRevoluteJoint::isMotorEnabled(){
    return joint->IsMotorEnabled();
}

//----------------------------------------
ofVec2f ofxBox2dRevoluteJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dRevoluteJoint::getReactionForceB2D(float inv_dt) const {
	return joint->GetReactionForce(inv_dt);
}
float ofxBox2dRevoluteJoint::getReactionTorque(float inv_dt) const {
	return (float)joint->GetReactionTorque(inv_dt);
}


