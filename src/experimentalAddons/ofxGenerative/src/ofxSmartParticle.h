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

#ifndef OFX_SMARTPARTICLE
#define OFX_SMARTPARTICLE

#include "ofxParticle.h"

class ofxSmartParticle : public ofxParticle 
{
public:
	ofxSmartParticle() : ofxParticle()
	{
		initSmart();
	}
	
	ofxSmartParticle(ofVec3f _pos) : ofxParticle(_pos)
	{
		initSmart();		
	}
	
	virtual ~ofxSmartParticle()
	{
		
	}
	
	virtual void initSmart()
	{
		sphericalRadius = 100; 
		centerPos = NULL;
		targetHome = false; 
		targetSphere = false; 
		distort = false; 
		color.set(255, 0, 0, 100); 
		damping = .85; 
		accLimit = 1.0; 
		velLimit = 3.0; 		
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
			if (targetSphere) 
			{
				acc+=goSpherical(); 
			}
			if(targetHome)
			{
				acc+=goHome(); 
			}
			if(distort)
			{
				acc+=addDistortion(); 
			}
			acc -=vel*damping; 
			acc.limit(accLimit); 
			vel+=acc; 
			vel.limit(velLimit); 
			pos += vel; 			
			acc.set(0); 
		}				
	}
	
	virtual void draw()
	{
		ofSetColor(color); 
		ofSphere(pos.x,pos.y,pos.z, radius/10.0); 		
	}
	
	virtual ofVec3f goSpherical()
	{
		if(centerPos != NULL)
		{
			ofVec3f temp = pos-(*centerPos); 
			temp.normalize(); 
			temp*=(sphericalRadius);
			temp+=(*centerPos); 
			
			ofVec3f push = pos-temp; 		
			float d = push.length(); 
			push.normalize(); 
			push*=-d;
//			push.limit(5); 
			return push; 
		}
		else 
		{
			return ofVec3f(0,0,0); 
		}
	}
	
	virtual ofVec3f goHome()
	{
		ofVec3f temp = pos-home; 
		temp*=.15; 
		ofVec3f tempvel = vel; 
		tempvel *=  .17;            
		temp -=tempvel; 
		temp*=-1.0; 
		return temp; 
	}
	
	virtual ofVec3f addDistortion()
	{
		if(distorter != NULL)
		{
			ofVec3f push = pos-(*distorter); 
			float d = pow(pos.distance(*distorter),2); 
			push/=(d);
			push*=20.0; 			
			return push; 
		}
		else 
		{
			return ofVec3f(0,0,0); 			
		}
	}
	
	void setCenterPos(ofVec3f *_centerPos) { centerPos = _centerPos; }
	
	void setTargetHome(bool _targetHome) { targetHome = _targetHome; }
	
	void toggleTargetHome() { targetHome = !targetHome; }
	
	void setTargetSphere(bool _targetSphere) { targetSphere = _targetSphere; }
	
	void toggleTargetSphere() { targetSphere = !targetSphere; }
	
	void setRandomizeVel() { vel.set(ofRandom(-velLimit,velLimit), ofRandom(-velLimit,velLimit), ofRandom(-velLimit,velLimit)); }
	
	void setRandomizeVel(float amplitude) { vel.set(ofRandom(-amplitude,amplitude), ofRandom(-amplitude,amplitude), ofRandom(-amplitude,amplitude)); }
	
	void setSphericalRadius(float _sphericalRadius) { sphericalRadius = _sphericalRadius; }
	
    float getSphericalRadius() { return sphericalRadius; }
    
	void setDistortion(bool _distort) { distort = _distort; }
	
	void toggleDistortion() { distort = !distort; }
	
	void setDistortVector(ofVec3f *_distorter) { distorter = _distorter; }
	
	
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
	float sphericalRadius; 
	ofVec3f *centerPos; 
	bool targetHome; 	
	bool targetSphere; 
	bool distort; 
	ofVec3f *distorter; 
	
};


#endif