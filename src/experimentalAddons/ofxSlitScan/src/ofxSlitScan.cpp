/*
 *  ofxSlitScan.cpp
 *  openFrameworks
 *
 *  Created by James George on 12/7/09.
 *  Copyright 2009 http://jamesgeorge.org. All rights reserved.
 *
 */

#include "ofxSlitScan.h"

//converts from an index (0, capacity) to the appropriate fraem in the rolling buffer
static inline int frame_index(int framepointer, int index, int capacity)
{ return (framepointer + index) % capacity; }

ofxSlitScan::ofxSlitScan()
{
	buffersAllocated = false;
}

void ofxSlitScan::setup(int w, int h, int _capacity)
{
	setup(w,h,_capacity, OF_IMAGE_COLOR);
}

void ofxSlitScan::setup(int w, int h, int _capacity, int _type)
{
	type = _type;
	switch (type) {
		case OF_IMAGE_GRAYSCALE:{
			bytesPerPixel = 1;
		}break;
		case OF_IMAGE_COLOR:{
			bytesPerPixel = 3;
		}break;
		case OF_IMAGE_COLOR_ALPHA:{
			bytesPerPixel = 4;
		}break;
		default:{
			ofLog(OF_LOG_ERROR, "ofxSlitScan Error -- Invalid image type");
			return;
		}break;
	}
	
	//clean up if reallocating
	if(buffersAllocated){
		free(delayMapPixels);
		for(int i = 0; i < capacity; i++){
			free(buffer[i]);
		}
		free(buffer);
		buffersAllocated = false;
	}
	
	width = w;
	height = h;
	capacity = _capacity;
	framepointer = 0;
	blend = false;
	timeDelay = 0;
	timeWidth = capacity;
	bytesPerFrame = width*height*bytesPerPixel;
	delayMapPixels = (float*)calloc(w*h, sizeof(float));
	buffer = (unsigned char**)calloc(capacity, sizeof(unsigned char*));
	for(int i = 0; i < capacity; i++){
		buffer[i] = (unsigned char*)calloc(bytesPerFrame, sizeof(unsigned char));
	}
	outputImage.allocate(w, h, (ofImageType)type);
	delayMapImage.allocate(w, h, OF_IMAGE_GRAYSCALE);
	buffersAllocated = true;
	outputIsDirty = true;
	delayMapIsDirty = true;
}

bool ofxSlitScan::isSetup()
{
	return buffersAllocated;
}

void ofxSlitScan::setCapacity(int _capacity)
{
	if(_capacity <= 0){
		_capacity = 1;
	}
	
	if(_capacity == capacity){
		return;
	}
	
	//the new capacity is bigger
	if (capacity < _capacity) {
		buffer = (unsigned char**)realloc(buffer, _capacity*sizeof(unsigned char*));
		for(int i = capacity; i < _capacity; i++){
			buffer[i] = (unsigned char*)calloc(bytesPerFrame, sizeof(unsigned char));
		}
	}
	//the new capacity is smaller
	else {
		for( int i = _capacity; i < capacity; i++){
			free(buffer[i]);
		}
		buffer = (unsigned char**)realloc(buffer, _capacity*sizeof(unsigned char*));
		framepointer %= _capacity;
	}
	capacity = _capacity;
	outputIsDirty = true;
}

void ofxSlitScan::setDelayMap(unsigned char* pix, int type)
{
	switch (type) {
		case OF_IMAGE_COLOR:{
			for(int i = 0; i < width*height; i++){
				//RGB 0 - 255 ==> YUV 0.0 - 1.0
				delayMapPixels[i] = (0.299*pix[i*3] + 0.587*pix[i*3+1] + 0.114*pix[i*3+2]) / 255.0; 
			}				
		}break;
			
		case OF_IMAGE_COLOR_ALPHA:{
			for(int i = 0; i < width*height; i++){
				//RGBA 0 - 255 ==> YUV 0.0 - 1.0
				delayMapPixels[i] = (0.299*pix[i*4] + 0.587*pix[i*4+1] + 0.114*pix[i*4+2]) / 255.0;
			}				
		}break;
			
		case OF_IMAGE_GRAYSCALE:{
			for(int i = 0; i < width*height; i++){
				delayMapPixels[i] = pix[i] / 255.0;
			}	
		}break;
			
		default:{
			ofLog(OF_LOG_ERROR, "ofxSlitScan -- unsupported image map type");
		}break;
	}
	
	delayMapIsDirty = true;
	outputIsDirty = true; 
}

void ofxSlitScan::setDelayMap(float* mappix)
{
	//assumed monochrome float image
	for(int i = 0; i < width*height; i++){
		delayMapPixels[i] = mappix[i];
	}
	delayMapIsDirty = true;
	outputIsDirty = true; 
}

void ofxSlitScan::setDelayMap(ofImage map)
{
	if(map.getWidth() != width || map.getHeight() != height){
		ofLog(OF_LOG_ERROR, "ofxSlitScan Error -- Map dimensions do not match image dimensions. given %fx%f, need %dx%d\n", map.getWidth(), map.getHeight(), width, height);
		return;
	}
	setDelayMap(map.getPixels(), map.type);
}

void ofxSlitScan::setBlending(bool _blend)
{
	blend = _blend;
	outputIsDirty = true;
}

void ofxSlitScan::toggleBlending()
{
	blend = !blend;
	outputIsDirty = true;
}

void ofxSlitScan::addImage(unsigned char* image)
{
	
	//write the image into the buffer
	memcpy(buffer[framepointer], image, bytesPerFrame*sizeof(unsigned char));
	
	//increment the framepointer
	framepointer = ( (framepointer + 1) % capacity );	
	
	outputIsDirty = true;	
}

void ofxSlitScan::addImage(ofImage image)
{
	if(image.type != type){
		ofLog(OF_LOG_ERROR, "ofxSlitScan -- adding image of the wrong type");
		return;
	}
	addImage( image.getPixels() );
}

ofImage* ofxSlitScan::getOutputImage()
{
	if(outputIsDirty){
		//calculate the new distorted image
		unsigned char* writebuffer = outputImage.getPixels();
		unsigned char* outbuffer = writebuffer;
		
		int x, y, offset, lower_offset, upper_offset, pixelIndex;
		float precise, alpha, invalpha;	
		int mapMin = capacity - timeDelay - timeWidth;// (time_delay + time_width);
		int mapMax = capacity - 1 - timeDelay;// - time_delay;
		int bytesPerRow = width*bytesPerPixel;
		
		if(blend){
			for(y = 0; y < height; y++){
				for(x = 0; x < width; x++){		
					//find pixel point in local reference
					pixelIndex = bytesPerRow*y + x*bytesPerPixel;
					precise = ofMap(delayMapPixels[width*y+x], 0.0, 1.0, mapMin, mapMax, false);
					//cast it to an integer
					offset = int(precise);
					
					//calculate alpha
					alpha = precise - offset;
					invalpha = 1 - alpha;
					
					//convert to framepointer reference point
					lower_offset = frame_index(framepointer, offset, capacity);
					upper_offset = frame_index(framepointer, offset+1, capacity);
					
					//get buffers
					unsigned char *a = buffer[lower_offset] + pixelIndex;
					unsigned char *b = buffer[upper_offset] + pixelIndex;
					
					//interpolate and set values;
					for(int c = 0; c < bytesPerPixel; c++){
						*outbuffer++ = (a[c]*invalpha)+(b[c]*alpha);
					}
				}
			}
		}
		else{
			for(y = 0; y < height; y++){
				for(x = 0; x < width; x++){
					pixelIndex = bytesPerRow*y + x*bytesPerPixel;
					offset = frame_index(framepointer, ofMap(delayMapPixels[width*y+x], 0.0, 1.0, mapMin, mapMax), capacity);
					memcpy(outbuffer, buffer[offset]+pixelIndex, bytesPerPixel);	
					outbuffer += bytesPerPixel;
				}
			}
		}
		outputImage.setFromPixels(writebuffer, width, height, (ofImageType)type);
		outputIsDirty = false;
	}

	return &outputImage;
}

ofImage* ofxSlitScan::getDelayMap()
{
	if(delayMapIsDirty){
		unsigned char* pix = delayMapImage.getPixels();
		for(int i = 0; i < width*height; i++){
			pix[i] = char(delayMapPixels[i]*255);
		}
		delayMapImage.setFromPixels(pix, width, height, OF_IMAGE_GRAYSCALE);
		delayMapIsDirty = false;
	}
	return &delayMapImage;
}

int ofxSlitScan::getWidth()
{
	return width;
}

int ofxSlitScan::getHeight()
{
	return height;
}

void ofxSlitScan::pixelsForFrame(int num, unsigned char* outbuf)
{
	memcpy(outbuf, buffer[frame_index(framepointer, num, capacity)], bytesPerFrame*sizeof(unsigned char));
}

void ofxSlitScan::setTimeDelayAndWidth(int _timeDelay, int _timeWidth)
{
	timeDelay = ofClamp(_timeDelay, 0, capacity-1);
	timeWidth = ofClamp(_timeWidth, 1, capacity);
	if(timeDelay + timeWidth > capacity){
		ofLog(OF_LOG_ERROR, "ofxSlitScan -- Invalid time delay and width specified, adds to %d with a capacity of %d", (timeDelay+timeWidth), capacity);
		timeDelay = 0;
		timeWidth = capacity;
	}
	outputIsDirty = true;	
}

void ofxSlitScan::setTimeDelay(int _timeDelay)
{
	timeDelay = ofClamp(_timeDelay, 0, capacity - timeWidth - 1);
	outputIsDirty = true;
}

void ofxSlitScan::setTimeWidth(int _timeWidth)
{
	timeWidth = ofClamp(_timeWidth, 1, capacity - timeDelay);
	outputIsDirty = true;
}

int ofxSlitScan::getCapacity()
{
	return capacity;
}

int ofxSlitScan::getTimeDelay()
{
	return timeDelay;
}

int ofxSlitScan::getTimeWidth()
{
	return timeWidth;
}

int ofxSlitScan::getType()
{
	return type;
}

bool ofxSlitScan::isBlending()
{	
	return blend;
}

