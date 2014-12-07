/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXRPARTICLESYSTEM
#define OFXRPARTICLESYSTEM

#include "ofMain.h"
#include "ofxSolver.h"
#include "ofxRParticle.h"
#include "ofxRParticleRenderer.h"

class ofxRParticleSystem
{    
public:
    ofxRParticleSystem();
    ~ofxRParticleSystem();
    void clear();
    void init();
    void update();
    void draw();
    void addBehavior(ofxBehavior b);
    void addParticle(ofxRParticle& p);
    void setDt(float _dt);
    float getDt();
    void setDamping(float _damping);
    float getDamping();
    void setRestitution(float _restitution);
    float getRestitution();
    void setVelocityLimit(float _vlimit);
    float getVelocityLimit();
    void setAccelerationLimit(float _alimit);
    float getAccelerationLimit();
    void setCount(int _count);
    float getCount();
    vector<ofxRParticle> &getParticles();
    vector<ofxRParticle> *getParticlesPtr();
    ofxRParticle& getParticle(int index);
    void setRenderer(ofxRParticleRenderer _renderer);
    ofxRParticleRenderer *getRenderer();
    void setSolver(ofxSolver _solver);
    ofxSolver *getSolver();
    
    void randomize(float magnitude);    
    
protected:
    vector<ofxRParticle>::iterator it;
    vector<ofxRParticle> particles;
    vector<ofxBehavior *> behaviors;
    ofxRParticleRenderer *renderer;
    ofxSolver *solver;

    int uniqueIDs;
    float *dt; 
    float *count;
	float *damping;
    float *restitution;
	float *accLimit;
    float *velLimit;
};

#endif
