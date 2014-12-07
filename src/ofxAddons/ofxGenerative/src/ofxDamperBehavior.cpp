//
//  ofxDamperBehavior.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxDamperBehavior.h"

ofxDamperBehavior::ofxDamperBehavior() : ofxBehavior()
{
    setup(); 
}

ofxDamperBehavior::~ofxDamperBehavior()
{

}

void ofxDamperBehavior::setup()
{

}

void ofxDamperBehavior::actUpon(ofxRParticle particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    acc -= vel*(*magnitude)*dt;
}