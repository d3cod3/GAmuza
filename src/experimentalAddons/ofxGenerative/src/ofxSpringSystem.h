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

#ifndef OFX_SPRINGSYSTEM
#define OFX_SPRINGSYSTEM

#include <vector>
#include "ofxSpring.h"

class ofxSpringSystem 
{
public:
	
	ofxSpringSystem()
	{
        init();
	}
	
    void init()
    {
        uniqueIDs = 0; 
    }
    
	~ofxSpringSystem()
	{	
        clear();
    }
	
    void clear()
    {
        vector<ofxSpring * >::iterator it;    
        for ( it=springs.begin() ; it < springs.end(); it++ )
        {
            delete (*it);
            springs.erase(it);
        }                        
        springs.clear();         
    }
    
	virtual void update(float dt = 1)
	{
		for(int i = 0; i < springs.size(); i++)
		{
			springs[i]->update(dt);
		}		
	}
	
	virtual void draw()
	{
        ofMesh mesh; 
        mesh.setMode(OF_PRIMITIVE_LINES);
		for(int i = 0; i < springs.size(); i++)
		{
            mesh.addColor(springs[i]->getColor());
            mesh.addVertex(springs[i]->getPos(0));
            mesh.addColor(springs[i]->getColor());
            mesh.addVertex(springs[i]->getPos(1));
		}
        mesh.draw();
	}
	
	virtual void addSpring(ofxSpring *s)
	{
		uniqueIDs++; 
		s->setID(uniqueIDs); 
		springs.push_back(s); 
	}
	
	virtual int getCount()
	{
		return (int)springs.size(); 
	}
	
	ofxSpring *getSpring(int index)
	{
		if(index < springs.size() && index >= 0)
		{
			return springs[index];
		}
		else {
			return NULL;
		}
	}
	
	void setRestDistance(float _restDist)
	{
		for(int i = 0; i < springs.size(); i++)
		{
			springs[i]->setRestDistance(_restDist); 
		}
	}
    
    vector<ofxSpring*> &getSprings()
    {
        return springs; 
    }
	
    vector<ofxSpring*> springs; 
	
protected:

	int uniqueIDs; 
};

#endif
