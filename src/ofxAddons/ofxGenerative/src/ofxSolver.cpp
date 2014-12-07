//
//  ofxSolver.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxSolver.h"
#include "ofxRParticle.h"

ofxSolver::ofxSolver(float _dt)
{
    init();
    setDt(_dt);
}

ofxSolver::~ofxSolver()
{
    if(bSelfAllocatedDt)
    {
        delete dt;
    }
}

void ofxSolver::init()
{
    zero.dpdt.set(0);
    zero.dvdt.set(0);
    dt = new float;
    bSelfAllocatedDt = true;
    setDt(1.0);
}

Derivative ofxSolver::evaluate(ofxRParticle& particle, ofVec3f *iPos, ofVec3f *iVel, float dt, Derivative &d)
{
    ofVec3f p = *iPos + d.dpdt*dt;
    ofVec3f v = *iVel + d.dvdt*dt;
    
    Derivative output;
    output.dpdt = v;
    output.dvdt = particle.calculateAcceleration(p, v, dt);
    return output;
}

void ofxSolver::update(ofxRParticle& particle)
{
    ofVec3f *ppos = particle.getPposPtr();
    ofVec3f *pos = particle.getPosPtr();
    ofVec3f *vel = particle.getVelPtr();
    
    ppos->set(*pos);
    
    a = evaluate(particle, pos, vel, 0.0f, zero);
    b = evaluate(particle, pos, vel, (*dt/2.0), a);
    c = evaluate(particle, pos, vel, (*dt/2.0), b);
    d = evaluate(particle, pos, vel, *dt, c);
    
    *pos += (*dt/6.0) * (a.dpdt + 2.0f*(b.dpdt + c.dpdt) + d.dpdt);
    *vel += (*dt/6.0) * (a.dvdt + 2.0f*(b.dvdt + c.dvdt) + d.dvdt);
    vel->limit(particle.getVelocityLimit());
//    (*vel)*=particle.getDamping();
}

float ofxSolver::getDt()
{
    return *dt;
}

void ofxSolver::setDtPtr(float *_dt)   //in case we set DT from the sketch
{
    if(bSelfAllocatedDt)
    {
        delete dt;
        bSelfAllocatedDt = false;
    }
    dt = _dt;
    setDt(*dt);
}

void ofxSolver::setDt(float _dt)
{
    *dt = _dt;
}