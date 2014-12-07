/*
 *  ofxOpticalFlowFarneback.h
 *  created by Timothy Scaffidi on 13/11/2012
 *  based on ofxOpticalFlowLK by lukasz karluk.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofxOpticalFlowLK {
	
public:
	
	 ofxOpticalFlowLK();
	~ofxOpticalFlowLK();
	
	void setup(const ofRectangle& size);
	void setup(int width, int height);
    void setup(int width, int height,
               double pyramidScale,
               int pyramidLevels,
               int windowSize,
               int iterationsPerLevel,
               int expansionArea,
               double expansionSigma,
               bool flowFeedback,
               bool gaussianFiltering);
	
	void reset();
	void destroy();
	
	void update(ofImage& source);
	void update(ofxCvColorImage& source);
	void update(ofxCvGrayscaleImage& source);
	void update(ofVideoPlayer& source);
	void update(ofVideoGrabber& source);
	void update(unsigned char* pixels, int width, int height, int imageType);
    void update(IplImage * previousImage, IplImage * currentImage);
	
	ofPoint getVelAtNorm(float x, float y);
	ofPoint getVelAtPixel(int x, int y);
	
	void draw(int width, int height, float lineScale = 10, int res = 10);
	void drawColored(int width, int height, float lineScale = 10, int res = 10);
	
	void setMirror(bool mirrorHorizontally, bool mirrorVertically);
    bool isInitialized() { return bInitialised; }
    
    double getPyramidScale() { return pyr_scale; }
    int getPyramidLevels() { return levels; }
    int getWindowSize() { return winsize; }
    int getIterationsPerLevel() { return iterations; }
    int getExpansionArea() { return poly_n; }
    double getExpansionSigma() { return poly_sigma; }
    bool getFlowFeedback() { return flowFeedback; }
    bool getGaussianFiltering() { return gaussianFiltering; }
    
    void setPyramidScale(double value) { pyr_scale = value; }
    void setPyramidLevels(int value) { levels = value; }
    void setWindowSize(int value) { winsize = value; }
    void setIterationsPerLevel(int value) { iterations = value; }
    void setExpansionArea(int value) { poly_n = value; }
    void setExpansionSigma(double value) { poly_sigma = value; }
    void setFlowFeedback(bool value) { flowFeedback = value; }
    void setGaussianFiltering(bool value) { gaussianFiltering = value; }
    
private:
	bool bInitialised;
	ofRectangle sizeSml;
	ofRectangle sizeLrg;
	
	ofxCvColorImage colrImgLrg;		// full scale color image.
	ofxCvColorImage	colrImgSml;		// full scale color image.
	ofxCvGrayscaleImage	greyImgLrg;	// full scale grey image.
	ofxCvGrayscaleImage	greyImgSml;	// scaled down grey image.
	ofxCvGrayscaleImage	greyImgPrv;	// scaled down grey image - copy of previous frame.
	CvMat * flow;       // optical flow in the y direction.

	bool bMirrorH;
	bool bMirrorV;
    
    double pyr_scale;
    int levels;
    int winsize;
    int iterations;
    int poly_n;
    double poly_sigma;
    bool flowFeedback;
    bool gaussianFiltering;
};