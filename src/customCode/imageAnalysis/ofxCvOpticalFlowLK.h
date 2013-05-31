//
// ofxCvOpticalFlowLK.h - a OpenCV cvOpticalFlowLK wrapper for openFrameworks
//
// Copyright (C) 2008 Takashi Maekawa <takachin@generative.info>
//     All rights reserved.
//     This is free software with ABSOLUTELY NO WARRANTY.
//
// You can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License.
//

#pragma once

#include "ofMain.h"
#include "ofxCvConstants.h"
#include "ofxCvGrayscaleImage.h"

#define	    OPTICAL_FLOW_COLS_STEP		16
#define	    OPTICAL_FLOW_ROWS_STEP		16

class ofxCvOpticalFlowLK
{
public:
	ofxCvOpticalFlowLK(void);
	~ofxCvOpticalFlowLK(void);

	void allocate(int _w, int _h);

	void calc( ofxCvGrayscaleImage & pastImage,ofxCvGrayscaleImage & currentImage,int size);

	void setCalcStep(int _cols, int _rows);

	void reset();
	void draw();

	IplImage* getVelX();
	IplImage* getVelY();
    
    vector<ofVec4f>       velArray;

private:

	static const int DEFAULT_CAPTURE_WIDTH = 320;
	static const int DEFAULT_CAPTURE_HEIGHT = 240;

	int captureWidth;
	int captureHeight;

	// 320x240 / 8 means 40x30 analysis grid
	// 320x240 / 20 means 16x12 analysis grid
	static const int DEFAULT_CAPTURE_COLS_STEP = OPTICAL_FLOW_COLS_STEP;
	static const int DEFAULT_CAPTURE_ROWS_STEP = OPTICAL_FLOW_ROWS_STEP;

	int captureColsStep;
	int captureRowsStep;

	IplImage* vel_x;
	IplImage* vel_y;

};
