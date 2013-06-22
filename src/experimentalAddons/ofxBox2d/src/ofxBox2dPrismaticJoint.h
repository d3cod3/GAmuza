//
//  ofxBox2dPrismaticJoint.h
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dBaseJoint.h"
#include "ofxBox2dUtils.h"

class ofxBox2dPrismaticJoint : public ofxBox2dBaseJoint {
    protected:
        b2PrismaticJoint *joint;
    
    public:
        ofxBox2dPrismaticJoint();
        void    destroy();

        void    setup(b2World*, b2Body *body1, b2Body *body2, b2Vec2 anchor, b2Vec2 axis, float angle,
                      float lowerTransition, float upperTransition, bool bEnableLimit,
                      float maxMotorForce, float motorSpeed, bool bEnableMotor, bool bCollideConnected);
    
        b2PrismaticJoint* getJoint();
    
        float   getLowerLimit();
        float   getUpperLimit();
        void    setLimits(float, float);
        void    setEnableLimit(bool);
        bool    isLimitEnabled();
        bool    isMotorEnabled();
        void    setEnableMotor(bool);
        void    setMotorSpeed(float);
        float   getMotorSpeed();
        void    setMaxMotorForce(float);
        float   getMotorForce();
        
        //----------------------------------------
        ofVec2f getReactionForce(float inv_dt) const;
        b2Vec2  getReactionForceB2D(float inv_dt) const;
        float   getReactionTorque(float inv_dt) const;
};