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

#ifndef OFXPARTICLE
#define OFXPARTICLE

#include "ofMain.h"

class ofxParticle 
{
public:
	ofxParticle()
	{
		init(); 		
	}
	
	ofxParticle(ofVec3f _pos)
	{	
		init(); 
		pos = _pos; 	
		ppos = pos;		//previous position
        home = pos; 
	}
	
	virtual ~ofxParticle()
	{

	}
    
    virtual void setBorders(float _w, float _h)
    {
        _width = _w;
        _height = _h;
    }
	
	virtual void init()
	{
		pos = ofVec3f(0,0,0);
		ppos = ofVec3f(0,0,0);
		home = ofVec3f(0,0,0);
		vel = ofVec3f(0,0,0); 
		acc = ofVec3f(0,0,0);
		color = ofColor(255,0,0,255); 
		fixed = false;
        setRadius(10);
		mass = 1.0;
        damping = 0.25;
		accLimit = 5;
		velLimit = 10;
        lifeTime = 1.0;
        dead = false; 
	}

	virtual void update(float dt = 1)
	{
		if(!fixed)
		{
            /*
			ppos = pos;
            for(int i = 0; i < externalForces.size(); i++)
            {
            	acc+=(*externalForces[i]);
			}
			acc -=vel*damping; 
			acc.limit(accLimit);
			vel+=acc*dt;
			vel.limit(velLimit);
            pos+=vel*dt+0.5*acc*dt*dt;
//			pos+= vel;
//            pos += ppos + (ppos - pos)*.5 + acc*dt*dt;

			acc.set(0);
            */
            
            ppos = pos;
            
            for(int i = 0; i < externalForces.size(); i++)
            {
            	acc+=(*externalForces[i]);
			}
			
            acc.limit(accLimit);
            
            vel.limit(velLimit);
            
            pos += (pos - ppos)*damping + vel*dt + acc*(dt*dt)*mass;

            for(int i = 0; i < springForces.size(); i++)
            {
            	pos+=(*springForces[i])/(float)springForces.size();
			}

            vel*=damping;
			acc.set(0);
		}
	}
	
	virtual void draw()
	{
		ofSetColor(color); 
		ofEllipse(pos.x, pos.y, radius, radius); 
	}
    
    virtual void drawVertex()
    {
		ofSetColor(color); 
        glVertex3f(pos.x, pos.y, pos.z);
    }
	
	virtual void borders()
	{
        if(pos.x > _width)
        {
            pos.x = 0;
            ppos = pos;
        }
        else if(pos.x < 0)
        {
            pos.x = _width;
            ppos = pos; 
        }
                
        if(pos.y > _height)
        {
            pos.y = 0;
            ppos = pos;
        }
        else if(pos.y < 0)
        {            
            pos.y = _height;
            ppos = pos; 
        }
    }

	virtual void elasticBorder(float _k)
    {
        float w = _width;
        float h = _height;
        if(pos.x > w)
        {
            pos.x = w-1;
            vel*=-_k;
        }
        else if(pos.x < 0)
        {   
            pos.x = 1; 
            vel*=-_k;
        }
        if(pos.y > h)
        {
            pos.y = h-1;
            vel*=-_k;            
        }
        else if(pos.y < 0)
        {
            pos.y = 1; 
            vel*=-_k;            
        }	        
    }
    
    virtual void circleborders()
    {
        float halfRadius = radius;
        if(pos.x > _width+halfRadius)
        {
            pos.x = -halfRadius; 
        }
        else if(pos.x < -halfRadius)
        {
            pos.x = _width+halfRadius;
        }
        
        if(pos.y > _height+halfRadius)
        {
            pos.y = -halfRadius;
        }
        else if(pos.y < -halfRadius)
        {            
            pos.y = _height+halfRadius;
        }        
    }

	void setRadius(float _radius) { radius = _radius; hradius = .5*radius; }
	void setPos(ofVec3f _pos) { pos = _pos; }
	void setVel(ofVec3f _vel) { vel = _vel; }
	void setAcc(ofVec3f _acc) { acc = _acc; }
	void setHome(ofVec3f _home) { home = _home; }
	void setHome(float _x, float _y, float _z) { home.x = _x; home.y = _y; home.z = _z; }	
	void setColor(ofColor _color){ color = _color; }
	void setDamping(float _damping) { damping = _damping; }	
	void setAccerationLimit(float _acclimit) { accLimit = _acclimit; }
	void setVelocityLimit(float _vellimit) { velLimit = _vellimit; }
	void addExternalForce(ofVec3f _extforce) {
        ofVec3f *_temp = new ofVec3f();
        _temp[0] = _extforce;
        externalForces.push_back(_temp);
    }
    void addSpringForce(ofVec3f _extforce) {
        ofVec3f *_temp = new ofVec3f();
        _temp[0] = _extforce;
        springForces.push_back(_temp);
    }
	void setFixed(bool _fixed) { fixed = _fixed; }
	bool isFixed() { return fixed; } 
	void addForce(ofVec3f _force) { (acc) += _force; } 

	ofVec3f* getHomePtr() { return &home; }
	ofVec3f* getPosPtr() { return &pos; }
	ofVec3f* getVelPtr() { return &vel; }
	ofVec3f* getAccPtr() { return &acc; }
	
	ofVec3f& getPos() { return pos; }
	ofVec3f& getHome() { return home; }
	ofVec3f& getPpos() { return ppos; } 
	ofVec3f& getVel() { return vel; }
	ofVec3f& getAcc() { return acc; }
	ofColor& getColor() { return color; } 
	void setColorAlpha(float _alpha) { color.a = _alpha; }
	float getColorAlpha() { return color.a;  } 
	float getRadius() { return radius; } 
	
	int getID() { return pid; }
	void setID(int _pid) { pid = _pid; } 

    void decay(float _amount)
    {
        lifeTime-= _amount;
        if(lifeTime < 0)
        {
            dead = true;
        }
    }
    
    float getLifeTime() { return lifeTime; } 
    bool isDead() { return dead; } 
    
protected:
	ofVec3f pos, vel, acc, home, ppos; 
    vector<ofVec3f *> externalForces;
    vector<ofVec3f *> springForces;
	float mass;
	float damping;
    float lifeTime;
    bool dead; 
	float accLimit; 
    float velLimit;
	ofColor color; 
	
	bool fixed; 
	float radius;
    float hradius;
	int pid;
    float _width, _height;
};


#endif
