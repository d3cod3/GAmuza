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
 
 Based on code from Memo Akten, www.memo.tv http://memo.tv/archive/node/767
 
 **********************************************************************************/

#ifndef OFX_HOCPARTICLESYSTEM
#define OFX_HOCPARTICLESYSTEM

#include "ofxParticleSystem.h"
#include "ofxHOCParticle.h"

#define		GRIDX				100					// new size of grid on x
#define		GRIDY				100					// new size of grid on y
#define		MAX_PARTICLES		(GRIDX*GRIDY)	

class ofxHOCParticleSystem : public ofxSmartParticleSystem 
{
public:
	ofxHOCParticleSystem() : ofxSmartParticleSystem()
	{
        initHOCSystem();
	}
	
	void initHOCSystem()
    {
        autoUpdate = true; 
		frame = 1; 
		sphericalRadius = 50; 
		for(int i = 0; i < MAX_PARTICLES; i++)
		{
			ofxHOCParticle *hocp = new ofxHOCParticle(); 
			this->addParticle(hocp); 
		}
		load(); 		
		glow = NULL; 
		camRef = NULL;  
    }
    
	virtual ~ofxHOCParticleSystem()
	{
        //Parent classes will destroy necessary things
	}
	
	void addParticle(ofxHOCParticle *p)
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
	
	
	void update()
	{
		if(autoUpdate)
		{
			nextFrame(); 
		}
		
		for(int i = 0; i < particles.size(); i++)
		{
			particles[i]->update(); 
		}		
	}
	
	void draw()
	{

//		ofNoFill(); 
//		drawTris(); 
//		ofFill(); 
		drawLines(); 
//		drawPoints();
//		drawGlowies(); 

		drawPointSprites(); 
//		glPushMatrix();		
//		glRotatef(180,0,1,0);
//		drawPoints(); 					
//		glPopMatrix(); 
	}
	
	void drawPointSprites()
	{
		
		glow->bind(); 
		ofEnableBlendMode(OF_BLENDMODE_ADD); 		
		//
		// Set up the OpenGL state machine for using point sprites...
		//
		
		// This is how will our point sprite's size will be modified by 
		// distance from the viewer
//		float quadratic[] =  { 1.0f, 0.0f, 0.01f };
//		glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );
		
		// Query for the max point size supported by the hardware
//		float maxSize = 0.0f;
//		glGetFloatv( GL_POINT_SIZE_MAX_ARB, &maxSize );
		

//		if( maxSize > 100.0f )
//			maxSize = 100.0f;
//		
//		glPointSize( maxSize );
		
		// The alpha of a point is calculated to allow the fading of points 
		// instead of shrinking them past a defined threshold size. The threshold 
		// is defined by GL_POINT_FADE_THRESHOLD_SIZE_ARB and is not clamped to 
		// the minimum and maximum point sizes.
		glPointParameterfARB( GL_POINT_FADE_THRESHOLD_SIZE_ARB, 10.0f );
		
		glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, 20.0f );
		glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, 100.0f );
		

		glTexEnvf( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );	
		glEnable( GL_POINT_SPRITE_ARB );		
		drawPoints(); 		
		glDisable( GL_POINT_SPRITE_ARB );			
		glow->unbind(); 
	}
	
	void drawGlowies()
	{
		if(camRef != NULL && glow != NULL)
		{
			ofSetRectMode(OF_RECTMODE_CENTER); 
			for(int i = 0; i < particles.size(); i++)
			{
				glPushMatrix();
				ofVec3f pos = particles[i]->getPos(); 
				glTranslatef(pos.x, pos.y, pos.z); 
				billBoard(camRef->getGlobalPosition(), pos); 
				ofSetColor(particles[i]->getColor()); 
				float r = particles[i]->getColorAlpha(); 
				r/=5.0;
				glow->draw(0, 0, r, r); 
				glPopMatrix();	
			}				
			ofSetRectMode(OF_RECTMODE_CORNER);			
		}
	}
	
	void drawTris()
	{
		for(int y = 0; y < GRIDY-1; y++)
		{
			glBegin(GL_QUADS);
			for(int x = 0; x < GRIDX-1; x++)
			{							
				int xNext = x+1; 
				int yNext = y+1; 
				
				particles[x+(y*GRIDX)]->draw(); 
				particles[xNext+(y*GRIDX)]->draw(); 
				particles[xNext+(yNext*GRIDX)]->draw(); 					
				particles[x+(yNext*GRIDX)]->draw(); 									
			}
			glEnd(); 
		}		
	}
	
	void drawLines()
	{
		ofSetLineWidth(1); 		
		for(int y = 0; y < GRIDY; y++)
		{
			glBegin(GL_LINE_STRIP);
			for(int x = 0; x < GRIDX; x++)
			{
				particles[x+(y*GRIDX)]->draw(); 
			}
			glEnd(); 
		}		
	}
	
	void drawPoints()
	{
		//drawPoints
		glBegin(GL_POINTS); 
		for(int i = 0; i < particles.size(); i++)
		{
			particles[i]->draw(); 
		}
		glEnd(); 
	}
	
	void nextFrame()
	{
		frame++; 
		if(frame > 2101)
		{
			frame = 1; 
		}
		load(); 
	}
	
	void previousFrame()
	{
		frame--; 
		if(frame < 1)
		{
			frame = 2101; 
		}
		load(); 
	}
	
	void setFrame(int _frame)
	{
		frame = _frame; 
		load(); 
	}
	
	void load()
	{
		string path = "HOC/" +ofToString(frame) + ".bin"; 
		FILE *fileIn = fopen(ofToDataPath(path).c_str(), "rb"); 
		if(fileIn != NULL) 
		{
			// obtain file size:
			fseek(fileIn, 0, SEEK_END);
			int fileSize = ftell(fileIn);							// file size in bytes
			int numDots = fileSize/2;								// number of dots in the file (2 bits of info per dot)
			if(numDots > MAX_PARTICLES) printf(" *** WARNING : particle count greater than buffer *** \n");
			
			unsigned char *buffer = new unsigned char[fileSize];		// allocate memory to contain the whole file
			if(buffer != NULL) 
			{
				rewind(fileIn);											// rewind to beginning
				size_t numRead = fread(buffer, 1, fileSize, fileIn);	// read entire file
				if (numRead == fileSize)								// if whole file successefully read
				{								
					int index;
					for(int c=0; c<numDots; c++) 
					{
						index = c<<1;
						int xx = c % GRIDX;
						int yy = floor(c / GRIDX);
						ofxHOCParticle *hocp = (ofxHOCParticle *) particles[c]; 
						hocp->updateHomeData((xx-50) * 4.5f, (yy-45) * 6.0f, -(buffer[index]*1.5f)+50, buffer[index+1], 7.0f); 
					}
				} 
				else 
				{
					printf(" *** Error reading file contents for file %i %i != %i *** \n", frame, (int)numRead, fileSize);
				}
			} 
			else 
			{
				printf(" *** Could not allocate memory for buffer for file %i *** \n", frame);
			}
			
			fclose(fileIn);
			delete buffer;
		}		
	}
	
	void setCameraRef(ofEasyCam *_camRef) { camRef = _camRef; }
	
	void setGlowImage(ofImage *_glow) { glow = _glow; }
	
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
	
	void zeroPositions()
	{
		for(int i = 0; i < particles.size(); i++)
		{
			particles[i]->setPos(ofVec3f(0,0,0)); 
		}		
	}
	
	
protected:
	int frame; 
	bool autoUpdate; 
	
	ofEasyCam *camRef; 
	ofImage *glow; 
	
	/*
	 ofVec3f *center;
	 ofVec3f *distorter; 
	 float sphericalRadius; 
	 bool targetHome; 
	 bool targetSphere; 
	 bool distort; 
	 */
};



#endif