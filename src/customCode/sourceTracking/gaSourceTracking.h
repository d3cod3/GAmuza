#ifndef 	_GASOURCETRACKING_H
#define 	_GASOURCETRACKING_H

////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxControlPanel.h"

// imageAnalysis
#include "ofxCvOpticalFlowLK.h"     // cvOpticalFlowLK wrapper for OF [from Takashi Maekawa]
#include "ofxCvHaarFinder.h"		// openCV haar finder [by Charlie, Stefanix & Kyle Mcdonald + Theo Watson]
#include "ofContourAnalysis.h"		// contour geometry analysis [from Chris Sugrue]
#include "contourSimplify.h"		// contour simplify [from Theodore Watson]
#include "matrixAreas.h"			// sub matrix areas for indipendent trigger areas [from Emanuele Mazza]

// extends ofxCvBlob functions
#include "ofxCvBlobTracker.h"		
#include "ofxCvTrackedBlob.h"
#include "ofxCvConstants_Track.h"

// constants
#include "gamuzaConstants.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////

class gaSourceTracking: public ofBaseApp, public ofxCvBlobListener{

	public:
			gaSourceTracking();
            ~gaSourceTracking();
            
			void setupCam(int __id, int _w, int _h, int deviceID, bool player = false, string haarFile = GAMUZA_HAAR_DEFAULT, string movie = GAMUZA_VIDEOTEST);
    
            void setHaarFile(string hF);
            void setMovieFile(string mF);
            void switchCamMovie();
            void setup(int deviceID, int _w, int _h);
    
			void update();
			void draw();
			void mouseDragged(int x, int y);
			void mousePressed(int x, int y);
			void mouseReleased(int x, int y);
	
			void loadCalibration();
			void getQuadSubImage(unsigned char* inputData,unsigned char* outputData,int inW,int inH,int outW,int outH,ofPoint *quad,int bpp);
			
			void calculateColorDifference();									// background subtraction using rgb image
			void calculateGrayscaleDifference();								// background subtraction using grayscale image
			void calculateColorDifferenceHSV();									// tracking color difference over time using HSV color information
			void balanceTracking();												// filter information from the two different algorithms
			void calculateMotion();												// motion detection
			void computeContourAnalysis();										// compute contour analysis
			void drawMotionCentroid();											// draw basic motion detection centroid
			void drawContourAnalysis();											// draw contour analysis
			void drawHaarFinder();
	
			// advanced blob tracking functions
			void blobOn( int x, int y, int id, int order );
			void blobMoved( int x, int y, int id, int order );
			void blobOff( int x, int y, int id, int order );
	
			float averageBnWVal(IplImage * img);
	
			// optical flow utils function
			void getVelAtPixel(int x, int y, float *u, float *v);               // get optical_flow pixel velocity
			void getVelAtNorm(float x, float y, float *u, float *v);            // get optical_flow normal velocity
			
			// utils functions
			void kalmanFilterValues();											// kalman weighted average correction
			void smoothingValues();												// smoothing numerical data
			void normalizeValues();												// normalize numerical data
			
			
			int						_id;
			int						_devID;
			int						_width;
			int						_height;
			int						_numPixels;
			bool					isPlayer;
			string					movieFile;
            string                  haarFileName;
	
			string					trackBg;
			string					trackBgBW;
			
			int						videoCamSelector;
			int						randomWait;
			
			ofVideoGrabber			vidGrabber;
			ofVideoPlayer			vidPlayer;
    
            void grabBackgroundEvent(guiCallbackData & data);
            void activateTrackingCF(guiCallbackData & data);
            void resetInputWarping(guiCallbackData & data);
            void resetWarpingPoints();
            void setGuiSettingsFile(string file);
    
            ofxControlPanel             gui;
            string                      guiSettingsFile;
            simpleColor					gamuzaMainColor;
            simpleColor					gamuzaWhiteColor;
            simpleColor					gamuzaMarkColor;
            simpleColor					gamuzaChartBackColor;
            ofTrueTypeFont				fontSmall;
            ofImage						_empty;
            ofImage                     _hueWheel;
            vector<string>				bgSubTechniques;
            vector<string>				sourceFlipUse;
            vector<string>				cfDetailUse;
    
    
            //////////// WRAPPER GETTERS
            ofTexture getCameraTexture();
            ofTexture getCameraTextureMod();
            ofPixelsRef getCameraPixels();
            void captureBackground();
            float getMotionQ();
            float getMotionX();
            float getMotionY();
            int getNumBlobs();
            float getBlobX(int i);
            float getBlobY(int i);
            float getBlobW(int i);
            float getBlobH(int i);
            float getBlobAngle(int i);
            int getBlobContourSize(int i);
            float getBlobCPointX(int blob,int i);
            float getBlobCPointY(int blob,int i);
            int getBlobGeometrySize(int i);
            float getBlobGLineX1(int blob,int i);
            float getBlobGLineY1(int blob,int i);
            float getBlobGLineX2(int blob,int i);
            float getBlobGLineY2(int blob,int i);
            float getOpticalFlowX(int i);
            float getOpticalFlowY(int i);
            float getOpticalFlowVX(int i);
            float getOpticalFlowVY(int i);
            int getNumHaars();
            float getHaarX(int i);
            float getHaarY(int i);
            float getHaarW(int i);
            float getHaarH(int i);
            bool  getTrigger(int i);
            //////////// WRAPPER GETTERS
			
    
            ////////////////////////////////////////////// IMAGE MANIPULATION SECTION
            //////////////////////////////////////////////
            unsigned char			*camPixels;         // Live cam pixels copy
			ofTexture				camTexture;			// Live cam texture copy
    
            ////////////////////////////////////////////// TRACKING SECTION
            //////////////////////////////////////////////
			ofxCvColorImage			preColorImg;		// Live cam input image
			ofxCvColorImage			colorImg;			// Live cam input image without lens correction
			ofxCvColorImage			colorImgUndistorted;// Live cam input image with lens correction
			ofxCvColorImage			colorImgWarped;		// warping input for adjust tracking area
			ofxCvColorImage			colorImgHSV;		// HSV image
			ofxCvColorImage			colorBg;			// color background static image
			ofImage					savedBG;			// saving color background on hard drive
			ofImage					loadBG;				// load color background from hard drive
			int						colorImgBlur;		// input image blur value
	
			ofxCvGrayscaleImage		grayImg;			// B&W Live cam input image
			unsigned char			*grayImgPixels;
			ofxCvGrayscaleImage		grayBg;				// gray background static image
			ofxCvGrayscaleImage		grayThresh;			// background subtraction over b&w input image
			ofxCvGrayscaleImage		grayThreshMD;		// background subtraction frame differencing
			ofImage					savedGrayBG;		// saving gray background on hard drive
			ofImage					loadGrayBG;			// load gray background from hard drive
			ofImage					fakeBG;
			int						bgSubBlur;			// background subtraction blur value
			int						bgSubErode;			// background subtraction erode value
			int						bgSubDilate;		// background subtraction dilate value
			bool					bgUseContrastStrech;
			int						bgSubTech;			// background subtraction algorithm selector
	
			ofxCvGrayscaleImage		hueImg;				// Hue image
			ofxCvGrayscaleImage		satImg;				// Saturation image
			ofxCvGrayscaleImage		valImg;				// Value image
			unsigned char			*huePixels;			// hue pixel info
			unsigned char			*satPixels;			// sat pixel info
			unsigned char			*valPixels;			// val pixel info
			unsigned char			*hsvTrackedPixels;	// HSV tracked image
			ofxCvGrayscaleImage		hsvTracking;		// hsv tracking result image
			int						hsvBlur;			// hsv tracking result blur value
			int						hsvErode;			// hsv tracking result erode value
			int						hsvDilate;			// hsv tracking result dilate value
			bool					useHsvTracking;
			//////////////////////////////////////////////
			float					hue, hueWidth, sat, satWidth, val, valWidth;
			float					minHue, maxHue, minSat, maxSat, minVal, maxVal;
			
			//////////////////////////////////////////////
			ofxCvGrayscaleImage 	colorDiff;			// background subtraction over RGB input image
			unsigned char			*pixels1;
			unsigned char			*pixels2;
			unsigned char			*resPixels;
			
			
			//////////////////////////////////////////////
			ofPoint					*sourcePoints;		// input image warping points
			ofPoint					*destPoints;		// destination image warping points
			matrixAreas				sourceFrame;
			
			// source image lens correction (undistort)
			bool					undistortInput;
			float					un_radialX;
			float					un_radialY;
			float					un_tangentX;
			float					un_tangentY;
			float					un_focusX;
			float					un_focusY;
			float					un_centerX;
			float					un_centerY;
	
			// source image brightness/contrast
			float					contrast;
			float					brightness;
	
			// balanced tracking
			ofxCvGrayscaleImage		balancedTracking;	// balanced tracking from back subtraction over color & HSV tracking together
			int						btBlur;
			int						btErode;
			int						btDilate;
			unsigned char			*alg1;
			unsigned char			*alg2;
			unsigned char			*balPixels;
	
			// motion detection
			ofxCvGrayscaleImage		motionGUI;
			ofxCvGrayscaleImage 	grayPrev;
			ofxCvGrayscaleImage 	grayNow;
			ofxCvGrayscaleImage 	motionImg;
			unsigned char			*motion;
			int						frameCounter;
			int						numPixelsChanged; // motion quantity
			int						mCX, mCY, mCX2, mCY2;
			ofVec2f					MDCM; // motion centroid
			int						mThreshold;
			float					mNoiseComp; // motion noise compensation
	
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
	
			// face tracking
			ofxCvHaarFinder			haarFinder;
			int						numFace;
	
			// matrix areas for motion trigger
			matrixAreas				triggerAreas;
			bool					*triggerState;
			int						lastAreaON;
			int						actualArea;
			int						offHorizon, onHorizon;
			int						lastTime;
			int						silencePeriod;
	
			// generic vars
			unsigned char			*blackPixels;

			int						threshold;
			bool					bLearnBackground;
	
			// smoothed vars
			float					_smoothingFactor;								// smoothing factor
			ofVec2f					_s_MDCM;										// smoothed motion detection center mass
			float					_s_MDQ;											// smoothed motion quantity
			CvBox2D32f				*_s_blobInfo;									// smoothed blobs info
			vector<ofVec4f>			*_s_blobGeom;									// smoothed blobs geometry
			vector<ofVec2f>			*_s_contourSmooth;								// smoothed smooth contour points
			vector<ofVec2f>			*_s_contourSimple;								// smoothed simple contour points (redux)
			ofVec4f					*_s_opfVel;										// smoothed optical flow pixel velocity
			ofVec4f					*_s_ftInfo;										// smoothed face tracking blobs info
			
	
			// OSC sending vars
			ofVec2f					_osc_MDCM;										// normalized motion detection centers mass
			float					_osc_MDQ;										// normalized motion quantity
			CvBox2D32f				*_osc_blobInfo;									// normalized blobs info
			vector<ofVec4f>			*_osc_blobGeom;									// normalized blobs geometry
			vector<ofVec2f>			*_osc_contourSmooth;							// normalized smooth contour points
			vector<ofVec2f>			*_osc_contourSimple;							// normalized simple contour points (redux)
			ofVec4f					*_osc_opfVel;									// normalized optical flow pixel velocity
			ofVec4f					*_osc_ftInfo;									// normalized face tracking blobs info
			
			// selectors
			bool					captureVideo;
			bool					sourceHFlip;
			bool					sourceVFlip;
			int						_sourceFlipUse;
			bool					drawInfoGraphics;
			bool					computeContourFinder;
			bool					computeContourGeometry;
			bool					computeOpticalFlow;
			bool					computeHaarFinder;
			bool					computeTriggerAreas;
	
			bool					saveAllSettings;
			
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
