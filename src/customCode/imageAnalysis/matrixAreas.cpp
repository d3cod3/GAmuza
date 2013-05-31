#include "matrixAreas.h"

//---------------------------------------------------------
matrixAreas::matrixAreas(){
	_width 	    = 320;
	_height 	= 240;
	
}

//---------------------------------------------------------
matrixAreas::matrixAreas(int w, int h){
	
	_width 	    = w;
	_height 	= h;
	
}

//--------------------------------------------------------
void matrixAreas::setup(float x, float y, float w, float h, int _nAreas){
	
	xCalib = x;
	yCalib = y;
	wCalib = w;
	hCalib = h;
	pointBeingCalibrated = -1;
	diameterBeingCalibrated = -1;
	
	areaON = 0;
	
	numAreas = _nAreas;
	
	resOrigin = (int)sqrt(numAreas);
	
	points		= new ofPoint[numAreas];
	diameters	= new float[numAreas];
	imOver		= new bool[numAreas];
	
	for(int i=0;i<numAreas;i++){
		imOver[i] = false;
	}

	_width 	    = w;
	_height     = h;
	
	scalew = wCalib / (float)_width;
	scaleh = hCalib / (float)_height;
	
	automatFont.loadFont("fonts/D3Litebitmapism.ttf",8, true, true);

	reset(w,h);

}

//--------------------------------------------------------
void matrixAreas::reset(float w, float h){
	
	for(int i=0;i<numAreas;i++){
		diameters[i] = 20.0;
		float xx = (i % resOrigin) / (float)(resOrigin-1);
		float yy = (i / resOrigin) / (float)(resOrigin-1);
		points[i].x = xx*w;
		points[i].y = yy*h;
	}
	
}

//--------------------------------------------------------
void matrixAreas::update(bool manualEdit,int actualPoint){
    if(manualEdit){
        pointBeingCalibrated = actualPoint;
        
    }else{
        pointBeingCalibrated = -1;
    }
    
    for (int i = 0; i < numAreas; i++){
        if(actualPoint == i){
            imOver[i] = true;
        }else{
            imOver[i] = false;
        }
    }
}

//--------------------------------------------------------
void matrixAreas::mouseMoved(float x, float y){
	for (int i = 0; i < numAreas; i++){
		float xdiff = xCalib + points[i].x*scalew - x;
		float ydiff = yCalib + points[i].y*scaleh - y;
		float dist = sqrt(xdiff * xdiff + ydiff * ydiff);
		if (dist < 5){
			imOver[i] = true;
		}else{
			imOver[i] = false;
		}
	}
}

//--------------------------------------------------------
void matrixAreas::mousePressed(float x, float y){

	//float scalew = wCalib / (float)_width;
	//float scaleh = hCalib / (float)_height;
	
	for (int i = 0; i < numAreas; i++){
		float xdiff = xCalib + points[i].x*scalew - x;
		float ydiff = yCalib + points[i].y*scaleh - y;
		float dist = sqrt(xdiff * xdiff + ydiff * ydiff);
		if (dist < 5){
			pointBeingCalibrated = i;
		}
		if(dist > 6 && dist < 20){
			diameterBeingCalibrated = i;
		}
	}
}

//--------------------------------------------------------
void matrixAreas::mouseDragged(float x, float y){

	//float scalew = wCalib / (float)_width;
	//float scaleh = hCalib / (float)_height;
	
	if(x > xCalib && x < (xCalib+wCalib) && y > yCalib && y < (yCalib + hCalib)){

		if(pointBeingCalibrated >= 0 && pointBeingCalibrated <= numAreas-1){
			float newx = (x - xCalib) / scalew;
			float newy = (y - yCalib) / scaleh;
			points[pointBeingCalibrated].x = newx;
			points[pointBeingCalibrated].y = newy;
			
			glColor4f(0.847f,0.25f,0.25f, 1.0f);
			char buf[256];
			sprintf(buf,"%i,%i", (int)newx,(int)newy);
			automatFont.drawString(buf,6 + newx, newy);
			
		}else if(diameterBeingCalibrated >= 0 && diameterBeingCalibrated <= numAreas-1){
			float newX = (x - xCalib) / scalew;
			float newD = points[diameterBeingCalibrated].x - newX;
			diameters[diameterBeingCalibrated] = newD;
		}
	
	}
	
	
}

//--------------------------------------------------------
void matrixAreas::mouseReleased(float x, float y){
	pointBeingCalibrated = -1;
	diameterBeingCalibrated = -1;
}

//--------------------------------------------------------
void matrixAreas::isPointInside(float x, float y){
	
	//float scalew = wCalib / (float)_width;
	//float scaleh = hCalib / (float)_height;
	for (int i = 0; i < numAreas; i++){
		float xdiff = xCalib + points[i].x*scalew - x;
		float ydiff = yCalib + points[i].y*scaleh - y;
		float dist = sqrt(xdiff * xdiff + ydiff * ydiff);
		float absDiam = sqrt(diameters[i]*diameters[i]);
		if (dist < absDiam){
			areaON = i;
		}
	}
}

//---------------------------------------------------------
void matrixAreas::draw(){
	
	glEnable(GL_BLEND);
	for (int i = 0; i < numAreas; i++){
	
		if(pointBeingCalibrated == i){
			ofFill();
			glColor4f(0.847f,0.25f,0.25f, 0.8f);
			
		}else{
			ofNoFill();
			glColor4f(0.847f,0.25f,0.25f, 0.3f);
		}
		ofCircle(xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh, 5);
		
		glColor4f(1.0f,0.906f,0.463f, 1.0f);
		char buf[256];
		sprintf(buf,"%i",i);
		automatFont.drawString(buf,6 + xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh);
		
		if(diameterBeingCalibrated == i){
			ofFill();
			glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
		}else{
			ofFill();
			glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
		}
		ofCircle(xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh, diameters[i]);
	}
	glDisable(GL_BLEND);

}

//---------------------------------------------------------
void matrixAreas::draw(bool* _areas){
	
	glEnable(GL_BLEND);
	for (int i = 0; i < numAreas; i++){
		
		if(pointBeingCalibrated == i){
			ofFill();
			glColor4f(0.847f,0.25f,0.25f, 0.8f);
		}else if(!_areas[i]){
			ofNoFill();
			glColor4f(0.847f,0.25f,0.25f, 0.3f);
		}else if(_areas[i]){
			ofNoFill();
			glColor4f(1.0f,0.906f,0.463f, 0.3f);
		}
		ofCircle(xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh, 5);
		
		glColor4f(1.0f,0.906f,0.463f, 1.0f);
		char buf[256];
		sprintf(buf,"%i",i);
		automatFont.drawString(buf,6 + xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh);
		
		if(diameterBeingCalibrated == i){
			ofFill();
			glColor4f(1.0f, 1.0f, 1.0f, 0.1f);
		}else if(!_areas[i]){
			ofFill();
			glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
		}else if(_areas[i]){
			ofNoFill();
			glColor4f(1.0f,0.906f,0.463f, 0.3f);
		}
		ofCircle(xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh, diameters[i]);
	}
	glDisable(GL_BLEND);
	
}

//---------------------------------------------------------
void matrixAreas::drawMinimal(){
	
	glEnable(GL_BLEND);
	ofFill();
	for (int i = 0; i < numAreas; i++){
		
		if(pointBeingCalibrated == i){
			ofFill();
			glColor4f(0.847f,0.25f,0.25f, 0.8f);
			
		}else{
			ofNoFill();
			glColor4f(0.847f,0.25f,0.25f, 1.0f);
		}
		ofCircle(xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh, 5);
		
		glColor4f(1.0f,0.906f,0.463f, 1.0f);
		char buf[256];
		sprintf(buf,"%i",i);
		automatFont.drawString(buf,6 + xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh);
	}
	glDisable(GL_BLEND);
	
}

//---------------------------------------------------------
void matrixAreas::drawMinimalWithLines(){
	
	glEnable(GL_BLEND);
	ofFill();
	for (int i = 0; i < numAreas; i++){
		
		if(pointBeingCalibrated == i){
			ofFill();
			glColor4f(0.847f,0.25f,0.25f, 0.8f);
			
		}else{
			ofNoFill();
			glColor4f(0.847f,0.25f,0.25f, 1.0f);
		}
		
		ofCircle(xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh, 5);
		
		glColor4f(1.0f,0.906f,0.463f, 1.0f);
		char buf[256];
		sprintf(buf,"%i",i);
		automatFont.drawString(buf,6 + xCalib + points[i].x*scalew, yCalib + points[i].y*scaleh);
	}
	
	glColor4f(0.847f,0.25f,0.25f, 1.0f);
	
	ofLine(xCalib + points[0].x*scalew, yCalib + points[0].y*scaleh,xCalib + points[1].x*scalew, yCalib + points[1].y*scaleh);
	ofLine(xCalib + points[1].x*scalew, yCalib + points[1].y*scaleh,xCalib + points[2].x*scalew, yCalib + points[2].y*scaleh);
	ofLine(xCalib + points[2].x*scalew, yCalib + points[2].y*scaleh,xCalib + points[3].x*scalew, yCalib + points[3].y*scaleh);
	ofLine(xCalib + points[3].x*scalew, yCalib + points[3].y*scaleh,xCalib + points[0].x*scalew, yCalib + points[0].y*scaleh);
	
	ofLine(xCalib + points[0].x*scalew, yCalib + points[0].y*scaleh,xCalib + points[2].x*scalew, yCalib + points[2].y*scaleh);
	ofLine(xCalib + points[1].x*scalew, yCalib + points[1].y*scaleh,xCalib + points[3].x*scalew, yCalib + points[3].y*scaleh);
	
	glDisable(GL_BLEND);
}

//---------------------------------------------------------
void matrixAreas::drawMinimalGrid(){
	
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	ofNoFill();
    ofSetLineWidth(3);
	for(int x=0; x < resOrigin-1; x++) {
		ofBeginShape();
		for(int y=0; y < resOrigin-1; y++) { 
			ofPoint mp;
			mp = points[(x)+(y)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
			mp = points[(x+1)+(y)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
			mp = points[(x+1)+(y+1)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
			mp = points[(x)+(y+1)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
			mp = points[(x)+(y)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
		}
		ofEndShape();
	}
	
	
	for (int i = 0; i < numAreas; i++){
		if(pointBeingCalibrated == i && imOver[i] == true){
			glColor4f(1.0f,0.906f,0.463f, 1.0f);
			ofRect(xCalib + points[i].x*scalew - 15, yCalib + points[i].y*scaleh - 15, 30,30);
			ofRect(xCalib + points[i].x*scalew - 40, yCalib + points[i].y*scaleh - 40, 80,80);
		}else if(imOver[i] == true){
			glColor4f(1.0f,0.906f,0.463f, 1.0f);
			ofRect(xCalib + points[i].x*scalew - 5, yCalib + points[i].y*scaleh - 5, 10,10);
			ofRect(xCalib + points[i].x*scalew - 10, yCalib + points[i].y*scaleh - 10, 20,20);
			ofRect(xCalib + points[i].x*scalew - 15, yCalib + points[i].y*scaleh - 15, 30,30);
		}else{
			glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
			ofRect(xCalib + points[i].x*scalew - 5, yCalib + points[i].y*scaleh - 5, 10,10);
			ofRect(xCalib + points[i].x*scalew - 10, yCalib + points[i].y*scaleh - 10, 20,20);
		}
		
	}
    ofSetLineWidth(1);
	
	glDisable(GL_BLEND);
	
}

//---------------------------------------------------------
void matrixAreas::drawMinimalGrid(int pX, int pY){
	
    ofPushMatrix();
    ofTranslate(pX, pY, 0.0f);
    
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	ofNoFill();
	ofSetLineWidth(3);
	for(int x=0; x < resOrigin-1; x++) {
		ofBeginShape();
		for(int y=0; y < resOrigin-1; y++) { 
			ofPoint mp;
			mp = points[(x)+(y)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
			mp = points[(x+1)+(y)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
			mp = points[(x+1)+(y+1)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
			mp = points[(x)+(y+1)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
			mp = points[(x)+(y)*resOrigin];
			ofVertex(xCalib + mp.x*scalew, yCalib + mp.y*scaleh);
		}
		ofEndShape();
	}
	
	
	for (int i = 0; i < numAreas; i++){
		if(pointBeingCalibrated == i && imOver[i] == true){
			glColor4f(1.0f,0.906f,0.463f, 1.0f);
			ofRect(xCalib + points[i].x*scalew - 15, yCalib + points[i].y*scaleh - 15, 30,30);
			ofRect(xCalib + points[i].x*scalew - 40, yCalib + points[i].y*scaleh - 40, 80,80);
		}else if(imOver[i] == true){
			glColor4f(1.0f,0.906f,0.463f, 1.0f);
			ofRect(xCalib + points[i].x*scalew - 5, yCalib + points[i].y*scaleh - 5, 10,10);
			ofRect(xCalib + points[i].x*scalew - 10, yCalib + points[i].y*scaleh - 10, 20,20);
			ofRect(xCalib + points[i].x*scalew - 15, yCalib + points[i].y*scaleh - 15, 30,30);
		}else{
			glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
			ofRect(xCalib + points[i].x*scalew - 5, yCalib + points[i].y*scaleh - 5, 10,10);
			ofRect(xCalib + points[i].x*scalew - 10, yCalib + points[i].y*scaleh - 10, 20,20);
		}
		
	}
	ofSetLineWidth(1);
	
	glDisable(GL_BLEND);
    
    ofPopMatrix();
	
}

//---------------------------------------------------------
void matrixAreas::loadSettings(string filename_){

	ofxXmlSettings  xml;

    if( xml.loadFile(filename_) ){
		printf("Loaded %s settings.\n",filename_.c_str());
	}else{
		printf("Unable to load %s settings, check data/ folder\n",filename_.c_str());
		return;
	}

	char temp[255];

	for (int i = 0; i < numAreas; i++){
			sprintf(temp, "matrixArea_%i_X", i);
			points[i].x = xml.getValue(temp, 0.0f);
			sprintf(temp, "matrixArea_%i_Y", i);
			points[i].y = xml.getValue(temp, 0.0f);
			sprintf(temp, "matrixArea_%i_D", i);
			diameters[i] = xml.getValue(temp, 0.0f);
	}

}

//---------------------------------------------------------
void matrixAreas::saveSettings(string filename_){

	ofxXmlSettings  xml;
    xml.loadFile(filename_);

	char temp[255];

	for (int i = 0; i < numAreas; i++){
		sprintf(temp, "matrixArea_%i_X", i);
		xml.setValue(temp, (points[i].x));
		sprintf(temp, "matrixArea_%i_Y", i);
		xml.setValue(temp, (points[i].y));
		sprintf(temp, "matrixArea_%i_D", i);
		xml.setValue(temp, (diameters[i]));
	}
	xml.saveFile(filename_);
	
	printf("Saved settings on %s\n",filename_.c_str());

}
