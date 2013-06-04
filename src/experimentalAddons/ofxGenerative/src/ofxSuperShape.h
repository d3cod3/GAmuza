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

#ifndef OFXSUPERSHAPE
#define OFXSUPERSHAPE

#include "ofMain.h"
#include "ofxSmartParticleSystem.h"
#include "ofxSpringSystem.h"

class ofxSuperShape
{
public:
	ofxSuperShape()
	{
		init(25, 60, ofVec3f(0,0,0), 0.0, TWO_PI, 1.0, 1.0, 3.0, 100.0, 38.36, 36.35);
	}
	
	ofxSuperShape(float _radius, int _resolution = 60, ofVec3f _center = ofVec3f(0,0,0), float _thetaStart = 0.0, float _thetaEnd = TWO_PI, float _a = 1.0, float _b = 1.0, float _m = 3.0, float _n1 = 100.00, float _n2 = 38.36, float _n3 = 36.35)
	{
		init(_radius, _resolution, _center, _thetaStart, _thetaEnd, _a, _b, _m, _n1, _n2, _n3);
	}
	
	virtual ~ofxSuperShape()
	{
        sps->clear();
        delete sps;
        delete center;
        homes.clear();
        points.clear();
        colors.clear();
	}
	
    void init(float _radius, int _resolution, ofVec3f _center, float _thetaStart, float _thetaEnd, float _a, float _b, float _m, float _n1, float _n2, float _n3)
	{
        sps = new ofxSmartParticleSystem();
        radius = _radius;
        center = new ofVec3f(_center.x, _center.y, _center.z);
        center->set(_center);
        resolution = _resolution;
        thetaStart = _thetaStart;
        thetaEnd = _thetaEnd; 
        thetaInc = (thetaEnd-thetaStart)/(float)resolution;
        a = _a;
        b = _b;
        m = _m;
        n1 = _n1;
        n2 = _n2;
        n3 = _n3; 
        
        for(float theta = thetaStart; theta <= thetaEnd; theta+=thetaInc)
        {
            float raux = powf(abs(1.0/a)*abs(cos((m*theta/4.0))),n2) + powf(abs(1.0/b)*abs(sin(m*theta/4.0)),n3);
            float r = radius*powf(abs(raux),(-1.0/n1));
            float x=r*cos(theta);
            float y=r*sin(theta);
            ofxSmartParticle *sp = new ofxSmartParticle(ofVec3f(x, y, center->z));
            sp->setVelocityLimit(4);
            sp->setAccerationLimit(.25);
            sps->addParticle(sp);
            points.push_back(sp->getPosPtr());
            homes.push_back(sp->getHomePtr());
            colors.push_back(ofColor(0,255,255));
            deltas.push_back(0);
        }
        sps->setTargetHome(true);        
	}
    
    void update()
    {
        sps->update();
    }

    void setVelocityLimit(float _vlimit)
    {
        sps->setVelocityLimit(_vlimit);
    }

    void setAccerationLimit(float _alimit)
    {
        sps->setAccerationLimit(_alimit);
    }

    void setDamping(float _damping)
    {
        sps->setDamping(_damping);
    }
        
    void setRadius(float _radius, bool affectPoints = false)
    {
        radius = _radius;
        if(affectPoints)
        {
            updateShape();
        }
        else
        {
            updateShapeHomes();
        }
    }

    void setA(float _a, bool affectPoints = false)
    {
        a = _a;
        if(affectPoints)
        {
            updateShape();
        }
        else
        {
            updateShapeHomes();
        }
    }
    
    void setB(float _b, bool affectPoints = false)
    {
        b = _b;
        if(affectPoints)
        {
            updateShape();
        }
        else
        {
            updateShapeHomes();
        }
    }

    void setM(float _m, bool affectPoints = false)
    {
        m = _m;
        if(affectPoints)
        {
            updateShape();
        }
        else
        {
            updateShapeHomes();
        }
    }

    void setN1(float _n1, bool affectPoints = false)
    {
        n1 = _n1;
        if(affectPoints)
        {
            updateShape();
        }
        else
        {
            updateShapeHomes();
        }
    }

    void setN2(float _n2, bool affectPoints = false)
    {
        n2 = _n2;
        if(affectPoints)
        {
            updateShape();
        }
        else
        {
            updateShapeHomes();
        }
    }

    void setN3(float _n3, bool affectPoints = false)
    {
        n3 = _n3;
        if(affectPoints)
        {
            updateShape();
        }
        else
        {
            updateShapeHomes();
        }
    }
    
    void updateShape()
    {
        int i = 0;
        for(float theta = thetaStart; theta <= thetaEnd; theta+=thetaInc)
        {
            float raux = powf(abs(1.0/a)*abs(cos((m*theta/4.0))),n2) + powf(abs(1.0/b)*abs(sin(m*theta/4.0)),n3);
            float r = radius*powf(abs(raux),(-1.0/n1));
            float x=r*cos(theta);
            float y=r*sin(theta);
            homes[i]->set(x,y, center->z);            
            points[i]->set(x,y, center->z);
            i++;
        }        
    }
    
    void updateShapeHomes()
    {
        int i = 0;
        for(float theta = thetaStart; theta <= thetaEnd; theta+=thetaInc)
        {
            float raux = powf(abs(1.0/a)*abs(cos((m*theta/4.0))),n2) + powf(abs(1.0/b)*abs(sin(m*theta/4.0)),n3);
            float r = radius*powf(abs(raux),(-1.0/n1));
            float x=r*cos(theta);
            float y=r*sin(theta);
            homes[i]->set(x,y, center->z);
            i++;
        }
    }
    
    void reset()
    {

    }
    
    ofxSmartParticleSystem *sps; 
    vector<ofVec3f *> points;
    vector<ofVec3f *> homes;
    vector<ofColor> colors;
    vector<float> deltas;
    float radius;
    float thetaStart;
    float thetaEnd;
    float thetaInc;
    float a;
    float b;
    float m;
    float n1;
    float n2;
    float n3;
    ofVec3f *center;
    int resolution;
};


#endif
