/*
 *  videoDelay.cpp
 *  openFrameworks
 *
 *  Created by damian on 4/09/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "videoDelayEffect.h"


videoDelayEffect::videoDelayEffect()
{
	srcFunc = GL_SRC_ALPHA;
	destFunc = GL_ONE_MINUS_SRC_ALPHA;

	alpha       = 0.0f;
	scale       = 1;
	scaleTo     = 1;
	needToGrab  = false;
	bOn         = true;
	fCounter 	= 0;
	alphaTo 	= 0.0;
}


videoDelayEffect::~videoDelayEffect()
{
}

void videoDelayEffect::setup( int _grabX, int _grabY, int _grabW, int _grabH )
{
	grabX = _grabX;
	grabY = _grabY;
	grabW = _grabW;
	grabH = _grabH;

	// allocate the texture
	backBufferTex.allocate( grabW, grabH, GL_RGB );
	clearBuffer();
}

void videoDelayEffect::update()
{

	alpha = .995 * alpha + .005 * alphaTo;
	scale = .95 * scale + .05 * scaleTo;
	halfscale = (1.000000f - scale) / 2.000000f;

}


void videoDelayEffect::setScale( float _scale )
{
	scaleTo = _scale;

}

void videoDelayEffect::clearBuffer()
{
	needToGrab = true;
}


void videoDelayEffect::draw()
{
	if ( needToGrab )
	{
		backBufferTex.loadScreenData( grabX, grabY, grabW, grabH );
		needToGrab = false;
	}

	//	turn on blending
	ofEnableAlphaBlending();
	glBlendFunc(srcFunc,destFunc);

	glColor4f(1.0f,1.0f,1.0f,alpha);

    glPushMatrix();

        // draw
        backBufferTex.draw( grabX + grabW * halfscale, grabY + grabH * halfscale, grabW * scale, grabH * scale );

        // store
        backBufferTex.loadScreenData( grabX, grabY, grabW, grabH );

    glPopMatrix();

	// turn blending back off
	ofDisableAlphaBlending();
}

