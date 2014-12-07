/*
 *  ofxOcean.cpp
 *  NMMOcean
 *
 *  Created by James George on 3/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxOcean.h"

//static functions
static float GaussianRnd() {
	float x1 = ofRandomuf();
	float x2 = ofRandomuf();

	if (x1 == 0.0){
		x1 = 0.01;
	}

	return sqrt (-2.0 * log(x1)) * cos(2.0 * PI * x2);
}

// Phillips spectrum
static float P_spectrum (ofVec2f vec_k, ofVec2f wind) {
	float A = vec_k.x > 0.0 ? 1.0 : 0.05; // Set wind to blow only in one direction - otherwise we get turmoiling water
	float L = wind.lengthSquared() / 9.81;
	float k2 = vec_k.lengthSquared();
	// Avoid division by zero
	if (vec_k.length() == 0.0) {
		return 0.0;
	}
	return A * exp(-1.0 / (k2*L*L) - pow( float(vec_k.length() * 0.1f), float(2.0f))) / (k2*k2) * pow ( float((vec_k/vec_k.length()).dot(wind/wind.length())), float(2.0));// * wind_x * wind_y;
}

static float disp (ofVec2f vec_k) {
	return sqrt(9.81 * vec_k.length());
}

ofxOcean::ofxOcean()
{
    allocated = false;

    vertices = NULL;
    baseUVs = NULL;
    baseVertices = NULL;
	baseNormals = NULL;
	baseTangents = NULL;

    fftInputBuf = NULL;
    fftOutputBuf = NULL;

    width = 64;
	height = 64;

    windSpeed = 40;
    waveSpeed = 1.0;
    waveScale = 3.0;
    choppyScale = 3.0;
	currentWaveScale = waveScale;
	
    size = ofVec3f(300.0, 1.0, 300.0);

    highestWave = lowestWave = 0;
}

ofxOcean::~ofxOcean()
{
    if(allocated){
        delete[] vertices;
        delete[] baseUVs;
        delete[] baseNormals;
        delete[] baseTangents;
        delete[] fftInputBuf;
        delete[] fftOutputBuf;
    }
}

void ofxOcean::setup()
{

    data.clear();
	// Init the water height matrix
	data.reserve(width*height);
	t_x.clear();
	t_x.reserve(width*height);
    t_y.clear();
	t_y.reserve(width*height);

    heightDenom = width*height+size.x*size.y;
	// Geometry size
	g_height = height + 1;
	g_width = width + 1;

	// Init wave spectra
	InitWaveGenerator();
    GenerateGeometry();

    frameNum = 0;
    allocated = true;
}

void ofxOcean::InitWaveGenerator()
{
    h0.reserve(width*height);
    ofVec2f wind = ofVec2f (windSpeed, 0.0);
    ofVec2f vec_k;
	// Initialize wave generator
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float yc = y < height / 2 ? y : -height + y;
			float xc = x < width / 2 ? x : -width + x;
			vec_k = ofVec2f(2.0 * PI * xc / size.x, 2.0 * PI * yc / size.z);
			h0[width * y + x] = complex<float>( GaussianRnd(), GaussianRnd()) * 0.707f * sqrt(P_spectrum(vec_k, wind));
		}
    }

    //allocate FFT data
    const int dims[2] = {height, width}; // dimensions of fft ( height, width)
    const int ndims = 2; // number of dimensions. here 2 (2D)

    sti = kiss_fftnd_alloc(dims, ndims, 1, 0, 0); // inverse 2d fft configure
    fftInputBuf = new kiss_fft_cpx[width * height];
    fftOutputBuf = new kiss_fft_cpx[width * height];
}

void ofxOcean::GenerateGeometry() {

    // Build the base vertices and UVs
    vertexCount = g_height * g_width;
    baseVertices = new ofVec3f[vertexCount];
	vertices = new ofVec3f[vertexCount];
	baseTangents = new ofVec4f[vertexCount];
    baseNormals = new ofVec3f[vertexCount];
	baseUVs = new ofVec2f[vertexCount];

	ofVec2f uvScale = ofVec2f(1.0 / (g_width - 1), 1.0 / (g_height - 1));
	ofVec3f sizeScale = ofVec3f(size.x / (g_width - 1), size.y, size.z / (g_height - 1));

	for (int y = 0; y < g_height; y++) {
		for (int x = 0; x < g_width; x++) {
			ofVec3f vertex = ofVec3f (x, 0.0, y);
			baseVertices[y * g_width + x] = vertex * sizeScale;
			baseUVs[y*g_width + x] = ofVec2f(x, y) * uvScale;
		}
	}

    lowestWave = highestWave = baseVertices[0].y;
	for(int y = 0; y < g_height; y++) {
		for (int x = 0; x < g_width;x++) {
			baseTangents[y*g_width + x] = ofVec4f (1.0, 0.0, 0.0, -1.0);
		}
	}
}

void ofxOcean::setFrameNum(int _frameNum)
{
    frameNum = _frameNum;
}

void ofxOcean::update()
{
    heightDenom = width*height+size.x*size.y;
	ofVec3f centerOffset;
	centerOffset.x = floor(cameraPosition.x/size.x) * size.x;
	centerOffset.z = floor(cameraPosition.z/size.z) * size.z;
	//	centerOffset.y = transform.position.y;
	centerOffset.y = 0;

	ofVec3f sampleOffset(fmod(cameraPosition.x ,size.x) / size.x * width,
						 0,
						 fmod(cameraPosition.z,size.z) / size.z * height);
	if(sampleOffset.x < 0) sampleOffset.x += width;
	if(sampleOffset.z < 0) sampleOffset.z += height;
	
//	cout << "sample offset is " << sampleOffset << endl;
	int sampleOffsetX = fmod(float(cameraPosition.x/size.x), 1.0f) * width;
	int sampleOffsetZ = fmod(float(cameraPosition.z/size.z), 1.0f) * height;
	for (int y = 0;y < height; y++) {
		for (int x = 0; x < width; x++) {
			int idx = width * y + x ;
			int yc = y < height / 2 ? y : -height + y;
			int xc = x < width / 2 ? x : -width + x;
			ofVec2f vec_k = ofVec2f(2.0 * PI * xc / size.x, 2.0 * PI * yc / size.z);

			//float iwkt = disp(vec_k) * ofGetElapsedTimef();
            float iwkt = disp(vec_k) * waveSpeed * frameNum / 100.0;
			complex<float> coeffA = complex<float>(cos(iwkt), sin(iwkt));
			complex<float> coeffB = conj( coeffA );

			int ny = y > 0 ? height - y : 0;
			int nx = x > 0 ? width - x : 0;

            data[idx] = h0[idx] * coeffA + conj( h0[width * ny + nx] ) * coeffB;
			t_x[idx] = data[idx] * complex<float>(0.0, vec_k.x) - data[idx] * vec_k.y;

			// Choppy wave calcuations
			if (x + y > 0){
				data[idx] += data[idx] * vec_k.x / vec_k.length();
            }
		}
	}
	
    IFF2(data);
    IFF2(t_x);

	float scaleA = choppyScale / (heightDenom);
	float scaleB = -waveScale / (heightDenom);
	float scaleBinv = 1.0 / scaleB;

//    for (int i = 0; i < width*height; i++) {
	for (int y = 0;y < height; y++) {
		for (int x = 0; x < width; x++) {
			int i = width * y + x;
			int iw = i+i/width;
			
//			if( y == width/2 && x == width/2) cout << "normal " << i << " offset " << j << endl;
			
			vertices[iw] = baseVertices[iw] + centerOffset;
			vertices[iw].x += imag(data[i]) * scaleA;
			vertices[iw].y  = real(data[i]) * scaleB;

			//cout << "vertex is " << vertices[iw].x << " " << vertices[iw].y << " " << vertices[iw].z << endl;

			baseNormals[iw] = ofVec3f(real( t_x[i] ), scaleBinv, imag( t_x[i] )).normalized();

			if (!((i+1) % width)) {
				vertices[iw+1] = baseVertices[iw+1] + centerOffset;
				vertices[iw+1].x += imag(data[i+1-width]) * scaleA;
				vertices[iw+1].y  = real(data[i+1-width]) * scaleB;
				baseNormals[iw+1] = ofVec3f(real(t_x[i+1-width]), scaleBinv, imag( t_x[i+1-width])).normalized();
			}
		}
	}
	
	int offset = g_width*(g_height-1);
	for (int i = 0; i < g_width; i++){
		vertices[i+offset] = baseVertices[i+offset] + centerOffset;
		vertices[i+offset].x += imag( data[i%width] ) * scaleA;
		vertices[i+offset].y  = real( data[i%width] ) * scaleB;

		baseNormals[i+offset] = ofVec3f(real( t_x[i%width] ), scaleBinv, imag( t_x[i%width]) ).normalized();
    }

	if(currentWaveScale != waveScale){
		highestWave = lowestWave = vertices[0].y;
		currentWaveScale = waveScale;
	}
	
    //find wave range
    for (int i = 0; i < width*height; i++) {
	    if(vertices[i].y > highestWave){
            highestWave = vertices[i].y;
        }
        if(vertices[i].y < lowestWave){
            lowestWave = vertices[i].y;
        }
    }

    //cout << "highest wave is " << highestWave << " lowest wave is " << lowestWave << endl;

    for (int i = 0; i < g_width*g_height-1; i++) {

        //Need to preserve w in refraction/reflection mode
        if (((i+1) % g_width) == 0) {
            baseTangents[i] = (vertices[i-width+1] + ofVec3f(size.x, 0.0, 0.0) - vertices[i]).normalized();
        }
        else {
            baseTangents[i] = (vertices[i+1]-vertices[i]).normalized();
        }

        baseTangents[i].w = 1.0;
    }


    //FOAM: left out for now
    /*
    //In reflection mode, use tangent w for foam strength
    for (y = 0; y < g_height; y++)
    {
        for (x = 0; x < g_width; x++)
        {
            if (x+1 >= g_width)
            {
                tangents[x + g_width*y].w = tangents[g_width*y].w;

                continue;
            }

            if (y+1 >= g_height)
            {
                tangents[x + g_width*y].w = tangents[x].w;

                continue;
            }

            var right : Vector3 = vertices[(x+1) + g_width*y] - vertices[x + g_width*y];
            var back : Vector3 = vertices[x + g_width*y] - vertices[x + g_width*(y+1)];

            var foam : float = right.x/(size.x/g_width);


            if (foam < 0.0)
                tangents[x + g_width*y].w = 1;
            else if (foam < 0.5)
                tangents[x + g_width*y].w += 3.0 * Time.deltaTime;
            else
                tangents[x + g_width*y].w -= 0.4 * Time.deltaTime;

            tangents[x + g_width*y].w = Mathf.Clamp(tangents[x + g_width*y].w, 0.0, 2.0);
        }
		tangents[g_width*g_height-1] = (vertices[g_width*g_height-1]+Vector3(size.x, 0.0, 0.0)-vertices[1]).normalized;
	}
     */
}

float ofxOcean::getHighestWave()
{
    return highestWave;
}

float ofxOcean::getLowestWave()
{
	return lowestWave;
}

ofVec3f ofxOcean::floatingPosition(ofVec3f position, bool considerChoppy){
	return floatingPosition(position.x, position.z, considerChoppy);
}

ofVec3f ofxOcean::floatingPosition(float u, float v, bool considerChoppy)
{
    float xoffset = considerChoppy ? choppyOffset(u,v) : 0;
    return ofVec3f(u+xoffset, waterHeight(u, v), v);
}

float ofxOcean::waterHeight(float u, float v)
{
    float x,y;
    x = u / size.x;
    x = (x - floor(x)) * width;

    y = v / size.z;
    y = (y - floor(y)) * height;

    float fx, fy, cx, cy;
    fx = int(floor(x));
    fy = int(floor(y));
    cx = int(ceil(x))%width;
    cy = int(ceil(y))%height;

    float FFd = real( data[width * fy + fx] ) * waveScale / (heightDenom);
    float CFd = real( data[width * fy + cx] ) * waveScale / (heightDenom);
    float CCd = real( data[width * cy + cx] ) * waveScale / (heightDenom);
    float FCd = real( data[width * cy + fx] ) * waveScale / (heightDenom);

    //interp across x's
    float h1 = ofLerp(FFd, CFd, x - fx);
    float h2 = ofLerp(FCd, CCd, x - fx);

    //interp across y
    return -ofLerp(h1, h2, y - fy);
}

float ofxOcean::choppyOffset(float u, float v)
{
    float x,y;
    x = u / size.x;
    x = (x - floor(x)) * width;

    y = v / size.z;
    y = (y - floor(y)) * height;

    //do quad interp
    float fx = int(floor(x));
    float fy = int(floor(y));
    float cx = int(ceil(x))%width;
    float cy = int(ceil(y))%height;

    //find data points for all four points
    float FFd = imag( data[width * fy + fx] ) * choppyScale / (heightDenom);
    float CFd = imag( data[width * fy + cx] ) * choppyScale / (heightDenom);
    float CCd = imag( data[width * cy + cx] ) * choppyScale / (heightDenom);
    float FCd = imag( data[width * cy + fx] ) * choppyScale / (heightDenom);

    //interp across x's
    float h1 = ofLerp(FFd, CFd, x - fx);
    float h2 = ofLerp(FCd, CCd, x - fx);

    //interp across y
    return ofLerp(h1, h2, y - fy);
}

void ofxOcean::IFF2(vector< complex<float> >& data)
{
    //copy into buf
    for(int i = 0; i < width*height; i++){
        fftInputBuf[i].r = real( data[i] );
        fftInputBuf[i].i = imag( data[i] );
    }

    //transform
    kiss_fftnd(sti, fftInputBuf, fftOutputBuf);

    //copy out of buf
    for(int i = 0; i < width*height; i++){
        data[i] = complex<float>(fftOutputBuf[i].r,fftOutputBuf[i].i);
    }
}

ofVec2f* ofxOcean::getUVs()
{
	return baseUVs;
}

ofVec3f* ofxOcean::getVertices()
{
	return vertices;
}

ofVec3f* ofxOcean::getNormals()
{
    return baseNormals;
}

ofVec4f* ofxOcean::getTangents()
{
 	return baseTangents;
}
