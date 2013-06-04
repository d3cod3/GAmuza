//
//  ofxSolver.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxVerletSolver.h"
#include "ofxRParticle.h"

ofxVerletSolver::ofxVerletSolver(float *_dt) : ofxSolver(_dt)
{
    
}

ofxVerletSolver::~ofxVerletSolver()
{

}

void ofxVerletSolver::init()
{
    zero.dpdt.set(0);
    zero.dvdt.set(0);
    dt = new float;
    bSelfAllocatedDt = true;
    setDt(1.0);
}

void ofxVerletSolver::update(ofxRParticle& particle)
{
    ofVec3f *ppos = particle.getPposPtr();
    ofVec3f *pos = particle.getPosPtr();
    ofVec3f *vel = particle.getVelPtr();
    ofVec3f *acc = particle.getAccPtr();
    vel->set((*pos - *ppos));    
    ppos->set(*pos);
    vel->limit(particle.getVelocityLimit());
    particle.calculateAcceleration(*pos, *vel, *dt);
    *pos += *vel + *acc;
}