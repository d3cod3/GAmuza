//
//  ofxBehavior.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxBehavior.h"
#include "ofxRParticle.h"

ofxBehavior::ofxBehavior()
{
    init();
}

ofxBehavior::~ofxBehavior()
{
    if(bAllocatedMagnitude)
    {
        delete magnitude;
    }
}

void ofxBehavior::init()
{
    bEnabled = true;
    bAllocatedMagnitude = true;
    magnitude = new float;
    setMagnitude(1.0);
}

void ofxBehavior::update()
{
    
}

void ofxBehavior::actUpon(ofxRParticle particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
 
}

bool* ofxBehavior::getEnabledPtr()
{
    return &bEnabled;
}

bool ofxBehavior::isEnabled()
{
    return bEnabled;
}

float* ofxBehavior::getMagnitudePtr()
{
    return magnitude;
}

void ofxBehavior::setMagnitudePtr(float *_magnitude)
{
    if(bAllocatedMagnitude)
    {
        delete magnitude;
        bAllocatedMagnitude = false;
    }
    magnitude = _magnitude;
}

float ofxBehavior::getMagnitude()
{
    return *magnitude; 
}

void ofxBehavior::setMagnitude(float _magnitude)
{
    *magnitude = _magnitude; 
}