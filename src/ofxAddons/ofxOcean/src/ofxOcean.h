/*
 *  ofxOcean.h
 *  NMMOcean
 *
 *  Created by James George on 3/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once

#include "ofMain.h"

#include <complex>
#include "kiss_fftnd.h"


class ofxOcean
{
  public:
	ofxOcean();
    ~ofxOcean();

    //set before calling set up
	int width; //must be power of two
	int height;    //must be power of two
	ofVec3f size;
	float windSpeed;

	void setup();
	void update();

    ofVec3f floatingPosition(ofVec3f position, bool considerChoppy = true);
    ofVec3f floatingPosition(float u, float v, bool considerChoppy = true);
    float waterHeight(float u, float v);
    float choppyOffset(float u, float v);

    //only works after one frame of update
    float getHighestWave();
    float getLowestWave();

    //shape vars, can be changed in real time
    float waveScale;
	float choppyScale;
    float waveSpeed;

	ofVec3f* getVertices();
    ofVec2f* getUVs();
	ofVec3f* getNormals();
	ofVec4f* getTangents();

	int g_width;
    int g_height;
	int vertexCount; // == g_width*g_height
	
	ofVec3f cameraPosition;
	
    //use this to synchronize...
    void setFrameNum(int frameNum);

  private:
	float currentWaveScale;
    bool allocated;
	int frameNum;
    float highestWave;
    float lowestWave;

    float heightDenom;

	void InitWaveGenerator();
	void GenerateGeometry();

	vector< complex<float> > h0;
	vector< complex<float> > t_x;
	vector< complex<float> > t_y;

	vector< complex<float> > data;
	void IFF2(vector< complex<float> >& data);

	int n_width;
	int n_height;

    //fft vars
    kiss_fftnd_cfg sti;
    kiss_fft_cpx* fftInputBuf;
    kiss_fft_cpx* fftOutputBuf;

	ofVec2f* baseUVs;
	ofVec3f* baseVertices;
	ofVec3f* baseNormals;
	ofVec4f* baseTangents;

    ofVec3f* vertices;//current vertices;

};

