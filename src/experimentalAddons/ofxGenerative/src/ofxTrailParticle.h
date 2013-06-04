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

#ifndef OFX_TRAILPARTICLE
#define OFX_TRAILPARTICLE

#include "ofxTrailParticle.h"

class ofxTrailParticle : public ofxParticle 
{
public:
	ofxTrailParticle() : ofxParticle()
	{
		initTrail(100);
	}
	
	ofxTrailParticle(ofVec3f _pos) : ofxParticle(_pos)
	{
		initTrail(100);		
	}

    ofxTrailParticle(ofVec3f _pos, int _trailLength) : ofxParticle(_pos)
	{
		initTrail(_trailLength);		
	}

	virtual ~ofxTrailParticle()
	{
        vector<ofVec3f *>::iterator it;    
        for ( it=trail.begin() ; it < trail.end(); it++ )
        {
            delete (*it);
            trail.erase(it);
        }                        
        trail.clear();           
	}
	
	virtual void initTrail(int _trailLength)
	{
        trailLength = _trailLength;
        for(int i = 0; i < trailLength; i++)
        {
            trail.push_back(new ofVec3f(pos.x, pos.y, pos.z));
        }
	}	
	
	virtual void updateTrail()
	{
        int start = trailLength-1; 
        for(int i = start; i >= 0; i--)
        {
            if(i-1 == -1)
            {
                trail[i]->set(pos); 
            }
            else
            {    
                trail[i]->set((*trail[i-1])); 
            }
        }
	}
    
	virtual void update()
	{
		if(!fixed)
		{
			ppos = pos; 
            for(int i = 0; i < externalForces.size(); i++)
            {
            	acc+=(*externalForces[i]); 
			}
			acc -=vel*damping; 
			acc.limit(accLimit); 
			vel+=acc; 
			vel.limit(velLimit); 			
			pos += vel; 		
			acc.set(0);             
		}		
        updateTrail();
	}    
    
    virtual void drawVertex(int _trailLength = 0)
    {
        glColor4f(color.r/255.0, color.g/255.0, color.b/255.0, color.a/255.0);    
        glVertex3f(pos.x, pos.y, pos.z);
        for(int i = 0; i < _trailLength; i++)
        {
            glVertex3f(trail[i]->x, trail[i]->y, trail[i]->z);            
        }
    }

	
	
protected:			//for reference
    //	ofVec3f pos, vel, acc, home; 
    //	ofVec3f *extforce; 
    //	float mass; 
    //	float damping; 
    //	float accLimit, velLimit; 
    //	ofColor color; 
    //	
    //	bool fixed; 
    //	float radius;
    
    vector<ofVec3f *> trail; 
    int trailLength; 
    
    
};


#endif