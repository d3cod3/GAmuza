#include "openniTracking.h"


//--------------------------------------------------------------
openniTracking::openniTracking(){
	
}

//--------------------------------------------------------------
openniTracking::~openniTracking(){
	
}

//--------------------------------------------------------------
void openniTracking::setupDevice(int _w, int _h,bool _ir,int _ledState){
	
	_width	 = _w;
	_height  = _h;
	useIR	 = _ir;
	ledState = _ledState;
	
	useKinect		= true;
	isTrackingHands = true;
	
	nearThreshold	= 500;
	farThreshold	= 1000;
	filterFactor	= 0.1f;
	
	maxHands		  = NUM_KINECT_USERS*2;
	_osc_hands_Pos = new ofPoint[maxHands];
	
	isOniConnected = false;
    
    if(isOniConnected){
    
        camTexture.allocate(_width,_height,GL_RGB);
        //////////////////////////////////////////////
        // opencv setup
        cleanImage.allocate(_width, _height);
        
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
        _kalman_blobInfo		= new CvBox2D32f[MAX_NUM_CONTOURS_TO_FIND];
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
        
        useKalmanFilter = false;
        _smoothingFactor = 0.95f;
        
        saveAllSettings = false;
        
        // OSC flags
        sendOsc_BD = false;
        sendOsc_CF = false;
        sendOsc_CG = false;
        sendOsc_OF = false;
        sendOsc_TA = false;
        sendOsc_HT = false;
        sendOsc_HW = true;
        //////////////////////////////////////////////
    }
	
}

//--------------------------------------------------------------
void openniTracking::updateDevice(){
	
    if(isOniConnected){
        
        
        
        updateOpenCV();
        
        //////////////////////////////////////////////
        // save all settings
        if (saveAllSettings == true){
            triggerAreas.saveSettings("settings/openni/triggerAreas.xml");
            saveAllSettings = false;
        }
        //////////////////////////////////////////////
        
    }
	
}

//--------------------------------------------------------------
void openniTracking::updateOpenCV(){
	
	//cleanImage.setFromPixels(depthRangeMaskScaled.getPixels(), _width, _height);
	
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
	// smoothing & normalize numerical variable
	// (prepare it for sending via OSC)
	smoothingValues();
	normalizeValues();
	//////////////////////////////////////////////
	
}

//--------------------------------------------------------------
void openniTracking::drawDevice(){
    
    if(isOniConnected){
	
        //////////////////////////////////////////////////
        // blob detection + contours
        if(computeContourFinder){
            if(runningBlobs > 0){
                cv_mutex.lock();
                drawContourAnalysis();
                cv_mutex.unlock();
            }
        }
        //////////////////////////////////////////////////
        
        //////////////////////////////////////////////////
        // optical flow LK
        if(computeOpticalFlow){
            glPushMatrix();
            glTranslatef(366, 83, 0);
            glScalef(320.0f/_width, 240.0f/_height, 1.0);
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
	
}

//--------------------------------------------------------------
void openniTracking::mouseDragged(int x, int y, int button){
	
	// trigger areas control
    if(isOniConnected){
        triggerAreas.mouseDragged(x, y);
    }
	
}

//--------------------------------------------------------------
void openniTracking::mousePressed(int x, int y, int button){
	
	// trigger areas control
    if(isOniConnected){
        triggerAreas.mousePressed(x, y);
    }
	
}

//--------------------------------------------------------------
void openniTracking::mouseReleased(int x, int y, int button){
	
	// trigger areas control
    if(isOniConnected){
        triggerAreas.mouseReleased(x,y);
    }
	
}

//--------------------------------------------------------------
void openniTracking::calculateMotion(){
	
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
void openniTracking::computeContourAnalysis(){
	
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
void openniTracking::drawContourAnalysis(){
	
	string temp;
	
	glPushMatrix();
	glTranslatef(366, 90, 0);
	glScalef(320.0f/_width, 240.0f/_height, 1.0);
	
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
void openniTracking::blobOn( int x, int y, int id, int order ){
	
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
void openniTracking::blobMoved( int x, int y, int id, int order){
	
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
void openniTracking::blobOff( int x, int y, int id, int order ){
	
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
float openniTracking::averageBnWVal(IplImage * img){
	
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
void openniTracking::getVelAtPixel(int x, int y, float *u, float *v) {
	*u = cvGetReal2D( opticalFlow.getVelX(), y, x );
	*v = cvGetReal2D( opticalFlow.getVelY(), y, x );
}

//--------------------------------------------------------------
void openniTracking::getVelAtNorm(float x, float y, float *u, float *v) {
	int ix = x * _width;
	int iy = y * _height;
	if(ix<0) ix = 0; else if(ix>=_width) ix = _width - 1;
	if(iy<0) iy = 0; else if(iy>=_height) iy = _height - 1;
	*u = cvGetReal2D( opticalFlow.getVelX(), iy, ix );
	*v = cvGetReal2D( opticalFlow.getVelY(), iy, ix );
}

//--------------------------------------------------------------
void openniTracking::smoothingValues(){
		
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
	
}

//--------------------------------------------------------------
void openniTracking::normalizeValues(){
	
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
	
	
	// openni sensor kinect hardware
	_osc_sensorAcc.x = ofNormalize(sensor_accelerometer.x,-10.0f,10.0f);
	_osc_sensorAcc.y = ofNormalize(sensor_accelerometer.y,-10.0f,10.0f);
	_osc_sensorAcc.z = ofNormalize(sensor_accelerometer.z,-10.0f,10.0f);
	
	_osc_sensorTilt  = ofNormalize(sensor_tilt,0.0f,360.0f);
	
}
