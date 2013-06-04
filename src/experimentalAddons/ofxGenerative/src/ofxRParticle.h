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

#ifndef OFXRPARTICLE
#define OFXRPARTICLE

#include "ofMain.h"
#include "ofxRParticleData.h"
#include "ofxBehavior.h"

class ofxRParticle
{
public:
	ofxRParticle();
	ofxRParticle(ofVec3f _pos);
	virtual ~ofxRParticle();	
	virtual void init();
    ofVec3f& calculateAcceleration(ofVec3f &pos, ofVec3f &vel, float dt);
	void setRadius(float _radius);
    void setPos(ofVec3f _pos);
    void setPpos(ofVec3f _ppos);
    void setVel(ofVec3f _vel);
    void setAcc(ofVec3f _acc);
    void setHome(ofVec3f _home);
    void setHome(float _x, float _y, float _z);
    void setColor(ofColor _color);
    void setDamping(float _damping);
    void setDampingPtr(float *_damping);
    float& getDamping(); 
    void setRestitution(float _restitution);
    void setRestitutionPtr(float *_restitution);
    float& getRestitution();
    void setAccerationLimit(float _acclimit);
    void setAccerationLimitPtr(float *_acclimit);
    float& getAccerationLimit();
    void setVelocityLimit(float _vellimit);
    void setVelocityLimitPtr(float *_vellimit);
    float& getVelocityLimit();
    void addExternalForce(ofVec3f *_extforce);
    void addSpringForce(ofVec3f *_extforce);
    void setFixed(bool _fixed);
    bool isFixed();
    void addForce(ofVec3f _force);
	ofVec3f* getHomePtr();
    ofVec3f* getPposPtr(); 
    ofVec3f* getPosPtr();
    ofVec3f* getVelPtr();
    ofVec3f* getAccPtr();
	ofVec3f& getPos();
	ofVec3f& getHome();
    ofVec3f& getPpos();
    ofVec3f& getVel();
	ofVec3f& getAcc();
	ofColor& getColor();
    ofColor* getColorPtr();
    void setColorAlpha(float _alpha);
    float getColorAlpha();
    float getRadius();
	int getID();
    void setID(int _pid);
    float getLifeTime();
    bool isDead();
    void setBehaviorVectorPtr(vector<ofxBehavior *> *_behaviors);
    void setParticleData(ofxRParticleData *_data);
    
    vector<ofxBehavior *> *behaviors;    //Pointer to Dynamic Behaviors
	ofVec3f pos;
    ofVec3f vel;
    ofVec3f acc;
    ofVec3f home;
    ofVec3f ppos;  //Properties
    
    vector<ofVec3f *> externalForces;
    vector<ofVec3f *> springForces;

    ofxRParticleData *data;
    
    //Per Particle Properties
   	int pid;                            //Particle ID
    int type;                           //Base, verse, etc.
    bool dead;
	bool fixed;
	float radius;
    float hradius;
	float mass;
    float lifeTime;
	ofColor color;
    
    bool bAllocatedDamping;
    bool bAllocatedRestitution;
    bool bAllocatedAccLimit;
    bool bAllocatedVelLimit;

    //Global Particle Properties
    float *damping;
    float *restitution;
	float *accLimit;
    float *velLimit;
};


#endif
