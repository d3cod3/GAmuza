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

#ifndef OFX_1DEXTRUDER
#define OFX_1DEXTRUDER

#include "ofMain.h"

class ofx1DExtruder
{
public:
	ofx1DExtruder()
	{
		init(); 
	}
	
	ofx1DExtruder(float _pos)
	{
		initWith(_pos);
	}
	
	void init()
	{
		home = 0; 
		pos = 0; 
		vel = 0; 
		acc = 0;  
		damping = .75; 
		extForce = 0; 
		extForceInQue = false; 
		accLimit = .050; 
		velLimit = .20; 		
	}
	
	void initWith(float _pos)
    {
        init(); 
        home = _pos; 
        pos = _pos; 
    }
	
	
	void setPhysics(float _damping, float _accLimit, float _velLimit)
	{
		damping = _damping; 
		accLimit = _accLimit;
		velLimit = _velLimit; 
	}
    
    void setDamping(float _damping)
    {
        damping = _damping;         
    }

    void setAccLimit(float _accLimit)
    {
        accLimit = _accLimit;         
    }

    void setVelLimit(float _velLimit)
    {
        velLimit = _velLimit;         
    }

    float getDamping()    
    {
        return damping;         
    }

    float getVelLimit()
    {
        return velLimit;         
    }

    float getAccLimit()
    {
        return accLimit;         
    }    
    
	void update()
	{
		acc = 0; 
		acc+=goHome(); 		
		if(extForceInQue)
		{	
			acc+=extForce; 
			extForceInQue = false; 
			extForce = 0; 
		}
		acc-=vel*damping; 
		if(fabs(acc) > accLimit)
		{
			if(acc > 0)
			{
				acc = accLimit; 
			}
			else {
				acc = -accLimit; 
			}
		}
		vel+=acc; 
		if(fabs(vel) > velLimit)
		{
			if(vel > 0)
			{
				vel = velLimit; 
			}
			else {
				vel = -velLimit; 
			}
		}		
		pos+=vel; 		
	}
	
	float goHome()
	{
		float temp = pos-home;
		temp*=.15;  
		float tempvel = vel; 
		tempvel *= .17;
		temp -=tempvel; 
		temp*=-1.0; 
		return temp; 		
	}	
    
	void draw()
	{
		ofSetColor(255,0,0); 
		ofLine(pos,ofGetHeight()*.5, home, ofGetHeight()*.5); 

		ofSetColor(0,0,255); 		
		ofEllipse(home, ofGetHeight()*.5, 10, 10); 

		ofSetColor(0,255,0); 		
		ofEllipse(pos, ofGetHeight()*.5, 10, 10); 

	}
	
	float getPos()
    {
        return pos;
    }
	
    float *getPosPtr()
    {
        return &pos;
    }
    
	void setPos(float _pos)
	{
		pos = _pos; 
	}

	void setHome(float _home)
	{
		home = _home; 
	}
    
    float getHome()
    {
        return home;
    }

    float *getHomePtr()
    {
        return &home;
    }
    
    void setPosAndHome(float _home)
    {
        home = _home; 
        pos = _home; 
    }
	
	void addForce(float _extForce)
	{
		extForceInQue = true; 
		extForce += _extForce; 
	}
	
protected:
	float home; 
	float pos; 
	float vel; 
	float acc; 
	float damping; 	
	float extForce;
	float velLimit; 
	float accLimit; 
	bool extForceInQue; 
}; 


#endif