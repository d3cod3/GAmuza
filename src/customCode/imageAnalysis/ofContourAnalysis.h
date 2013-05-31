#ifndef 	_OF_CONTOUR_ANALYSIS_H
#define 	_OF_CONTOUR_ANALYSIS_H

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <vector>


//-----------------------------
// returns angle of major axis in RADIANS
float getOrientation( vector <ofPoint>  & contour );

//-----------------------------
// opencv ellipse fitting
void fitEllipse( vector <ofPoint>  & contour, CvBox2D32f & box );

//-----------------------------
// returns the index of the blob the pt lies inside of. returns -1 if it is not inside any blob
int getIndexOfBlobIAmIn( vector<ofxCvBlob> & blobs, ofPoint pt);

//-----------------------------
// checks if point is inside contour
bool isPointInsideMe(float x, float y, vector <ofPoint>  & contour);

//-----------------------------
// code adapted from zach lieberman's finger tracking genius in opensourcery project
// searches for lines on contour
// note that this walks along the contour backwards because it only works in counter clockwise direction
// also it doesn't seem to work with convexity

// pts: vector of contour pts
// lines: reference to a vector of 4d points. The start and endpoints of the found lines are stored here
// angleThreshold: if change in theta is greater than this amount, consider it a new line
// minLen: minimum length a line can be (so can disregard short segments)
// res: number of points to skip while walking along the contour.

void findLines(vector <ofPoint>  & pts, vector<ofVec4f> & lines, float angleThreshold, float minLen, int res = 30);


//--------------------------------------------------------------------------------
// draw an individual blob ( contour only )
void drawBlob( float x, float y, ofxCvBlob & blob );


#endif
