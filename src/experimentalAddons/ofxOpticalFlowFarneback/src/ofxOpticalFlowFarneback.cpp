/*
 *  ofxOpticalFlowFarneback.cpp
 *  created by Timothy Scaffidi on 13/11/2012
 *  based on ofxOpticalFlowLK by lukasz karluk.
 *
 */

#include "ofxOpticalFlowFarneback.h"

ofxOpticalFlowLK::ofxOpticalFlowLK() {
    
    flow = NULL;
    
    bMirrorH = false;
    bMirrorV = false;
    
    bInitialised = false;
}

ofxOpticalFlowLK::~ofxOpticalFlowLK() {
	destroy();
}

///////////////////////////////////////////
//	SETUP.
///////////////////////////////////////////

void ofxOpticalFlowLK::setup(const ofRectangle& size) {
	setup(size.width, size.height);
}

void ofxOpticalFlowLK::setup(int width, int height){
    setup(width, height, 0.5, 3, 10, 1, 7, 1.5, false, false);
}

void ofxOpticalFlowLK::setup(int width, int height,
                             double pyramidScale,
                             int pyramidLevels,
                             int windowSize,
                             int iterationsPerLevel,
                             int expansionArea,
                             double expansionSigma,
                             bool flowFeedback,
                             bool gaussianFiltering) {
	sizeSml.width = width;
	sizeSml.height = height;
	
	sizeLrg.width = width;		// assume input size is the same as optical flow size.
	sizeLrg.height = height;
	
	if(bInitialised) {
		destroy();
    }
	
	colrImgLrg.allocate(sizeLrg.width, sizeLrg.height);
	colrImgSml.allocate(sizeSml.width, sizeSml.height);
	greyImgLrg.allocate(sizeLrg.width, sizeLrg.height);
	greyImgSml.allocate(sizeSml.width, sizeSml.height);
	greyImgPrv.allocate(sizeSml.width, sizeSml.height);
    
    flow = cvCreateMat(sizeSml.height, sizeSml.width, CV_32FC2);
	
    pyr_scale = pyramidScale;
    levels = pyramidLevels;
    winsize = windowSize;
    iterations = iterationsPerLevel;
    poly_n = expansionArea;
    poly_sigma = expansionSigma;
    this->flowFeedback = flowFeedback;
    this->gaussianFiltering = gaussianFiltering;
    
	reset();
	
	bInitialised = true;
}

void ofxOpticalFlowLK::reset() {
	colrImgLrg.set(0);
	colrImgSml.set(0);
	greyImgLrg.set(0);
	greyImgSml.set(0);
	greyImgPrv.set(0);

    cvSetZero(flow);
}

void ofxOpticalFlowLK::destroy() {
	colrImgLrg.clear();
	colrImgSml.clear();
	greyImgLrg.clear();
	greyImgSml.clear();
	greyImgPrv.clear();
	
    if(flow) {
        cvReleaseMat(&flow);
    }
}

///////////////////////////////////////////
//	UPDATE.
///////////////////////////////////////////

void ofxOpticalFlowLK::update(ofImage& source) {
	update(source.getPixels(), source.width, source.height, source.type);
}

void ofxOpticalFlowLK::update(ofxCvColorImage& source) {
	update(source.getPixels(), source.width, source.height, OF_IMAGE_COLOR);
}

void ofxOpticalFlowLK::update(ofxCvGrayscaleImage& source) {
	update(source.getPixels(), source.width, source.height, OF_IMAGE_GRAYSCALE);
}

void ofxOpticalFlowLK::update(ofVideoPlayer& source) {
	update(source.getPixels(), source.width, source.height, OF_IMAGE_COLOR);	// assume colour image type.
}

void ofxOpticalFlowLK::update(ofVideoGrabber& source) {
	update(source.getPixels(), source.width, source.height, OF_IMAGE_COLOR);	// assume colour image type.
}

void ofxOpticalFlowLK::update(unsigned char* pixels, int width, int height, int imageType) {

	bool rightSize = (sizeSml.width == width && sizeSml.height == height);
	
	//-- making the input the right size for optical flow to work with.
	
	if(rightSize) {
		if(imageType == OF_IMAGE_COLOR) {
			colrImgSml.setFromPixels(pixels, sizeSml.width, sizeSml.height);
			greyImgSml.setFromColorImage(colrImgSml);
		} else if(imageType == OF_IMAGE_GRAYSCALE) {
			greyImgSml.setFromPixels(pixels, sizeSml.width, sizeSml.height);
		} else {
			return;		// wrong image type.
		}
	} else {

		bool sizeLrgChanged = (sizeLrg.width != width || sizeLrg.height != height);
		
		if(sizeLrgChanged) {		// size of input has changed since last update.
			sizeLrg.width = width;
			sizeLrg.height = height;
			
			colrImgLrg.clear();
			greyImgLrg.clear();
			
			colrImgLrg.allocate(sizeLrg.width, sizeLrg.height);
			greyImgLrg.allocate(sizeLrg.width, sizeLrg.height);
			
			colrImgLrg.set(0);
			greyImgLrg.set(0);
		}
		
		if(imageType == OF_IMAGE_COLOR) {
			colrImgLrg.setFromPixels(pixels, sizeLrg.width, sizeLrg.height);
			colrImgSml.scaleIntoMe(colrImgLrg);
			greyImgSml.setFromColorImage(colrImgSml);
		} else if(imageType == OF_IMAGE_GRAYSCALE) {
			greyImgLrg.setFromPixels(pixels, sizeLrg.width, sizeLrg.height);
			greyImgSml.scaleIntoMe(greyImgLrg);
		} else {
			return;		// wrong image type.
		}
	}
	
	if(bMirrorH || bMirrorV) {
		greyImgSml.mirror(bMirrorV, bMirrorH);
    }
	
    update(greyImgPrv.getCvImage(), greyImgSml.getCvImage());
	
	greyImgPrv = greyImgSml;
}

void ofxOpticalFlowLK::update(IplImage * previousImage, IplImage * currentImage) {
    
    if((previousImage->width != currentImage->width) || (previousImage->height != currentImage->height)) {
        return; // images do not match.
    }
    
    int w = currentImage->width;
    int h = currentImage->height;

    if(flow) {
        if((flow->width != w) || (flow->height != h)) {
            cvReleaseMat(&flow);
            flow = cvCreateMat(h, w, CV_32FC2);
        }
    } else {
        flow = cvCreateMat(h, w, CV_32FC2);
    }
    
    int flags = 0;
    if(flowFeedback) flags |= cv::OPTFLOW_USE_INITIAL_FLOW;
    if(gaussianFiltering) flags |= cv::OPTFLOW_FARNEBACK_GAUSSIAN;
    
    cvCalcOpticalFlowFarneback(previousImage, currentImage, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
}

///////////////////////////////////////////
//	OP.FLOW VELOCITY GETTERS.
///////////////////////////////////////////

ofPoint ofxOpticalFlowLK::getVelAtNorm(float x, float y) {
	int px = x * (flow->width - 1);
	int py = y * (flow->height - 1);
    return getVelAtPixel(px, py);
}

ofPoint ofxOpticalFlowLK::getVelAtPixel(int x, int y) {
	x = ofClamp(x, 0, flow->width - 1);
	y = ofClamp(y, 0, flow->height - 1);
	
	ofPoint p;
    CvPoint2D32f fxy = CV_MAT_ELEM(*flow, CvPoint2D32f, y, x);
    p.x = fxy.x;
    p.y = fxy.y;

	return p;
}

///////////////////////////////////////////
//	DRAW.
///////////////////////////////////////////

void ofxOpticalFlowLK::draw(int width, int height,  float lineScale, int res) {
	bool rightSize = (sizeSml.width == width && sizeSml.height == height);
	
	ofPoint vel;
	
	for(int x=0; x<width; x+=res) {
		for(int y=0; y<height; y+=res) {
			if(rightSize) {
				vel = getVelAtPixel(x, y);
            } else {
				vel = getVelAtNorm(x / (float)width, y / (float)height);
            }
			
			if(vel.length() < 1) {  // smaller then 1 pixel, no point drawing.
				continue;
            }
			
			ofLine(x, y, x + vel.x * lineScale, y + vel.y * lineScale);
		}
	}
}

void ofxOpticalFlowLK::drawColored(int width, int height,  float lineScale, int res) {
	bool rightSize = (sizeSml.width == width && sizeSml.height == height);
	
	ofPoint vel;
    ofMesh velMesh;
    
    velMesh.setMode(OF_PRIMITIVE_LINES);
	
	for(int x=0; x<width; x+=res) {
		for(int y=0; y<height; y+=res) {
			if(rightSize) {
				vel = getVelAtPixel(x, y);
            } else {
				vel = getVelAtNorm(x / (float)width, y / (float)height);
            }
			
			if(vel.length() < 1) {  // smaller then 1 pixel, no point drawing.
				continue;
            }
			ofVec3f p(x,y);
            ofVec3f vc = vel;
            vc.normalize();
            float hue = (atan2(vc.y, vc.x)+3.14159265)/(3.14159265*2.0);
            ofFloatColor c;
            c.setHsb(hue, 1.0, 1.0);
            c.a = 0.25;
            
            velMesh.addColor(c);
            velMesh.addVertex(p);
            c.a = 0.0;
            velMesh.addColor(c);
            velMesh.addVertex(p+vel*lineScale);
		}
	}
    ofPushStyle();
    ofEnableAlphaBlending();
    velMesh.draw();
    ofPopStyle();
}

///////////////////////////////////////////
//	CONFIG.
///////////////////////////////////////////

void ofxOpticalFlowLK::setMirror(bool mirrorHorizontally, bool mirrorVertically) {
	bMirrorH = mirrorHorizontally;
	bMirrorV = mirrorVertically;
}
