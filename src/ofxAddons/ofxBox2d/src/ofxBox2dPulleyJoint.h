//
//  ofxBox2dPulleyJoint.h
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dBaseJoint.h"

class ofxBox2dPulleyJoint : public ofxBox2dBaseJoint {
    protected:
        b2PulleyJoint *joint;

    public:
        ofxBox2dPulleyJoint();
        void    destroy();
    
        void    setup(b2World *w, b2Body* body1, b2Body* body2,
                      const b2Vec2& groundAnchor1, const b2Vec2& groundAnchor2,
                      const b2Vec2& anchor1, const b2Vec2& anchor2,
                      float ratio,
                      bool  bCollideConnected);
        
        float getLength1();
        float getLength2();
        float getRatio();
    
        //----------------------------------------
        ofVec2f getReactionForce(float inv_dt) const;
        b2Vec2  getReactionForceB2D(float inv_dt) const;
        float   getReactionTorque(float inv_dt) const;
        
};