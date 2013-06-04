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

#ifndef OFXRPARTICLEGLOWIERENDERER
#define OFXRPARTICLEGLOWIERENDERER

#include "ofMain.h"
#include "ofx1DExtruder.h"
#include "ofxRParticleRenderer.h"

class ofxRParticleGlowieRenderer : public ofxRParticleRenderer
{
public:
    ofxRParticleGlowieRenderer();
    ~ofxRParticleGlowieRenderer();
    void setup();
    void draw();
    void setCamPtr(ofEasyCam *_cam);
    void setAxisAngleOffsets(ofx1DExtruder *_xAxis, ofx1DExtruder *_yAxis, ofx1DExtruder *_zAxis); 
    void billBoard(); 
    void setGlowImage(ofImage *_glow);
    
protected:
    ofImage *glow;
    ofVec3f objectLookAt; 
    ofEasyCam *cam;
    ofx1DExtruder *xAxis;
    ofx1DExtruder *yAxis;
    ofx1DExtruder *zAxis;
};

#endif
