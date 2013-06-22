//
//  ofxBox2dDistanceJoint.h
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//
#pragma once

#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dBaseJoint.h"

class ofxBox2dDistanceJoint : public ofxBox2dBaseJoint {
    protected:
        b2DistanceJoint     *joint;
        
    public:
        ofxBox2dDistanceJoint();
        void    destroy();
    
        void    setup(b2World*, b2Body *body1, b2Body *body2,
                      float length, float frequencyHZ, float dampingRatio, bool bCollideConnected);
        
        void    setup(b2World*, b2Body *body1, b2Body *body2,
                      float frequencyHZ, float dampingRatio, bool bCollideConnected);
        
        void    setup(b2World*, b2Body *body1, b2Body *body2, b2Vec2 anchor1, b2Vec2 anchor2,
                      float length, float frequencyHZ, float dampingRatio, bool bCollideConnected);
        
        void    setup(b2World*, b2Body *body1, b2Body *body2, b2Vec2 anchor1, b2Vec2 anchor2,
                      float frequencyHZ, float dampingRatio, bool bCollideConnected);
        
        void    setLength(float);
        float   getLength();
        void    setFrequency(float);
        float   getFrequency();
        void    setDamping(float);
        float   getDamping();
    
        //----------------------------------------
        ofVec2f getReactionForce(float inv_dt) const;
        b2Vec2  getReactionForceB2D(float inv_dt) const;
        float   getReactionTorque(float inv_dt) const;
        
};
