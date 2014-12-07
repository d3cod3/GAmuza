//
//  ofxBox2dWeldJoint.cpp
//
//  Created by TORU URAKAWA on 2012/10/22.
//
//

#include "ofxBox2dWeldJoint.h"

//----------------------------------------
ofxBox2dWeldJoint::ofxBox2dWeldJoint(){
    
}

//----------------------------------------
void ofxBox2dWeldJoint::destroy(){
    if (world == NULL || joint == NULL) return;
	world->DestroyJoint(joint);
	joint       = NULL;
    alive       = false;
}

//----------------------------------------
void ofxBox2dWeldJoint::setup(b2World *w, b2Body *body1, b2Body *body2, const b2Vec2 &anchor,
                              float angle,
                              bool bCollideConnected){
    setWorld(w);
    
    b2WeldJointDef jointDef;
    jointDef.Initialize(body1, body2, anchor);
    jointDef.referenceAngle     = (float32)angle;
    jointDef.collideConnected   = bCollideConnected;
    
    joint = (b2WeldJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
    
}

//----------------------------------------
void ofxBox2dWeldJoint::setup(b2World *w, b2Body *body1, b2Body *body2, const b2Vec2 &anchor,
                              bool bCollideConnected){
    setWorld(w);
    
    b2WeldJointDef jointDef;
    jointDef.Initialize(body1, body2, anchor);
    jointDef.collideConnected   = bCollideConnected;
    
    joint = (b2WeldJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
    
}

//----------------------------------------
ofVec2f ofxBox2dWeldJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec =  getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}

b2Vec2 ofxBox2dWeldJoint::getReactionForceB2D(float inv_dt) const {
	return joint->GetReactionForce(inv_dt);
}

float ofxBox2dWeldJoint::getReactionTorque(float inv_dt) const {
	return (float)joint->GetReactionTorque(inv_dt);
}
