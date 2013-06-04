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

#ifndef OFXGENERICSHAPE
#define OFXGENERICSHAPE

#include "ofMain.h"
#include "ofxSmartParticleSystem.h"
#include "ofxSpringSystem.h"

class ofxGenericShape
{
public:
	ofxGenericShape()
	{
        
	}

	ofxGenericShape(ofPolyline _shape, int _resolution = 360, float _radius = 1, ofVec3f _center = ofVec3f(0,0,0))
	{
        init(_shape, _radius, _resolution, _center);
	}
	
	
	virtual ~ofxGenericShape()
	{
        ss->clear();
        sps->clear();
        delete ss; 
        delete sps;
        delete center;
        homes.clear();
        points.clear();
        colors.clear();
	}
	
    void init(ofPolyline &_shape, float _radius, int _resolution, ofVec3f &_center)
	{
        ss = new ofxSpringSystem(); 
        sps = new ofxSmartParticleSystem();
        radius = _radius;
        center = new ofVec3f(_center.x, _center.y, _center.z);
        center->set(_center);
        resolution = _resolution;

        shape = _shape.getResampledByCount(resolution); 
        
        ofxSmartParticle *last = NULL;
        vector<ofPoint> &shapepoints = shape.getVertices();
        for (int i = 0; i < shapepoints.size(); i++)
        {
            ofVec3f v = shapepoints[i];
            ofxSmartParticle *sp = new ofxSmartParticle(ofVec3f(radius*v.x, radius*v.y, center->z));
            sp->setVelocityLimit(4);
            sp->setAccerationLimit(.25);
            sps->addParticle(sp);
            points.push_back(sp->getPosPtr());
            homes.push_back(sp->getHomePtr());
            colors.push_back(ofColor(0,255,255));
            deltas.push_back(0);
            
            if(last != NULL)
            {
                ofxSpring *s = new ofxSpring(last->getPosPtr(), sp->getPosPtr(), last->getPos().distance(sp->getPos()), 2.0);
                ss->addSpring(s);
                last->addExternalForce(s->getForcePtr(0));
                sp->addExternalForce(s->getForcePtr(1));
                
                last = sp;                 
            }
            else
            {
                last = sp; 
            }
        }
        
        ofxSmartParticle *sp = (ofxSmartParticle *)sps->particles[0]; 
        ofxSpring *s = new ofxSpring(last->getPosPtr(), sp->getPosPtr(), last->getPos().distance(sp->getPos()), 1.0);
        ss->addSpring(s);        
        
        
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
    
    void setOffset(float x, float y, bool affectPoints = false)
    {
        if(affectPoints)
        {
            for (int i = 0; i < points.size(); i++)
            {
                ofVec3f v = shape[i];
                homes[i]->set(radius*v.x+x,radius*v.y+y, center->z);
                points[i]->set(radius*v.x+x,radius*v.y+y, center->z);
            }
        }
        else
        {
            for (int i = 0; i < points.size(); i++)
            {
                ofVec3f v = shape[i];
                homes[i]->set(radius*v.x+x,radius*v.y+y, center->z);
            }
        }
    }
    
    void updateShape()
    {
        for (int i = 0; i < points.size(); i++)
        {
            ofVec3f v = shape[i];
            homes[i]->set(radius*v.x,radius*v.y, center->z);
            points[i]->set(radius*v.x,radius*v.y, center->z);
        }
    }
    
    void updateShapeHomes()
    {
        for (int i = 0; i < points.size(); i++)
        {
            ofVec3f v = shape[i];
            homes[i]->set(radius*v.x,radius*v.y, center->z);
        }
    }
    
    ofPolyline shape; 
    ofxSmartParticleSystem *sps;
    ofxSpringSystem *ss; 
    vector<ofVec3f *> points;
    vector<ofVec3f *> homes;
    vector<ofColor> colors;
    vector<float> deltas;
    float radius;
    ofVec3f *center;
    int resolution;
};


#endif
