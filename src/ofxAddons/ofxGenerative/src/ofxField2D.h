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

#ifndef OFXFIELD
#define OFXFIELD

#include "ofMain.h"

class ofxField2D {
	
public: 
    
    ofxField2D(); 
    ~ofxField2D(); 

    void init(int xRes, int yRes, int width, int height); 
	void resize(int w, int h); 
    void reset(); 
    void input(float x, float y, float px, float py, float intensity=1.0); 
    void randomize(); 
	
    void update(); 
    void draw(); 
	
	void setViscosity(float v);
	void setDensityDecay(float dd);
	void setDifferential(float d);
	void setDt(float dt);
	void setIterations(int i);
	void setPointSize(float _pointSize);
    void setLineWidth(float _lineWidth);
    
    void setRenderType(int _renderType);
    
	// get vector at position 
	ofPoint getVector(int x, int y, bool averaged=false);
	float getDensity(int x, int y);
	int getRenderType();

    float &getViscosity();
    float &getDensityDecay();
	float &getDifferential();
	float &getDt();
	int &getIterations();
	float &getPointSize();
    float &getLineWidth();
    
	// create fluid field from pixels
	void adaptFromImage(ofPixels & pix, float amt);
    
    //Drawing Field Functions
    void drawField(); 
    void drawFieldGrid(); 
    void drawFieldGridWire(); 
    void drawFieldMesh(); 
    void drawFieldVectorMesh(); 
    void drawFieldLinesVertical(); 
    void drawFieldVelocityVertical();
    void drawFieldLinesHorizontal();
    void drawFieldVelocityHorizontal();    
    void drawFieldAroundMe(float radius, ofVec2f loc, ofVec3f color); 
    
    //Drawing Density Functions
    void drawDensity();
	
	// size
	int getWidth();
	int getHeight();
    
protected:
	
	//Get a specific cell
    int IX(int x, int y) { return (x+(dimX+2)*(y)); }   
	
	//Fluid Solver Steps    
    void vel_step(int DX, int DY, float* u, float* v, float* u0, float* v0, float visc, float dt);
    void dens_step( int DX, int DY, float* x, float* x0, float* u, float* v, float diff, float dt);
    
    //Fluid Solver Functions    
    void diffuse(int DX, int DY, int b, float* x, float* x0, float diff, float dt);     
    void advect(int DX, int DY, int b, float* d, float* d0, float* u, float* v, float dt);
    void project(int DX, int DY, float* u, float* v, float* p, float* dv); 
	//    void swap(float*&x0, float *&x);
    void set_bnd(int DX, int DY, int b, float* x);     
    
    void add_source(int DX, int DY, float* x, float* s, float dt); 
    void decay_density(int DX, int DY, float* x, float* s, float dt);
	
    int dimX, dimY, size;
    float xInterval, yInterval; 
    float pointSize;
    float lineWidth;
    int renderType;
    float visc, diff, dt;
    float densityDecayFactor;
    int iterations; 
    float* u;               //x_vel
    float* v;               //y_vel    
    float* u_prev;          //x_vel_prev
    float* v_prev;          //y_vel_prev
    float* dens;            //dens
    float* dens_prev;       //dens_prev
	
	float w, h;

}; 


#endif
