//
//  ofxBox2dDistanceJoint.cpp
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#include "ofxBox2dDistanceJoint.h"
#include "ofxBox2dUtils.h"

//----------------------------------------
ofxBox2dDistanceJoint::ofxBox2dDistanceJoint(){
    
}

//----------------------------------------
void ofxBox2dDistanceJoint::destroy(){
    if (world == NULL || joint == NULL) return;
	world->DestroyJoint(joint);
	joint       = NULL;
	alive       = false;
}

//----------------------------------------
void ofxBox2dDistanceJoint::setup(b2World *w, b2Body *body1, b2Body *body2, b2Vec2 anchor1, b2Vec2 anchor2,
                                  float length, float frequencyHZ, float dampingRatio, bool bCollideConnected){
   
    setWorld(w);
    
	b2DistanceJointDef jointDef;
	jointDef.Initialize(body1, body2, anchor1, anchor2);
	jointDef.collideConnected	= bCollideConnected;
    jointDef.length             = length;
	jointDef.frequencyHz		= frequencyHZ;
	jointDef.dampingRatio		= dampingRatio;
    
	joint						= (b2DistanceJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
}

//----------------------------------------
void ofxBox2dDistanceJoint::setup(b2World *w, b2Body *body1, b2Body *body2, b2Vec2 anchor1, b2Vec2 anchor2,
                                  float frequencyHZ, float dampingRatio, bool bCollideConnected){
   
    setWorld(w);
    
	b2DistanceJointDef jointDef;
	jointDef.Initialize(body1, body2, anchor1, anchor2);
	jointDef.collideConnected	= bCollideConnected;
	jointDef.frequencyHz		= frequencyHZ;
	jointDef.dampingRatio		= dampingRatio;
        
	joint						= (b2DistanceJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
}

//----------------------------------------
void ofxBox2dDistanceJoint::setup(b2World *w, b2Body *body1, b2Body *body2,
                                  float length, float frequencyHZ, float dampingRatio, bool bCollideConnected){
 
    setWorld(w);
    
	b2DistanceJointDef jointDef;
	jointDef.Initialize(body1, body2, body1->GetWorldCenter(), body2->GetWorldCenter());
	jointDef.collideConnected	= bCollideConnected;
    jointDef.length             = length;
	jointDef.frequencyHz		= frequencyHZ;
	jointDef.dampingRatio		= dampingRatio;
    
	joint						= (b2DistanceJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
}

//----------------------------------------
void ofxBox2dDistanceJoint::setup(b2World *w, b2Body *body1, b2Body *body2,
                                  float frequencyHZ, float dampingRatio, bool bCollideConnected){
  
    setWorld(w);
    
	b2DistanceJointDef jointDef;
	jointDef.Initialize(body1, body2, body1->GetWorldCenter(), body2->GetWorldCenter());
	jointDef.collideConnected	= bCollideConnected;
	jointDef.frequencyHz		= frequencyHZ;
	jointDef.dampingRatio		= dampingRatio;
        
	joint						= (b2DistanceJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
}


//----------------------------------------
void ofxBox2dDistanceJoint::setLength(float val){
    joint->SetLength((float32)b2dNum(val));
}

//----------------------------------------
float ofxBox2dDistanceJoint::getLength(){
    return joint->GetLength();
}

//----------------------------------------
void ofxBox2dDistanceJoint::setFrequency(float val){
    joint->SetFrequency((float32)val);
}

//----------------------------------------
float ofxBox2dDistanceJoint::getFrequency(){
    return joint->GetFrequency();
}

//----------------------------------------
void ofxBox2dDistanceJoint::setDamping(float val){
    joint->SetDampingRatio((float32)val);
}

//----------------------------------------
float ofxBox2dDistanceJoint::getDamping(){
    return joint->GetDampingRatio();
}

//----------------------------------------
ofVec2f ofxBox2dDistanceJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dDistanceJoint::getReactionForceB2D(float inv_dt) const {
	return joint->GetReactionForce(inv_dt);
}

float ofxBox2dDistanceJoint::getReactionTorque(float inv_dt) const {
	return (float)joint->GetReactionTorque(inv_dt);
}




