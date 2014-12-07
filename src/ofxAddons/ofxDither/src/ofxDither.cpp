/*
 *  ofxDither.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 28/02/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxDither.h"

ofxDither :: ofxDither ()
{
	unsigned char map_2x2[ 4 ] = 
	{
		1, 3,
		4, 2
	};
	
	unsigned char map_3x3[ 9 ] = 
	{ 
		3, 7, 4, 
		6, 1, 9, 
		2, 8, 5 
	};
	
	unsigned char map_4x4[ 16 ] = 
	{ 
		1,  9,  3,  11,
		13, 5,  15, 7,
		4,  12, 2,  10,
		16, 8,  14, 6
	};
	
	unsigned char map_8x8[ 64 ] = 
	{ 
		1,  49, 13, 61, 4,  52, 16, 64,
		33, 17, 45, 29, 36, 20, 48, 32,
		9,  57, 5,  53, 12, 60, 8,  56,
		41, 25, 37, 21, 44, 28, 40, 24,
		3,  51, 15, 63, 2,  50, 14, 62,
		35, 19, 47, 31, 34, 18, 46, 30,
		11, 59, 7,  55, 10, 58, 6,  54,
		43, 27, 39, 23, 42, 26, 38, 22
	};
	
	memcpy( threshold_map_2x2, map_2x2, 4 );
	memcpy( threshold_map_3x3, map_3x3, 9 );
	memcpy( threshold_map_4x4, map_4x4, 16 );
	memcpy( threshold_map_8x8, map_8x8, 64 );
	
	unsigned char* imageInPixels	= NULL;
	unsigned char* imageOutPixels	= NULL;
}

ofxDither :: ~ofxDither()
{
	//
}

////////////////////////////////////////////////////////////////////
//
//	ORDERED DITHER => http://en.wikipedia.org/wiki/Ordered_dithering
//
////////////////////////////////////////////////////////////////////

void ofxDither :: dither_ordered ( ofImage& imageIn, ofImage& imageOut, int mapSize )
{
	prepImagesForGreyscale( imageIn, imageOut );
	
	int w = imageIn.width;
	int h = imageIn.height;
	int s = mapSize;
	
	for( int y=0; y<h; y++ )
	{
		for( int x=0; x<w; x++ )
		{
			int p = y * w + x;
			int j = ( y % s ) * s + ( x % s );
			int i = 0;							// index matrix value.
			
			if( s == DITHER_ORDERED_2x2 )
			{
				i = threshold_map_2x2[ j ];
			}
			else if( s == DITHER_ORDERED_3x3 )
			{
				i = threshold_map_3x3[ j ];
			}
			else if( s == DITHER_ORDERED_4x4 )
			{
				i = threshold_map_4x4[ j ];
			}
			else if( s == DITHER_ORDERED_8x8 )
			{
				i = threshold_map_8x8[ j ];
			}
			
			int t = 255 * ( ( i - 0.5 ) / ( s * s ) );
			
			imageOutPixels[ p ] = ( imageInPixels[ p ] > t ) ? 255 : 0;
		}
	}
	
	finishGreyscale( imageIn, imageOut );
}

////////////////////////////////////////////////
//
//	FLOYD STEINBERG DITHER.
//	http://en.wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering
//	original code from, fixed quantization error round off bug.
//	also now errors are added up for every pixels, including bordering pixels.
//	https://github.com/jesusgollonet/ofxHalftoner
//
////////////////////////////////////////////////

void ofxDither :: dither_floyd_steinberg ( ofImage& imageIn, ofImage& imageOut )
{
	prepImagesForGreyscale( imageIn, imageOut );
	
	int w = imageIn.width;
	int h = imageIn.height;
	int t = w * h;

	float* qErrors = new float[ t ];
	for( int i=0; i<t; i++ )
		qErrors[ i ] = 0.0;
	
	memcpy( imageOutPixels, imageInPixels, t );
	
	for( int y=0; y<h; y++ )
	{
		for( int x=0; x<w; x++ )
		{
			int p = y * w + x;
			
			int oldPx = imageOutPixels[ p ] + qErrors[ p ];
			int newPx = oldPx < 127 ? 0 : 255;
			imageOutPixels[ p ] = newPx;
			
			int qError;				// quantization error
			qError = oldPx - newPx;
			
			int xx, yy, pp;
			bool b1, b2;
			
			//--- pixel right of current pixel.
			
			xx = x + 1;
			yy = y + 0;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += ( 7.0 / 16.0 ) * qError;
			}
			
			//--- pixel bottom left of current pixel.
			
			xx = x - 1;
			yy = y + 1;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += ( 3.0 / 16.0 ) * qError;
			}
			
			//--- pixel bottom of current pixel.
			
			xx = x + 0;
			yy = y + 1;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += ( 5.0 / 16.0 ) * qError;
			}
			
			//--- pixel bottom right of current pixel.
			
			xx = x + 1;
			yy = y + 1;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += ( 1.0 / 16.0 ) * qError;
			}
		}
	}
	
	delete[] qErrors;
	
	finishGreyscale( imageIn, imageOut );
}

////////////////////////////////////////////////
//
//	ATKINSON DITHER.
//
////////////////////////////////////////////////

void ofxDither :: dither_atkinson ( ofImage& imageIn, ofImage& imageOut )
{
	prepImagesForGreyscale( imageIn, imageOut );
	
	int w = imageIn.width;
	int h = imageIn.height;
	int t = w * h;
	
	float* qErrors = new float[ t ];
	for( int i=0; i<t; i++ )
		qErrors[ i ] = 0.0;
	
	memcpy( imageOutPixels, imageInPixels, t );
	
	for( int y=0; y<h; y++ )
	{
		for( int x=0; x<w; x++ )
		{
			int p = y * w + x;
			
			int oldPx = imageOutPixels[ p ] + qErrors[ p ];
			int newPx = oldPx < 127 ? 0 : 255;
			imageOutPixels[ p ] = newPx;
			
			int qError;				// quantization error
			qError = oldPx - newPx;
			
			int xx, yy, pp;
			bool b1, b2;
			
			//--- pixel right of current pixel.
			
			xx = x + 1;
			yy = y + 0;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += 0.125 * qError;
			}
			
			//--- pixel two spot to the right of current pixel.
			
			xx = x + 2;
			yy = y + 0;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += 0.125 * qError;
			}
			
			//--- pixel bottom left of current pixel.
			
			xx = x - 1;
			yy = y + 1;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += 0.125 * qError;
			}
			
			//--- pixel bottom of current pixel.
			
			xx = x + 0;
			yy = y + 1;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += 0.125 * qError;
			}
			
			//--- pixel bottom right of current pixel.
			
			xx = x + 1;
			yy = y + 1;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += 0.125 * qError;
			}
			
			//--- pixel two spots down from current pixel.
			
			xx = x + 0;
			yy = y + 2;
			pp = yy * w + xx;
			
			b1 = ( xx >= 0 ) && ( xx < w );		// check other pixel is inside image.
			b2 = ( yy >= 0 ) && ( yy < h );		// check other pixel is inside image.
			
			if( b1 && b2 )
			{
				qErrors[ pp ] += 0.125 * qError;
			}
		}
	}
	
	delete[] qErrors;
	
	finishGreyscale( imageIn, imageOut );
}

////////////////////////////////////////////////
//	PREP / FINISH.
////////////////////////////////////////////////

void ofxDither :: prepImagesForGreyscale ( ofImage& imageIn, ofImage& imageOut )
{
	int w = imageIn.width;
	int h = imageIn.height;
	
	//--- image in.
	
	if( imageIn.bpp == 8 )	// already greyscale.
	{
		imageInPixels = imageIn.getPixels();
	}
	else					// convert to greyscale.
	{
		ofImage imageInBW;
        imageInBW.setFromPixels( imageIn.getPixelsRef() );
		imageInBW.setImageType( OF_IMAGE_GRAYSCALE );
		
		imageInPixels = imageInBW.getPixels();
	}
	
	//--- image out.
	
	int b1 = imageOut.width  != w;
	int b2 = imageOut.height != h;
	int b3 = imageOut.bpp    != 8;
	
	if( b1 || b2 || b3 )
	{
		imageOut.clear();
		imageOut.allocate( w, h, OF_IMAGE_GRAYSCALE );
	}
	
	imageOutPixels = new unsigned char[ w * h ];
}

void ofxDither :: finishGreyscale ( ofImage& imageIn, ofImage& imageOut )
{
	int w = imageIn.width;
	int h = imageIn.height;
	
	imageOut.setFromPixels( imageOutPixels, w, h, OF_IMAGE_GRAYSCALE );
	
	imageInPixels	= NULL;
	
	delete[] imageOutPixels;
	imageOutPixels	= NULL;
}