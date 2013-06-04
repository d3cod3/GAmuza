//
//  ofxRParticleSystem.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxRParticleSystem.h"
#include "ofxRParticle.h"

ofxRParticleSystem::ofxRParticleSystem()
{
    init();
}

ofxRParticleSystem::~ofxRParticleSystem()
{
    delete dt;
    delete count;
    delete damping;
    delete restitution;
    delete accLimit;
    delete velLimit;
    delete solver;
    delete renderer;
    for(vector<ofxBehavior *>::iterator bit = behaviors.begin(); bit != behaviors.end(); bit++)
    {
        delete (*bit);
    }
    behaviors.clear();
    clear();
}

void ofxRParticleSystem::clear()
{
    particles.clear();
}

void ofxRParticleSystem::init()
{
    uniqueIDs = 0;
    count = new float;
    
    damping = new float;
    restitution = new float;
    accLimit = new float;
    velLimit = new float;
    dt = new float;
    
    setDt(1.0);
    setCount(0);
    setDamping(.25);
    setRestitution(1.0);
    setAccerationLimit(5.0);
    setVelocityLimit(10.0);
    
    renderer = new ofxRParticleRenderer();
    renderer->setParticlesPtr(&particles);

    solver = NULL;
    setSolver(new ofxSolver());
}

void ofxRParticleSystem::update()
{
    for(vector<ofxBehavior *>::iterator bit = behaviors.begin(); bit != behaviors.end(); bit++)
    {
        (*bit)->update(); 
    }
    
    for(it = particles.begin(); it != particles.end(); it++)
    {
        solver->update(*it);
    }
}

void ofxRParticleSystem::draw()
{
    renderer->draw();
}

void ofxRParticleSystem::addBehavior(ofxBehavior *b)
{
    behaviors.push_back(b);
}

void ofxRParticleSystem::addParticle(ofxRParticle& p)
{
    uniqueIDs++;
    p.setID(uniqueIDs);
    p.setDampingPtr(damping);
    p.setRestitutionPtr(restitution);
    p.setAccerationLimitPtr(accLimit);
    p.setVelocityLimitPtr(velLimit);
    p.setBehaviorVectorPtr(&behaviors);
    particles.push_back(p);
    setCount(uniqueIDs);
}

void ofxRParticleSystem::setDt(float _dt)
{
    *dt = _dt;
}

float* ofxRParticleSystem::getDt()
{
    return dt;
}

void ofxRParticleSystem::setDamping(float _damping)
{
    *damping = _damping;
}

float* ofxRParticleSystem::getDamping()
{
    return damping;
}

void ofxRParticleSystem::setRestitution(float _restitution)
{
    *restitution = _restitution;
}

float* ofxRParticleSystem::getRestitution()
{
    return restitution;
}

void ofxRParticleSystem::setVelocityLimit(float _vlimit)
{
    *velLimit = _vlimit;
}

float* ofxRParticleSystem::getVelocityLimit()
{
    return velLimit;
}

void ofxRParticleSystem::setAccerationLimit(float _alimit)
{
    *accLimit = _alimit;
}

float* ofxRParticleSystem::getAccelerationLimit()
{
    return accLimit;
}

void ofxRParticleSystem::setCount(int _count)
{
    *count = _count;
}

float* ofxRParticleSystem::getCount()
{
    return count;
}

vector<ofxRParticle>& ofxRParticleSystem::getParticles()
{
    return particles;
}

vector<ofxRParticle>* ofxRParticleSystem::getParticlesPtr()
{
    return &particles; 
}

ofxRParticle& ofxRParticleSystem::getParticle(int index)
{
    if(index < particles.size() && index >= 0)
    {
        return particles[index];
    }
    else
    {
        return particles[0];
    }
}

void ofxRParticleSystem::setRenderer(ofxRParticleRenderer *_renderer)
{
    if(renderer != NULL)
    {
        delete renderer;
    }
    renderer = _renderer;
    renderer->setParticlesPtr(&particles);    
}

ofxRParticleRenderer* ofxRParticleSystem::getRenderer()
{
    return renderer;
}

void ofxRParticleSystem::setSolver(ofxSolver *_solver)
{
    if(solver != NULL)
    {
        delete solver;
    }
    solver = _solver;
    solver->setDtPtr(dt);
}

ofxSolver* ofxRParticleSystem::getSolver()
{
    return solver;
}

void ofxRParticleSystem::randomize(float magnitude)
{
    for(it = particles.begin(); it != particles.end(); it++)
    {
        it->setPpos(ofVec3f(ofRandom(-magnitude, magnitude), ofRandom(-magnitude, magnitude), ofRandom(-magnitude, magnitude)));
    }
}