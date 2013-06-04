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

#ifndef OFX_REZAPARTICLE
#define OFX_REZAPARTICLE

#include "ofxSmartParticle.h"

class ofxRezaParticle : public ofxSmartParticle 
{
public:
	ofxRezaParticle() : ofxSmartParticle()
	{			
        initReza(); 
	}
	
	ofxRezaParticle(ofVec3f _pos) : ofxSmartParticle(_pos)
	{
        initReza(); 
	}
	
    void initReza()
    {
		absCenter = NULL;         
		particles = NULL; 		
		repulsion = true; 
		targetSphere = true; 
        targetAbsCenter = true; 
		saMulti = .5;         
		color = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));         
    }
	
	virtual ~ofxRezaParticle()
	{
		
	}
	
	virtual void update(float dt = 1)
	{
		if(!fixed)
		{
			ppos = pos; 
            for(int i = 0; i < externalForces.size(); i++)
            {
            	acc+=(*externalForces[i]); 
			}
			if(targetSphere) 
			{
				acc+=saMulti*(goSpherical()); 
			}
			if(targetHome)
			{
				acc+=goHome(); 
			}
			if(distort)
			{
				acc+=5.0*addDistortion(); 
			}
			if(repulsion)
			{
				acc+=repulse(); 
			}
			if(absCenter != NULL && targetAbsCenter)
			{
				acc+=.05*goSphericalCenter(); 
			}
			
			acc -=vel*damping; 
			acc.limit(accLimit); 
			vel+=acc; 
			vel.limit(velLimit); 
			pos += vel; 	
			acc.set(0); 
        }						
	}
		
	
	virtual ofVec3f goSphericalCenter()
	{
		ofVec3f temp = pos-(*absCenter); 
		temp.normalize(); 
		temp*=(sphericalRadius);
		temp+=(*absCenter); 
		
		ofVec3f push = pos-temp; 		
		float d = push.length(); 
		push.normalize(); 
		push*=-d;
		//			push.limit(5); 
		return push; 
	}
	
	
	virtual ofVec3f repulse()
	{
		if(particles != NULL)
		{			
			ofVec3f r = ofVec3f(0,0,0); 
			
			for(int i = 0; i < particles->size(); i++)
			{
				ofxParticle *other = (ofxParticle *)(*particles)[i]; 
				if(other->getID() != pid)
				{
					float distance = pos.distance(other->getPpos()); 
					ofVec3f direction = other->getPpos() - pos; 
					direction.normalize(); 
					direction *= -((100.0+radius*radius)/(distance+.000001)); 										
					r+=direction; 
				}		
			}
			r /= (float)particles->size();			
			return r; 
		}
		else 
		{
			return ofVec3f(0,0,0); 
		}
	}
	
	
	void setParticlesRef(vector<ofxParticle*> *_particles) { particles = _particles; }
	
	void setRepulsion(bool _repulsion) { repulsion = _repulsion; }
	
	void toggleRepulsion() { repulsion = !repulsion; }
	
	void setAbsCenter(ofVec3f *_absCenter) { absCenter = _absCenter; }
	
	void toggleAbsCenter() { targetAbsCenter = !targetAbsCenter; }	
	
	void setCenterTargeting(bool _targetAbsCenter) { targetAbsCenter = _targetAbsCenter; }
	
	void setSAMulti(float _saMulti) { saMulti = _saMulti; } 
	
protected:
    
//--------------------------//
//  FROM PARTICLE           //
//	ofVec3f pos, vel, acc, home; 
//	ofVec3f *extforce; 
//	float mass; 
//	float damping; 
//	float accLimit, velLimit; 
//	ofColor color; 
//	
//	bool fixed; 
//	float radius; 	
//--------------------------//
//  FROM SMART PARTICLE     //    
//	float sphericalRadius; 
//	ofVec3f *centerPos; 
//	bool targetHome; 	
//	bool targetSphere; 
//	bool distort; 
//	ofVec3f *distorter; 
//--------------------------//	
    
	vector<ofxParticle*> *particles; 
	bool repulsion; 
	ofVec3f *absCenter; 
	bool targetAbsCenter;
	float saMulti; 
};


#endif