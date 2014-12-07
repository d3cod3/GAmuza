/* 
	ofxLibdc is an Open Frameworks wrapper for libdc1394 that makes it easy to grab images from libdc1394-compatible cameras.
	
	For more information, see the readme.
*/

// ofxLibdc::Camera is the most efficient interface to libdc1394
#include "Camera.h"

// ofxLibdc::Grabber is modeled after ofBaseVideo, so it acts like ofVideoGrabber
#include "Grabber.h"

// ofxLibdc::PointGrey extends Grabber and has some Point Grey-specific functionality
#include "PointGrey.h"