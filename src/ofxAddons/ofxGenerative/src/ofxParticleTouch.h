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

#ifndef OFX_PARTICLETOUCH
#define OFX_PARTICLETOUCH

#define TOUCH_INIT_RADIUS 256.0

#include "ofx1DExtruder.h"

class ofxParticleTouch : public ofTouchEventArgs
{
public:  
    float theta; 
    bool dead; 
    ofx1DExtruder radius; 
	float px, py; 
    /*
     int id;
     int time;
     float x, y;
     */  
    ofxParticleTouch()
    {
        radius.initWith(TOUCH_INIT_RADIUS);
        radius.setPhysics(.25, 10, 50);         
        id = -1; 
        dead = true; 
        x = 0; 
        y = 0; 
		px = 0; 
		py = 0; 
        theta = 0; 
    }
    
    ofxParticleTouch(ofTouchEventArgs& parent)
    {
        init(parent); 
    }
    
    void init(ofTouchEventArgs& parent)
    {
        radius.initWith(TOUCH_INIT_RADIUS);
        radius.setPhysics(.25, 10, 50);         
        id = parent.id; 
        x = parent.x; 
        y = parent.y; 
        px = parent.x; 
		py = parent.y; 
        dead = false; 
        theta = 0; 
    }
	
    void init(int _id, float _x, float _y)
    {
        radius.initWith(TOUCH_INIT_RADIUS);
        radius.setPhysics(.25, 10, 50);         
        id = _id; 
        x = _x; 
        y = _y; 
        px = _x; 
		py = _y; 
        dead = false; 
        theta = 0; 
    }	
    
    void update()
    {
        radius.update(); 
        if(radius.getPos() < 1)
        {
            dead = true; 
        }
        theta += .025; 
    }
    
    float getRadius()
    {
        return radius.getPos(); 
    }
    
    void update(ofTouchEventArgs &parent)
    {
        radius.initWith(TOUCH_INIT_RADIUS);
        radius.setPhysics(.25, 10, 50);         
        id = parent.id; 
        x = parent.x; 
        y = parent.y;         
        dead = false; 
    }
    
    void update(float _x, float _y)
    {
        radius.initWith(TOUCH_INIT_RADIUS);
        radius.setPhysics(.25, 10, 50);         
		px = x; 
		py = y; 
        x = _x; 
        y = _y; 
        dead = false; 
    }
	
    bool isDead()
    {
        return dead; 
    }
    
    ofxParticleTouch & operator=(ofTouchEventArgs &parent)
    {       
        init(parent); 
        
        return *this; 
    }
    
    void kill()
    {
        cout << "KILLING: " << id << endl; 
        radius.setHome(0); 
    }
	
	void killDead()
	{
		dead = true; 
		radius.setPos(0); 
	}
}; 

#endif 
