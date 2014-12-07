//
//  ofxBox2dGearJoint.h
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dBaseJoint.h"
#include "ofxBox2dRevoluteJoint.h"
#include "ofxBox2dPrismaticJoint.h"

class ofxBox2dGearJoint : public ofxBox2dBaseJoint {
protected:
    b2GearJoint *joint;
    
public:
    ofxBox2dGearJoint();
    void    destroy();
    
    void    setup(b2World *w,
                  ofxBox2dRevoluteJoint* revoluteJoint, ofxBox2dPrismaticJoint* prismaticJoint,
                  float ratio, bool bCollideConnected);
    
    void    setRatio(float);
    float   getRatio();
    
    //----------------------------------------
    ofVec2f getReactionForce(float inv_dt) const;
    b2Vec2  getReactionForceB2D(float inv_dt) const;
    float   getReactionTorque(float inv_dt) const;
    
};