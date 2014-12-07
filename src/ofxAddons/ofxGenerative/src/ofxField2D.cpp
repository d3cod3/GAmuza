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

#include <iostream>

#include "ofxField2D.h"

using namespace std; 

ofxField2D::ofxField2D()
{
    u = NULL;
    v = NULL;
    u_prev = NULL;
    v_prev = NULL;
    dens = NULL;
    dens_prev = NULL; 
}

ofxField2D::~ofxField2D()
{
    delete[] u; 
    delete[] v;
    delete[] u_prev; 
    delete[] v_prev;
    delete[] dens; 
    delete[] dens_prev;    
}

void ofxField2D::init(int xRes, int yRes, int width, int height)
{
    if(u!= NULL)    delete[] u;
    if(v!= NULL)    delete[] v;
    if(u_prev!= NULL)    delete[] u_prev;
    if(v_prev!= NULL)    delete[] v_prev;
    if(dens!= NULL)    delete[] dens;
    if(dens_prev!= NULL)    delete[] dens_prev;
    
    dimX = xRes; 
    dimY = yRes; 
    
    xInterval = (float)width/(float)dimX; 
    yInterval = (float)height/(float)dimY;      
	
	w = width;
	h = height;
    	
    renderType = 0;
	pointSize = 12;
    lineWidth = 5;
    
    dt = 0.00005; 
    diff = .0005; 
    visc = .001; 
    densityDecayFactor = 1.0;
    iterations = 20; 
    
    size = (dimX+2)*(dimY+2);           //The +2 is to account for the First and Last which are the Boundary

    u = new float[size];
    v = new float[size];
    u_prev = new float[size];
    v_prev = new float[size];
    dens = new float[size];
    dens_prev = new float[size];     
    reset(); 
    randomize(); 
}


void ofxField2D::resize(int w, int h)
{
    xInterval = (float)w/(float)dimX; 
    yInterval = (float)h/(float)dimY;      
}

void ofxField2D::reset()
{
    for(int i = 0; i < size; i++)   //Randomize it up
    {
        u_prev[i] = 0; 
        u[i] = u_prev[i];
        
        v_prev[i] = 0; 
        v[i] = v_prev[i];       
        
        dens_prev[i] = 0; 
        dens[i] = dens_prev[i];
    }    
}

void ofxField2D::randomize()
{
	
	for(int x=0; x< dimX+2; x++){
		for(int y=0; y< dimY+2; y++){

			int i = y * (dimX + 2) + x;
			
			u_prev[i] = ofNoise(50+x*0.2, 50+y*0.2)*10; //ofRandom(-100,100);
			u[i] = u_prev[i];
			
			v_prev[i] = ofNoise(150+x*0.2, 150+y*0.2)*10; //ofRandom(-100,100);
			v[i] = v_prev[i];       
			
			dens_prev[i] = ofNoise(x*0.1, y*0.1, ofGetMinutes())*10; //ofRandom(0,1);
			//dens[i] = dens_prev[i];
		}
	}
	
	/*
	
    for(int i = 0; i < size; i++)   //Randomize it up
    {
        u_prev[i] = ofNoise(50+i*0.02)*10; //ofRandom(-100,100);
        u[i] = u_prev[i];
        
        v_prev[i] = ofNoise(150+i*0.02)*10; //ofRandom(-100,100);
        v[i] = v_prev[i];       
        
        dens_prev[i] = ofNoise(i*0.02)*10; //ofRandom(0,1);
        dens[i] = dens_prev[i];
    }
	 
	*/
}

void ofxField2D::update()
{
	vel_step(dimX, dimY, u, v, u_prev, v_prev, visc, dt);
	dens_step(dimX, dimY, dens, dens_prev, u, v, diff, dt);    
	
	//printf("outside %p\n", dens);
}

void ofxField2D::input(float x, float y, float px, float py, float intensity)
{
    int i = (int)ofMap(x,0,ofGetWidth(),1,dimX, true);
    int j = (int)ofMap(y,0,ofGetHeight(),1,dimY, true);
    u[IX(i,j)] = (25.0*(x-px))*intensity; 
    v[IX(i,j)] = (25.0*(y-py))*intensity;
    dens[IX(i,j)] = 15.0 * intensity; 

}

void ofxField2D::setViscosity(float v){
	
    visc = v; 
}

void ofxField2D::setDensityDecay(float dd){
	
    densityDecayFactor = dd;
}

void ofxField2D::setDifferential(float d){

	diff = .0005; 
}

void ofxField2D::setDt(float newDt){
	
	dt = newDt; 
}

void ofxField2D::setIterations(int i){

	iterations = i;
}

void ofxField2D::setPointSize(float _pointSize)
{
    pointSize = _pointSize;
}

void ofxField2D::setLineWidth(float _lineWidth)
{
    lineWidth = _lineWidth; 
}

float &ofxField2D::getPointSize()
{
    return pointSize;
}

float &ofxField2D::getLineWidth()
{
    return lineWidth;
}

float &ofxField2D::getViscosity()
{
    return visc;
}

float &ofxField2D::getDensityDecay()
{
    return densityDecayFactor;
}

float &ofxField2D::getDifferential()
{
    return diff;
}

float &ofxField2D::getDt()
{
    return dt;
}

int &ofxField2D::getIterations()
{
    return iterations;
}

ofPoint ofxField2D::getVector(int x, int y, bool averaged){

	x = ofClamp(x, 0, w);
	y = ofClamp(y, 0, h);
	
	float xRatio = float(x) / w;
	float yRatio = float(y) / h;
	
	float dX, dY, intensity;

	if( !averaged ){
		
		x = int(xRatio * dimX);
		y = int(yRatio * dimY);
		
		//x = ofClamp(x, 0, dimX);
		//y = ofClamp(y, 0, dimY);
	
		int pos = IX(x, y);
		intensity = dens[pos];
		dX = u[pos];
		dY = v[pos];
		
	} else {
	
		float fx = xRatio * dimX;
		float fy = yRatio * dimY;
		
		x = int(xRatio * dimX);
		y = int(yRatio * dimY);
		
		float difX = fx - x;
		float difY = fy - y;
		
		//printf("%i %i - %f %f\n", x, y, fx, fy);
		
		int posA = IX(x, y);
		float intensityA = dens[posA];
		
		int posB = IX(x+1, y+1);
		float intensityB = dens[posB];

		intensity = intensityB * difX + intensityA * (1.0 - difX);
		dX = u[posB] * difX + u[posA] * (1.0 - difX);
		dY = u[posB] * difY + u[posA] * (1.0 - difY);
	}
	
	return ofPoint(dX*intensity, dY*intensity);
}

float ofxField2D::getDensity(int x, int y){
	
	float xRatio = float(x) / w;
	float yRatio = float(y) / h;
	
	x = int(xRatio * dimX);
	y = int(yRatio * dimY);
	
	x = ofClamp(x, 0, dimX);
	y = ofClamp(y, 0, dimY);
	
	int pos = IX(x, y);
	
	return dens[pos];
}

void ofxField2D::adaptFromImage(ofPixels & pix, float amt){
	
	// assume the same size as fluid field
	
	int numPix = pix.getWidth() * pix.getHeight();
	unsigned char * srcPixels = pix.getPixels();
	unsigned char brightness[numPix];
	
	//printf("%i %i\n", size, numPix);
	
	for(int i=0; i<size; i++){
	
		unsigned char r = srcPixels[i*3];
		unsigned char g = srcPixels[i*3+1];
		unsigned char b = srcPixels[i*3+2];
		
		brightness[i] = ( r * 0.299) + (.587 * g) + (.114 * b);
		dens[i] += (brightness[i] / 25) * amt;
	}
	
	int width = pix.getWidth();
	int height = pix.getHeight();
	
	for(int x=1; x<width-1; x++){
		for(int y=1; y<height-1; y++){
			
			int vecPos = y * width + x;
			char areaPixels[9];
			
			// loop through the area pixels
			for(int i=-1; i<=1; i++){
				for(int j=-1; j<=1; j++){
					
					// determine where to read from in the area (not optimized)
					int readPos = ((y + j) * width + (x + i));
					
					char BR = brightness[readPos];
					
					int writePos = (j+1) * 3 + (i + 1);
					
					areaPixels[writePos] = BR;
				}
			}
			
			float dX = (areaPixels[0] + areaPixels[3] + areaPixels[6])/3 - (areaPixels[2] + areaPixels[5] + areaPixels[8])/3;
			float dY = (areaPixels[0] + areaPixels[1] + areaPixels[2])/3 - (areaPixels[6] + areaPixels[7] + areaPixels[8])/3;
			
			u[vecPos] = u[vecPos] * (1.0 - amt) + (dY * (amt));
			v[vecPos] = v[vecPos] * (1.0 - amt) + (dX * (amt));
		}
	}
	
	/*
	 float* u;               //x_vel
	 float* v;               //y_vel    
	 float* u_prev;          //x_vel_prev
	 float* v_prev;          //y_vel_prev
	 float* dens;            //dens
	 float* dens_prev;       //dens_prev
	*/
}


void ofxField2D::vel_step(int DX, int DY, float* u, float* v, float* u0, float* v0, float visc, float dt)
{
    add_source(DX,DY,u,u0,dt);    
    add_source(DX,DY,v,v0,dt);
    
    std::swap(u0,u);
    diffuse(DX,DY,1,u,u0,visc,dt);
	
    std::swap(v0,v); 
    diffuse(DX,DY,2,v,v0,visc,dt);
    
    project(DX,DY,u,v,u0,v0);
    
    std::swap(u0,u);
    std::swap(v0,v);
    
    advect(DX,DY,1,u,u0,u0,v0,dt);
    advect(DX,DY,2,v,v0,u0,v0,dt);
    
    project(DX,DY,u,v,u0,v0);
}

void ofxField2D::dens_step(int DX, int DY, float* x, float* x0, float* u, float* v, float diff, float dt)
{
	
	//printf("inside %p\n", x);
	
    add_source(DX,DY,x,x0,dt);
	std::swap(x0,x); 
    
	diffuse(DX,DY,0,x,x0,diff,dt);    
    std::swap(x0,x);	
	
    advect(DX,DY,0,x,x0,u,v,dt);    	
	std::swap(x0,x);
	 
	decay_density(DX,DY,x,x0,dt);
	swap(x0,x);
}

void ofxField2D::add_source(int DX, int DY, float*x, float*s, float dt)
{
    for(int i = 0; i < size; i++)
    {
        x[i] +=dt*s[i];
    }
}

void ofxField2D::decay_density(int DX, int DY, float*x, float*s, float dt)
{
	
    for(int i = 0; i < size; i++)
    {
        s[i] = s[i]*densityDecayFactor; //x[i]*.02; //*densityDecayFactor;
		//if( i == size/2) printf("pre %f, post %f\n", s[i], x[i]);
    }
}


void ofxField2D::diffuse( int DX, int DY, int b, float* x, float* x0, float diff, float dt)
{
    float a = dt*diff*DX*DX;     
    for(int k = 0; k < iterations; k++)             //
    {
        for(int i = 1; i <= DX; i++)
        {
            for(int j = 1; j <= DY; j++)
            {
                x[IX(i,j)] = (x0[IX(i,j)] + a*(x[IX(i-1,j)]+x[IX(i+1,j)]+x[IX(i,j-1)]+x[IX(i,j+1)]))/(1+4*a);
            }
        }
        set_bnd (DX,DY,b,x); 
    }    
}

void ofxField2D::advect(int DX, int DY, int b, float* d, float* d0, float* u, float* v, float dt)
{
    int i0,j0,i1,j1; 
    float x, y, s0, t0, s1, t1, dt0x, dt0y;
    
    dt0x = dt*DX;          //this line might be:     dt0 = dt*DX*DY; 
	dt0y = dt*DY;          //this line might be:     dt0 = dt*DX*DY; 
    
    for(int i = 1; i <=DX; i++)
    {
        for(int j = 0; j <=DY; j++)
        {
            x = i-dt0x*u[IX(i,j)];
            y = j-dt0y*v[IX(i,j)];         
            if(x<0.5)
            {
                x = 0.5;             ///0.5 = gridspacing ->will change in mine 
            }
            if(x>DX+0.5)
            {
                x = DX+0.5;  
            }
            
            i0 = (int)x; 
            i1 = i0+1;       
            
            if(y<0.5)
            {
                y = 0.5;
            }
            if(y>DY+0.5)
            {
                y = DY+0.5;  
            }
            
            j0 = (int)y; 
            j1 = j0+1;   
            
            s1 = x-i0; 
            s0 = 1-s1; 
            t1 = y-j0; 
            t0 = 1-t1;
            
            d[IX(i,j)] = s0*(t0*d0[IX(i0,j0)]+t1*d0[IX(i0,j1)])  +
            s1*(t0*d0[IX(i1,j0)]+t1*d0[IX(i1,j1)]); 
        }
    }
    set_bnd (DX,DY,b,d);
}

void ofxField2D::project(int DX, int DY, float* u, float* v, float* p, float* dv)
{
    float hx = xInterval/(float)DY;   ///h 1.0 = grid spacing....
    float hy = yInterval/(float)DX;   ///h 1.0 = grid spacing....	
    
    for(int i = 1; i <=DX; i++)
    {
        for(int j = 1; j <=DY; j++)
        {
            dv[IX(i,j)] = -0.5*(hx*(u[IX(i+1,j)]-u[IX(i-1,j)])+hy*(v[IX(i,j+1)]-v[IX(i,j-1)]));
            p[IX(i,j)] = 0; 
        }
    }
    set_bnd(DX,DY,0,dv);
    set_bnd(DX,DY,0,p);
    
    for(int k = 0; k < iterations; k++)
    {
        for(int i = 1; i <=DX; i++)
        {
            for(int j = 1; j <=DY; j++)
            {
                p[IX(i,j)] = (dv[IX(i,j)]+p[IX(i-1,j)]+p[IX(i+1,j)]+p[IX(i,j-1)]+p[IX(i,j+1)])/4.0; 
            }
        }
        set_bnd(DX,DY,0,p);
    }
    
    for(int i = 1; i <=DX; i++)
    {
        for(int j = 1; j<=DY; j++)
        {
            u[IX(i,j)] -= 0.5*(p[IX(i+1,j)]-p[IX(i-1,j)])/hx;             
            v[IX(i,j)] -= 0.5*(p[IX(i,j+1)]-p[IX(i,j-1)])/hy; 
        }
    }
    set_bnd(DX,DY,1,u);
    set_bnd(DX,DY,2,v);
}
/*
void ofxField2D::swap(float*&x0, float *&x)
{
	float *t = x0;
	x0 = x;
	x = t;
}
 */

void ofxField2D::set_bnd( int DX, int DY, int b, float* x)
{
    int N = DX; 
    for(int i =1; i<=DY; i++)
    {
        //Y??           comp ? TRUE VALUE : FALSE VALUE
        x[IX(0,i)] = b==1 ? -x[IX(1,i)] : x[IX(1,i)];
        x[IX(DX+1,i)] = b==1 ? -x[IX(DX,i)] : x[IX(DX,i)];
    }
    
    for(int i =1; i<=DX; i++)
    {
        //X??           comp ? TRUE VALUE : FALSE VALUE
        x[IX(i,0)] = b==2 ? -x[IX(i,1)] : x[IX(i,1)];
        x[IX(i,DY+1)] = b==2 ? -x[IX(i,DY)] : x[IX(i,DY)];
    }
    
    x[IX(0,0)] = 0.5*(x[IX(1,0)]+x[IX(0,1)]);
    x[IX(0,DY+1)] = 0.5*(x[IX(1,DY+1)]+x[IX(0,DY)]);
    x[IX(DX+1,0)] = 0.5*(x[IX(DX,0)]+x[IX(DX+1,1)]);
    x[IX(DX+1,DY+1)] = 0.5*(x[IX(DX,DY+1)]+x[IX(DX+1,DY)]);
}


void ofxField2D::draw()
{
    switch(renderType)
    {
        case 0: 
            drawDensity(); 
            break;  
            
        case 1: 
            drawFieldGrid(); 
            break;  
            
        case 2: 
            drawFieldGridWire(); 
            break;  
            
        case 3: 
            drawFieldMesh(); 
            break;  
            
        case 4: 
            drawFieldVectorMesh(); 
            break;  
            
        case 5: 
            drawFieldLinesVertical(); 
            break;  
            
        case 6: 
            drawFieldVelocityVertical();
            break; 
            
        case 7: 
            drawFieldLinesHorizontal();
            break;  
            
        case 8: 
            drawFieldVelocityHorizontal();
            break;  
			
        default:     
			renderType%=9;
            break;          
    }
}

int ofxField2D::getRenderType()
{
    return renderType;
}

void ofxField2D::setRenderType(int _renderType)
{
    renderType = _renderType;
}

void ofxField2D::drawField()
{
    ofPushStyle();
    ofSetLineWidth(lineWidth);
    glBegin(GL_LINES);
    for(int i = 0; i <=dimX; i++)
    {
        for(int j = 0; j <=dimY; j++)
        {
            glColor4f(1,1,1,dens[IX(i,j)]);
            glVertex2f(i*xInterval,j*yInterval);
            glVertex2f(i*xInterval+u[IX(i,j)],j*yInterval+v[IX(i,j)]);
        }
    }
    glEnd();    
    ofPopStyle(); 
}

void ofxField2D::drawDensity()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 
    glPointSize(pointSize);
    glBegin(GL_POINTS);
    for(int i = 0; i <=dimX; i++)
    {
        for(int j = 0; j <=dimY; j++)
        {
            glColor4f(1,1,1,dens[IX(i,j)]/10.0);
            glVertex2f(i*xInterval,j*yInterval);
        }
    }
    glEnd();
    ofPopStyle(); 
}


void ofxField2D::drawFieldGrid()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);       
	for(int i = 0; i <=dimX; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j <=dimY; j++)
		{
			glColor4f(1.0,1.0,1.0,dens[IX(i,j)]);
			glVertex3f(i*xInterval,j*yInterval,10.0*dens[IX(i,j)]);
			glVertex3f((i+1)*xInterval,j*yInterval,10.0*dens[IX(i,j)]);                
		}
		glEnd();  
	}
	ofPopStyle(); 	
}


void ofxField2D::drawFieldGridWire()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(int i = 0; i <=dimX; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <=dimY; j++)
		{
			glColor4f(1.0,1.0,1.0,dens[IX(i,j)]);
			glVertex3f(i*xInterval,j*yInterval,10.0*dens[IX(i,j)]);
			glVertex3f((i+1)*xInterval,j*yInterval,10.0*dens[IX(i,j)]);                
		}
		glEnd();  
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  	
	ofPopStyle(); 
}

void ofxField2D::drawFieldMesh()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(int i = 0; i <=dimX; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j <=dimY; j++)
		{
			glColor4f(1.0,1.0,1.0,dens[IX(i,j)]);
			glVertex3f(i*xInterval,j*yInterval,10.0*dens[IX(i,j)]);
			glColor4f(1.0,1.0,1.0,dens[IX(i+1,j)]);
			glVertex3f((i+1)*xInterval,j*yInterval,10.0*dens[IX(i+1,j)]);                
		}
		glEnd();  
	}	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  	
	ofPopStyle(); 
}

void ofxField2D::drawFieldVectorMesh()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 		
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(int i = 0; i <=dimX; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for(int j = 0; j <=dimY; j++)
		{
			glColor4f(1.0,1.0,1.0,dens[IX(i,j)]);
			glVertex3f(i*xInterval,j*yInterval,u[IX(i,j)]+v[IX(i,j)]);
			glColor4f(1.0,1.0,1.0,dens[IX(i+1,j)]);
			glVertex3f((i+1)*xInterval,j*yInterval,u[IX(i+1,j)]+v[IX(i+1,j)]);                
		}
		glEnd();  
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  	
	ofPopStyle(); 	
}

void ofxField2D::drawFieldLinesVertical()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 		
	ofSetLineWidth(lineWidth);
	for(int i = 0; i <=dimX; i++)
	{
		glBegin(GL_LINE_STRIP);
		for(int j = 0; j <=dimY; j++)
		{
			glColor4f(1.0,1.0,1.0,dens[IX(i,j)]);
			glVertex3f(i*xInterval,j*yInterval,dens[IX(i,j)]);
		}
		glEnd();  
	}
	ofPopStyle(); 		
}

void ofxField2D::drawFieldVelocityVertical()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 	
	
	ofSetLineWidth(5);
	for(int i = 0; i <=dimX; i++)
	{
		glBegin(GL_LINE_STRIP);
		for(int j = 0; j <=dimY; j++)
		{
			glColor4f(1.0,1.0,1.0,dens[IX(i,j)]);
			glVertex3f(i*xInterval,j*yInterval,u[IX(i,j)]+v[IX(i,j)]);        
		}
		glEnd();  
	}
	ofPopStyle(); 		
}

void ofxField2D::drawFieldLinesHorizontal()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 		
	ofSetLineWidth(5); 
	for(int j = 0; j <=dimY; j++)
	{
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i <=dimX; i++)
		{
			glColor4f(1.0,1.0,1.0,dens[IX(i,j)]);
			glVertex3f(i*xInterval,j*yInterval,dens[IX(i,j)]);
			//        glVertex3f(i*xInterval,j*yInterval,u[IX(i,j)]+v[IX(i,j)]);        
		}
		glEnd();  
	}
	ofPopStyle(); 
}

void ofxField2D::drawFieldVelocityHorizontal()
{
    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 		
	ofSetLineWidth(5); 
	for(int j = 0; j <=dimY; j++)
	{
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i <=dimX; i++)
		{
			glColor4f(1.0,1.0,1.0,dens[IX(i,j)]);
			glVertex3f(i*xInterval,j*yInterval,u[IX(i,j)]+v[IX(i,j)]);        
		}
		glEnd();  
	}
	ofPopStyle(); 	
}

void ofxField2D::drawFieldAroundMe(float radius, ofVec2f loc, ofVec3f color)
{
	
	float width = ofGetWidth(); 
	float height = ofGetHeight(); 
	
	float icenter = ofMap(loc.x,0,width,1,dimX); 
	float jcenter = ofMap(loc.y,0,height,1,dimY); 
	
	float i0 = ofMap(loc.x-radius*2,0,width,1,dimX); 
	float j0 = ofMap(loc.y-radius*2,0,height,1,dimY);
	float i9 = ofMap(loc.x+radius*2,0,width,1,dimX); 
	float j9 = ofMap(loc.y+radius*2,0,height,1,dimY);

    ofPushStyle();  
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); 			
	ofSetLineWidth(3); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    
	
	for(int j = (int)j0; j <=j9; j++)
	{
		glBegin(GL_LINE_STRIP);
		
		for(int i = (int)i0; i <=i9; i++)
		{
			float op = ofDist(i*xInterval,j*yInterval,icenter*xInterval,jcenter*yInterval);
			op= radius/pow(op,2);  
			
			glColor4f(color.x,color.y,color.z,op);
			
			glVertex3f(i*xInterval,j*yInterval,0);  
			glVertex3f(i*xInterval+u[IX(i,j)],j*yInterval+v[IX(i,j)],0);          
			//        glVertex3f(i0*xInterval,j0*yInterval,u[IX(i0,j0)]+v[IX(i0,j0)]);        
			//        glVertex3f(i*xInterval,j*yInterval,u[IX(i,j)]+v[IX(i,j)]);  
		}
		glEnd();  
	}
	ofSetLineWidth(1);    
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);   
	ofPopStyle(); 
}

int ofxField2D::getWidth(){
	
	return dimX+2;
}

int ofxField2D::getHeight(){
	
	return dimY+2;
}
















