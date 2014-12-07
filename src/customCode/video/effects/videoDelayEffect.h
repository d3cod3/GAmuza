/*
 *  videoDelayEffect.h
 *  openFrameworks
 *
 *  Created by damian on 4/09/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _VIDEO_DELAY_EFFECT_H
#define _VIDEO_DELAY_EFFECT_H

#include "ofMain.h"
#include "ofTexture.h"

class videoDelayEffect{
public:
	videoDelayEffect();
	~videoDelayEffect();

	// grab* are in screen coordinates - specify an area of screen to grab
	void setup( int grabX, int grabY, int grabW, int grabH );
	void setScale( float scale );

	void update();

	// same syntax as glBlendFunc
	void setBlendFunc( int src, int dest );

	// clear the back buffer
	void clearBuffer();

	void draw();

	float alphaTo;
	float scaleTo;
	bool bOn;
	float scale;
	float alpha;

	int grabX, grabY, grabW, grabH;


private:

	ofTexture backBufferTex;
	int srcFunc, destFunc;


	float halfscale;
	float fCounter;


	bool needToGrab;


};


#endif
