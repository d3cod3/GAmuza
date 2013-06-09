//
//  ofxElectrostaticBehavior.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxElectroStaticBehavior.h"
#include "ofxRParticle.h"

ofxElectroStaticBehavior::ofxElectroStaticBehavior() : ofxBehavior()
{
    setup();     
}

ofxElectroStaticBehavior::~ofxElectroStaticBehavior()
{
    
}

void ofxElectroStaticBehavior::setup()
{
    particles = NULL; 
}

void ofxElectroStaticBehavior::actUpon(ofxRParticle particle, ofVec3f &pos, ofVec3f &vel, ofVec3f &acc, float dt)
{
    ofVec3f r = ofVec3f(0,0,0);
    for(vector<ofxRParticle>::iterator it = (*particles).begin(); it != (*particles).end(); it++)
    {
        if(it->getID() != particle.getID())
        {
            ofVec3f direction = it->getPpos() - pos;
            float distance = direction.length(); 
            direction /= distance*distance;
            r+=direction;
        }
    }
    r /= ((float)particles->size());
    acc-=r*(*magnitude)*dt;
}

void ofxElectroStaticBehavior::setParticlesPtr(vector<ofxRParticle> *_particles)
{
    particles = _particles; 
}
