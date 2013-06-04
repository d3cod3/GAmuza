//
//  ofxDamperBehavior.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxDistorterBehavior.h"
#include "ofxRParticle.h"

ofxDistorterBehavior::ofxDistorterBehavior() : ofxBehavior()
{
    setup(); 
}

ofxDistorterBehavior::~ofxDistorterBehavior()
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

void ofxDistorterBehavior::setup()
{
    bAllocatedPosition = true;
    position = new ofVec3f(0,0,0);
    bAllocatedRadius = true;
    radius = new float;
    setRadius(100.0); 
    bAllocatedExpFactor = true;
    expFactor = new float;
    setExpFactor(2.0); 
}

void ofxDistorterBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    float length = pos.distance(*position);
//    if(length < (*radius))
//    {
        ofVec3f push = pos-(*position);
        push.normalize();
        push*=(*magnitude)*(*radius)*exp(-powf(length,*expFactor)/(*radius));
//    push*=(*magnitude)*(*radius)*log(length/(*radius));
    
//        push*=(*magnitude)*(*radius)*exp(-length/(*radius));
//        push*=(*magnitude)*(*radius)*exp(powf(-length/(*radius), 2.0));
        
        
        acc+= push*dt;
//    }
}

ofVec3f* ofxDistorterBehavior::getPositionPtr()
{
    return position;
}

void ofxDistorterBehavior::setPositionPtr(ofVec3f *_position)
{
    if(bAllocatedPosition)
    {
        delete position;
        bAllocatedPosition = false;
    }
    position = _position;    
}

ofVec3f& ofxDistorterBehavior::getPosition()
{
    return *position;
}

void ofxDistorterBehavior::setPosition(ofVec3f _position)
{
    *position = _position;
}

float* ofxDistorterBehavior::getRadiusPtr()
{
    return radius;
}

void ofxDistorterBehavior::setRadiusPtr(float *_radius)
{
    if(bAllocatedRadius)
    {
        delete radius;
        bAllocatedRadius = false;
    }
    radius = _radius;
}

float ofxDistorterBehavior::getRadius()
{
    return *radius;
}

void ofxDistorterBehavior::setRadius(float _radius)
{
    *radius = _radius;
}

float* ofxDistorterBehavior::getExpFactorPtr()
{
    return expFactor; 
}

void ofxDistorterBehavior::setExpFactorPtr(float *_expFactor)
{
    if(bAllocatedExpFactor)
    {
        delete expFactor;
        bAllocatedExpFactor = false;
    }
    expFactor = _expFactor;    
}

float ofxDistorterBehavior::getExpFactor()
{
    return *expFactor; 
}

void ofxDistorterBehavior::setExpFactor(float _expFactor)
{
    *expFactor = _expFactor; 
}