#include "gaSourceTracking.h"


//--------------------------------------------------------------
gaSourceTracking::gaSourceTracking(){
	haarFileName = GAMUZA_HAAR_DEFAULT;
    movieFile = GAMUZA_VIDEOTEST;
    guiSettingsFile = "guiSettings.xml";
    
    fontSmall.loadFont("fonts/D3Litebitmapism.ttf", 8, true, true);
    _empty.loadImage("img/empty.png");
    _hueWheel.loadImage("img/hueWheel.jpg");
    
    gamuzaMainColor         = simpleColor(9,147,211,255);
	gamuzaWhiteColor        = simpleColor(240,240,240,255);
	gamuzaMarkColor         = simpleColor(255,231,118,255);
    gamuzaChartBackColor    = simpleColor(40, 40, 40, 255);
}

//--------------------------------------------------------------
gaSourceTracking::~gaSourceTracking(){
	
}

//--------------------------------------------------------------
void gaSourceTracking::setHaarFile(string hF){
    haarFileName = hF;
}

//--------------------------------------------------------------
void gaSourceTracking::setMovieFile(string mF){
    movieFile = mF;
}

//--------------------------------------------------------------
void gaSourceTracking::switchCamMovie(){
    isPlayer = !isPlayer;
}

//--------------------------------------------------------------
void gaSourceTracking::setGuiSettingsFile(string file){
    guiSettingsFile = file;
}

//--------------------------------------------------------------
void gaSourceTracking::setup(int deviceID, int _w, int _h){
    
    char xml_name[256];
	char temp[128];
	
	_id			= 0;
	_devID		= deviceID;
	_width		= _w;
	_height		= _h;
	_numPixels	= _width*_height;
	
	randomWait = ofRandom(100);
    
    // vector<string> of bgSubTechniques list
    bgSubTechniques.assign(4, string());
	bgSubTechniques[0] = "COLOR ABS";
	bgSubTechniques[1] = "B&W ABS";
	bgSubTechniques[2] = "LIGHTER THAN";
	bgSubTechniques[3] = "DARKER THAN";
	// vector<string> of sourceFlipUse list
    sourceFlipUse.assign(4, string());
	sourceFlipUse[0] = "OFF";
	sourceFlipUse[1] = "VERTICAL";
	sourceFlipUse[2] = "HORIZONTAL";
	sourceFlipUse[3] = "VERTICAL + HORIZONTAL";
	// vector<string> of cfDetailUse list
    cfDetailUse.assign(3, string());
	cfDetailUse[0] = "RAW";
	cfDetailUse[1] = "SMOOTH";
	cfDetailUse[2] = "SIMPLE";
    
    gui.loadFont("fonts/D3Litebitmapism.ttf", 8);
	gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(120, 120, 120, 55));
	gui.setTextColor(gamuzaWhiteColor,simpleColor(240, 240, 240, 225));
	gui.setOutlineColor(simpleColor(0,0,0,255));
    ofxControlPanel::topSpacing = 20;
    gui.setup("CAMERA TRACKING MODULE",0,20,1200,720);
	gui.setDraggable(false);
    
    //////////////////////////////////////
    gui.setBackgroundColor(simpleColor(20, 20, 20, 165));
    gui.setOutlineColor(simpleColor(0,0,0,255));
    sprintf(temp," CAM DEVICE [%i]",deviceID);
    gui.addPanel(temp, 5);
    
    gui.setWhichPanel(temp);
    gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    gui.setOutlineColor(simpleColor(20, 20, 20, 125));
    
    gui.setWhichColumn(0);
    gui.addDrawableRect("COLOR INPUT", &colorImg, 240, 180);
    
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    sprintf(xml_name,"SWITCH_CAM_VIDEO_%i",deviceID);
    gui.addToggle("USE CAMERA/VIDEOFILE", xml_name, false);
    sprintf(xml_name,"UNDISTORT_INPUT_%i",deviceID);
    gui.addToggle("UNDISTORT [LENS CORRECTION]", xml_name, false);
    gui.addDrawableRect("MOTION DETECTION", &motionGUI, 160, 120);
    sprintf(xml_name,"RESET_INPUT_WARPING_DEV_%i",deviceID);
    gui.addToggle("RESET QUAD WARPING", xml_name, false);
    
    gui.setWhichColumn(1);
    gui.addDrawableRect("BALANCED TRACKING", &balancedTracking, 240, 180);
    sprintf(xml_name,"BG_CAPTURE_%i",deviceID);
    gui.addToggle("CAPTURE BACKGROUND", xml_name, true);
    sprintf(xml_name,"BG_USE_STRECH_%i",deviceID);
    gui.addToggle("USE CONTRAST STRETCH", xml_name, true);
    gui.addDrawableRect("BACKGROUND SUBTRACTION", &grayThresh, 160, 120);
    sprintf(xml_name,"USE_COLOR_TRACKING_%i",deviceID);
    gui.addToggle("USE COLOR TRACKING", xml_name, true);
    gui.addDrawableRect("COLOR TRACKING", &hsvTracking, 160, 120);
    
    gui.setWhichColumn(2);
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("GENERAL SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    //////////////////////////////////////////////
    sprintf(xml_name,"FLIP_SOURCE_USE_%i",deviceID);
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
    gui.addTextDropDown("FLIP SOURCE IMAGE ", xml_name, 1,sourceFlipUse);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
    //////////////////////////////////////////////
    sprintf(xml_name,"INPUT_BLUR_%i",deviceID);
    gui.addSlider("SOURCE BLUR", xml_name,colorImgBlur, 0, 33, true);
    sprintf(xml_name,"CONTRAST_%i",deviceID);
    gui.addSlider("CONTRAST", xml_name,contrast, 0.0, 1.0f, false);
    sprintf(xml_name,"BRIGHTNESS_%i",deviceID);
    gui.addSlider("BRIGHTNESS", xml_name,brightness, -1.0, 3.0f, false);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("BACKGROUND SUBTRACTION SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"BGSUB_TECH_%i",deviceID);
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
    gui.addTextDropDown("SUBTRACTION TECHNIQUE ", xml_name, 3, bgSubTechniques);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
    sprintf(xml_name,"BGSUB_THRESHOLD_%i",deviceID);
    gui.addSlider("SUBTRACTION THRESHOLD", xml_name,threshold, 1, 254, true);
    sprintf(xml_name,"BGSUB_BLUR_%i",deviceID);
    gui.addSlider("BLUR", xml_name, bgSubBlur, 0, 33, true);
    sprintf(xml_name,"BGSUB_ERODE_%i",deviceID);
    gui.addSlider("ERODE", xml_name,bgSubErode, 0, 10, true);
    sprintf(xml_name,"BGSUB_DILATE_%i",deviceID);
    gui.addSlider("DILATE", xml_name,bgSubDilate, 0, 10, true);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("OSC DATA SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    sprintf(xml_name,"SMOOTHING_FACTOR_%i",deviceID);
    gui.addSlider("SMOOTHING FACTOR",xml_name,_smoothingFactor,0.01f,0.99f,false);
    //////////////////////////////////////////////
    
    gui.setWhichColumn(3);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("COLOR TRACKING SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    gui.addDrawableRect(" ", &_hueWheel,180, 8);
    sprintf(xml_name,"HUE_%i",deviceID);
    gui.addSlider("HUE", xml_name, hue, 0.0, 1.0f, false);
    sprintf(xml_name,"HUE_WIDTH_%i",deviceID);
    gui.addSlider("HUE RANGE", xml_name, hueWidth, 0.0, 1.0f, false);
    sprintf(xml_name,"SAT_%i",deviceID);
    gui.addSlider("SATURATION", xml_name, sat, 0.0, 1.0f, false);
    sprintf(xml_name,"SAT_WIDTH_%i",deviceID);
    gui.addSlider("SATURATION RANGE", xml_name,satWidth, 0.0, 1.0f, false);
    sprintf(xml_name,"VAL_%i",deviceID);
    gui.addSlider("VALUE", xml_name,val, 0.0, 1.0f, false);
    sprintf(xml_name,"VAL_WIDTH_%i",deviceID);
    gui.addSlider("VALUE RANGE", xml_name,valWidth, 0.0, 1.0f, false);
    sprintf(xml_name,"HSV_BLUR_%i",deviceID);
    gui.addSlider("HSV BLUR", xml_name,hsvBlur, 0, 33, true);
    sprintf(xml_name,"HSV_ERODE_%i",deviceID);
    gui.addSlider("ERODE", xml_name, hsvErode, 0, 10, true);
    sprintf(xml_name,"HSV_DILATE_%i",deviceID);
    gui.addSlider("DILATE", xml_name,hsvDilate, 0, 10, true);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("MOTION DETECTION SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"M_THRESHOLD_%i",deviceID);
    gui.addSlider("MOTION THRESHOLD", xml_name,mThreshold, 1, 300, true);
    sprintf(xml_name,"M_NOISE_COMP_%i",deviceID);
    gui.addSlider("MOTION NOISE COMPENSATION", xml_name,mNoiseComp, 0, 1000, true);
    sprintf(xml_name,"MOTION_ON_HORIZON_%i",deviceID);
    gui.addSlider("MOTION TRIGGER LOW LIMIT", xml_name,onHorizon, 1, 100, true);
    sprintf(xml_name,"MOTION_OFF_HORIZON_%i",deviceID);
    gui.addSlider("MOTION TRIGGER RANGE LIMIT", xml_name,offHorizon, 0, 200, true);
    //////////////////////////////////////////////
    
    gui.setWhichColumn(4);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("BLOB TRACKING SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"MIN_BLOB_AREA_%i",deviceID);
    gui.addSlider("MIN BLOB",xml_name,minBlobArea,2,5000,true);
    sprintf(xml_name,"MAX_BLOB_AREA_%i",deviceID);
    gui.addSlider("MAX BLOB",xml_name,maxBlobArea,0,100000,true);
    sprintf(xml_name,"CF_DETAIL_%i",deviceID);
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
    gui.addTextDropDown("CONTOUR DETAIL", xml_name, 0, cfDetailUse);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
    sprintf(xml_name,"CF_SMOOTH_PCT_%i",deviceID);
    gui.addSlider("CONTOUR SMOOTH FACTOR", xml_name,smoothPct,0.01f,0.99f,false);
    sprintf(xml_name,"CF_TOLERANCE_%i",deviceID);
    gui.addSlider("CONTOUR SIMPLE TOLERANCE", xml_name,tolerance,0.01f,20.0f,false);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("BALANCED TRACKING SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"BT_BLUR_%i",deviceID);
    gui.addSlider("BALANCED TRACKING BLUR", xml_name, btBlur, 0, 33, true);
    sprintf(xml_name,"BT_ERODE_%i",deviceID);
    gui.addSlider("ERODE", xml_name, btErode, 0, 10, true);
    sprintf(xml_name,"BT_DILATE_%i",deviceID);
    gui.addSlider("DILATE", xml_name, btDilate, 0, 10, true);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("COMPUTING ALGORITHM SELECTOR");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"COMPUTE_CF_%i",deviceID);
    gui.addToggle("COMPUTE CONTOUR FINDER", xml_name, false);
    sprintf(xml_name,"COMPUTE_CG_%i",deviceID);
    gui.addToggle("COMPUTE CONTOUR GEOMETRY", xml_name, false);
    sprintf(xml_name,"COMPUTE_OF_%i",deviceID);
    gui.addToggle("COMPUTE OPTICAL FLOW", xml_name, false);
    sprintf(xml_name,"COMPUTE_FT_%i",deviceID);
    gui.addToggle("COMPUTE HAAR FINDER", xml_name, false);
    sprintf(xml_name,"COMPUTE_TA_%i",deviceID);
    gui.addToggle("COMPUTE TRIGGER AREAS", xml_name, false);
    //////////////////////////////////////////////
    // load default gui settings
	gui.loadSettings(guiSettingsFile);
    // GUI Events
	gui.setupEvents();
	gui.enableEvents();
    // create event for capture background
    sprintf(temp,"BG_CAPTURE_%i",deviceID);
    ofAddListener(gui.createEventGroup(temp), this, &gaSourceTracking::grabBackgroundEvent);
    // create event for reset input warping points
    sprintf(temp,"RESET_INPUT_WARPING_DEV_%i",deviceID);
    ofAddListener(gui.createEventGroup(temp), this, &gaSourceTracking::resetInputWarping);
    // create events to force contour finder computing
    sprintf(temp,"COMPUTE_CG_%i",deviceID);
    ofAddListener(gui.createEventGroup(temp), this, &gaSourceTracking::activateTrackingCF);
    sprintf(temp,"COMPUTE_TA_%i",deviceID);
    ofAddListener(gui.createEventGroup(temp), this, &gaSourceTracking::activateTrackingCF);
    //////////////////////////////////////////////
	
	sprintf(temp,"settings/cams/backgrounds/bgColor%i.jpg",deviceID);
	trackBg = temp;
	sprintf(temp,"settings/cams/backgrounds/bgBW%i.jpg",deviceID);
	trackBgBW = temp;
	
	isPlayer = false;
	
	vidGrabber.setDeviceID(deviceID);
    vidGrabber.initGrabber(_width,_height);
	vidPlayer.loadMovie(movieFile);
    vidPlayer.play();
	
    camPixels = new unsigned char[_numPixels*3];                // Live Cam pixels copy
	camTexture.allocate(_width,_height,GL_RGB);                 // Live Cam texture copy
    
    preColorImg.allocate(_width,_height);						// Live Cam as input source
	colorImg.allocate(_width,_height);							// Live Cam as input source without lens correction
	colorImgUndistorted.allocate(_width,_height);				// Live Cam as input source with lens correction
	grayImg.allocate(_width,_height);							// B&W lve Cam
	grayImgPixels = new unsigned char[_numPixels];
	colorImgWarped.allocate(_width,_height);					// warping input for adjust tracking area
	
	colorImgHSV.allocate(_width,_height);						// HSV image
	hueImg.allocate(_width,_height);							// Hue Image
    satImg.allocate(_width,_height);							// Saturation Image
    valImg.allocate(_width,_height);							// value Image
	hsvTrackedPixels = new unsigned char[_numPixels];			// Hue pixels
	huePixels = new unsigned char[_numPixels];					// Sat pixels
	satPixels = new unsigned char[_numPixels];					// Val pixels
	valPixels = new unsigned char[_numPixels];					// HSV tracked image
	hsvTracking.allocate(_width,_height);						// resulting texture from HSV tracking
	
	colorBg.allocate(_width,_height);							// background color image
	savedBG.allocate(_width,_height,OF_IMAGE_COLOR);			// saved background color image
	colorDiff.allocate(_width,_height);							// background subtraction over RGB input image
	resPixels = new unsigned char[_numPixels];					// single channel - b & w
	pixels1 = new unsigned char[_numPixels];
	pixels2 = new unsigned char[_numPixels];
	
	grayBg.allocate(_width,_height);							// background b&w image
	savedGrayBG.allocate(_width,_height,OF_IMAGE_GRAYSCALE);	// saved background b&w image
	grayThresh.allocate(_width,_height);						// background subtraction thresholded
	grayThreshMD.allocate(_width,_height);						// background subtraction thresholded + Motion Detection
	
	balancedTracking.allocate(_width,_height);					// balanced tracking from back subtraction over RGB & HSV tracking merged
	alg1 = new unsigned char[_numPixels];
	alg2 = new unsigned char[_numPixels];
	balPixels = new unsigned char[_numPixels];
	
	motionGUI.allocate(_width, _height);
	grayPrev.allocate(_width,_height);							// previous frame for motion detection
	grayNow.allocate(_width,_height);							// actual frame for motion detection
	motionImg.allocate(_width,_height);							// motion detection image
	motion = new unsigned char[_numPixels];
	
	opticalFlow.allocate(_width,_height);
	
	blackPixels = new unsigned char[_numPixels];				// black image
	for(unsigned int b=0;b<_numPixels;b++){
		blackPixels[b] = 0;
	}
	
	//////////////////////////////////////////////
	// set background subtraction vars
	bLearnBackground = false;
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// set motion detection vars
	frameCounter	 = 0;
	numPixelsChanged = 0;
	mCX				 = 0;
	mCY				 = 0;
	mCX2			 = 0;
	mCY2			 = 0;
	_s_MDQ			 = 0.0f;
	_osc_MDQ		 = 0.0f;
	
	MDCM.set(0.0f,0.0f);
	_s_MDCM.set(0.0f,0.0f);
	_osc_MDCM.set(0.0f,0.0f);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// contour finder
	contourReg				= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	contourSmooth			= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	contourSimple			= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	geomLines				= new vector<ofVec4f>[MAX_NUM_CONTOURS_TO_FIND];
	_s_blobGeom				= new vector<ofVec4f>[MAX_NUM_CONTOURS_TO_FIND];
	_osc_blobGeom			= new vector<ofVec4f>[MAX_NUM_CONTOURS_TO_FIND];
	_s_contourSmooth		= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	_osc_contourSmooth		= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	_s_contourSimple		= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	_osc_contourSimple		= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	
	box						= new CvBox2D32f[MAX_NUM_CONTOURS_TO_FIND];
	blobAngle				= new float[MAX_NUM_CONTOURS_TO_FIND];
	_s_blobInfo				= new CvBox2D32f[MAX_NUM_CONTOURS_TO_FIND];
	_osc_blobInfo			= new CvBox2D32f[MAX_NUM_CONTOURS_TO_FIND];
	
	
	smoothPct = 0.13f;
	tolerance = 20.0f;
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// advanced blob tracking (blob order)
	blobTracker.setListener(this);
	blobsOrder = new int[MAX_USERS_HARDLIMIT];
	topLeftX = 1;
	topLeftY = 1;
	maxUsers = MAX_USERS_HARDLIMIT;
	lowRightX = _width;
	lowRightY = _height;
	userOffsetX = 0;
	userOffsetY = 0;
	moodSpike = 0.25f;
	nonMoodFrames = 3;
	currNonMoodFrame = 0;
	csState = CO_SELNONE;
	// All blobs are marked as dead initially
	for (unsigned int i = 0; i < MAX_USERS_HARDLIMIT; i++){
		usersTracking[i] = B_DEAD;
	}
	currAdjustment = AJ_THRESH;
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// optical flow
	opticalFlowXGrid = (int)(_width/OPTICAL_FLOW_COLS_STEP);
	opticalFlowYGrid = (int)(_height/OPTICAL_FLOW_ROWS_STEP);
	
	_s_opfVel		= new ofVec4f[opticalFlowXGrid*opticalFlowYGrid];
	_osc_opfVel		= new ofVec4f[opticalFlowXGrid*opticalFlowYGrid];
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// face tracking
	//load in our face xml file
	haarFinder.setup(haarFileName);
	
	_s_ftInfo		= new ofVec4f[MAX_NUM_CONTOURS_TO_FIND];
	_osc_ftInfo		= new ofVec4f[MAX_NUM_CONTOURS_TO_FIND];
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// matrix areas for motion trigger
	float	flopX = 30;
	float	flopY = 90;
    
	triggerAreas.setup(flopX,flopY,240,180,TRIGGER_AREAS_NUM);
	sprintf(temp,"settings/cams/triggerAreas_id_%i.xml",deviceID);
	triggerAreas.loadSettings(temp);
	triggerState = new bool[TRIGGER_AREAS_NUM];
	for(unsigned int i=0;i<TRIGGER_AREAS_NUM;i++){
		triggerState[i] = false;
	}
	lastAreaON = -1;
	actualArea = -1;
	lastTime = 0;
	silencePeriod = 0;
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// set input warping points
	sourceFrame.setup(flopX,flopY,240,180,4);
	sprintf(temp,"settings/cams/sourceFrame_id_%i.xml",deviceID);
	sourceFrame.loadSettings(temp);
	
	sourcePoints  = new ofPoint[4];
	sourcePoints[0] = ofPoint(flopX, flopY);
	sourcePoints[1] = ofPoint(240.0f + flopX, flopY);
	sourcePoints[2] = ofPoint(240.0f + flopX, 180.0f + flopY);
	sourcePoints[3] = ofPoint(flopX, 180.0f + flopY);
	
	destPoints  = new ofPoint[4];
	destPoints[0] = ofPoint(0.0f, 0.0f);
	destPoints[1] = ofPoint(240.0f, 0.0f);
	destPoints[2] = ofPoint(240.0f, 180.0f);
	destPoints[3] = ofPoint(0.0f, 180.0f);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// loading tracking backgrounds (color and b&w)
	fakeBG.loadImage("img/fakeBG.jpg");
	
	if(loadBG.loadImage(trackBg)){
		loadBG.resize(_width,_height);
		colorBg.setFromPixels(loadBG.getPixels(),_width,_height);
	}else{
		fakeBG.resize(_width,_height);
		colorBg.setFromPixels(fakeBG.getPixels(),_width,_height);
	}
	
	if(loadGrayBG.loadImage(trackBgBW)){
		loadGrayBG.resize(_width,_height);
		grayBg.setFromPixels(loadGrayBG.getPixels(),_width,_height);
	}else{
		fakeBG.resize(_width,_height);
		grayBg.setFromPixels(fakeBG.getPixels(),_width,_height);
	}
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// loading lens correction vars (undistorting image)
	loadCalibration();
	//////////////////////////////////////////////
	
	
	//////////////////////////////////////////////
	// dummy gui vars init
	captureVideo = true;
    drawInfoGraphics = true;
	saveAllSettings = false;
	//////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gaSourceTracking::setupCam(int __id, int _w, int _h, int deviceID, bool player, string haarFile, string movie){
	
	_id			= __id;
	_devID		= deviceID;
	_width		= _w;
	_height		= _h;
	_numPixels	= _width*_height;
	
	randomWait = ofRandom(1000, 2000);
	randomWait *= deviceID;
	
	char temp[128];
	sprintf(temp,"settings/cams/backgrounds/bgColor%i.jpg",deviceID);
	trackBg = temp;
	sprintf(temp,"settings/cams/backgrounds/bgBW%i.jpg",deviceID);
	trackBgBW = temp;
	
	isPlayer = player;
	movieFile = movie;
    haarFileName = haarFile;
	
	if(!isPlayer){
		vidGrabber.setDeviceID(deviceID);
		vidGrabber.initGrabber(_width,_height);
	}else{
		vidPlayer.loadMovie(movieFile);
		vidPlayer.play();
	}
	
    camPixels = new unsigned char[_numPixels*3];                // Live Cam pixels copy
	camTexture.allocate(_width,_height,GL_RGB);                 // Live Cam texture copy
    
    preColorImg.allocate(_width,_height);						// Live Cam as input source
	colorImg.allocate(_width,_height);							// Live Cam as input source without lens correction
	colorImgUndistorted.allocate(_width,_height);				// Live Cam as input source with lens correction
	grayImg.allocate(_width,_height);							// B&W lve Cam
	grayImgPixels = new unsigned char[_numPixels];
	colorImgWarped.allocate(_width,_height);					// warping input for adjust tracking area
	
	colorImgHSV.allocate(_width,_height);						// HSV image
	hueImg.allocate(_width,_height);							// Hue Image
    satImg.allocate(_width,_height);							// Saturation Image
    valImg.allocate(_width,_height);							// value Image
	hsvTrackedPixels = new unsigned char[_numPixels];			// Hue pixels
	huePixels = new unsigned char[_numPixels];					// Sat pixels
	satPixels = new unsigned char[_numPixels];					// Val pixels
	valPixels = new unsigned char[_numPixels];					// HSV tracked image
	hsvTracking.allocate(_width,_height);						// resulting texture from HSV tracking
	
	colorBg.allocate(_width,_height);							// background color image
	savedBG.allocate(_width,_height,OF_IMAGE_COLOR);			// saved background color image
	colorDiff.allocate(_width,_height);							// background subtraction over RGB input image
	resPixels = new unsigned char[_numPixels];					// single channel - b & w
	pixels1 = new unsigned char[_numPixels];
	pixels2 = new unsigned char[_numPixels];
	
	grayBg.allocate(_width,_height);							// background b&w image
	savedGrayBG.allocate(_width,_height,OF_IMAGE_GRAYSCALE);	// saved background b&w image
	grayThresh.allocate(_width,_height);						// background subtraction thresholded
	grayThreshMD.allocate(_width,_height);						// background subtraction thresholded + Motion Detection
	
	balancedTracking.allocate(_width,_height);					// balanced tracking from back subtraction over RGB & HSV tracking merged
	alg1 = new unsigned char[_numPixels];						
	alg2 = new unsigned char[_numPixels];
	balPixels = new unsigned char[_numPixels];
	
	motionGUI.allocate(_width, _height);
	grayPrev.allocate(_width,_height);							// previous frame for motion detection
	grayNow.allocate(_width,_height);							// actual frame for motion detection
	motionImg.allocate(_width,_height);							// motion detection image
	motion = new unsigned char[_numPixels];
	
	opticalFlow.allocate(_width,_height);
	
	blackPixels = new unsigned char[_numPixels];				// black image
	for(unsigned int b=0;b<_numPixels;b++){
		blackPixels[b] = 0;
	}
	
	//////////////////////////////////////////////
	// set background subtraction vars
	bLearnBackground = false;
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// set motion detection vars
	frameCounter	 = 0;
	numPixelsChanged = 0;
	mCX				 = 0;
	mCY				 = 0;
	mCX2			 = 0;
	mCY2			 = 0;
	_s_MDQ			 = 0.0f;
	_osc_MDQ		 = 0.0f;
	
	MDCM.set(0.0f,0.0f);
	_s_MDCM.set(0.0f,0.0f);
	_osc_MDCM.set(0.0f,0.0f);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// contour finder
	contourReg				= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	contourSmooth			= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	contourSimple			= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	geomLines				= new vector<ofVec4f>[MAX_NUM_CONTOURS_TO_FIND];
	_s_blobGeom				= new vector<ofVec4f>[MAX_NUM_CONTOURS_TO_FIND];
	_osc_blobGeom			= new vector<ofVec4f>[MAX_NUM_CONTOURS_TO_FIND];
	_s_contourSmooth		= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	_osc_contourSmooth		= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	_s_contourSimple		= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	_osc_contourSimple		= new vector<ofVec2f>[MAX_NUM_CONTOURS_TO_FIND];
	
	box						= new CvBox2D32f[MAX_NUM_CONTOURS_TO_FIND];
	blobAngle				= new float[MAX_NUM_CONTOURS_TO_FIND];
	_s_blobInfo				= new CvBox2D32f[MAX_NUM_CONTOURS_TO_FIND];
	_osc_blobInfo			= new CvBox2D32f[MAX_NUM_CONTOURS_TO_FIND];
	
	
	smoothPct = 0.13f;
	tolerance = 20.0f;
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// advanced blob tracking (blob order)
	blobTracker.setListener(this);
	blobsOrder = new int[MAX_USERS_HARDLIMIT];
	topLeftX = 1;
	topLeftY = 1;
	maxUsers = MAX_USERS_HARDLIMIT;
	lowRightX = _width;
	lowRightY = _height;
	userOffsetX = 0;
	userOffsetY = 0;
	moodSpike = 0.25f;
	nonMoodFrames = 3;
	currNonMoodFrame = 0;
	csState = CO_SELNONE;
	// All blobs are marked as dead initially
	for (unsigned int i = 0; i < MAX_USERS_HARDLIMIT; i++){
		usersTracking[i] = B_DEAD;
	}
	currAdjustment = AJ_THRESH;
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// optical flow
	opticalFlowXGrid = (int)(_width/OPTICAL_FLOW_COLS_STEP);
	opticalFlowYGrid = (int)(_height/OPTICAL_FLOW_ROWS_STEP);
	
	_s_opfVel		= new ofVec4f[opticalFlowXGrid*opticalFlowYGrid];
	_osc_opfVel		= new ofVec4f[opticalFlowXGrid*opticalFlowYGrid];
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// face tracking
	//load in our face xml file
	haarFinder.setup(haarFileName);
	
	_s_ftInfo		= new ofVec4f[MAX_NUM_CONTOURS_TO_FIND];
	_osc_ftInfo		= new ofVec4f[MAX_NUM_CONTOURS_TO_FIND];
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// matrix areas for motion trigger
	float	flopX = 30;
	float	flopY = 90;
    
	triggerAreas.setup(flopX,flopY,240,180,TRIGGER_AREAS_NUM);
	sprintf(temp,"settings/cams/triggerAreas_id_%i.xml",deviceID);
	triggerAreas.loadSettings(temp);
	triggerState = new bool[TRIGGER_AREAS_NUM];
	for(unsigned int i=0;i<TRIGGER_AREAS_NUM;i++){
		triggerState[i] = false;
	}
	lastAreaON = -1;
	actualArea = -1;
	lastTime = 0;
	silencePeriod = 0;
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// set input warping points
	sourceFrame.setup(flopX,flopY,240,180,4);
	sprintf(temp,"settings/cams/sourceFrame_id_%i.xml",deviceID);
	sourceFrame.loadSettings(temp);
	
	sourcePoints  = new ofPoint[4];
	sourcePoints[0] = ofPoint(flopX, flopY);
	sourcePoints[1] = ofPoint(240.0f + flopX, flopY);
	sourcePoints[2] = ofPoint(240.0f + flopX, 180.0f + flopY);
	sourcePoints[3] = ofPoint(flopX, 180.0f + flopY);
	
	destPoints  = new ofPoint[4];
	destPoints[0] = ofPoint(0.0f, 0.0f);
	destPoints[1] = ofPoint(240.0f, 0.0f);
	destPoints[2] = ofPoint(240.0f, 180.0f);
	destPoints[3] = ofPoint(0.0f, 180.0f);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// loading tracking backgrounds (color and b&w)
	fakeBG.loadImage("img/fakeBG.jpg");
	
	if(loadBG.loadImage(trackBg)){
		loadBG.resize(_width,_height);
		colorBg.setFromPixels(loadBG.getPixels(),_width,_height);
	}else{
		fakeBG.resize(_width,_height);
		colorBg.setFromPixels(fakeBG.getPixels(),_width,_height);
	}
	
	if(loadGrayBG.loadImage(trackBgBW)){
		loadGrayBG.resize(_width,_height);
		grayBg.setFromPixels(loadGrayBG.getPixels(),_width,_height);
	}else{
		fakeBG.resize(_width,_height);
		grayBg.setFromPixels(fakeBG.getPixels(),_width,_height);
	}
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// loading lens correction vars (undistorting image)
	loadCalibration();
	//////////////////////////////////////////////
	
	
	//////////////////////////////////////////////
	// dummy gui vars init
	captureVideo = true;
	
	sourceHFlip		= true;
	sourceVFlip		= false;
	_sourceFlipUse	= 0;
	
	undistortInput	= false;
	useHsvTracking	= true;
	
	hue = hueWidth = sat = satWidth = val = valWidth = 1.0;
	
	contrast = 0.0; // -1 ---- 1
	brightness = 0.0; // -1 ---- 3
	
	colorImgBlur = 3;
	
	bgSubBlur = 1;
	bgSubErode = 0;
	bgSubDilate = 0;
	
	bgUseContrastStrech = false;
	
	bgSubTech = 3;
	threshold = 80;
	
	hsvBlur = 1;
	hsvErode = 0;
	hsvDilate = 0;
	
	mNoiseComp = 10.0;
	mThreshold = 100;
	
	btBlur = 1;
	btErode = 1;
	btDilate = 1;
	
	minBlobArea = 20;
	maxBlobArea = 100000;
	cfDetail = 1;
	
	onHorizon = 20;
	offHorizon = 50;
	
	computeContourFinder = false;
	computeContourGeometry = false;
	computeOpticalFlow = false;
	computeHaarFinder = false;
	computeTriggerAreas = false;
	
	_smoothingFactor = 0.95f;
	
	drawInfoGraphics = true;
	
	saveAllSettings = false;
	//////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gaSourceTracking::update(){
	
	char temp[128];
    char xml_name[256];
    
    //////////////////////////////////////////////
    sprintf(xml_name,"SWITCH_CAM_VIDEO_%i",_devID);
    isPlayer = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"FLIP_SOURCE_USE_%i",_devID);
    _sourceFlipUse = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"UNDISTORT_INPUT_%i",_devID);
    undistortInput = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"INPUT_BLUR_%i",_devID);
    colorImgBlur = gui.getValueI(xml_name);
    sprintf(xml_name,"CONTRAST_%i",_devID);
    contrast = gui.getValueF(xml_name);
    sprintf(xml_name,"BRIGHTNESS_%i",_devID);
    brightness = gui.getValueF(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"USE_COLOR_TRACKING_%i",_devID);
    useHsvTracking = gui.getValueI(xml_name);
    sprintf(xml_name,"HUE_%i",_devID);
    hue = gui.getValueF(xml_name);
    sprintf(xml_name,"HUE_WIDTH_%i",_devID);
    hueWidth = gui.getValueF(xml_name);
    sprintf(xml_name,"SAT_%i",_devID);
    sat = gui.getValueF(xml_name);
    sprintf(xml_name,"SAT_WIDTH_%i",_devID);
    satWidth = gui.getValueF(xml_name);
    sprintf(xml_name,"VAL_%i",_devID);
    val = gui.getValueF(xml_name);
    sprintf(xml_name,"VAL_WIDTH_%i",_devID);
    valWidth = gui.getValueF(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"MOTION_ON_HORIZON_%i",_devID);
    onHorizon = gui.getValueI(xml_name);
    sprintf(xml_name,"MOTION_OFF_HORIZON_%i",_devID);
    offHorizon = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"BGSUB_TECH_%i",_devID);
    bgSubTech = gui.getValueI(xml_name);
    sprintf(xml_name,"BGSUB_THRESHOLD_%i",_devID);
    threshold = gui.getValueI(xml_name);
    sprintf(xml_name,"BG_USE_STRECH_%i",_devID);
    bgUseContrastStrech = gui.getValueI(xml_name);
    sprintf(xml_name,"BGSUB_BLUR_%i",_devID);
    bgSubBlur = gui.getValueI(xml_name);
    sprintf(xml_name,"BGSUB_ERODE_%i",_devID);
    bgSubErode = gui.getValueI(xml_name);
    sprintf(xml_name,"BGSUB_DILATE_%i",_devID);
    bgSubDilate = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"HSV_BLUR_%i",_devID);
    hsvBlur = gui.getValueI(xml_name);
    sprintf(xml_name,"HSV_ERODE_%i",_devID);
    hsvErode = gui.getValueI(xml_name);
    sprintf(xml_name,"HSV_DILATE_%i",_devID);
    hsvDilate = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"M_THRESHOLD_%i",_devID);
    mThreshold = gui.getValueI(xml_name);
    sprintf(xml_name,"M_NOISE_COMP_%i",_devID);
    mNoiseComp = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"BT_BLUR_%i",_devID);
    btBlur = gui.getValueI(xml_name);
    sprintf(xml_name,"BT_ERODE_%i",_devID);
    btErode = gui.getValueI(xml_name);
    sprintf(xml_name,"BT_DILATE_%i",_devID);
    btDilate = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"MIN_BLOB_AREA_%i",_devID);
    minBlobArea = gui.getValueI(xml_name);
    sprintf(xml_name,"MAX_BLOB_AREA_%i",_devID);
    maxBlobArea = gui.getValueI(xml_name) + minBlobArea;
    sprintf(xml_name,"CF_DETAIL_%i",_devID);
    cfDetail = gui.getValueI(xml_name);
    sprintf(xml_name,"CF_SMOOTH_PCT_%i",_devID);
    smoothPct = gui.getValueF(xml_name);
    sprintf(xml_name,"CF_TOLERANCE_%i",_devID);
    tolerance = gui.getValueF(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"COMPUTE_CF_%i",_devID);
    computeContourFinder = gui.getValueI(xml_name);
    sprintf(xml_name,"COMPUTE_CG_%i",_devID);
    computeContourGeometry = gui.getValueI(xml_name);
    sprintf(xml_name,"COMPUTE_OF_%i",_devID);
    computeOpticalFlow = gui.getValueI(xml_name);
    sprintf(xml_name,"COMPUTE_FT_%i",_devID);
    computeHaarFinder = gui.getValueI(xml_name);
    sprintf(xml_name,"COMPUTE_TA_%i",_devID);
    computeTriggerAreas = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"SMOOTHING_FACTOR_%i",_devID);
    _smoothingFactor = gui.getValueF(xml_name);
    //////////////////////////////////////////////
    
    gui.update();
	
	//////////////////////////////////////////////
	// input warping points from GUI
	for (unsigned int j = 0; j < 4; j++){		
		sourcePoints[j].x = sourceFrame.points[j].x;
		sourcePoints[j].y = sourceFrame.points[j].y;
	}
	//////////////////////////////////////////////
	
	bool bNewFrame = false;
	
	if(ofGetElapsedTimeMillis() > randomWait){ // startup safe delay
		if(!isPlayer){
			vidGrabber.update();
			bNewFrame = vidGrabber.isFrameNew();
		}else{
			vidPlayer.update();
			bNewFrame = vidPlayer.isFrameNew();
		}

	}
	
	if(bNewFrame && captureVideo){
		if(!isPlayer){
			preColorImg.setFromPixels(vidGrabber.getPixels(), _width,_height);
		}else{
			preColorImg.setFromPixels(vidPlayer.getPixels(), _width,_height);
		}
		
		//////////////////////////////////////////////
		// undistort | lens correction
		if(undistortInput){
			colorImgUndistorted = preColorImg;
			colorImgUndistorted.undistort(un_radialX,un_radialY,un_tangentX,un_tangentY,un_focusX,un_focusY,un_centerX,un_centerY);
			colorImg = colorImgUndistorted;
		}else{
			colorImg = preColorImg;
		}
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// flip horizontally/vertically input image
		switch(_sourceFlipUse){
			case 0:
				sourceVFlip = false;
				sourceHFlip = false;
				break;
			case 1:
				sourceVFlip = true;
				sourceHFlip = false;
				break;
			case 2:
				sourceVFlip = false;
				sourceHFlip = true;
				break;
			case 3:
				sourceVFlip = true;
				sourceHFlip = true;
				break;
			default:
				break;
		}
		colorImg.mirror(sourceVFlip,sourceHFlip);
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// cam texture & pixels copy
		camTexture.loadData(colorImg.getPixels(), _width, _height, GL_RGB);
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// eventually blur adjusted source
		colorImg.blur(colorImgBlur);
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// warping image frame
		colorImgWarped = colorImg;
		colorImgWarped.warpIntoMe(colorImg, sourcePoints, destPoints);
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// copy in BW the input image
		grayImg			= colorImgWarped;
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// set brightness & contrast to the BW input image
		grayImg.brightnessContrast(brightness,contrast);
		
		grayImgPixels	= grayImg.getPixels();
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// background learning
		if(bLearnBackground == true){
			colorBg = colorImgWarped;
			grayBg = grayImg;
			savedBG.setFromPixels(colorBg.getPixels(),_width,_height,OF_IMAGE_COLOR);
			savedBG.saveImage(trackBg);
			savedGrayBG.setFromPixels(grayBg.getPixels(),_width,_height,OF_IMAGE_GRAYSCALE);
			savedGrayBG.saveImage(trackBgBW);
			bLearnBackground = false;
			printf("Background of device %i saved\n",_devID);
		}
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// background subtraction
		if(bgSubTech == 0){
			calculateColorDifference();
		}else{
			calculateGrayscaleDifference();
		}
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// tracking color difference over time using HSV color information
		if(useHsvTracking){
			calculateColorDifferenceHSV();
		}else{
			colorImgHSV = colorImgWarped;
			hsvTracking.setFromPixels(blackPixels,_width,_height);
		}
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// filter information from the two different algorithms
		balanceTracking();
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// motion detection with optical flow control
		calculateMotion();
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// find contours
		if(computeContourFinder){
			runningBlobs = contourFinder.findContours(balancedTracking, minBlobArea, maxBlobArea, MAX_NUM_CONTOURS_TO_FIND, false, false);
			if(runningBlobs > 0 && runningBlobs < MAX_NUM_CONTOURS_TO_FIND){
				computeContourAnalysis();
				blobTracker.trackBlobs(contourFinder.blobs);
			}
		}
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// face tracking
		if(computeHaarFinder){
			haarFinder.findHaarObjects(grayImg);
			numFace = haarFinder.blobs.size();
		}
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// motion trigger areas
		if(computeContourFinder && computeTriggerAreas){
			if(numPixelsChanged > onHorizon){
				// if first blob is inside area...
				// this is useful when working with laser tracking 
				triggerAreas.isPointInside(box[0].center.x,box[0].center.y);
				if(lastAreaON != triggerAreas.areaON){
					if(actualArea != triggerAreas.areaON){
						actualArea = triggerAreas.areaON;
						// actualArea activated
						triggerState[actualArea] = !triggerState[actualArea];
					}
					
					lastTime = ofGetElapsedTimeMillis();
					
				}
				lastAreaON = triggerAreas.areaON;
			}
			if(numPixelsChanged < offHorizon){
				if(lastAreaON != -1){
					silencePeriod = ofGetElapsedTimeMillis();
					// actualArea deactivated after (silencePeriod-lastTime);
				}
				lastAreaON = -1;
			}
			
		}
		//////////////////////////////////////////////
		
		//////////////////////////////////////////////
		// apply kalman filter (if selected) to every output value
		// smoothing & normalize numerical variable
		// (prepare it for sending via OSC)
		smoothingValues();
		normalizeValues();
		//////////////////////////////////////////////
		
	}
	
	//////////////////////////////////////////////
	// save all settings
	if (saveAllSettings == true){
		sprintf(temp,"settings/cams/sourceFrame_id_%i.xml",_devID);
		sourceFrame.saveSettings(temp);
		sprintf(temp,"settings/cams/triggerAreas_id_%i.xml",_devID);
		triggerAreas.saveSettings(temp);
		saveAllSettings = false;
	}
	//////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gaSourceTracking::draw(){
    
    char temp[128];
    string temp1;
	ostringstream temp2;
	
	if(captureVideo){
        
        //////////////////////////////////////////////////
		// Draw gui
        ofSetColor(255);
		gui.draw(1);
        ofEnableAlphaBlending();
		ofFill();
        glColor4f(1.0,0.3,0.0,0.6);
        ofRect(gui.panelTabs[0].x+1, gui.panelTabs[0].y+1, gui.panelTabs[0].width-2, gui.panelTabs[0].height-2);
        ofDisableAlphaBlending();
		//////////////////////////////////////////////////
		
		//////////////////////////////////////////////////
		// Draw lines between warping points (input source)
		if(drawInfoGraphics){
			sourceFrame.drawMinimalWithLines();
		}
		//////////////////////////////////////////////////
		
		//////////////////////////////////////////////////
		// Draw motion detection centroid
		if(drawInfoGraphics){
			drawMotionCentroid();
		}
		//////////////////////////////////////////////////
		
		//////////////////////////////////////////////////
		// blob detection + contours
		if(computeContourFinder && drawInfoGraphics){
			if(runningBlobs > 0){
				drawContourAnalysis();
			}
		}
		//////////////////////////////////////////////////
		
		//////////////////////////////////////////////////
		// optical flow LK
		if(computeOpticalFlow && drawInfoGraphics){
			glPushMatrix();
				glTranslatef(286, 83, 0);
				glScalef(240.0f/_width, 180.0f/_height, 1.0);
				opticalFlow.draw();
			glPopMatrix();
		}
		//////////////////////////////////////////////////
		
		//////////////////////////////////////////////////
		// face tracking
		if(computeHaarFinder && drawInfoGraphics){
			drawHaarFinder();
		}
		//////////////////////////////////////////////////
		
		//////////////////////////////////////////////////
		// motion trigger areas
		if(computeContourFinder && computeTriggerAreas && drawInfoGraphics){
			triggerAreas.draw(triggerState);
		}
        
		//////////////////////////////////////////////////
        
        //////////////////////////////////////////////////
        // Additional text info
        ofSetColor(255);
        sprintf(temp,"MOTION QUANTITY : %i",numPixelsChanged);
        fontSmall.drawString(temp, 30, 490);
        if(computeContourFinder && computeTriggerAreas){
            temp2 << "TRIGGERS: ";
            for(unsigned int t=0;t<TRIGGER_AREAS_NUM;t++){
                temp2 << t;
                temp2 << "[";
                sprintf(temp,"%i",triggerState[t]);
                temp2 << temp;
                temp2 << "] ";
            }
            temp2 << endl;
            temp1 = temp2.str();
            sprintf(temp,"%s",temp1.c_str());
            fontSmall.drawString(temp, 286,280);
        }
        //////////////////////////////////////////////////
		
	}
	
}

//--------------------------------------------------------------
void gaSourceTracking::grabBackgroundEvent(guiCallbackData & data){
	
	char temp[256];
    sprintf(temp,"BG_CAPTURE_%i",_devID);
    if(data.isElement(temp) && data.getInt(0) == 1 ){
        bLearnBackground = true;
        gui.setValueB(temp, false);
    }
	
}

//--------------------------------------------------------------
void gaSourceTracking::activateTrackingCF(guiCallbackData & data){
	
	char temp[256], temp2[256],temp3[256];
    sprintf(temp,"COMPUTE_CG_%i",_devID);
    sprintf(temp2,"COMPUTE_TA_%i",_devID);
    sprintf(temp3,"COMPUTE_CF_%i",_devID);
    if((data.isElement(temp) || data.isElement(temp2)) && data.getInt(0) == 1 ){
        gui.setValueB(temp3, true);
    }
	
}

//--------------------------------------------------------------
void gaSourceTracking::resetInputWarping(guiCallbackData & data){
	
	char temp[256];
	sprintf(temp,"RESET_INPUT_WARPING_DEV_%i",_devID);
    if(data.isElement(temp) && data.getInt(0) == 1){
        resetWarpingPoints();
        gui.setValueB(temp, false);
    }
}

//--------------------------------------------------------------
void gaSourceTracking::resetWarpingPoints(){
	
	sourceFrame.points[0].x = 0.0f;
	sourceFrame.points[0].y = 0.0f;
	sourceFrame.points[1].x = 240.0f;
	sourceFrame.points[1].y = 0.0f;
	sourceFrame.points[2].x = 240.0f;
	sourceFrame.points[2].y = 180.0f;
	sourceFrame.points[3].x = 0.0f;
	sourceFrame.points[3].y = 180.0f;
	
}

//--------------------------------------------------------------
ofTexture gaSourceTracking::getCameraTexture(){
    if(isPlayer){
        return vidPlayer.getTextureReference();
    }else{
        return vidGrabber.getTextureReference();
    }
}

//--------------------------------------------------------------
ofTexture gaSourceTracking::getCameraTextureMod(){
    return camTexture;
}

//--------------------------------------------------------------
ofPixelsRef gaSourceTracking::getCameraPixels(){
    if(isPlayer){
        return vidPlayer.getPixelsRef();
    }else{
        return vidGrabber.getPixelsRef();
    }
}

//--------------------------------------------------------------
void gaSourceTracking::captureBackground(){
    bLearnBackground = true;
}

//--------------------------------------------------------------
float gaSourceTracking::getMotionQ(){
    return _osc_MDQ;
}

//--------------------------------------------------------------
float gaSourceTracking::getMotionX(){
    return _osc_MDCM.x;
}

//--------------------------------------------------------------
float gaSourceTracking::getMotionY(){
    return _osc_MDCM.y;
}

//--------------------------------------------------------------
int gaSourceTracking::getNumBlobs(){
    if(computeContourFinder){
        return runningBlobs;
    }else{
        return 0;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobX(int i){
    if(computeContourFinder){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == i){
                return _osc_blobInfo[e].center.x;
            }
        }
    }else{
        return 0.0;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobY(int i){
    if(computeContourFinder){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == i){
                return _osc_blobInfo[e].center.y;
            }
        }
    }else{
        return 0.0;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobW(int i){
    if(computeContourFinder){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == i){
                return _osc_blobInfo[e].size.width;
            }
        }
    }else{
        return 0.0;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobH(int i){
    if(computeContourFinder){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == i){
                return _osc_blobInfo[e].size.height;
            }
        }
    }else{
        return 0.0;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobAngle(int i){
    if(computeContourFinder){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == i){
                return _osc_blobInfo[e].angle;
            }
        }
    }else{
        return 0.0;
    }
}

//--------------------------------------------------------------
int gaSourceTracking::getBlobContourSize(int i){
    if(computeContourFinder){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == i){
                if(cfDetail == 0 || cfDetail == 1){
                    return contourSmooth[e].size();
                }else if(cfDetail == 2){
                    return contourSimple[e].size();
                }
            }
        }
    }else{
        return 0;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobCPointX(int blob,int i){
    if(computeContourFinder){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == blob){
                if(cfDetail == 0 || cfDetail == 1){
                    if(i < contourSmooth[e].size()){
                        return contourSmooth[e].at(i).x;
                    }else{
                        return 0.0;
                    }
                }else if(cfDetail == 2){
                    if(i < contourSimple[e].size()){
                        return contourSimple[e].at(i).x;
                    }else{
                        return 0.0;
                    }
                }
            }
        }
    }else{
        return 0.0;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobCPointY(int blob,int i){
    if(computeContourFinder){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == blob){
                if(cfDetail == 0 || cfDetail == 1){
                    if(i < contourSmooth[e].size()){
                        return contourSmooth[e].at(i).y;
                    }else{
                        return 0.0;
                    }
                }else if(cfDetail == 2){
                    if(i < contourSimple[e].size()){
                        return contourSimple[e].at(i).y;
                    }else{
                        return 0.0;
                    }
                }
            }
        }
    }else{
        return 0.0;
    }
}

//--------------------------------------------------------------
int gaSourceTracking::getBlobGeometrySize(int i){
    if(computeContourFinder && computeContourGeometry){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == i){
                return geomLines[e].size();
            }
        }
    }else{
        return 0;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobGLineX1(int blob,int i){
    if(computeContourFinder && computeContourGeometry){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == blob && i < _osc_blobGeom[e].size()){
                return geomLines[e].at(i).x;
            }
        }
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobGLineY1(int blob,int i){
    if(computeContourFinder && computeContourGeometry){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == blob && i < _osc_blobGeom[e].size()){
                return geomLines[e].at(i).y;
            }
        }
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobGLineX2(int blob,int i){
    if(computeContourFinder && computeContourGeometry){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == blob && i < _osc_blobGeom[e].size()){
                return geomLines[e].at(i).z;
            }
        }
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getBlobGLineY2(int blob,int i){
    if(computeContourFinder && computeContourGeometry){
        for(unsigned int e = 0; e < runningBlobs; e++){
            if(blobsOrder[e] == blob && i < _osc_blobGeom[e].size()){
                return geomLines[e].at(i).w;
            }
        }
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getOpticalFlowX(int i){
    if(computeOpticalFlow){
        return _osc_opfVel[i].x;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getOpticalFlowY(int i){
    if(computeOpticalFlow){
        return _osc_opfVel[i].y;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getOpticalFlowVX(int i){
    if(computeOpticalFlow){
        return _osc_opfVel[i].z;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getOpticalFlowVY(int i){
    if(computeOpticalFlow){
        return _osc_opfVel[i].w;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
int gaSourceTracking::getNumHaars(){
    if(computeHaarFinder){
		return numFace;
	}else{
		return 0;
	}
}

//--------------------------------------------------------------
float gaSourceTracking::getHaarX(int i){
    if(i < numFace && computeHaarFinder){
        return _osc_ftInfo[i].x;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getHaarY(int i){
    if(i < numFace && computeHaarFinder){
        return _osc_ftInfo[i].y;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getHaarW(int i){
    if(i < numFace && computeHaarFinder){
        return _osc_ftInfo[i].z;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaSourceTracking::getHaarH(int i){
    if(i < numFace && computeHaarFinder){
        return _osc_ftInfo[i].w;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
bool  gaSourceTracking::getTrigger(int i){
    if(computeContourFinder && computeTriggerAreas){
        return triggerState[i];
    }else{
        return -1;
    }
}

//--------------------------------------------------------------
void gaSourceTracking::mouseDragged(int x, int y){
	
	triggerAreas.mouseDragged(x, y);
	// input source quad control
	sourceFrame.mouseDragged(x, y);
    
    gui.mouseDragged(x, y, 0);
	
}

//--------------------------------------------------------------
void gaSourceTracking::mousePressed(int x, int y){
	
	triggerAreas.mousePressed(x, y);
	// input source quad control
	sourceFrame.mousePressed(x, y);
    
    gui.mousePressed(x, y, 0);
    
    if(gui.saveDown){
        saveAllSettings = true;
    }
	
}

//--------------------------------------------------------------
void gaSourceTracking::mouseReleased(int x, int y){
	
	// trigger areas control
	triggerAreas.mouseReleased(x,y);
	// input source quad control
	sourceFrame.mouseReleased(x,y);
    
    gui.mouseReleased();
	
}

//--------------------------------------------------------------
void gaSourceTracking::loadCalibration(){
	
	ofxXmlSettings xml;
	char temp[128];
	sprintf(temp,"settings/cams/calibration_id_%i.xml",_devID);
	xml.loadFile(temp);
	
	un_radialX		= xml.getValue("un_radialX", 0.0f);
	un_radialY		= xml.getValue("un_radialY", 0.0f);
	un_tangentX		= xml.getValue("un_tangentX", 0.0f);
	un_tangentY		= xml.getValue("un_tangentY", 0.0f);
	un_focusX		= xml.getValue("un_focusX", 0.0f);
	un_focusY		= xml.getValue("un_focusY", 0.0f);
	un_centerX		= xml.getValue("un_centerX", 0.0f);
	un_centerY		= xml.getValue("un_centerY", 0.0f);
}

//--------------------------------------------------------------
void gaSourceTracking::getQuadSubImage(unsigned char* inputData,unsigned char* outputData,int inW,int inH,int outW,int outH,ofPoint *quad,int bpp){
	
	for(int x=0;x<outW;x++) {
		for(int y=0;y<outH;y++) {
			float xlrp = x/(float)outW;
			float ylrp = y/(float)outH;
			int xinput = (quad[0].x*(1-xlrp)+quad[1].x*xlrp)*(1-ylrp) + (quad[3].x*(1-xlrp)+quad[2].x*xlrp)*ylrp;
			int yinput = (quad[0].y*(1-ylrp)+quad[3].y*ylrp)*(1-xlrp) + (quad[1].y*(1-ylrp)+quad[2].y*ylrp)*xlrp;
			int inIndex = (xinput + yinput*inW)*bpp;
			int outIndex = (x+y*outW)*bpp;
			memcpy((void*)(outputData+outIndex),(void*)(inputData+inIndex),sizeof(unsigned char)*bpp);
		}
	}
	
}

//--------------------------------------------------------------
void gaSourceTracking::calculateColorDifference(){
	
	int bpp = 3;
	pixels1 = colorImgWarped.getPixels();
	pixels2 = colorBg.getPixels();
	bool pixelDiff;
	
	for(unsigned int i=0; i < _height; i++){
		for(unsigned int j=0; j < _width; j++){
			pixelDiff = false;
			
			for(unsigned int b=0; b < bpp; b++){
				int diff = pixels1[(i*_width+j)*bpp+b] - pixels2[(i*_width+j)*bpp+b];
				diff = (diff < 0)?-diff:diff;
				if(diff > (int)threshold){
					pixelDiff = true;
					break;
				}
			}
			resPixels[i*_width+j] = (pixelDiff)?255:0;
		}
	}
	colorDiff.setFromPixels(resPixels, _width, _height);
	
	colorDiff.erode(bgSubErode);
	colorDiff.dilate(bgSubDilate);
	colorDiff.blur(bgSubBlur);
	
}

//--------------------------------------------------------------
void gaSourceTracking::calculateGrayscaleDifference(){
	
	if(bgSubTech == 1){ // abs difference
		grayThresh = grayImg;
		grayThresh.absDiff(grayBg);
	}else if(bgSubTech == 2){ // lighter than
		grayThresh = grayImg;
		grayThresh -= grayBg;
	}else if(bgSubTech == 3){ // darker than
		grayThresh = grayBg;
		grayThresh -= grayImg;
	}
	
	if(bgUseContrastStrech){
		grayThresh.contrastStretch();
	}
	
	grayThresh.threshold(threshold);
	
	grayThresh.erode(bgSubErode);
	grayThresh.dilate(bgSubDilate);
	grayThresh.blur(bgSubBlur);
}

//--------------------------------------------------------------
void gaSourceTracking::calculateColorDifferenceHSV(){
	
	//Calculate min and max thersholds values
	minHue = max((hue - hueWidth*0.5) * 255, 0.0);
	maxHue = min((hue + hueWidth*0.5) * 255, 255.0);
	minSat = max((sat - satWidth*0.5) * 255, 0.0);
	maxSat = min((sat + satWidth*0.5) * 255, 255.0);
	minVal = max((val - valWidth*0.5) * 255, 0.0);
	maxVal = min((val + valWidth*0.5) * 255, 255.0);
	
	// HSV
	colorImgHSV = colorImgWarped;
	colorImgHSV.convertRgbToHsv();
	colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, valImg);
	
	// Perform tracking calculations
	huePixels = hueImg.getPixels();
	satPixels = satImg.getPixels();
	valPixels = valImg.getPixels();
	
	for (unsigned int i = 0; i < _numPixels; i++){
		if((huePixels[i] >= minHue && huePixels[i] <= maxHue) &&
		   (satPixels[i] >= minSat && satPixels[i] <= maxSat) &&
		   (valPixels[i] >= minVal && valPixels[i] <= maxVal)){
			hsvTrackedPixels[i] = 255;
		}else{
			hsvTrackedPixels[i] = 0;
		}
	}
	
	hsvTracking.setFromPixels(hsvTrackedPixels, _width, _height);
	
	hsvTracking.erode(hsvErode);
	hsvTracking.dilate(hsvDilate);
	hsvTracking.blur(hsvBlur);
	
}

//--------------------------------------------------------------
void gaSourceTracking::balanceTracking(){
	
	if(bgSubTech == 0){
		alg1 = colorDiff.getPixels();
	}else{
		alg1 = grayThresh.getPixels();
	}
	
	if(useHsvTracking){
		alg2 = hsvTracking.getPixels();
	}else{
		alg2 = blackPixels;
	}
	
	for (unsigned int i = 0; i < _numPixels; i++){
        balPixels[i] = (int)(alg1[i]+alg2[i])/2;
        if(balPixels[i] >= 255){
            balPixels[i] = 255; 
        }
	}
	
	balancedTracking.setFromPixels(balPixels, _width, _height);
	
	balancedTracking.erode(btErode);
	balancedTracking.dilate(btDilate);
	balancedTracking.blur(btBlur);
	
}

//--------------------------------------------------------------
void gaSourceTracking::calculateMotion(){
	
	if(frameCounter > 5){// dont do anything until we have enough in history
		
		grayNow = balancedTracking;
		
		if(computeOpticalFlow){
			opticalFlow.calc(grayPrev,grayNow,11); // optical flow analysis based on frame difference
			cvSmooth(opticalFlow.getVelX(), opticalFlow.getVelX(), CV_BLUR , CAM_VELOCITY_BLUR);
			cvSmooth(opticalFlow.getVelY(), opticalFlow.getVelY(), CV_BLUR , CAM_VELOCITY_BLUR);
		}
		
		motionImg.absDiff(grayPrev, grayNow);   // motionImg is the difference between current and previous frame
		cvThreshold(motionImg.getCvImage(), motionImg.getCvImage(), (int)mThreshold, 255, CV_THRESH_TOZERO); // anything below mThreshold, drop to zero (compensate for noise)
		numPixelsChanged = motionImg.countNonZeroInRegion(0, 0, _width, _height); // this is how many pixels have changed that are above mThreshold
		
		if(numPixelsChanged >= (int)mNoiseComp){ // noise compensation
			grayPrev = grayNow; // save current frame for next loop
			
			cvThreshold(motionImg.getCvImage(), motionImg.getCvImage(), (int)mThreshold, 255, CV_THRESH_TOZERO);// chop dark areas
			
		}else{
			motionImg.setFromPixels(blackPixels, _width, _height);
		}
		
		motion = motionImg.getPixels();
		
		// Calculate the general "mood" of the scene
		mood = averageBnWVal(motionImg.getCvImage());
		
		//////////////////////////////////////////////////
		// get upper and lower middle points from motion detection
		for(unsigned int i = 0; i < _numPixels; i++){
			if (motion[i] > (int)mThreshold){
				mCY = (int)i/_width;//y position from [i] position in image vector
				mCX = i - mCY*_width;// x position from [i] position in image vector
			}
		}
		for(unsigned int i = _numPixels - 1; i > 0; i--){
			if (motion[i] > (int)mThreshold){
				mCY2 = (int)i/_width;//y position from [i] position in image vector
				mCX2 = i - mCY2*_width;// x position from [i] position in image vector
			}
		}
		
		MDCM.x = (mCX+mCX2)/2.0f;
		MDCM.y = (mCY+mCY2)/2.0f;
		//////////////////////////////////////////////////
		
		for(unsigned int i = 0; i < _numPixels; i++){
			if(motion[i] == 0){
				motion[i] = grayImgPixels[i];
			}
		}
		
		motionGUI.setFromPixels(motion, _width, _height);
		
		
	}else{
		frameCounter++;
	}
	
}

//--------------------------------------------------------------
void gaSourceTracking::computeContourAnalysis(){
	
	for (unsigned int i = 0; i < contourFinder.nBlobs; i++){
		
		int length_of_contour = contourFinder.blobs[i].pts.size();
		
		// ellipse
		fitEllipse(contourFinder.blobs[i].pts, box[i]);
		
		// angles
		blobAngle[i] =  getOrientation(contourFinder.blobs[i].pts);
		
		// assign smoothed and normalized blobs geometry vectors vars
		if(computeContourGeometry){
			
			findLines(contourFinder.blobs[i].pts,geomLines[i],30,40,30);
		
			_s_blobGeom[i].clear();
			_s_blobGeom[i].assign(geomLines[i].size(), ofVec4f());
			_osc_blobGeom[i].clear();
			_osc_blobGeom[i].assign(geomLines[i].size(), ofVec4f());

		}
		
		// smoothed, simple and convexHull contours computing
		contourReg[i].clear();
		contourReg[i].assign(length_of_contour, ofVec2f());
		contourSmooth[i].clear();
		contourSmooth[i].assign(length_of_contour, ofVec2f());
		
		_s_contourSmooth[i].clear();
		_s_contourSmooth[i].assign(length_of_contour, ofVec2f());
		_osc_contourSmooth[i].clear();
		_osc_contourSmooth[i].assign(length_of_contour, ofVec2f());
		
		
		for(int j = 0; j < length_of_contour; j++){
			contourReg[i].at(j) = contourFinder.blobs[i].pts[j];
		}
		
		contourS.smooth(contourReg[i], contourSmooth[i], smoothPct);
		
		contourSimple[i].clear();
		contourS.simplify(contourSmooth[i], contourSimple[i], tolerance);
		
		_s_contourSimple[i].clear();
		_s_contourSimple[i].assign(contourSimple[i].size(), ofVec2f());
		_osc_contourSimple[i].clear();
		_osc_contourSimple[i].assign(contourSimple[i].size(), ofVec2f());
		
	}
}

//--------------------------------------------------------------
void gaSourceTracking::drawMotionCentroid(){
	
	glPushMatrix();
	glTranslatef(30, 378, 0);
	glScalef(160.0f/_width, 120.0f/_height, 1.0);
	
	ofEnableAlphaBlending();
	
	ofNoFill();
	glColor4f(0.847,0.25,0.25,0.7);
	
	ofRect(_s_MDCM.x - 10, _s_MDCM.y - 10, 20, 20);
	ofRect(_s_MDCM.x - 20, _s_MDCM.y - 20, 40, 40);
	
	ofLine(_s_MDCM.x - 26, _s_MDCM.y,_s_MDCM.x + 26, _s_MDCM.y);
	ofLine(_s_MDCM.x, _s_MDCM.y - 26,_s_MDCM.x, _s_MDCM.y + 26);
	
	ofFill();
	glColor4f(0.847,0.25,0.25,_osc_MDQ*2.0);
	ofRect(_s_MDCM.x - 20, _s_MDCM.y - 20, 40, 40);
	
	ofDisableAlphaBlending();
	
	glPopMatrix();
	
}

//--------------------------------------------------------------
void gaSourceTracking::drawContourAnalysis(){
	
	string temp;
	
	glPushMatrix();
	glTranslatef(286, 90, 0);
	ofEnableAlphaBlending();
	
	ofFill();
	
    // blob ID
	for(unsigned int i = 0; i < blobTracker.blobs.size(); i++){
		ostringstream docstring;
		docstring << blobTracker.findOrder(blobTracker.blobs[i]._id) << endl;
		temp = docstring.str();
		blobsOrder[i] = atoi(temp.c_str());
		
		glColor4f(0.0,1.0,0.0,1.0);
		if(temp != ""){
			ofDrawBitmapString(temp,(_s_blobInfo[i].center.x + _s_blobInfo[i].size.width/2.0)*240/_width,(_s_blobInfo[i].center.y + _s_blobInfo[i].size.height/2.0)*180/_height);
		}
	}
    
    // blobs area
    glScalef(240.0f/_width, 180.0f/_height, 1.0);
    for(unsigned int i = 0; i < contourFinder.nBlobs; i++){
		glColor4f(0.847,0.25,0.25,0.4);
		ofRect(contourFinder.blobs[i].boundingRect.x,contourFinder.blobs[i].boundingRect.y,contourFinder.blobs[i].boundingRect.width,contourFinder.blobs[i].boundingRect.height);
	}
	
	glColor4f(1.0,1.0,1.0,1.0);
	
	for (unsigned int i = 0; i < contourFinder.nBlobs; i++){
		
		//-------------------  draw the contours
		if(cfDetail == 0){
			glColor4f(0.847,0.25,0.25,1.0);
			ofNoFill();
			drawBlob(0,0,contourFinder.blobs[i]);
		}else if(cfDetail == 1){
			glColor4f(0.847,0.25,0.25,1.0);
			ofNoFill();
			ofBeginShape();
			for(unsigned int j = 0; j < contourSmooth[i].size(); j++){
				ofVertex(contourSmooth[i].at(j).x, contourSmooth[i].at(j).y);
			}
			ofEndShape(true);
		}else if(cfDetail == 2){
			glColor4f(0.847,0.25,0.25,1.0);
			ofNoFill();
			ofBeginShape();
			for(unsigned int k = 0; k < contourSimple[i].size(); k++){
				ofVertex(contourSimple[i].at(k).x, contourSimple[i].at(k).y);
			}
			ofEndShape(true);
		}
		//------------------- fit angle of orientation
		glColor4f(1.0,0.906,0.463,1.0);
			
		float x1,y1,x2,y2;
			
		x1 = contourFinder.blobs[i].centroid.x + 25 * cos(blobAngle[i]);
		y1 = contourFinder.blobs[i].centroid.y + 25 * sin(blobAngle[i]);
		x2 = contourFinder.blobs[i].centroid.x - 25 * cos(blobAngle[i]);
		y2 = contourFinder.blobs[i].centroid.y - 25 * sin(blobAngle[i]);
			
		glPushMatrix();
			glScalef(0.5,0.5,0.0);
			ofLine(x1*2,y1*2,x2*2,y2*2);
		glPopMatrix();
			
		x1 = contourFinder.blobs[i].centroid.x + 10 * cos(blobAngle[i]+HALF_PI);
		y1 = contourFinder.blobs[i].centroid.y + 10 * sin(blobAngle[i]+HALF_PI);
		x2 = contourFinder.blobs[i].centroid.x - 10 * cos(blobAngle[i]+HALF_PI);
		y2 = contourFinder.blobs[i].centroid.y - 10 * sin(blobAngle[i]+HALF_PI);
		
		glPushMatrix();
			glScalef(0.5,0.5,0.0);
			ofLine(x1*2,y1*2,x2*2,y2*2);
		glPopMatrix();
		//------------------- fit geometry lines on countour
		if(computeContourGeometry){
			glColor4f(0.1,1.0,0.0,0.8);
			ofNoFill();
			for(unsigned int j = 0; j < geomLines[i].size(); j++){
				ofLine(geomLines[i].at(j).x,geomLines[i].at(j).y,geomLines[i].at(j).z,geomLines[i].at(j).w);
				ofCircle(geomLines[i].at(j).x,geomLines[i].at(j).y,3);
				ofCircle(geomLines[i].at(j).z,geomLines[i].at(j).w,3);
			}
		}
	}
	
	glPopMatrix();
	
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void gaSourceTracking::drawHaarFinder(){
	
	glPushMatrix();
	glTranslatef(286, 83, 0);
    //glScalef(240.0f/_width, 180.0f/_height, 1.0);
	for(unsigned int i = 0; i < numFace; i++){
		float x = _s_ftInfo[i].x;
		float y = _s_ftInfo[i].y;
		float w = _s_ftInfo[i].z;
		float h = _s_ftInfo[i].w;
		
		ofNoFill();
		glColor4f(1.0,0.906,0.463,1.0);
		ofRect(x, y, w, h);
	}
	glPopMatrix();
	
}

//--------------------------------------------------------------
void gaSourceTracking::blobOn( int x, int y, int id, int order ){
	
	char updateMSG[100];
	
	int insideArea = 1;
    //cout << "blobOn() - id:" << id << " order:" << order << endl;
    float scaledX = (float) ((userOffsetX+x)-topLeftX) / (float)(lowRightX-topLeftX);
    float scaledY = (float) ((userOffsetY+y)-topLeftY) / (float)(lowRightY-topLeftY);
	
	
	if (scaledX < 0){ scaledX = 0; insideArea = 0;}
	if (scaledY < 0){ scaledY = 0; insideArea = 0;}
	if (scaledX > 1){ scaledX = 1; insideArea = 0;}
	if (scaledY > 1){ scaledY = 1; insideArea = 0;}
	if (insideArea){
		// A new user has appeared inside the area, therefore he's joined.
		//sprintf(updateMSG, "%d|%d|%f|%f|%f|%f\n", USER_JOINED, order, scaledX, scaledY,0.0, 0.0);
		//printf(updateMSG);
		
		usersTracking[order] = B_ALIVE_IN_AREA;
	}else{
		// A new user has appeared outside the play area. S/He's not reported as joining, but
		// taken into account when s/he walks inside the play area.
		usersTracking[order] = B_ALIVE_OUT_AREA;
	}
	
}

//--------------------------------------------------------------
void gaSourceTracking::blobMoved( int x, int y, int id, int order){
	
	char updateMSG[100];
	int insideArea = 1;
    //cout << "blobMoved() - id:" << id << " order:" << order << endl;
	
    // full access to blob object ( get a reference)
    //ofxCvTrackedBlob blob = blobTracker.getById( id );
    //cout << "area: " << blob.area << endl;
	float scaledX = (float) ((userOffsetX+x)-topLeftX) / (float)(lowRightX-topLeftX);
    float scaledY = (float) ((userOffsetY+y)-topLeftY) / (float)(lowRightY-topLeftY);
	
	
	if(scaledX < 0){ scaledX = 0; insideArea = 0;}
	if(scaledY < 0){ scaledY = 0; insideArea = 0;}
	if(scaledX > 1){ scaledX = 1; insideArea = 0;}
	if(scaledY > 1){ scaledY = 1; insideArea = 0;}
	
	if(insideArea){
		if (usersTracking[order] == B_ALIVE_IN_AREA){
			// The user is moving inside the area
			//sprintf(updateMSG, "%d|%d|%f|%f|%f|%f\n", USER_MOVED, order, scaledX, scaledY,0.0, 0.0);
			//printf(updateMSG);
			
		}else{
			// The user was outside the play area, but now came inside and therefore joined.
			usersTracking[order] = B_ALIVE_IN_AREA;
			//sprintf(updateMSG, "%d|%d|%f|%f|%f|%f\n", USER_JOINED, order, scaledX, scaledY,0.0, 0.0);
			//printf(updateMSG);
			
		}
		
	}else{
		if(usersTracking[order] == B_ALIVE_IN_AREA){
			// The user was inside the play area but has left
			//sprintf(updateMSG,"%d|%d|%f|%f|%f|%f\n", USER_LEFT, order, scaledX, scaledY,0.0, 0.0);
			//printf(updateMSG);
		}
		usersTracking[order] = B_ALIVE_OUT_AREA;
	}
}

//--------------------------------------------------------------
void gaSourceTracking::blobOff( int x, int y, int id, int order ){
	
	char updateMSG[100];
    //cout << "blobOff() - id:" << id << " order:" << order << endl;
    float scaledX = (float) ((userOffsetX+x)-topLeftX) / (float)(lowRightX-topLeftX);
    float scaledY = (float) ((userOffsetY+y)-topLeftY) / (float)(lowRightY-topLeftY);
	
	// Is this blob alive and inside the play area?
	// Then send the notification. Do not send notification otherwise..
	if (usersTracking[order] == B_ALIVE_IN_AREA)
	{
		if (scaledX < 0) scaledX = 0;
		if (scaledY < 0) scaledY = 0;
		if (scaledX > 1) scaledX = 1;
		if (scaledY > 1) scaledY = 1;
		
	}
	// mark blob as dead
	usersTracking[order] = B_DEAD;
}

//--------------------------------------------------------------
// Average black and white value calcualtion (used for "mood detection")
float gaSourceTracking::averageBnWVal(IplImage * img){
	
	int px = 0;
	int max = img->imageSize;
	float value = 0;
	
	for (px = 0; px < max; px++)
	{
		value += (float)img->imageData[px];
	}
	return value/(max*100.0);
	
}

//--------------------------------------------------------------
void gaSourceTracking::getVelAtPixel(int x, int y, float *u, float *v) {
	*u = cvGetReal2D( opticalFlow.getVelX(), y, x );
	*v = cvGetReal2D( opticalFlow.getVelY(), y, x );
}

//--------------------------------------------------------------
void gaSourceTracking::getVelAtNorm(float x, float y, float *u, float *v) {
	int ix = x * _width;
	int iy = y * _height;
	if(ix<0) ix = 0; else if(ix>=_width) ix = _width - 1;
	if(iy<0) iy = 0; else if(iy>=_height) iy = _height - 1;
	*u = cvGetReal2D( opticalFlow.getVelX(), iy, ix );
	*v = cvGetReal2D( opticalFlow.getVelY(), iy, ix );
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// In a race, the quickest runner can never overtake the slowest,
// since the pursuer must first reach the point whence the pursued started,
// so that the slower must always hold a lead.
//
//--------------------------------------------------------------
void gaSourceTracking::smoothingValues(){
	
	// motion detection centers coords.
	_s_MDCM.x = _s_MDCM.x*_smoothingFactor + (1.0-_smoothingFactor)*MDCM.x;
 	_s_MDCM.y = _s_MDCM.y*_smoothingFactor + (1.0-_smoothingFactor)*MDCM.y;
	
	// motion quantity
	_s_MDQ = _s_MDQ*_smoothingFactor + (1.0-_smoothingFactor)*numPixelsChanged;
	
	// blobs tracking from contour finder
	if(computeContourFinder){
		for(unsigned int b=0;b<contourFinder.nBlobs;b++){
			// blobs data
			_s_blobInfo[b].center.x		= _s_blobInfo[b].center.x*_smoothingFactor + (1.0-_smoothingFactor)*blobTracker.blobs[b].boundingRect.x;
			_s_blobInfo[b].center.y		= _s_blobInfo[b].center.y*_smoothingFactor + (1.0-_smoothingFactor)*blobTracker.blobs[b].boundingRect.y;
			_s_blobInfo[b].angle		= _s_blobInfo[b].angle*_smoothingFactor + (1.0-_smoothingFactor)*box[b].angle;
			_s_blobInfo[b].size.width	= _s_blobInfo[b].size.width*_smoothingFactor + (1.0-_smoothingFactor)*blobTracker.blobs[b].boundingRect.width;
			_s_blobInfo[b].size.height	= _s_blobInfo[b].size.height*_smoothingFactor + (1.0-_smoothingFactor)*blobTracker.blobs[b].boundingRect.height;
			// blob smoohContour points
			for(unsigned int j = 0; j < contourSmooth[b].size(); j++){
				_s_contourSmooth[b].at(j).x = _s_contourSmooth[b].at(j).x*_smoothingFactor + (1.0 - _smoothingFactor)*contourSmooth[b].at(j).x;
				_s_contourSmooth[b].at(j).y = _s_contourSmooth[b].at(j).y*_smoothingFactor + (1.0 - _smoothingFactor)*contourSmooth[b].at(j).y;
			}
			// blob simpleContour (redux) points
			for(unsigned int j = 0; j < contourSimple[b].size(); j++){
				_s_contourSimple[b].at(j).x = _s_contourSimple[b].at(j).x*_smoothingFactor + (1.0 - _smoothingFactor)*contourSimple[b].at(j).x;
				_s_contourSimple[b].at(j).y = _s_contourSimple[b].at(j).y*_smoothingFactor + (1.0 - _smoothingFactor)*contourSimple[b].at(j).y;
			}
		}
	}
	
	
	if(computeContourFinder && computeContourGeometry){
		for(unsigned int b=0;b<contourFinder.nBlobs;b++){
			for(unsigned int g = 0; g < geomLines[b].size(); g++){
				_s_blobGeom[b].at(g).x = _s_blobGeom[b].at(g).x*_smoothingFactor + (1.0-_smoothingFactor)*geomLines[b].at(g).x;
				_s_blobGeom[b].at(g).y = _s_blobGeom[b].at(g).y*_smoothingFactor + (1.0-_smoothingFactor)*geomLines[b].at(g).y;
				_s_blobGeom[b].at(g).z = _s_blobGeom[b].at(g).z*_smoothingFactor + (1.0-_smoothingFactor)*geomLines[b].at(g).z;
				_s_blobGeom[b].at(g).w = _s_blobGeom[b].at(g).w*_smoothingFactor + (1.0-_smoothingFactor)*geomLines[b].at(g).w;
			}
		}
	}
	
	// optical flow pixels velocity
	if(computeOpticalFlow){
        unsigned int oo=0;
        for (unsigned int y = 0; y < _height; y += OPTICAL_FLOW_ROWS_STEP ){
            for (unsigned int x = 0; x < _width; x += OPTICAL_FLOW_COLS_STEP ){
                _s_opfVel[oo].x = opticalFlow.velArray[oo].x;
                _s_opfVel[oo].y = opticalFlow.velArray[oo].y;
                _s_opfVel[oo].z = _s_opfVel[oo].z*_smoothingFactor + (1.0-_smoothingFactor)*opticalFlow.velArray[oo].z;
                _s_opfVel[oo].w = _s_opfVel[oo].w*_smoothingFactor + (1.0-_smoothingFactor)*opticalFlow.velArray[oo].w;
                
                oo++;
                
            }
        }
    }
	
	// face tracking blobs positions
	if(computeHaarFinder){
		for(unsigned int f = 0; f < numFace; f++){
			_s_ftInfo[f].x = _s_ftInfo[f].x*_smoothingFactor + (1.0-_smoothingFactor)*haarFinder.blobs[f].boundingRect.x;
			_s_ftInfo[f].y = _s_ftInfo[f].y*_smoothingFactor + (1.0-_smoothingFactor)*haarFinder.blobs[f].boundingRect.y;
			_s_ftInfo[f].z = _s_ftInfo[f].z*_smoothingFactor + (1.0-_smoothingFactor)*haarFinder.blobs[f].boundingRect.width;
			_s_ftInfo[f].w = _s_ftInfo[f].w*_smoothingFactor + (1.0-_smoothingFactor)*haarFinder.blobs[f].boundingRect.height;
		}
	}
	
}
//
//—Aristotle, Physics VI:9, 239b15
// http://en.wikipedia.org/wiki/Zeno%27s_paradoxes#Achilles_and_the_tortoise
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------
void gaSourceTracking::normalizeValues(){
	
	// motion detection center coords.
	_osc_MDCM.x = ofNormalize(_s_MDCM.x,0.0f,(float)_width);
	_osc_MDCM.y = ofNormalize(_s_MDCM.y,0.0f,(float)_height);
	
	// motion quantity
	_osc_MDQ = ofNormalize(_s_MDQ,mNoiseComp,_numPixels);
	
	// blobs tracking from contour finder
	if(computeContourFinder){
		// blobs data
		for(unsigned int b=0;b<contourFinder.nBlobs;b++){
			_osc_blobInfo[b].center.x = ofNormalize(_s_blobInfo[b].center.x,0.0f,(float)_width);
			_osc_blobInfo[b].center.y = ofNormalize(_s_blobInfo[b].center.y,0.0f,(float)_height);
			_osc_blobInfo[b].angle = ofNormalize(_s_blobInfo[b].angle,0.0f,360.0f);
			_osc_blobInfo[b].size.width = ofNormalize(_s_blobInfo[b].size.width,0.0f,(float)_width);
			_osc_blobInfo[b].size.height = ofNormalize(_s_blobInfo[b].size.height,0.0f,(float)_height);
			// blob smoohContour points
			for(unsigned int j = 0; j < contourSmooth[b].size(); j++){
				_osc_contourSmooth[b].at(j).x = ofNormalize(_s_contourSmooth[b].at(j).x, 0.0f, (float)_width);
				_osc_contourSmooth[b].at(j).y = ofNormalize(_s_contourSmooth[b].at(j).y, 0.0f, (float)_height);
			}
			// blob simpleContour (redux) points
			for(unsigned int j = 0; j < contourSimple[b].size(); j++){
				_osc_contourSimple[b].at(j).x = ofNormalize(_s_contourSimple[b].at(j).x, 0.0f, (float)_width);
				_osc_contourSimple[b].at(j).y = ofNormalize(_s_contourSimple[b].at(j).y, 0.0f, (float)_height);
			}
		}
	}
	
	// contour geometry from contour finder
	if(computeContourFinder && computeContourGeometry){
		for(unsigned int b=0;b<contourFinder.nBlobs;b++){
			for(unsigned int g = 0; g < geomLines[b].size(); g++){
				_osc_blobGeom[b].at(g).x = ofNormalize(_s_blobGeom[b].at(g).x,0.0f,(float)_width);
				_osc_blobGeom[b].at(g).y = ofNormalize(_s_blobGeom[b].at(g).y,0.0f,(float)_height);
				_osc_blobGeom[b].at(g).z = ofNormalize(_s_blobGeom[b].at(g).z,0.0f,(float)_width);
				_osc_blobGeom[b].at(g).w = ofNormalize(_s_blobGeom[b].at(g).w,0.0f,(float)_height);
			}
		}
	}
	
	// optical flow pixels velocity
	if(computeOpticalFlow){
        unsigned int oo=0;
        for (unsigned int y = 0; y < _height; y += OPTICAL_FLOW_ROWS_STEP ){
            for (unsigned int x = 0; x < _width; x += OPTICAL_FLOW_COLS_STEP ){
                _osc_opfVel[oo].x = _s_opfVel[oo].x;
                _osc_opfVel[oo].y = _s_opfVel[oo].y;
                _osc_opfVel[oo].z = _s_opfVel[oo].z;
                _osc_opfVel[oo].w = _s_opfVel[oo].w;
                oo++;
            }
        }
	}
	
	// face tracking blobs positions
	if(computeHaarFinder){
		for(unsigned int f = 0; f < numFace; f++){
			_osc_ftInfo[f].x = ofNormalize(_s_ftInfo[f].x,0.0f,(float)_width);
			_osc_ftInfo[f].y = ofNormalize(_s_ftInfo[f].y,0.0f,(float)_height);
			_osc_ftInfo[f].z = ofNormalize(_s_ftInfo[f].z,0.0f,(float)_width);
			_osc_ftInfo[f].w = ofNormalize(_s_ftInfo[f].w,0.0f,(float)_height);
		}
	}
	
}
