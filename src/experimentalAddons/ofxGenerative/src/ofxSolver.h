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

#ifndef OFXSOLVER
#define OFXSOLVER

#include "ofxRParticle.h"

struct Derivative
{
    ofVec3f dpdt;          // derivative of position: velocity
    ofVec3f dvdt;          // derivative of velocity: acceleration
};

class ofxSolver             //Solves the Particle's Physical Simulation
{
public:
    ofxSolver(float *_dt = NULL);
    ~ofxSolver();
    virtual void init();
    virtual Derivative evaluate(ofxRParticle& particle, ofVec3f *iPos, ofVec3f *iVel, float dt, Derivative &d);
    virtual void update(ofxRParticle& particle);
    float *getDt();
    void setDtPtr(float *_dt);
    void setDt(float _dt);
protected:
    float *dt;
    Derivative zero, a, b, c, d; 
    bool bSelfAllocatedDt;
};

#endif
