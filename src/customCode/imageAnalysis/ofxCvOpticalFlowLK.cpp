//
// ofxCvOpticalFlowLK.h - a OpenCV cvOpticalFlowLK warpper for openFrameworks
//
// Copyright (C) 2008 Takashi Maekawa <takachin@generative.info> 
//     All rights reserved.
//     This is free software with ABSOLUTELY NO WARRANTY.
//
// You can redistribute it and/or modify it under the terms of 
// the GNU Lesser General Public License.
//

#include "ofxCvOpticalFlowLK.h"

ofxCvOpticalFlowLK::ofxCvOpticalFlowLK(void)
{
	captureWidth = DEFAULT_CAPTURE_WIDTH;
	captureHeight = DEFAULT_CAPTURE_HEIGHT;

	captureColsStep = DEFAULT_CAPTURE_COLS_STEP;
	captureRowsStep = DEFAULT_CAPTURE_ROWS_STEP;
}

ofxCvOpticalFlowLK::~ofxCvOpticalFlowLK(void)
{
	//cvReleaseImage(&vel_x);
	//cvReleaseImage(&vel_y);
}
	
void ofxCvOpticalFlowLK::allocate(int _w, int _h){
	captureWidth = _w;
	captureHeight = _h;

	vel_x = cvCreateImage( cvSize( captureWidth ,captureHeight ), IPL_DEPTH_32F, 1  );
	vel_y = cvCreateImage( cvSize( captureWidth ,captureHeight ), IPL_DEPTH_32F, 1  );
	
    cvSetZero(vel_x);
    cvSetZero(vel_y);
    
    for (int y = 0; y < captureHeight; y+=captureRowsStep ){
		for (int x = 0; x < captureWidth; x+=captureColsStep ){
            
            ofVec4f	v;
            v.set(x,y,0,0);
            velArray.push_back(v);
            
		}
	}
}

void ofxCvOpticalFlowLK::setCalcStep(int _cols, int _rows){
	captureColsStep = _cols;
	captureRowsStep = _rows;
}

void ofxCvOpticalFlowLK::calc( ofxCvGrayscaleImage & pastImage,
					   ofxCvGrayscaleImage & currentImage,					   
					   int size
					   )
{
	cvCalcOpticalFlowLK( pastImage.getCvImage(), currentImage.getCvImage(),
		cvSize( size, size), vel_x, vel_y );
    
    int dx, dy;
    int ii = 0;
	for (int y = 0; y < captureHeight; y+=captureRowsStep ){
		for (int x = 0; x < captureWidth; x+=captureColsStep ){
            
			dx = (int)cvGetReal2D( vel_x, y, x );
			dy = (int)cvGetReal2D( vel_y, y, x );
            
            velArray[ii].set(x,y,dx,dy);
            ii++;
            
		}
	}
    
}

void ofxCvOpticalFlowLK::draw(void){

	ofEnableAlphaBlending();
	glColor4f(1.0,0.906,0.463,1.0);
	ofNoFill();

	int x, y, dx, dy;
	for ( y = 0; y < captureHeight; y+=captureRowsStep ){
		for ( x = 0; x < captureWidth; x+=captureColsStep ){

			dx = (int)cvGetReal2D( vel_x, y, x );
			dy = (int)cvGetReal2D( vel_y, y, x );

			ofLine(x,y,x+dx,y+dy);

		}
	}
	ofDisableAlphaBlending();
}

IplImage* ofxCvOpticalFlowLK::getVelX(){
	return vel_x;
}

IplImage* ofxCvOpticalFlowLK::getVelY(){
	return vel_y;
}
