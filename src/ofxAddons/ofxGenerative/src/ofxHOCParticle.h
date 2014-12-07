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

#ifndef OFX_HOCPARTICLE
#define OFX_HOCPARTICLE

#include "ofxSmartParticle.h"

class ofxHOCParticle : public ofxSmartParticle 
{
public:
	ofxHOCParticle() : ofxSmartParticle()
	{
        initHOC();	
    }

	ofxHOCParticle(ofVec3f _pos) : ofxSmartParticle(_pos)
	{
        initHOC();
	}

	~ofxHOCParticle()
	{
		
	}
	
    void initHOC()
    {
    
    }
	
	void update(float dt = 1)
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
//			float dis = pos.distance(home);
//			float a = 50.0*sphericalRadius/(.1+dis*dis); 
//			if(a > 255)
//			{
//				a = 255; 
//			}
//			
//			color.setAlpha(a); 
		}		
	}
		
	void updateHomeData(float _x, float _y, float _z, float _intensity, float _size)
	{
		home.set(_x, _y, _z); 
		home.rotate(180, ofVec3f(0,0,1)); 
		home.rotate(180, ofVec3f(0,1,0)); 
		home*=.15; 
		
		intensity = _intensity; 
		size = _size; 
		color.a = intensity; 
	}
	
	void updatePosData(float _x, float _y, float _z, float _intensity, float _size)
	{
		pos.set(_x, _y, _z); 
		pos.rotate(180, ofVec3f(0,0,1)); 
		pos.rotate(180, ofVec3f(0,1,0)); 
		pos*=.15; 
		
		intensity = _intensity; 
		size = _size; 
		color.a = intensity; 
	}
	
	ofVec3f goSpherical()
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
			push*=-d*(intensity/255.0);
			//			push.limit(5); 
			return push; 
		}
		else 
		{
			return ofVec3f(0,0,0); 
		}
	}
	
	ofVec3f goHome()
	{
		ofVec3f temp = pos-home; 
		temp*=.15; 
		ofVec3f tempvel = vel; 
		tempvel *=  .17;            
		temp -=tempvel; 
		temp*=-1.0; 
		return temp; 
	}
	
	ofVec3f addDistortion()
	{
		if(distorter != NULL)
		{
			ofVec3f push = pos-(*distorter); 
			float d = pow(pos.distance(*distorter),2); 
			push/=(d);
			push*=intensity; 			
			return push; 
		}
		else 
		{
			return ofVec3f(0,0,0); 			
		}
	}	
	
	ofVec3f addPerlinNoise()
	{
		float noiseFloat = ofSignedNoise(pos.x * 0.025, pos.y * 0.025, pos.z * 0.025 + ofGetSeconds()*0.0001);      
		float ax = cos(((noiseFloat - 0.3) * TWO_PI) * 1.0);
		float ay = sin(((noiseFloat - 0.3) * TWO_PI) * 1.0);
		float az = cos(((noiseFloat - 0.3) * TWO_PI) * 1.0);		
		acc+=ofVec3f(ax,ay,az); 
	}
	
protected:
	/*
	 ofVec3f pos, vel, acc, home, ppos; 
	 ofVec3f *extforce; 
	 float mass; 
	 float damping; 
	 float accLimit, velLimit; 
	 ofColor color; 
	 
	 bool fixed; 
	 float radius; 
	 int pid; 
	 */	 
	
	float intensity; 
	float size; 	
	
};

#endif