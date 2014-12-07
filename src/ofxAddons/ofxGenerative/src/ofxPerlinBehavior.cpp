//
//  ofxDamperBehavior.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxPerlinBehavior.h"
#include "ofxRParticle.h"

ofxPerlinBehavior::ofxPerlinBehavior() : ofxBehavior()
{
    setup();     
}

ofxPerlinBehavior::~ofxPerlinBehavior()
{
    
}

void ofxPerlinBehavior::setup()
{
    
}

void ofxPerlinBehavior::actUpon(ofxRParticle particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    float nx = ofSignedNoise(pos.x * 0.025, ofGetElapsedTimef(), particle.getID()*0.001);
    float ny = ofSignedNoise(pos.y * 0.025, ofGetElapsedTimef(), particle.getID()*0.001);
    float nz = ofSignedNoise(pos.z * 0.025, ofGetElapsedTimef(), particle.getID()*0.001);
    
    acc+=ofVec3f(nx, ny, nz)*(*magnitude)*dt;
}
