#pragma once

#include "ofMain.h"
#include <ar.h>

// Scale value for the border
// Based on the type of marker
#define BORDER_SCALE 1.25



class ofxARToolkitPlus  {

	public:	

	ofxARToolkitPlus();
	~ofxARToolkitPlus();
	
	///////////////////////////////////////////
	// SETUP
	///////////////////////////////////////////
	/* Setup ARToolKitPlus with the width and height of the image */ 
	void setup(int w, int h);
	/* Setup ARToolKitPlus with the width and height of the image
	 * as well as the camera parameter file and the multi-marker config file 
	 * The camera file can be created using GML and the instructions in the pdf below
	 * http://graphics.cs.msu.ru/en/science/research/calibration/cpp
	 * http://studierstube.icg.tu-graz.ac.at/doc/pdf/Stb_CamCal.pdf 
	 *
	 * You setup a custom initialziation to the tracker.
     * These parameters control the way the toolkit warps a found
     * marker to a perfect square. The square has size
     * pattWidth * pattHeight, the projected
     * square in the image is subsampled at a min of
     * pattWidth/pattHeight and a max of pattSamples
     * steps in both x and y direction
     *  @param maxImagePatterns describes the maximum number of patterns that can be analyzed in a camera image.
     *  @param pattWidth describes the pattern image width (must be 6 for binary markers)
     *  @param pattHeight describes the pattern image height (must be 6 for binary markers)
     *  @param pattSamples describes the maximum resolution at which a pattern is sampled from the camera image
     *  (6 by default, must a a multiple of pattWidth and pattHeight).
     *  @param maxLoadPatterns describes the maximum number of pattern files that can be loaded.
     *  Reduce maxLoadPatterns and maxImagePatterns to reduce memory footprint.
     */
	void setup(int w, int h, string camParamFile, string multiFile, int maxImagePatterns = 8, int pattWidth = 6, int pattHeight = 6, int pattSamples = 6, int maxLoadPatterns = 0);

	
	///////////////////////////////////////////
	// UPDATE
	///////////////////////////////////////////
	/* Find the marker and get back the confidence */
	int update(unsigned char *pixels);
    int update(ofTexture &tex);
	
	///////////////////////////////////////////
	// DRAW
	///////////////////////////////////////////
	/* Draw the marker center, outline, and id at the origin */
	void draw();
	/* Draw the marker center, outline, and id at the given position */
	void draw(int x, int y);
	/* Draw the marker center, outline, and id at the given position with the given size */
	void draw(int x, int y, int width, int height);
	
	///////////////////////////////////////////
	// 3D GEOMETRY
	///////////////////////////////////////////
	/* This is where we set the calculated matrix from ARToolkitPlus. 
	 * Call this once followed by the model matrix */
	void applyProjectionMatrix();
	void applyProjectionMatrix(int viewportWidth, int viewportHeight);
	/* Call this to then draw graphics at the location and orientation of the given marker.
	 * The matrix has the 0,0 point as the center of the marker. */
	void applyModelMatrix(int markerIndex);
	
	/* Get the ARTK model matrix for the given marker */ 
	ofMatrix4x4 getMatrix(int markerIndex);
	/* Get the ARTK model matrix (in OpenGL order) for the given marker */ 	
	ofMatrix4x4 getGLMatrix(int markerIndex);
	
	/* Get the homography matrix for the given marker based on the marker size */ 
	ofMatrix4x4 getHomography(int markerIndex);
	/* Get the homography matrix for the given marker based on four src corner points */ 
	ofMatrix4x4 getHomography(int markerIndex, vector<ofPoint> &src);

	/* Get the translation of the camera relative to the marker */
	ofVec3f getTranslation(int markerIndex);
	/* Get the orientation matrix without translation */
	ofMatrix4x4 getOrientationMatrix(int markerIndex);
	/* Get the orientation as a quaternion without translation */	
	ofQuaternion getOrientationQuaternion(int markerIndex);
	/* Load the translation and orientation into the given variables */
	void getTranslationAndOrientation(int markerIndex, ofVec3f &translation, ofMatrix4x4 &orientation);
	
	/* Get the camera position relative to the marker 
	 * Z Axis faces upwards from the marker */
	ofVec3f getCameraPosition(int markerIndex);
	
	///////////////////////////////////////////
	// MULTI MARKER
	///////////////////////////////////////////
	/* Get the translation of the multi-marker 
	 * Details on how to create and load a mult-marker file:
	 * http://www.hitl.washington.edu/artoolkit/documentation/tutorialmulti.htm */
	void getMultiMarkerTranslationAndOrientation(ofVec3f &translation, ofMatrix4x4 &orientation);
	/* Load a different multi-marker config file - returns true if it loaded (untested) */
	bool loadMultiMarkerFile(string filename);
	
	///////////////////////////////////////////
	// SETTINGS
	///////////////////////////////////////////
	/* Set the threshold manually */
	void setThreshold(int threshold);
	/* Enables or disables automatic threshold calculation */
	void activateAutoThreshold(bool state);
	/* Set the width of the markers to calculate an accurate matrix in real world scale */
	void setMarkerWidth(float mm);

	///////////////////////////////////////////
	// MARKER INFO
	///////////////////////////////////////////
	/* Return the number of detected markers */
	int getNumDetectedMarkers();
	/* Get the index of the marker if found, else return -1 */
	int getMarkerIndex(int markerID);
	/* Get the marker ID of the given index - returns -1 if out of range */	
	int getMarkerID(int markerIndex);
	
	///////////////////////////////////////////
	// 2D GEOMETRY
	///////////////////////////////////////////
	/* Return the center of the detected marker in screen coordinates */
	ofPoint getDetectedMarkerCenter(int markerIndex);
	/* 	Return the direction that tells about the rotation about the marker (possible values are 0, 1, 2 or 3). 
	 *  This parameter makes it possible to tell about the line order of the detected marker 
	 *  (so which line is the first one) and so find the first vertex. */
	int getDetectedMarkerDirection(int markerIndex);
	/* Adds the four corners of the detected marker in screen coordinates to the passed in vector */
	void getDetectedMarkerCorners(int markerIndex, vector<ofPoint> &corners);
    void getDetectedMarkerCorners(int markerIndex);
	/* Adds the four corners of the detected marker in screen coordinates to the passed in vector.
	 * The corners are ordered consistantly, starting in the top left and going around in a clockwise direction. */
	void getDetectedMarkerOrderedCorners(int markerIndex, vector<ofPoint> &corners);
    void getDetectedMarkerOrderedCorners(int markerIndex);
	/* Adds the four corners of the detected marker border in screen coordinates to the passed in vector */
	void getDetectedMarkerBorderCorners(int markerIndex, vector<ofPoint> &corners);
    void getDetectedMarkerBorderCorners(int markerIndex);
	/* Adds the four corners of the detected marker border in screen coordinates to the passed in vector.
	 * The corners are ordered consistantly, starting in the top left and going around in a clockwise direction. */
	void getDetectedMarkerOrderedBorderCorners(int markerIndex, vector<ofPoint> &corners);
    void getDetectedMarkerOrderedBorderCorners(int markerIndex);
    
    ofPoint getCornerPoint(int index);
    ofPoint getOrderedCornerPoint(int index);
    ofPoint getBorderCornerPoint(int index);
    ofPoint getOrderedBorderCornerPoint(int index);
    
    ofPixels temp_pix;
    vector<ofPoint> mCorners;
    vector<ofPoint> orderedCorners;
    vector<ofPoint> borderCorners;
    vector<ofPoint> orderedBorderCorners;

protected:
	
	/*
	 * Homography Functions adapted from:
	 * http://www.openframeworks.cc/forum/viewtopic.php?p=22611
	 * Author: arturo castro
	 */
	void gaussian_elimination(float *input, int n){
		// ported to c from pseudocode in
		// http://en.wikipedia.org/wiki/Gaussian_elimination
		
		float * A = input;
		int i = 0;
		int j = 0;
		int m = n-1;
		while (i < m && j < n){
			// Find pivot in column j, starting in row i:
			int maxi = i;
			for(int k = i+1; k<m; k++){
				if(fabs(A[k*n+j]) > fabs(A[maxi*n+j])){
					maxi = k;
				}
			}
			if (A[maxi*n+j] != 0){
				//swap rows i and maxi, but do not change the value of i
				if(i!=maxi)
					for(int k=0;k<n;k++){
						float aux = A[i*n+k];
						A[i*n+k]=A[maxi*n+k];
						A[maxi*n+k]=aux;
					}
				//Now A[i,j] will contain the old value of A[maxi,j].
				//divide each entry in row i by A[i,j]
				float A_ij=A[i*n+j];
				for(int k=0;k<n;k++){
					A[i*n+k]/=A_ij;
				}
				//Now A[i,j] will have the value 1.
				for(int u = i+1; u< m; u++){
					//subtract A[u,j] * row i from row u
					float A_uj = A[u*n+j];
					for(int k=0;k<n;k++){
						A[u*n+k]-=A_uj*A[i*n+k];
					}
					//Now A[u,j] will be 0, since A[u,j] - A[i,j] * A[u,j] = A[u,j] - 1 * A[u,j] = 0.
				}
				
				i++;
			}
			j++;
		}
		
		//back substitution
		for(int i=m-2;i>=0;i--){
			for(int j=i+1;j<n-1;j++){
				A[i*n+m]-=A[i*n+j]*A[j*n+m];
				//A[i*n+j]=0;
			}
		}
	}

	void findHomography(vector<ofPoint> src, vector<ofPoint> dst, float homography[16]){
		
		// create the equation system to be solved
		//
		// from: Multiple View Geometry in Computer Vision 2ed
		//       Hartley R. and Zisserman A.
		//
		// x' = xH
		// where H is the homography: a 3 by 3 matrix
		// that transformed to inhomogeneous coordinates for each point
		// gives the following equations for each point:
		//
		// x' * (h31*x + h32*y + h33) = h11*x + h12*y + h13
		// y' * (h31*x + h32*y + h33) = h21*x + h22*y + h23
		//
		// as the homography is scale independent we can let h33 be 1 (indeed any of the terms)
		// so for 4 points we have 8 equations for 8 terms to solve: h11 - h32
		// after ordering the terms it gives the following matrix
		// that can be solved with gaussian elimination:
		
		float P[8][9]={
			{-src[0].x, -src[0].y, -1,   0,   0,  0, src[0].x*dst[0].x, src[0].y*dst[0].x, -dst[0].x }, // h11
			{  0,   0,  0, -src[0].x, -src[0].y, -1, src[0].x*dst[0].y, src[0].y*dst[0].y, -dst[0].y }, // h12
			
			{-src[1].x, -src[1].y, -1,   0,   0,  0, src[1].x*dst[1].x, src[1].y*dst[1].x, -dst[1].x }, // h13
			{  0,   0,  0, -src[1].x, -src[1].y, -1, src[1].x*dst[1].y, src[1].y*dst[1].y, -dst[1].y }, // h21
			
			{-src[2].x, -src[2].y, -1,   0,   0,  0, src[2].x*dst[2].x, src[2].y*dst[2].x, -dst[2].x }, // h22
			{  0,   0,  0, -src[2].x, -src[2].y, -1, src[2].x*dst[2].y, src[2].y*dst[2].y, -dst[2].y }, // h23
			
			{-src[3].x, -src[3].y, -1,   0,   0,  0, src[3].x*dst[3].x, src[3].y*dst[3].x, -dst[3].x }, // h31
			{  0,   0,  0, -src[3].x, -src[3].y, -1, src[3].x*dst[3].y, src[3].y*dst[3].y, -dst[3].y }, // h32
		};
		
		gaussian_elimination(&P[0][0],9);
		
		// gaussian elimination gives the results of the equation system
		// in the last column of the original matrix.
		// opengl needs the transposed 4x4 matrix:
		float aux_H[]={ P[0][8],P[3][8],0,P[6][8],	// h11  h21 0 h31
						P[1][8],P[4][8],0,P[7][8],	// h12  h22 0 h32
						0      ,      0,0,0,		// 0    0   0 0
						P[2][8],P[5][8],0,1};		// h13  h23 0 h33
		
		for(int i=0;i<16;i++) homography[i] = aux_H[i];
	}

	ofMatrix4x4 findHomography(vector<ofPoint> src, vector<ofPoint> dst){
		float homography[16];
		findHomography(src, dst, homography);
		return ofMatrix4x4(homography);
	}

	/* Get the transpose matrix, first trying RPP then with standard functions if necessary */
	void getTransMat(ARToolKitPlus::ARMarkerInfo *marker_info, float center[2], float conv[3][4]);
	
	int width, height;
	bool useBCH;
	/* Width of the markers in mm (used to calculate matrix homography) */
	float markerWidth;
	float halfMarkerWidth;
	/* Corners of the marker we use to calculate the homography */
	vector<ofPoint> homoSrc;
	/* Setup the homography source */
	void setupHomoSrc();
	
	/* Matrix storage */
	float m34[ 3 ][ 4 ];
	float c[ 2 ];
	float m[ 16 ]; 
	
	/* If a multi-marker config file has been loaded after initialization */
	bool multiMarkerLoaded;
	
};

