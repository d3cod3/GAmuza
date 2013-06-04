//
//  ofxBufferEffectorBehavior.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/25/13.
//
//

#include "ofxBufferEffectorBehavior.h"
#include "ofxRParticle.h"

ofxBufferEffectorBehavior::ofxBufferEffectorBehavior() : ofxBehavior()
{
    setup();
}

ofxBufferEffectorBehavior::~ofxBufferEffectorBehavior()
{
    
}

void ofxBufferEffectorBehavior::setup()
{
    buffer = NULL; 
}

void ofxBufferEffectorBehavior::actUpon(ofxRParticle *particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    particle->setRadius(buffer[particle->getID()%bufferSize]*(*magnitude));
}

void ofxBufferEffectorBehavior::setBuffer(float *_buffer, int _bufferSize)
{
    buffer = _buffer;
    bufferSize = _bufferSize;
}

float* ofxBufferEffectorBehavior::getBuffer()
{
    return buffer; 
}

int ofxBufferEffectorBehavior::getBufferSize()
{
    return bufferSize; 
}