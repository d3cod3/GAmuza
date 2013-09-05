//
//  ofxBox2dRevoluteJoint.h
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dBaseJoint.h"
#include "ofxBox2dUtils.h"

class ofxBox2dRevoluteJoint : public ofxBox2dBaseJoint {
    protected:
        b2RevoluteJoint     *joint;
    
    public:
        ofxBox2dRevoluteJoint();
        void    destroy();
    
        void    setup(b2World*, b2Body *body1, b2Body *body2, b2Vec2 anchor, float angle,
                      float lowerLimitRadian, float upperLimitRadian, bool bEnableLimit,
                      float motorSpeed, float maxMotorTorque, bool bEnableMotor, bool bCollideConnected);
    
        void    setup(b2World*, b2Body *body1, b2Body *body2, b2Vec2 anchor,
                      float lowerLimitRadian, float upperLimitRadian, bool bEnableLimit,
                      float motorSpeed, float maxMotorTorque, bool bEnableMotor, bool bCollideConnected);
    
        void    setup(b2World*, b2Body *body1, b2Body *body2, float anchorX, float anchorY,
                  float motorSpeed, float maxMotorTorque, bool bEnableMotor, bool bCollideConnected);
    
        b2RevoluteJoint*   getJoint();
    
        float   getLowerLimit();
        float   getUpperLimit();
        float   getAngle();
        void    setLimits(float, float);
        void    setEnableLimit(bool);
        bool    isLimitEnabled();
        void    setMotorSpeed(float);
        float   getMotorSpeed();
        void    setMaxMotorTorque(float);
        float   getMotorTorque();
        void    setEnableMotor(bool);
        bool    isMotorEnabled();
    
        //----------------------------------------
        ofVec2f getReactionForce(float inv_dt) const;
        b2Vec2  getReactionForceB2D(float inv_dt) const;
        float   getReactionTorque(float inv_dt) const;

};