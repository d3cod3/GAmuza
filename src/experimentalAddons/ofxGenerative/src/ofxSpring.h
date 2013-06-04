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

#ifndef OFX_SPRING 
#define OFX_SPRING 

#include "ofMain.h"
#include "ofVec3f.h"

class ofxSpring 
{	
public:
	ofxSpring() 
	{
        init();
	}
	
    void init()
    {
        delta = 0; 
		restDist = 0; 
		k = 0; 
		p1 = NULL; 
		p2 = NULL; 		
		p1force = ofVec3f(0,0,0); 
		p2force = ofVec3f(0,0,0);                
		sid = -1; 
        color = ofColor(255, 15);     
    }
	
    ~ofxSpring() 
    {
    
    }

	ofxSpring(ofVec3f *_p1, ofVec3f *_p2, float _restDist, float _k)
	{
        init();
		p1 = _p1; 
		p2 = _p2; 
		restDist = _restDist;
		k = _k;        
	}
	
	void update(float dt = 1)
	{
		if(p1 != NULL && p2 != NULL)
		{
			float distance = p1->distance(*p2); 			
			ofVec3f direction = (*p1)-(*p2); 
			direction.normalize();
//            delta = 1.0 - restDist/distance;
            delta = (distance-restDist);
            direction*=k*delta*0.5;
			p2force.set(direction.x, direction.y,direction.z);
			direction*=(-1.0); 
			p1force.set(direction.x, direction.y,direction.z);
		}
	}
	
	void draw()
	{		
	    if(p1 != NULL && p2 != NULL)
		{    	
            ofSetColor(color); 
            ofLine(p1->x,p1->y,p1->z, p2->x,p2->y,p2->z);
		}		
	}
	
	ofVec3f& getForce(int index)
	{
		if(index == 0)
		{
			return p1force; 
		}
		else 		
		{
			return p2force; 			
		}
	}
	
	ofVec3f* getForcePtr(int index)
	{
		if(index == 0)
		{
			return &p1force; 
		}
		else 		
		{
			return &p2force; 			
		}		
	}
	
	void setRestDistance(float _restDist)
	{
		restDist = _restDist; 
	}
	
    float getRestDistance()
    {
        return restDist; 
    }
    
    float getK()
    {
        return k;
    }
    
    void setK(float _k)
    {
        k = _k; 
    }
    
    ofVec3f & getPos(int index)
    {
        if(index == 0)
        {
            return (*p1);            
        }
        else
        {
            return (*p2);             
        }
    }
    
	int getID() { return sid; }
	void setID(int _sid) { sid = _sid; } 

    float getDelta() { return delta; } 
	void setColor(ofColor _color){ color = _color; }    
	ofColor& getColor() { return color; } 
	void setColorAlpha(float _alpha) { color.a = _alpha; }
	float getColorAlpha() { return color.a;  } 

protected:
	float restDist;
    float delta; 
	float k; 
	ofVec3f *p1; 
	ofVec3f *p2; 
	ofVec3f p1force;
	ofVec3f p2force;	    
	int sid; 
    ofColor color; 
};



#endif
