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

#ifndef OFX_PARTICLESYSTEM
#define OFX_PARTICLESYSTEM

#include <vector>
#include "ofxParticle.h"

class ofxParticleSystem 
{
public:	
	ofxParticleSystem()
	{
        init();
	}
    
    void init()
    {
    	uniqueIDs = 0; 
    }
	
	void clear()
	{
        vector<ofxParticle *>::iterator it;    
        for ( it=particles.begin() ; it < particles.end(); it++ )
        {
            delete (*it);
            particles.erase(it);
        }                        
        particles.clear();             
	}
    
	virtual ~ofxParticleSystem()
	{        
        clear();
	}
	
	virtual void update(float dt = 1)
	{
		for(it = particles.begin(); it < particles.end(); it++)
		{
			(*it)->update(dt);
		}		
	}
	
	virtual void updateAndDecay(float _amount, float dt = 1)
	{
		for(it = particles.begin(); it < particles.end(); it++)
		{
            (*it)->decay(_amount);
            if((*it)->isDead())
            {
                ofxParticle *p = (*it);
                delete p;
                particles.erase(it);
            }
            else
            {
                (*it)->update(dt);
            }
		}
	}
    
    virtual void setDamping(float _damping)
    {
		for(it = particles.begin(); it < particles.end(); it++)
		{
			(*it)->setDamping(_damping);
        }
    }
    
    virtual void setVelocityLimit(float _vlimit)
    {
        for(it = particles.begin(); it < particles.end(); it++)
		{
			(*it)->setVelocityLimit(_vlimit);
		}
    }
    
    virtual void setAccerationLimit(float _alimit)
    {
        for(it = particles.begin(); it < particles.end(); it++)
		{
			(*it)->setAccerationLimit(_alimit);
		}
    }

    virtual void randomize(float magnitude)
    {
        for(it = particles.begin(); it < particles.end(); it++)
		{
			(*it)->setAcc(ofVec3f(ofRandom(-magnitude, magnitude), ofRandom(-magnitude, magnitude), ofRandom(-magnitude, magnitude)));
		}
    }

	virtual void draw()
	{
        for(it = particles.begin(); it < particles.end(); it++)
		{
			(*it)->draw();
		}
	}
	
	virtual void addParticle(ofxParticle *p)
	{
		uniqueIDs++; 
		p->setID(uniqueIDs); 
		particles.push_back(p); 
	}
    	
	virtual int getCount()
	{
		return (int)particles.size(); 
	}
	
    vector<ofxParticle*> &getParticles()
    {
        return particles; 
    }
    
    ofxParticle* getParticle(int index)
	{
		if(index < particles.size() && index >= 0)
		{
			return particles[index];
		}
		else
		{
			return NULL;
		}        
	}

	vector<ofxParticle*> particles; 

protected:
    vector<ofxParticle*>::iterator it;
    int uniqueIDs;
};

#endif