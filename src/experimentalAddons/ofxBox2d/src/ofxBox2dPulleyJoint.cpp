//
//  ofxBox2dPulleyJoint.cpp
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#include "ofxBox2dPulleyJoint.h"

//----------------------------------------
ofxBox2dPulleyJoint::ofxBox2dPulleyJoint(){
    
}

//----------------------------------------
void ofxBox2dPulleyJoint::setup(b2World *w, b2Body *body1, b2Body *body2,
                                const b2Vec2 &groundAnchor1, const b2Vec2 &groundAnchor2,
                                const b2Vec2 &anchor1, const b2Vec2 &anchor2,
                                float ratio,
                                bool bCollideConnected){
    
    setWorld(w);
    
    b2PulleyJointDef jointDef;
    jointDef.Initialize(body1, body2, groundAnchor1, groundAnchor2, anchor1, anchor2, ratio);
    jointDef.collideConnected = bCollideConnected;
    
    joint = (b2PulleyJoint*)world->CreateJoint(&jointDef);
    
    alive = true;
    
}

//----------------------------------------
void ofxBox2dPulleyJoint::destroy(){
    if (world == NULL || joint == NULL) return;
	world->DestroyJoint(joint);
	joint       = NULL;
    alive       = false;
}

//----------------------------------------
float ofxBox2dPulleyJoint::getLength1(){
    return (float)joint->GetLength1();
}

//----------------------------------------
float ofxBox2dPulleyJoint::getLength2(){
    return (float)joint->GetLength2();
}

//----------------------------------------
float ofxBox2dPulleyJoint::getRatio(){
    return (float)joint->GetRatio();
}


//----------------------------------------
ofVec2f ofxBox2dPulleyJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec =  getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}

b2Vec2 ofxBox2dPulleyJoint::getReactionForceB2D(float inv_dt) const {
	return joint->GetReactionForce(inv_dt);
}

float ofxBox2dPulleyJoint::getReactionTorque(float inv_dt) const {
	return (float)joint->GetReactionTorque(inv_dt);
}

