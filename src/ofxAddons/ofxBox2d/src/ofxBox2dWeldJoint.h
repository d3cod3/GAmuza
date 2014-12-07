//
//  ofxBox2dWeldJoint.h
//
//  Created by TORU URAKAWA on 2012/10/22.
//
//

#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dBaseJoint.h"

class ofxBox2dWeldJoint : public ofxBox2dBaseJoint{
protected:
    b2WeldJoint *joint;
    
public:
    ofxBox2dWeldJoint();
    void    destroy();
    
    void    setup(b2World *w, b2Body* body1, b2Body* body2, const b2Vec2& anchor,
                  float angle,
                  bool bCollideConnected);
    
    void    setup(b2World *w, b2Body* body1, b2Body* body2, const b2Vec2& anchor,
                  bool bCollideConnected);
    
    //----------------------------------------
    ofVec2f getReactionForce(float inv_dt) const;
    b2Vec2  getReactionForceB2D(float inv_dt) const;
    float   getReactionTorque(float inv_dt) const;
    
};