/*
 *  ofxDither.h
 *  emptyExample
 *
 *  Created by lukasz karluk on 28/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

#define DITHER_ORDERED_2x2	2
#define DITHER_ORDERED_3x3	3
#define DITHER_ORDERED_4x4	4
#define DITHER_ORDERED_8x8	8

class ofxDither
{
	
public:

	 ofxDither();
	~ofxDither();
	
	void dither_ordered			( ofImage& imageIn, ofImage& imageOut, int mapSize = DITHER_ORDERED_8x8 );
	void dither_floyd_steinberg	( ofImage& imageIn, ofImage& imageOut );
	void dither_atkinson		( ofImage& imageIn, ofImage& imageOut );
	
	unsigned char threshold_map_2x2[ 4 ];
	unsigned char threshold_map_3x3[ 9 ];
	unsigned char threshold_map_4x4[ 16 ];
	unsigned char threshold_map_8x8[ 64 ];
	
private:
	
	void prepImagesForGreyscale	( ofImage& imageIn, ofImage& imageOut );
	void finishGreyscale		( ofImage& imageIn, ofImage& imageOut );
	
	unsigned char* imageInPixels;
	unsigned char* imageOutPixels;
	
};