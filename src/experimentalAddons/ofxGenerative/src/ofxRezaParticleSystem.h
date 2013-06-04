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

#ifndef OFX_REZAPARTICLESYSTEM
#define OFX_REZAPARTICLESYSTEM

#include "ofxRezaParticle.h"

class ofxRezaParticleSystem : public ofxSmartParticleSystem 
{
public:
	ofxRezaParticleSystem() : ofxSmartParticleSystem()
	{
        initRezaSystem();
	}

	void initRezaSystem()
    {
		repulsion = true; 
		glow = NULL; 
		camRef = NULL; 
    }
        
	~ofxRezaParticleSystem()
	{
        
	}
	
	void draw()
	{
		if(glow != NULL && camRef != NULL)
		{
			ofSetRectMode(OF_RECTMODE_CENTER); 
			for(int i = 0; i < particles.size(); i++)
			{
				glPushMatrix();
				ofVec3f pos = particles[i]->getPos(); 
                glTranslatef(pos.x, pos.y, pos.z); 
				billBoard(camRef->getGlobalPosition(), pos); 
                ofSetColor(particles[i]->getColor()); 
				float r = particles[i]->getRadius()*.5;  
				glow->draw(0, 0, r, r); 
				glPopMatrix();	
			}				
			ofSetRectMode(OF_RECTMODE_CORNER);
		}
		else 
		{
			glPointSize(3); 
            ofMesh mesh; 
            mesh.setMode(OF_PRIMITIVE_POINTS);

			for(int i = 0; i < particles.size(); i++)
			{
				mesh.addColor(particles[i]->getColor());
                mesh.addVertex(particles[i]->getPos());
			}		
            mesh.draw();
			glPointSize(1); 			
		}
	}
	
	virtual void addParticle(ofxRezaParticle *p)
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
		
		p->setRepulsion(repulsion); 
		p->setParticlesRef(&particles); 
		particles.push_back(p); 
	}
	
	void setRepulsion(bool _repulsion) 
	{ 
		repulsion = _repulsion; 
		for(int i = 0; i < particles.size(); i++)
		{
			ofxRezaParticle *p = (ofxRezaParticle *) particles[i]; 
			p->setRepulsion(repulsion); 
		}		
	}
    
    bool getRepulsion()
    {
        return repulsion; 
    }
		
	void toggleRepulsion() 
	{ 
		repulsion = !repulsion; 
		setRepulsion(repulsion); 
	}
	
	void billBoard(ofVec3f globalCamPosition, ofVec3f globelObjectPosition)
	{
		ofVec3f objectLookAt = ofVec3f(0,0,1); 
		ofVec3f objToCam = globalCamPosition - globelObjectPosition; 
		objToCam.normalize(); 	
		float theta = objectLookAt.angle(objToCam); 
		ofVec3f axisOfRotation = objToCam.crossed(objectLookAt); 
		axisOfRotation.normalize(); 
		glRotatef(-theta, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);  
	}
	
	void setCameraRef(ofEasyCam *_camRef) { camRef = _camRef; }
	
	void setGlowImage(ofImage *_glow) { glow = _glow; }
	
	ofxRezaParticle* getParticle(int index)
	{
		if(index < particles.size() && index >= 0)
		{
			return (ofxRezaParticle*) particles[index];
		}
		else 
		{
			return NULL; 
		}

	}

protected:
	bool repulsion; 
	ofEasyCam *camRef; 
	ofImage *glow; 
};


#endif