/**
 * 
 * The MIT License
 * 
 * Copyright (c) 2010 james george http://www.jamesgeorge.org
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * ofxSlitScan.h
 *
 * ofxSlitScan is a simple utility for creating slit scan
 * effects and video time delays. It works by keeping a 
 * rolling buffer of video frames that can be sampled
 * from arbitrarly via a warp map 
 *
 * For inspiring works using this effect, check out Golen Leven's page
 * on Slit Scan artworks
 *
 * http://www.flong.com/texts/lists/slit_scan/
 *
 *
 * Usage:
 *
 * First call set up with the width and height that matches the video you want to process
 * after calling setup, use any image to set the delay map 
 * then with every incoming frame call addImage();
 * Calling getOutputImage will return a reference to the warped / delayed video frame
 */

#ifndef _OFX_SLITSCAN
#define _OFX_SLITSCAN

#import "ofMain.h"

class ofxSlitScan
{
  public:
	ofxSlitScan();
	
	/**
	 * Width / Height of input stream
	 * capcity sets the maximum number of frames to
	 * be held. 
	 * type is  OF_IMAGE_GRAYSCALE, OF_IMAGE_COLOR, or OF_IMAGE_COLOR_ALPHA
	 * default type is OF_IMAGE_COLOR
	 */
	void setup(int w, int h, int capacity);
	void setup(int w, int h, int capacity, int type);

	bool isSetup();

	/**
	 * set the map used to distort the frame buffer.
	 * the Map is a grayscale image the same dimensions
	 * as the input stream. 
	 * White pixels map to the newest frames and black the oldest,
	 * gray in between.
	 */
	void setDelayMap(ofImage map);
	void setDelayMap(unsigned char* map, int type);
	void setDelayMap(float* map);
	
	/**
	 * add an image to the input system
	 * call this in succession, once per frame, when reading
	 * an input movie or video stream
	 */
	void addImage(ofImage image);
	void addImage(unsigned char* image);

	/**
	 * returns the results of the
	 * distortion
	 */
	ofImage* getOutputImage();
	
	/**
	 * gives you the output image back as an ofImage
	 */
	ofImage* getDelayMap();
	
	/**
	 * fills outbuf with the undistorted pixels 
	 * for frame "num".
	 */
	void pixelsForFrame(int num, unsigned char* outbuf);
	
	/**
	 * reset the maxmum delay. Call this sparingly
	 * as it incurs memory allocation
	 */
	void setCapacity(int capacity); 
	
	/**
	 * Allows clamping of the delay amount and width of the delay within the capacity
	 * timeDelay + timeWidth must be less than the total capacity.
	 * these values can be scrubbed in real time for glitch and speed ramp effects
	 */
	void setTimeDelayAndWidth(int timeDelay, int timeWidth); 
	void setTimeDelay(int timeDelay);
	void setTimeWidth(int timeWidth);
	
	/**
	 * turn on to smooth inter-frame differences
	 */
	void setBlending(bool blend);
	void toggleBlending();
	
	int getTimeDelay();
	int getTimeWidth();
	int getWidth();
	int getHeight();
	int getCapacity();
	int getType();
	bool isBlending();
	
  protected:
	unsigned char ** buffer;
	float * delayMapPixels;
	bool blend;

	bool outputIsDirty;
	ofImage outputImage;
	
	bool delayMapIsDirty;
	ofImage delayMapImage;
	
	int timeWidth, timeDelay, framepointer, capacity;
	int width, height;
	int type;
	
	int bytesPerPixel;	
	int bytesPerFrame;
	bool buffersAllocated;
};

#endif