//
//  ofxSphericalAttractionBehavior.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxSphericalAttractionBehavior.h"

ofxSphericalAttractionBehavior::ofxSphericalAttractionBehavior() : ofxBehavior()
{
    setup(); 
}

ofxSphericalAttractionBehavior::~ofxSphericalAttractionBehavior()
{
    if(bAllocatedPosition)
    {
        delete position;
    }
    if(bAllocatedRadius)
    {
        delete radius;
    }
}

void ofxSphericalAttractionBehavior::setup()
{
    bAllocatedPosition = true;
    position = new ofVec3f(0,0,0);
    bAllocatedRadius = true;
    radius = new float;
    setRadius(100.0);
}

void ofxSphericalAttractionBehavior::actUpon(ofxRParticle particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    ofVec3f temp = pos-(*position);
    temp.normalize();
    temp*=(*radius);
    temp+=(*position);

    ofVec3f push = pos-temp;
//    float d = push.length();
//    push.normalize();
//    push*=-d;
    acc-=(push)*(*magnitude)*dt;
}

ofVec3f* ofxSphericalAttractionBehavior::getPositionPtr()
{
    return position;
}

void ofxSphericalAttractionBehavior::setPositionPtr(ofVec3f *_position)
{
    if(bAllocatedPosition)
    {
        delete position;
        bAllocatedPosition = false;
    }
    position = _position;
}

ofVec3f& ofxSphericalAttractionBehavior::getPosition()
{
    return *position;
}

void ofxSphericalAttractionBehavior::setPosition(ofVec3f _position)
{
    *position = _position;
}

float* ofxSphericalAttractionBehavior::getRadiusPtr()
{
    return radius;
}

void ofxSphericalAttractionBehavior::setRadiusPtr(float *_radius)
{
    if(bAllocatedRadius)
    {
        delete radius;
        bAllocatedRadius = false;
    }
    radius = _radius;
}

float ofxSphericalAttractionBehavior::getRadius()
{
    return *radius;
}

void ofxSphericalAttractionBehavior::setRadius(float _radius)
{
    *radius = _radius;
}