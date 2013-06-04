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

#ifndef OFX_SMARTPARTICLESYSTEM
#define OFX_SMARTPARTICLESYSTEM

#include "ofxParticleSystem.h"
#include "ofxSmartParticle.h"

class ofxSmartParticleSystem : public ofxParticleSystem 
{
public:
	ofxSmartParticleSystem() : ofxParticleSystem()
	{
        initSmartSystem();
	}

	void initSmartSystem()
    {
        useExternalCenter = false; 
		center = new ofVec3f(0,0,0); 
        useExternalDistorter = false; 
		distorter = new ofVec3f(0,0,0); 
		sphericalRadius = 10; 
		targetHome = false; 
		targetSphere = false; 
		distort = false; 
    }
    
	virtual ~ofxSmartParticleSystem()
	{
		if(distorter != NULL && !useExternalDistorter)
		{
			delete distorter; 
			distorter = NULL; 
		}
		if(center != NULL && !useExternalCenter)
		{
			delete center; 
			center = NULL; 
		}
        //Parent class will kill the particles for us
	}
	
	virtual void update()
	{
		for(int i = 0; i < particles.size(); i++)
		{
			particles[i]->update(); 
		}		
	}
	
	virtual void draw()
	{
		for(int i = 0; i < particles.size(); i++)
		{
			particles[i]->draw(); 
		}
	}
	
	virtual void addParticle(ofxSmartParticle *p)
	{
		uniqueIDs++; 
		p->setID(uniqueIDs); 		
		p->setCenterPos(center); 
		p->setSphericalRadius(sphericalRadius); 
		p->setTargetHome(targetHome); 
		p->setTargetSphere(targetSphere); 
		p->setDistortion(distort);
		if(distorter != NULL)
		{
			p->setDistortVector(distorter); 
		}
		particles.push_back(p); 
	}
	
	
	void setCenter(ofVec3f *_center)
	{
		if(center != NULL && !useExternalCenter)
		{
			delete center; 
		}
		useExternalCenter = true; 
		center = _center; 
		
		for(int i = 0; i < particles.size(); i++)
		{
			ofxSmartParticle *sp = (ofxSmartParticle *) particles[i];
			sp->setCenterPos(center); 
		}				
	}

	void setTargetHome(bool _targetHome)
	{
		targetHome = _targetHome; 
		for(int i = 0; i < particles.size(); i++)
		{
			ofxSmartParticle *sp = (ofxSmartParticle *) particles[i];
			sp->setTargetHome(targetHome); 
		}				
	}
    
    bool getTargetHome()
    {
        return targetHome; 
    }
	
	void toggleTargetHome()
	{
		targetHome = !targetHome; 
		setTargetHome(targetHome); 
	}

	void setTargetSphere(bool _targetSphere)
	{
		targetSphere = _targetSphere; 
		for(int i = 0; i < particles.size(); i++)
		{
			ofxSmartParticle *sp = (ofxSmartParticle *) particles[i];
			sp->setTargetSphere(targetSphere); 
		}						
	}
    
    bool getTargetSphere()
    {
        return targetSphere; 
    }
	
	void toggleTargetSphere()
	{
		targetSphere = !targetSphere; 
		setTargetSphere(targetSphere); 
	}
	
	void setSphericalRadius(float _sphericalRadius)
	{
		sphericalRadius = _sphericalRadius; 
		for(int i = 0; i < particles.size(); i++)
		{
			ofxSmartParticle *sp = (ofxSmartParticle *) particles[i];
			sp->setSphericalRadius(sphericalRadius); 
		}		
	}	
	
	float getSphericalRadius() { return sphericalRadius; }
	
	void setRandomizeVel()
	{
		for(int i = 0; i < particles.size(); i++)
		{
			ofxSmartParticle *sp = (ofxSmartParticle *) particles[i];
			sp->setRandomizeVel();
		}				
	}

	void setRandomizeVel(float amplitude)
	{
		for(int i = 0; i < particles.size(); i++)
		{
			ofxSmartParticle *sp = (ofxSmartParticle *) particles[i];
			sp->setRandomizeVel(amplitude);
		}				
	}	
	void toggleDistortion()
	{
		distort = !distort;
		setDistortion(distort); 
	}
	
	void setDistortion(bool _distort)
	{
		distort = _distort; 
		for(int i = 0; i < particles.size(); i++)
		{
			ofxSmartParticle *sp = (ofxSmartParticle *) particles[i];
			sp->setDistortion(distort); 
		}						
	}
	
	void setDistortVector(ofVec3f *_distorter)
	{
		if(distorter != NULL)
		{
			delete distorter; 
		}
		useExternalDistorter = true; 
		distorter = _distorter; 
		
		for(int i = 0; i < particles.size(); i++)
		{
			ofxSmartParticle *sp = (ofxSmartParticle *) particles[i];
			sp->setDistortVector(distorter); 
		}				
	}
	
	ofVec3f *getCenterPtr() { return center; }
	
protected:	
	bool useExternalCenter; 
	ofVec3f *center;
    bool useExternalDistorter; 
	ofVec3f *distorter; 
	float sphericalRadius; 
	bool targetHome; 
	bool targetSphere; 
	bool distort; 	
};

#endif