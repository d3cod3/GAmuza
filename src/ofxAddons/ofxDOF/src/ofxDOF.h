/**
 * Depth of Field add on for openFrameworks
 * 
 * Prototyped as part of the RGBDToolkit, extracted out as a simple add on for a workshop at ITP
 *
 * James George (@obviousjim) -- 4/3/2013 http://www.jamesgeorge.org : http://github.com/obviousjim
 *
 */

#pragma once

#include "ofMain.h"

class ofxDOF {

  public:
	
	ofxDOF();
	
	void setup(); //defaults to screen resolution
	void setup(int width, int height);
	
	//default path is bin/data/dof/
	void setShaderPath(string path);
	void reloadShader(); // you can call this if you are tweaking the shader file

	//usually between 0 and 2 or 3
	void setBlurAmount(float blurAmount);
	float getBlurAmount();
	
	// how much of the scene is in focus, smaller number is a narrower focal distance
	void setFocalRange(float focalRange);
	float getFocalRange();
	
	// where is the focal plane from the camera
	void setFocalDistance(float focalDistance);
	float getFocalDistance();

	int getWidth();
	int getHeight();

	ofRectangle getDimensions();

	//draw your scene between calls to begin and end like you would an FBO or shader
	void begin();
	void end();

	//then draw the scene using this accessor, or use it elsewhere
	ofFbo& getFbo();
	
	void drawFocusAssist(int x, int y);
	void drawFocusAssist(int x, int y, int width, int height);
	void drawFocusAssist(ofRectangle drawRect);

  protected:
	
    ofVboMesh dofQuad;
	ofRectangle dimensions;
	ofFbo dofTarget;
	ofFbo swap;
	ofFbo scene;
	
	string shaderPath;
	ofShader depthOfField;
	ofShader focusAssist;

	float blurAmount;
	float focalRange;
	float focalDistance;

};
