#ifndef 	_gaKinectTracking_H
#define 	_gaKinectTracking_H

////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxControlPanel.h"

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

class gaKinectTracking: public ofBaseApp, public ofxCvBlobListener{

	public:
			gaKinectTracking();
            ~gaKinectTracking();
    
            void    setup(int _id, bool _ir, bool videoImage, int _ledState);
            void    update();
            void    draw();
            void    close();
	
			void				setupDevice(int _id, bool _ir, bool videoImage, int _ledState);
			void				updateDevice();
			void				drawDevice();
	
			void mouseDragged(int x, int y);
			void mousePressed(int x, int y);
			void mouseReleased(int x, int y);
			
			void updateOpenCV();
            void updateGUI();
			void calculateMotion();
			void computeContourAnalysis();										// compute contour analysis
			void drawContourAnalysis();											// draw contour analysis
            void drawPointCloud();
            void drawGUI();
	
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
    
            // GUI
            void activateTrackingCF(guiCallbackData & data);
            void setGuiSettingsFile(string file);
    
            //////////// WRAPPER GETTERS
            ofTexture getCameraTexture();
            ofPixelsRef getCameraPixels();
            ofTexture getDepthTexture();
            int     getNumBlobs();
            float   getBlobX(int i);
            float   getBlobY(int i);
            float   getBlobW(int i);
            float   getBlobH(int i);
            float   getBlobAngle(int i);
            int     getBlobContourSize(int i);
            float   getBlobCPointX(int blob,int i);
            float   getBlobCPointY(int blob,int i);
            int     getBlobGeometrySize(int i);
            float   getBlobGLineX1(int blob,int i);
            float   getBlobGLineY1(int blob,int i);
            float   getBlobGLineX2(int blob,int i);
            float   getBlobGLineY2(int blob,int i);
            float   getOpticalFlowX(int i);
            float   getOpticalFlowY(int i);
            float   getOpticalFlowVX(int i);
            float   getOpticalFlowVY(int i);
            bool    getTrigger(int i);
            float   getAccelX();
            float   getAccelY();
            float   getAccelZ();
            //////////// WRAPPER GETTERS
    
    
            //////////////////////////////////////////
            // Kinect sensor variables
            ofxKinect kinect;
            ofEasyCam easyCam;
    
            bool bDrawPointCloud;
            int nearThreshold;
            int farThreshold;
            int tiltAngle;
            int devID;
            //////////////////////////////////////////
    
            //////////////////////////////////////////
            // GUI
            ofxControlPanel             gui;
            string                      guiSettingsFile;
            simpleColor					gamuzaMainColor;
            simpleColor					gamuzaWhiteColor;
            simpleColor					gamuzaMarkColor;
            simpleColor					gamuzaChartBackColor;
            ofTrueTypeFont				fontSmall;
            ofImage						_empty;
            vector<string>				cfDetailUse;
            //////////////////////////////////////////
			
			//////////////////////////////////////////
			// opencv tracking vars
			int						_width, _height;
			ofxCvGrayscaleImage		cleanImage;
            ofxCvGrayscaleImage     grayThreshNear;
            ofxCvGrayscaleImage     grayThreshFar;
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
			bool					saveAllSettings;
			
			// smoothed vars
			float					_smoothingFactor;								// smoothing factor
			CvBox2D32f				*_s_blobInfo;									// smoothed blobs info
			vector<ofVec4f>			*_s_blobGeom;									// smoothed blobs geometry
			vector<ofVec2f>			*_s_contourSmooth;								// smoothed smooth contour points
			vector<ofVec2f>			*_s_contourSimple;								// smoothed simple contour points (redux)
			ofVec4f					*_s_opfVel;										// smoothed optical flow pixel velocity
            ofVec3f                 *_s_hAccel;
			
			// OSC sending vars
			CvBox2D32f				*_osc_blobInfo;									// normalized blobs info
			vector<ofVec4f>			*_osc_blobGeom;									// normalized blobs geometry
			vector<ofVec2f>			*_osc_contourSmooth;							// normalized smooth contour points
			vector<ofVec2f>			*_osc_contourSimple;							// normalized simple contour points (redux)
			ofVec4f					*_osc_opfVel;									// normalized optical flow pixel velocity
            ofVec3f                 *_osc_hAccel;
	
			bool					computeContourFinder;
			bool					computeContourGeometry;
			bool					computeOpticalFlow;
			bool					computeTriggerAreas;
			//////////////////////////////////////////
			
			
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
