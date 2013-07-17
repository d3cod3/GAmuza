#include "gaKinectTracking.h"


//--------------------------------------------------------------
gaKinectTracking::gaKinectTracking(){
	fontSmall.loadFont("fonts/D3Litebitmapism.ttf", 8, true, true);
    _empty.loadImage("img/empty.png");
    guiSettingsFile = "guiSettings.xml";
    
    gamuzaMainColor         = simpleColor(9,147,211,255);
	gamuzaWhiteColor        = simpleColor(240,240,240,255);
	gamuzaMarkColor         = simpleColor(255,231,118,255);
    gamuzaChartBackColor    = simpleColor(40, 40, 40, 255);
}

//--------------------------------------------------------------
gaKinectTracking::~gaKinectTracking(){
	
}

//--------------------------------------------------------------
void gaKinectTracking::setup(int _id, bool _ir, bool videoImage, int _ledState){
    setupDevice(_id, _ir, videoImage, _ledState);
}

//--------------------------------------------------------------
void gaKinectTracking::update(){
    updateDevice();
}

//--------------------------------------------------------------
void gaKinectTracking::draw(){
    drawDevice();
}

//--------------------------------------------------------------
void gaKinectTracking::close(){
    kinect.setCameraTiltAngle(0);
	kinect.close();
}

//--------------------------------------------------------------
void gaKinectTracking::setupDevice(int _id, bool _ir, bool videoImage, int _ledState){
    
    //////////////////////////////////////////////
    // kinect setup
    kinect.setRegistration(true);
	kinect.init(_ir,videoImage);
    kinect.open(_id);
	
	_width	= kinect.getWidth();
	_height = kinect.getHeight();
    devID   = _id;
    
    nearThreshold = 230;
	farThreshold = 70;
    bDrawPointCloud = false;
    tiltAngle = 0;
	kinect.setCameraTiltAngle(tiltAngle);
    
    switch (_ledState) {
        case -1:
            kinect.setLed(ofxKinect::LED_DEFAULT);
            break;
        case 0:
            kinect.setLed(ofxKinect::LED_OFF);
            break;
        case 1:
            kinect.setLed(ofxKinect::LED_GREEN);
            break;
        case 2:
            kinect.setLed(ofxKinect::LED_RED);
            break;
        case 3:
            kinect.setLed(ofxKinect::LED_YELLOW);
            break;
        case 4:
            kinect.setLed(ofxKinect::LED_BLINK_GREEN);
            break;
        case 6:
            kinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
            break;
        default:
            break;
    }
    
    //////////////////////////////////////////////
    // hardware sensors
    _s_hAccel       = new ofVec3f(0,0,0);
    _osc_hAccel       = new ofVec3f(0,0,0);
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // opencv setup
    cleanImage.allocate(_width, _height);
    grayThreshNear.allocate(_width, _height);
    grayThreshFar.allocate(_width, _height);
    
    //////////////////////////////////////////////
    // set motion detection vars
    grayPrev.allocate(_width,_height);
    grayNow.allocate(_width,_height);
    motionImg.allocate(_width,_height);
    
    frameCounter	 = 0;
    numPixelsChanged = 0;
    mThreshold		 = 0;
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
    opticalFlow.allocate(_width,_height);
    opticalFlowXGrid = (int)(_width/OPTICAL_FLOW_COLS_STEP);
    opticalFlowYGrid = (int)(_height/OPTICAL_FLOW_ROWS_STEP);
    
    _s_opfVel		= new ofVec4f[opticalFlowXGrid*opticalFlowYGrid];
    _osc_opfVel		= new ofVec4f[opticalFlowXGrid*opticalFlowYGrid];
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // matrix areas for motion trigger
    float	flopX = 30;
    float	flopY = 90;
    
    triggerAreas.setup(flopX,flopY,_width,_height,TRIGGER_AREAS_NUM);
    triggerAreas.loadSettings("settings/openni/triggerAreas.xml");
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
    // dummy gui vars init
    ciBlur = 1;
    ciErode = 1;
    ciDilate = 1;
    
    minBlobArea = 20;
    maxBlobArea = 100000;
    cfDetail = 1;
    
    onHorizon = 20;
    offHorizon = 50;
    
    computeContourFinder = false;
    computeContourGeometry = false;
    computeOpticalFlow = false;
    computeTriggerAreas = false;
    
    _smoothingFactor = 0.95f;
    
    saveAllSettings = false;
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // GUI setup
    char xml_name[256];
	char temp[128];
    
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
    gui.setup("KINECT TRACKING MODULE",0,20,1200,720);
	gui.setDraggable(false);
    
    gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
    gui.setOutlineColor(simpleColor(0,0,0,255));
    sprintf(temp," KINECT DEVICE[%i] - %s",devID,kinect.getSerial().c_str());
    gui.addPanel(temp, 5);
    gui.setWhichPanel(temp);
    
    gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    gui.setOutlineColor(simpleColor(0,0,0,255));
    gui.setWhichColumn(0);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    gui.addDrawableRect("CAMERA IMAGE", &kinect.getTextureReference(), 240,180);
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    gui.addDrawableRect("DEPTH IMAGE", &kinect.getDepthTextureReference(), 240,180);
    sprintf(xml_name,"NEAR_THRESHOLD_SENSOR_KINECT");
    gui.addSlider("NEAR TRESHOLD",xml_name,nearThreshold,0,4000,true);
    sprintf(xml_name,"FAR_THRESHOLD_SENSOR_KINECT");
    gui.addSlider("FAR TRESHOLD",xml_name,farThreshold,0,4000,true);
    
    gui.setWhichColumn(1);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    gui.addDrawableRect("DEPTH RANGE MASK", &cleanImage, 240,180);
    //gui.addDrawableRect("POINTS CLOUD", &_empty, 240,180);
    //sprintf(xml_name,"DRAW_POINT_CLOUD");
    //gui.addToggle("DRAW POINTS CLOUD", xml_name, false);
    
    gui.setWhichColumn(2);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("GENERAL SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"CI_BLUR_SENSOR_KINECT");
    gui.addSlider("SENSOR KINECT BLUR", xml_name, ciBlur, 0, 33, true);
    sprintf(xml_name,"CI_ERODE_SENSOR_KINECT");
    gui.addSlider("ERODE", xml_name, ciErode, 0, 10, true);
    sprintf(xml_name,"CI_DILATE_SENSOR_KINECT");
    gui.addSlider("DILATE", xml_name, ciDilate, 0, 10, true);
    
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("MOTION DETECTION SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"M_THRESHOLD_SENSOR_KINECT");
    gui.addSlider("MOTION THRESHOLD", xml_name, mThreshold, 1, 300, true);
    sprintf(xml_name,"MOTION_ON_HORIZON_SENSOR_KINECT");
    gui.addSlider("MOTION TRIGGER LOW LIMIT", xml_name, onHorizon, 1, 100, true);
    sprintf(xml_name,"MOTION_OFF_HORIZON_SENSOR_KINECT");
    gui.addSlider("MOTION TRIGGER RANGE LIMIT", xml_name, offHorizon, 0, 200, true);
    gui.addDrawableRect("MOTION IMAGE", &motionImg, 160, 120);
    //////////////////////////////////////////////
    
    gui.setWhichColumn(3);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("BLOB TRACKING SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"MIN_BLOB_AREA_SENSOR_KINECT");
    gui.addSlider("MIN BLOB",xml_name,minBlobArea,2,5000,true);
    sprintf(xml_name,"MAX_BLOB_AREA_SENSOR_KINECT");
    gui.addSlider("MAX BLOB",xml_name,maxBlobArea,0,100000,true);
    sprintf(xml_name,"CF_DETAIL_SENSOR_KINECT");
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
    gui.addTextDropDown("CONTOUR DETAIL", xml_name, 0, cfDetailUse);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
    sprintf(xml_name,"CF_SMOOTH_PCT_SENSOR_KINECT");
    gui.addSlider("CONTOUR SMOOTH FACTOR", xml_name,smoothPct,0.01f,0.99f,false);
    sprintf(xml_name,"CF_TOLERANCE_SENSOR_KINECT");
    gui.addSlider("CONTOUR SIMPLE TOLERANCE", xml_name,tolerance,0.01f,20.0f,false);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("COMPUTING ALGORITHM SELECTOR");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"COMPUTE_CF_SENSOR_KINECT");
    gui.addToggle("COMPUTE CONTOUR FINDER", xml_name, false);
    sprintf(xml_name,"COMPUTE_CG_SENSOR_KINECT");
    gui.addToggle("COMPUTE CONTOUR GEOMETRY", xml_name, false);
    sprintf(xml_name,"COMPUTE_OF_SENSOR_KINECT");
    gui.addToggle("COMPUTE OPTICAL FLOW", xml_name, false);
    sprintf(xml_name,"COMPUTE_TA_SENSOR_KINECT");
    gui.addToggle("COMPUTE TRIGGER AREAS", xml_name, false);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("OSC DATA SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"SMOOTHING_FACTOR_SENSOR_KINECT");
    gui.addSlider("SMOOTHING FACTOR",xml_name,_smoothingFactor,0.01f,0.99f,false);
    
    gui.setWhichColumn(4);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("SENSOR KINECT HARDWARE");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    gui.setBackgroundColor(gamuzaChartBackColor);
    sprintf(temp,"ACCELEROMETER X");
    gui.addChartPlotter(temp, guiStatVarPointer("X", &_osc_hAccel->x, GUI_VAR_FLOAT, true, 2), 110, 80, 200, 0.0f, 1.0f);
    sprintf(temp,"ACCELEROMETER Y");
    gui.addChartPlotter(temp, guiStatVarPointer("Y", &_osc_hAccel->y, GUI_VAR_FLOAT, true, 2), 110, 80, 200, 0.0f, 1.0f);
    sprintf(temp,"ACCELEROMETER Z");
    gui.addChartPlotter(temp, guiStatVarPointer("Z", &_osc_hAccel->z, GUI_VAR_FLOAT, true, 2), 110, 80, 200, 0.0f, 1.0f);
    
    // load default gui settings
	gui.loadSettings(guiSettingsFile);
    
    // GUI Events
	gui.setupEvents();
	gui.enableEvents();
    
    sprintf(temp,"COMPUTE_CG_SENSOR_KINECT");
    ofAddListener(gui.createEventGroup(temp), this, &gaKinectTracking::activateTrackingCF);
    sprintf(temp,"COMPUTE_TA_SENSOR_KINECT");
    ofAddListener(gui.createEventGroup(temp), this, &gaKinectTracking::activateTrackingCF);
    //////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gaKinectTracking::updateDevice(){
	
    updateOpenCV();
    
    updateGUI();
    
    //////////////////////////////////////////////
    // save all settings
    if (saveAllSettings == true){
        char temp[128];
        sprintf(temp,"settings/kinect/triggerAreas%i.xml",devID);
        triggerAreas.saveSettings(temp);
        saveAllSettings = false;
    }
    //////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gaKinectTracking::updateOpenCV(){
	
	kinect.update();
    cleanImage.setFromPixels(kinect.getDepthPixels(), _width, _height);
    
    grayThreshNear = cleanImage;
    grayThreshFar = cleanImage;
    grayThreshNear.threshold(nearThreshold, true);
    grayThreshFar.threshold(farThreshold);
    cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), cleanImage.getCvImage(), NULL);
    cleanImage.flagImageChanged();
	
	//////////////////////////////////////////////
	cleanImage.erode(ciErode);
	cleanImage.dilate(ciDilate);
	cleanImage.blur(ciBlur);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// motion detection
	calculateMotion();
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// find contours
	if(computeContourFinder){
		runningBlobs = contourFinder.findContours(cleanImage, minBlobArea, maxBlobArea, MAX_NUM_CONTOURS_TO_FIND, false, false);
		if(runningBlobs > 0 && runningBlobs < MAX_NUM_CONTOURS_TO_FIND){
			computeContourAnalysis();
			blobTracker.trackBlobs(contourFinder.blobs);
		}
	}
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// motion trigger areas
	if(computeContourFinder && computeTriggerAreas){
		if(numPixelsChanged > onHorizon){
			// if first blob is inside area...
			// this is useful when working with laser tracking 
			triggerAreas.isPointInside(blobTracker.blobs[0].boundingRect.x,blobTracker.blobs[0].boundingRect.y);
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
	// smoothing & normalize numerical variable
	// (prepare it for sending via OSC)
	smoothingValues();
	normalizeValues();
	//////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gaKinectTracking::updateGUI(){
    char xml_name[256];
    
    sprintf(xml_name,"NEAR_THRESHOLD_SENSOR_KINECT");
    nearThreshold = ceil(ofMap(gui.getValueI(xml_name),0,4000,0,255));
    sprintf(xml_name,"FAR_THRESHOLD_SENSOR_KINECT");
    farThreshold = ceil(ofMap(gui.getValueI(xml_name),0,4000,0,255));
    sprintf(xml_name,"DRAW_POINT_CLOUD");
    bDrawPointCloud = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"CI_BLUR_SENSOR_KINECT");
    ciBlur = gui.getValueI(xml_name);
    sprintf(xml_name,"CI_ERODE_SENSOR_KINECT");
    ciErode = gui.getValueF(xml_name);
    sprintf(xml_name,"CI_DILATE_SENSOR_KINECT");
    ciDilate = gui.getValueF(xml_name);
    sprintf(xml_name,"M_THRESHOLD_SENSOR_KINECT");
    mThreshold = gui.getValueI(xml_name);
    sprintf(xml_name,"MOTION_ON_HORIZON_SENSOR_KINECT");
    onHorizon = gui.getValueI(xml_name);
    sprintf(xml_name,"MOTION_OFF_HORIZON_SENSOR_KINECT");
    offHorizon = gui.getValueI(xml_name);
    sprintf(xml_name,"SMOOTHING_FACTOR_SENSOR_KINECT");
    _smoothingFactor = gui.getValueF(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"MIN_BLOB_AREA_SENSOR_KINECT");
    minBlobArea = gui.getValueI(xml_name);
    sprintf(xml_name,"MAX_BLOB_AREA_SENSOR_KINECT");
    maxBlobArea = gui.getValueI(xml_name);
    sprintf(xml_name,"CF_DETAIL_SENSOR_KINECT");
    cfDetail = gui.getValueI(xml_name);
    sprintf(xml_name,"CF_SMOOTH_PCT_SENSOR_KINECT");
    smoothPct = gui.getValueF(xml_name);
    sprintf(xml_name,"CF_TOLERANCE_SENSOR_KINECT");
    tolerance = gui.getValueF(xml_name);
    sprintf(xml_name,"COMPUTE_CF_SENSOR_KINECT");
    computeContourFinder = gui.getValueI(xml_name);
    sprintf(xml_name,"COMPUTE_CG_SENSOR_KINECT");
    computeContourGeometry = gui.getValueI(xml_name);
    sprintf(xml_name,"COMPUTE_OF_SENSOR_KINECT");
    computeOpticalFlow = gui.getValueI(xml_name);
    sprintf(xml_name,"COMPUTE_TA_SENSOR_KINECT");
    computeTriggerAreas = gui.getValueI(xml_name);
    
    gui.update();
}

//--------------------------------------------------------------
void gaKinectTracking::drawDevice(){
    
    drawGUI();
    
    //////////////////////////////////////////////////
    // Kinect source
    /*if(bDrawPointCloud){
		easyCam.begin();
		drawPointCloud();
		easyCam.end();
	}*/
    //////////////////////////////////////////////////
    
    //////////////////////////////////////////////////
    // blob detection + contours
    if(computeContourFinder){
        if(runningBlobs > 0){
            drawContourAnalysis();
        }
    }
    //////////////////////////////////////////////////
    
    //////////////////////////////////////////////////
    // optical flow LK
    if(computeOpticalFlow){
        glPushMatrix();
        glTranslatef(286, 83, 0);
        glScalef(240.0f/_width, 180.0f/_height, 1.0);
        opticalFlow.draw();
        glPopMatrix();
    }
    //////////////////////////////////////////////////
    
    //////////////////////////////////////////////////
    // motion trigger areas
    if(computeContourFinder && computeTriggerAreas){
        triggerAreas.draw(triggerState);
    }
    //////////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gaKinectTracking::drawGUI(){
    //////////////////////////////////////////////////
    // Draw gui
    ofSetColor(255);
    gui.draw(1);
    ofEnableAlphaBlending();
    ofFill();
    glColor4f(0.0,1.0,0.0,1.0);
    ofRect(gui.panelTabs[0].x+1, gui.panelTabs[0].y+1, gui.panelTabs[0].width-2, gui.panelTabs[0].height-2);
    ofDisableAlphaBlending();
    //////////////////////////////////////////////////
}

//--------------------------------------------------------------
void gaKinectTracking::drawPointCloud() {
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	int step = 3;
	for(int y = 0; y < _height-step; y += step) {
		for(int x = 0; x < _width-step; x += step) {
			if(kinect.getDistanceAt(x, y) > 0) {
				mesh.addColor(kinect.getColorAt(x,y));
				mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
			}
		}
	}
	glPointSize(3);
	ofPushMatrix();
	// the projected points are 'upside down'
	ofTranslate(0,0,-1000); // center the points a bit
    ofScale(1,1,-1);
	
	mesh.drawVertices();
	
	ofPopMatrix();
    //glPointSize(1);
}

//--------------------------------------------------------------
void gaKinectTracking::setGuiSettingsFile(string file){
    guiSettingsFile = file;
}

//--------------------------------------------------------------
ofTexture gaKinectTracking::getCameraTexture(){
    return kinect.getTextureReference();
}

//--------------------------------------------------------------
ofPixelsRef gaKinectTracking::getCameraPixels(){
    return kinect.getPixelsRef();
}

//--------------------------------------------------------------
ofTexture gaKinectTracking::getDepthTexture(){
    return kinect.getDepthTextureReference();
}

//--------------------------------------------------------------
int gaKinectTracking::getNumBlobs(){
    if(computeContourFinder){
        return runningBlobs;
    }else{
        return 0;
    }
}

//--------------------------------------------------------------
float gaKinectTracking::getBlobX(int i){
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
float gaKinectTracking::getBlobY(int i){
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
float gaKinectTracking::getBlobW(int i){
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
float gaKinectTracking::getBlobH(int i){
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
float gaKinectTracking::getBlobAngle(int i){
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
int gaKinectTracking::getBlobContourSize(int i){
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
float gaKinectTracking::getBlobCPointX(int blob,int i){
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
float gaKinectTracking::getBlobCPointY(int blob,int i){
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
int gaKinectTracking::getBlobGeometrySize(int i){
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
float gaKinectTracking::getBlobGLineX1(int blob,int i){
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
float gaKinectTracking::getBlobGLineY1(int blob,int i){
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
float gaKinectTracking::getBlobGLineX2(int blob,int i){
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
float gaKinectTracking::getBlobGLineY2(int blob,int i){
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
float gaKinectTracking::getOpticalFlowX(int i){
    if(computeOpticalFlow){
        return _osc_opfVel[i].x;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaKinectTracking::getOpticalFlowY(int i){
    if(computeOpticalFlow){
        return _osc_opfVel[i].y;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaKinectTracking::getOpticalFlowVX(int i){
    if(computeOpticalFlow){
        return _osc_opfVel[i].z;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
float gaKinectTracking::getOpticalFlowVY(int i){
    if(computeOpticalFlow){
        return _osc_opfVel[i].w;
    }else{
        return 0.0f;
    }
}

//--------------------------------------------------------------
bool  gaKinectTracking::getTrigger(int i){
    if(computeContourFinder && computeTriggerAreas){
        return triggerState[i];
    }else{
        return -1;
    }
}

//--------------------------------------------------------------
float gaKinectTracking::getAccelX(){
    return _osc_hAccel->x;
}

//--------------------------------------------------------------
float gaKinectTracking::getAccelY(){
    return _osc_hAccel->y;
}

//--------------------------------------------------------------
float gaKinectTracking::getAccelZ(){
    return _osc_hAccel->z;
}

//--------------------------------------------------------------
void gaKinectTracking::activateTrackingCF(guiCallbackData & data){
    char temp[256], temp2[256],temp3[256];
    sprintf(temp,"COMPUTE_CG_SENSOR_KINECT");
    sprintf(temp2,"COMPUTE_TA_SENSOR_KINECT");
    sprintf(temp3,"COMPUTE_CF_SENSOR_KINECT");
    if((data.isElement(temp) || data.isElement(temp2)) && data.getInt(0) == 1 ){
        gui.setValueB(temp3, true);
    }
}

//--------------------------------------------------------------
void gaKinectTracking::mouseDragged(int x, int y){
	
	// trigger areas control
    triggerAreas.mouseDragged(x, y);
    
    // GUI
    gui.mouseDragged(x, y, 0);
	
}

//--------------------------------------------------------------
void gaKinectTracking::mousePressed(int x, int y){
	
	// trigger areas control
    triggerAreas.mousePressed(x, y);
    
    // GUI
    gui.mousePressed(x, y, 0);
    
    if(gui.saveDown){
        saveAllSettings = true;
    }
	
}

//--------------------------------------------------------------
void gaKinectTracking::mouseReleased(int x, int y){
	
	// trigger areas control
    triggerAreas.mouseReleased(x,y);
    
    // GUI
    gui.mouseReleased();
	
}

//--------------------------------------------------------------
void gaKinectTracking::calculateMotion(){
	
	if(frameCounter > 5){// dont do anything until we have enough in history
		
		grayNow = cleanImage;
		
		if(computeOpticalFlow){
			opticalFlow.calc(grayPrev,grayNow,11); // optical flow analysis based on frame difference
			cvSmooth(opticalFlow.getVelX(), opticalFlow.getVelX(), CV_BLUR , CAM_VELOCITY_BLUR);
			cvSmooth(opticalFlow.getVelY(), opticalFlow.getVelY(), CV_BLUR , CAM_VELOCITY_BLUR);
		}
		
		motionImg.absDiff(grayPrev, grayNow);   // motionImg is the difference between current and previous frame
		cvThreshold(motionImg.getCvImage(), motionImg.getCvImage(), (int)mThreshold, 255, CV_THRESH_TOZERO); // anything below mThreshold, drop to zero (compensate for noise)
		numPixelsChanged = motionImg.countNonZeroInRegion(0, 0, _width, _height); // this is how many pixels have changed that are above mThreshold
		
		grayPrev = grayNow; // save current frame for next loop
			
		cvThreshold(motionImg.getCvImage(), motionImg.getCvImage(), (int)mThreshold, 255, CV_THRESH_TOZERO);// chop dark areas
		
		// Calculate the general "mood" of the scene
		mood = averageBnWVal(motionImg.getCvImage());
		
	}else{
		frameCounter++;
	}
	
}

//--------------------------------------------------------------
void gaKinectTracking::computeContourAnalysis(){
	
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
void gaKinectTracking::drawContourAnalysis(){
	
	string temp;
	
	glPushMatrix();
	glTranslatef(286, 90, 0);
	glScalef(240.0f/_width, 180.0f/_height, 1.0);
	
	ofEnableAlphaBlending();
	
	ofFill();
	
	for(unsigned int i = 0; i < blobTracker.blobs.size(); i++){
		ostringstream docstring;
		docstring << blobTracker.findOrder(blobTracker.blobs[i]._id) << endl;
		temp = docstring.str();
		blobsOrder[i] = atoi(temp.c_str());
		
		glColor4f(0.847,0.25,0.25,0.4);
		ofRect(_s_blobInfo[i].center.x,_s_blobInfo[i].center.y,_s_blobInfo[i].size.width,_s_blobInfo[i].size.height);
		
		glColor4f(0.0,0.0,1.0,1.0);
		if(temp != ""){
			ofDrawBitmapString(temp,_s_blobInfo[i].center.x + _s_blobInfo[i].size.width/2.0,_s_blobInfo[i].center.y + _s_blobInfo[i].size.height/2.0);
		}
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
void gaKinectTracking::blobOn( int x, int y, int id, int order ){
	
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
void gaKinectTracking::blobMoved( int x, int y, int id, int order){
	
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
void gaKinectTracking::blobOff( int x, int y, int id, int order ){
	
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
float gaKinectTracking::averageBnWVal(IplImage * img){
	
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
void gaKinectTracking::getVelAtPixel(int x, int y, float *u, float *v) {
	*u = cvGetReal2D( opticalFlow.getVelX(), y, x );
	*v = cvGetReal2D( opticalFlow.getVelY(), y, x );
}

//--------------------------------------------------------------
void gaKinectTracking::getVelAtNorm(float x, float y, float *u, float *v) {
	int ix = x * _width;
	int iy = y * _height;
	if(ix<0) ix = 0; else if(ix>=_width) ix = _width - 1;
	if(iy<0) iy = 0; else if(iy>=_height) iy = _height - 1;
	*u = cvGetReal2D( opticalFlow.getVelX(), iy, ix );
	*v = cvGetReal2D( opticalFlow.getVelY(), iy, ix );
}

//--------------------------------------------------------------
void gaKinectTracking::smoothingValues(){
		
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
    
    // hardware sensors
    _s_hAccel->x =  _s_hAccel->x*_smoothingFactor + (1.0-_smoothingFactor)*kinect.getMksAccel().x;
    _s_hAccel->y =  _s_hAccel->y*_smoothingFactor + (1.0-_smoothingFactor)*kinect.getMksAccel().y;
    _s_hAccel->z =  _s_hAccel->z*_smoothingFactor + (1.0-_smoothingFactor)*kinect.getMksAccel().z;
	
}

//--------------------------------------------------------------
void gaKinectTracking::normalizeValues(){
	
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
    
    // hardware sensors
    _osc_hAccel->x = ofNormalize(_s_hAccel->x,-10.0f,10.0f);
    _osc_hAccel->y = ofNormalize(_s_hAccel->y,-10.0f,10.0f);
    _osc_hAccel->z = ofNormalize(_s_hAccel->z,-10.0f,10.0f);
	
}
