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

#ifndef OFXCIRCLE
#define OFXCIRCLE

#include "ofMain.h"

class ofxCircle
{
public:
	ofxCircle()
	{
		init(25, 60, ofVec3f(0,0,0));
	}
	
	ofxCircle(float _radius, int _resolution = 60, ofVec3f _center = ofVec3f(0,0,0))
	{
		init(_radius, _resolution, _center);
	}
	
	virtual ~ofxCircle()
	{
        delete center;
        for(int i = 0; i < points.size(); i++)
        {
            ofVec3f *pt = points[i];
            ofVec3f *hpt = homes[i];
            delete hpt;
            delete pt;
        }
        homes.clear(); 
        points.clear(); 
	}
	
    void init(float _radius, int _resolution, ofVec3f _center)
	{
        center = new ofVec3f(_center.x, _center.y, _center.z); 
        center->set(_center);
        resolution = _resolution;
        float thetaStart = 0.0;
        float thetaEnd = 360.0;
        float thetaInc = (thetaEnd-thetaStart)/(float)resolution;
        radius = _radius;        
        
        for(float theta = thetaStart; theta <= thetaEnd; theta+=thetaInc)
        {
            float x = radius*sin(ofDegToRad(theta))+center->x;
            float y = radius*cos(ofDegToRad(theta))+center->y;
            ofVec3f *p = new ofVec3f(x, y, center->z);
            ofVec3f *h = new ofVec3f(x, y, center->z);
            points.push_back(p);
            homes.push_back(h);
        }
	}
    
    void setRadius(float _radius)
    {
        radius = _radius; 
        for(int i = 0; i < points.size(); i++)
        {
            homes[i]->normalize();
            homes[i]->scale(radius);
            points[i]->set(*homes[i]);            
        }
    }
    
    void reset()
    {
        for(int i = 0; i < points.size(); i++)
        {
            points[i]->set(*homes[i]);
        }
    }
    
    vector<ofVec3f *> points;
    vector<ofVec3f *> homes;
    float radius;
    ofVec3f *center;
    int resolution;
};


#endif
