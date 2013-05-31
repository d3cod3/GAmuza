#include "sourceTracking.h"


//--------------------------------------------------------------
sourceTracking::sourceTracking(){
	
}

//--------------------------------------------------------------
void sourceTracking::setupCam(int __id, int _w, int _h, int deviceID, bool player, string haarFile, string movie){
	
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
	
	if(!isPlayer){
		vidGrabber.setDeviceID(deviceID);
		vidGrabber.initGrabber(_width,_height);
	}else{
		vidPlayer.loadMovie(movieFile);
		vidPlayer.play();
	}
	
    camPixels = new unsigned char[_numPixels*3];                // Live Cam pixels copy
	camTexture.allocate(_width,_height,GL_RGB);                 // Live Cam texture copy
    effectedTexture.allocate(_width,_height,GL_RGB);    // Live effected cam texture
    
    cld_pixels = new unsigned char[_numPixels*3];
    cld_img.init(_width,_height);
    
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
	haarFinder.setup(haarFile);
	printf("loaded haar finder file: %s\n", haarFile.c_str());
	
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
	
	// OSC flags
	sendOsc_MD = false;
	sendOsc_BD = false;
	sendOsc_CF = false;
	sendOsc_CG = false;
	sendOsc_OF = false;
	sendOsc_HF = false;
	sendOsc_TA = false;
	//////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void sourceTracking::update(){
	
	char temp[128];
	
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
			vidGrabber.grabFrame();
			bNewFrame = vidGrabber.isFrameNew();
		}else{
			vidPlayer.idleMovie();
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
void sourceTracking::draw(){
	
	if(captureVideo){
		
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
				cv_mutex.lock();
				drawContourAnalysis();
				cv_mutex.unlock();
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
		
	}
	
}

//--------------------------------------------------------------
void sourceTracking::computeCLD(int _black, float _sigma1, float _sigma2, float _tau, float _thresh){
    
    if(_black < -255){
        _black = 255;
    }else if(_black > 255){
        _black = 255;
    }
    
    if(_sigma1 < 0.01f){
        _sigma1 = 0.01f;
    }else if(_sigma1 > 2.0f){
        _sigma1 = 2.0f;
    }
    
    if(_sigma2 < 0.01f){
        _sigma2 = 0.01f;
    }else if(_sigma2 > 10.0f){
        _sigma2 = 10.0f;
    }
    
    if(_tau < 0.8f){
        _tau = 0.8f;
    }else if(_tau > 1.0f){
        _tau = 1.0f;
    }
    
    if(_thresh < -1.0f){
        _thresh = -1.0f;
    }else if(_thresh > 1.0f){
        _thresh = 1.0f;
    }
    
    
    if(!isPlayer && vidGrabber.isFrameNew()){
        cld_pixels = vidGrabber.getPixels();
    }else if(isPlayer && vidPlayer.isFrameNew()){
        cld_pixels = vidPlayer.getPixels();
    }
    
    if(captureVideo){
        for(int w=0; w<_width; w++) {
            for(int h=0; h<_height; h++) {
        
                int p = h*_width + w;
                cld_img[w][h] = cld_pixels[p*3] - _black;
            }        
        }

        cld_e.init(_width, _height);
        cld_e.set(cld_img);
        cld_e.Smooth(4, 2);
        GetFDoG(cld_img, cld_e, _sigma1, _sigma2, _tau); 
        GrayThresholding(cld_img, _thresh);

        for(int w=0; w<_width; w++) {
            for(int h=0; h<_height; h++) {
        
                int p = h*_width + w;
                camPixels[p*3]      = CLAMP(cld_img[w][h], 0, 255);
                camPixels[p*3+1]    = CLAMP(cld_img[w][h], 0, 255);
                camPixels[p*3+2]    = CLAMP(cld_img[w][h], 0, 255);
            }        
        }

        effectedTexture.loadData(camPixels, _width, _height, GL_RGB);

    }
    
}

//--------------------------------------------------------------
void sourceTracking::mouseDragged(int x, int y, int button){
	
	
	triggerAreas.mouseDragged(x, y);
	// input source quad control
	sourceFrame.mouseDragged(x, y);
	
}

//--------------------------------------------------------------
void sourceTracking::mousePressed(int x, int y, int button){
	
	
	triggerAreas.mousePressed(x, y);
	// input source quad control
	sourceFrame.mousePressed(x, y);
	
}

//--------------------------------------------------------------
void sourceTracking::mouseReleased(int x, int y, int button){
	
	// trigger areas control
	triggerAreas.mouseReleased(x,y);
	// input source quad control
	sourceFrame.mouseReleased(x,y);
	
	
}

//--------------------------------------------------------------
void sourceTracking::loadCalibration(){
	
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
void sourceTracking::getQuadSubImage(unsigned char* inputData,unsigned char* outputData,int inW,int inH,int outW,int outH,ofPoint *quad,int bpp){
	
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
void sourceTracking::calculateColorDifference(){
	
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
void sourceTracking::calculateGrayscaleDifference(){
	
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
void sourceTracking::calculateColorDifferenceHSV(){
	
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
void sourceTracking::balanceTracking(){
	
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
void sourceTracking::calculateMotion(){
	
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
void sourceTracking::computeContourAnalysis(){
	
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
void sourceTracking::drawMotionCentroid(){
	
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
void sourceTracking::drawContourAnalysis(){
	
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
		
		glColor4f(0.0,0.0,1.0,1.0);
		if(temp != ""){
			ofDrawBitmapString(temp,(_s_blobInfo[i].center.x + _s_blobInfo[i].size.width/2.0)*240/_width,(_s_blobInfo[i].center.y + _s_blobInfo[i].size.height/2.0)*180/_height);
		}
	}
    
    // blobs area
    glScalef(240.0f/_width, 180.0f/_height, 1.0);
    for(unsigned int i = 0; i < blobTracker.blobs.size(); i++){
		glColor4f(0.847,0.25,0.25,0.4);
		ofRect(_s_blobInfo[i].center.x,_s_blobInfo[i].center.y,_s_blobInfo[i].size.width,_s_blobInfo[i].size.height);
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
void sourceTracking::drawHaarFinder(){
	
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
void sourceTracking::blobOn( int x, int y, int id, int order ){
	
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
void sourceTracking::blobMoved( int x, int y, int id, int order){
	
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
void sourceTracking::blobOff( int x, int y, int id, int order ){
	
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
float sourceTracking::averageBnWVal(IplImage * img){
	
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
void sourceTracking::getVelAtPixel(int x, int y, float *u, float *v) {
	*u = cvGetReal2D( opticalFlow.getVelX(), y, x );
	*v = cvGetReal2D( opticalFlow.getVelY(), y, x );
}

//--------------------------------------------------------------
void sourceTracking::getVelAtNorm(float x, float y, float *u, float *v) {
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
void sourceTracking::smoothingValues(){
	
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
void sourceTracking::normalizeValues(){
	
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
