#ifndef 	_OPENNITRACKING_H
#define 	_OPENNITRACKING_H

////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"

// imageAnalysis
#include "ofxCvOpticalFlowLK.h"     // cvOpticalFlowLK wrapper for OF [from Takashi Maekawa]
#include "ofContourAnalysis.h"		// contour geometry analysis [from Chris Sugrue]
#include "contourSimplify.h"		// contour simplify [from Theodore Watson]
#include "matrixAreas.h"			// sub matrix areas for indipendent areas tracking [from Emanuele Mazza]

// extends ofxCvBlob functions
#include "ofxCvBlobTracker.h"		
#include "ofxCvTrackedBlob.h"
#include "ofxCvConstants_Track.h"

// constants
#include "gamuzaConstants.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////

class openniTracking: public ofBaseApp, public ofxCvBlobListener{

	public:
			openniTracking();
            ~openniTracking();
	
			void				setupDevice(int _w, int _h,bool _ir,int _ledState);
			void				updateDevice();
			void				drawDevice();
	
			void mouseDragged(int x, int y, int button);
			void mousePressed(int x, int y, int button);
			void mouseReleased(int x, int y, int button);
			
			void updateOpenCV();
			void calculateMotion();
			void computeContourAnalysis();										// compute contour analysis
			void drawContourAnalysis();											// draw contour analysis
	
			// advanced blob tracking functions
			void blobOn( int x, int y, int id, int order );
			void blobMoved( int x, int y, int id, int order );
			void blobOff( int x, int y, int id, int order );
			
			float averageBnWVal(IplImage * img);
	
			// optical flow utils function
			void getVelAtPixel(int x, int y, float *u, float *v);               // get optical_flow pixel velocity
			void getVelAtNorm(float x, float y, float *u, float *v);            // get optical_flow normal velocity
			
			// utils functions
			void smoothingValues();												// smoothing numerical data
			void normalizeValues();												// normalize numerical data
			
			//////////////////////////////////////////
			// openni sensor kinect vars
			bool				useKinect;
			bool				useIR;
			
			
    
            ofTexture			camTexture;
	
			int					nearThreshold, farThreshold;
			
			ofImage				allUserMasks, depthRangeMask, depthRangeMaskScaled;
			
			float				filterFactor;
	
			bool				isTrackingHands;
			int					maxHands;
			
			
			ofPoint				sensor_accelerometer;
			int					sensor_tilt;
			int					ledState;
	
			ofPoint				_osc_sensorAcc;
			float				_osc_sensorTilt;
			
            bool                isOniConnected;
			//////////////////////////////////////////
			
			//////////////////////////////////////////
			// opencv tracking vars
			int						_width, _height;
			ofxCvGrayscaleImage		cleanImage;
			int						ciBlur;
			int						ciErode;
			int						ciDilate;
	
			// motion detection
			ofxCvGrayscaleImage 	grayPrev;
			ofxCvGrayscaleImage 	grayNow;
			ofxCvGrayscaleImage 	motionImg;
			int						frameCounter;
			int						numPixelsChanged; // motion quantity
			int						mThreshold;
	
			// contour finder
			ofxCvContourFinder		contourFinder;
			contourSimplify			contourS;
			vector<ofVec2f>			*contourReg;
			vector<ofVec2f>			*contourSmooth;
			vector<ofVec2f>			*contourSimple;
			vector<ofVec4f>			*geomLines;	// geometry lines find into countour
			CvBox2D32f				*box;
			float					*blobAngle;
			float					smoothPct;
			float					tolerance;
			int						runningBlobs;
			int						minBlobArea;
			int						maxBlobArea;
			int						cfDetail;
			
			// advanced blob tracking
			ofxCvBlobTracker		blobTracker;
			int						*blobsOrder;
			char					selectCornerMsg[100];
			cornerSelectStates		csState;
			int						topLeftX;
			int						topLeftY;
			int						lowRightX;
			int						lowRightY;
			int						userOffsetX;
			int						userOffsetY;
			int						maxUsers;
			int						usersTracking[MAX_USERS_HARDLIMIT];
			int						currAdjustment;
			
			float					mood;
			float					moodSpike;
			int						currNonMoodFrame;
			int						nonMoodFrames;
	
			// optical flow analysis
			ofxCvOpticalFlowLK		opticalFlow;
			int						opticalFlowXGrid;
			int						opticalFlowYGrid;
	
			// matrix areas for motion trigger
			matrixAreas				triggerAreas;
			bool					*triggerState;
			int						lastAreaON;
			int						actualArea;
			int						offHorizon, onHorizon;
			int						lastTime;
			int						silencePeriod;
	
			// generic vars
			ofMutex					cv_mutex;
			bool					saveAllSettings;
	
			// kalman weighted average vars
			bool					useKalmanFilter;
			
			CvBox2D32f				*_kalman_blobInfo;								// kalman filtered blobs info
			
			// smoothed vars
			float					_smoothingFactor;								// smoothing factor
			CvBox2D32f				*_s_blobInfo;									// smoothed blobs info
			vector<ofVec4f>			*_s_blobGeom;									// smoothed blobs geometry
			vector<ofVec2f>			*_s_contourSmooth;								// smoothed smooth contour points
			vector<ofVec2f>			*_s_contourSimple;								// smoothed simple contour points (redux)
			ofVec4f					*_s_opfVel;										// smoothed optical flow pixel velocity
			
			// OSC sending vars
			CvBox2D32f				*_osc_blobInfo;									// normalized blobs info
			vector<ofVec4f>			*_osc_blobGeom;									// normalized blobs geometry
			vector<ofVec2f>			*_osc_contourSmooth;							// normalized smooth contour points
			vector<ofVec2f>			*_osc_contourSimple;							// normalized simple contour points (redux)
			ofVec4f					*_osc_opfVel;									// normalized optical flow pixel velocity
			ofPoint					*_osc_hands_Pos;								// normalized hand tracking
	
			bool					computeContourFinder;
			bool					computeContourGeometry;
			bool					computeOpticalFlow;
			bool					computeTriggerAreas;
			
			// OSC flags
			bool					sendOsc_BD;										// send blob detection flag
			bool					sendOsc_CF;										// send contour fineder flag
			bool					sendOsc_CG;										// send contour geometry flag
			bool					sendOsc_OF;										// send optical flow flag
			bool					sendOsc_TA;										// send trigger areas flag
			bool					sendOsc_HT;										// send sensor kinect hand tracking flag
			bool					sendOsc_HW;										// send sensor kinect hardware flag
			//////////////////////////////////////////
			
			
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
