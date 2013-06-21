#ifndef _GAMUZAMAPPING
#define _GAMUZAMAPPING

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupMapping(){
    
    saveMappingSettings = false;
    
    res = gridRes+1;
	realRes = res*res;
	finalTextureMapping.setup(0,0,projectionScreenW,projectionScreenH,realRes);
    
    if(autoLoadMapping == 0){
        finalTextureMapping.loadSettings(GAMUZA_MAPPING_FILE);
        resetMappingPoints();
    }else{
        finalTextureMapping.loadSettings(autoMappingFile);
    }
    
    activateMouseMapping    = true;
    manualEditMappingPoint  = false;
    drawGrid                = false;
    actualMappingPoint = 0;
    totalMappingPoints = realRes;
    
}

//--------------------------------------------------------------
void gamuzaMain::updateMapping(){
    if(!activateMouseMapping){
        finalTextureMapping.update(manualEditMappingPoint,actualMappingPoint);
    }
}

//--------------------------------------------------------------
void gamuzaMain::drawMapping(){
    if(drawGrid){
        ofPushMatrix();
            ofTranslate(fboDrawingPosX,fboDrawingPosY,0);
            ofScale(fboDrawingW/projectionScreenW,fboDrawingH/projectionScreenH,1.0);
            finalTextureMapping.drawMinimalGrid();
        ofPopMatrix();
    }
    if(saveMappingSettings){
        finalTextureMapping.saveSettings(GAMUZA_MAPPING_FILE);
        saveMappingSettings = false;
    }
}

//--------------------------------------------------------------
void gamuzaMain::resetMappingPoints(){
    // warped grid reset
    finalTextureMapping.reset(projectionScreenW,projectionScreenH);
    saveMappingSettings = true;
    finalTextureMapping.saveSettings(GAMUZA_MAPPING_FILE);
    saveMappingSettings = false;
}

//--------------------------------------------------------------
void gamuzaMain::loadMappingPoints(){
	
    char temp[256];
    // warped grid load points
    string URL;
    
    ofFileDialogResult res = ofSystemLoadDialog("Open Mapping File", false);
    if(res.bSuccess == true){
        URL = res.getPath();
        finalTextureMapping.loadSettings(URL);
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
        sprintf(temp,"OPEN MAPPING FILE: %s", URL.c_str());
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, temp);
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
        finalTextureMapping.saveSettings(GAMUZA_MAPPING_FILE);
    }else{
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, "OPEN MAPPING FILE Canceled");
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
    }
	
}

//--------------------------------------------------------------
void gamuzaMain::saveMappingPoints(){
	
    char temp[256];
    saveMappingSettings = true;
    // warped grid save points
    string folderURL;
    string fileName;
    
    ofFileDialogResult res = ofSystemSaveDialog(folderURL, "Save Mapping File");
    if(res.bSuccess == true){
        folderURL = res.getPath();
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
        sprintf(temp,"SAVE MAPPING FILE: %s", folderURL.c_str());
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, temp);
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
        finalTextureMapping.saveSettings(folderURL);
        finalTextureMapping.saveSettings(GAMUZA_MAPPING_FILE);
    }else{
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, "SAVE MAPPING FILE Canceled");
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
    }
    saveMappingSettings = false;
	
}

//--------------------------------------------------------------
void gamuzaMain::toggleDrawGrid(){
    drawGrid = !drawGrid;
}

//--------------------------------------------------------------
bool gamuzaMain::switchMouseKeyControl(){
    activateMouseMapping = !activateMouseMapping;
    
    return activateMouseMapping;
}

//--------------------------------------------------------------
void gamuzaMain::manualPointEditON(){
    if(!activateMouseMapping){
        manualEditMappingPoint = true; // OF_KEY_RETURN
    }
}

//--------------------------------------------------------------
void gamuzaMain::manualPointEditOFF(){
    if(!activateMouseMapping){
        manualEditMappingPoint = false; // OF_KEY_BACKSPACE
    }
}

//--------------------------------------------------------------
void gamuzaMain::northMappingPoint(){
    if(!activateMouseMapping){
        if(manualEditMappingPoint){
            finalTextureMapping.points[actualMappingPoint].y--;
        }else{
            if(actualMappingPoint > gridRes){
                actualMappingPoint -= (gridRes+1);
            }else{
                actualMappingPoint += (gridRes+1)*gridRes;
            }
        }
    }
}

//--------------------------------------------------------------
void gamuzaMain::southMappingPoint(){
    if(!activateMouseMapping){
        if(manualEditMappingPoint){
            finalTextureMapping.points[actualMappingPoint].y++;
        }else{
            if(actualMappingPoint < ((gridRes+1)*(gridRes+1))-(gridRes+1)){
                actualMappingPoint += (gridRes+1);
            }else{
                actualMappingPoint -= (gridRes+1)*gridRes;
            }
        }
    }
}

//--------------------------------------------------------------
void gamuzaMain::eastMappingPoint(){
    if(!activateMouseMapping){
        if(!manualEditMappingPoint){
            if(actualMappingPoint < totalMappingPoints){
                actualMappingPoint++;
            }else{
                actualMappingPoint = 0;
            }
        }else{
            finalTextureMapping.points[actualMappingPoint].x++;
        }
    }
}

//--------------------------------------------------------------
void gamuzaMain::westMappingPoint(){
    if(!activateMouseMapping){
        if(!manualEditMappingPoint){
            if(actualMappingPoint > 0){
                actualMappingPoint--;
            }else{
                actualMappingPoint = totalMappingPoints-1;
            }
        }else{
            finalTextureMapping.points[actualMappingPoint].x--;
        }
    }
}

//--------------------------------------------------------------
void gamuzaMain::applyHomography(){
	
	//lets make a matrix for openGL
	//this will be the matrix that peforms the transformation
	GLfloat myMatrix[16];
	
	//we set it to the default - 0 translation
	//and 1.0 scale for x y z and w
	for(int i = 0; i < 16; i++){
		if(i % 5 != 0) myMatrix[i] = 0.0;
		else myMatrix[i] = 1.0;
	}
	
	//we need our points as opencv points
	CvPoint2D32f cvsrc[realRes];
	CvPoint2D32f cvdst[realRes];
	
	//we set the warp coordinates
	//source coordinates as the dimensions of our FBO texture
	for(int i=0;i<realRes;i++){
		float x = (i % res) / (float)(res-1);
		float y = (i / res) / (float)(res-1);
		cvsrc[i].x = x*projectionScreenW;
		cvsrc[i].y = y*projectionScreenH;
	}
	
	for(int i=0; i<realRes;i++){
		cvdst[i].x = finalTextureMapping.points[i].x;
		cvdst[i].y = finalTextureMapping.points[i].y;
	}
	
	//we create a matrix that will store the results
	//from openCV - this is a 3x3 2D matrix that is
	//row ordered
	CvMat * translate = cvCreateMat(3,3,CV_32FC1);
	
	//for the more accurate method we need to create
	//a couple of matrixes that just act as containers
	//to store our points  - the nice thing with this
	//method is you can give it more than four points!
	
	CvMat* src_mat = cvCreateMat( realRes, 2, CV_32FC1 );
	CvMat* dst_mat = cvCreateMat( realRes, 2, CV_32FC1 );
	
	//copy our points into the matrixes
	cvSetData( src_mat, cvsrc, sizeof(CvPoint2D32f));
	cvSetData( dst_mat, cvdst, sizeof(CvPoint2D32f));
	
	//figure out the warping!
	cvFindHomography(src_mat, dst_mat, translate);
	
	//get the matrix as a list of floats
	float *matrix = translate->data.fl;
	
	//we need to copy these values
	//from the 3x3 2D openCV matrix which is row ordered
	//
	// ie:   [0][1][2] x
	//       [3][4][5] y
	//       [6][7][8] w
	
	//to openGL's 4x4 3D column ordered matrix
	//        x   y   z   w
	// ie:   [0] [4] [8][12]
	//       [1] [5] [9][13]
	//       [2] [6][10][14]
	//		 [3] [7][11][15]
	//
	
	myMatrix[0]		= matrix[0];
	myMatrix[4]		= matrix[1];
	myMatrix[12]	= matrix[2];
	
	myMatrix[1]		= matrix[3];
	myMatrix[5]		= matrix[4];
	myMatrix[13]	= matrix[5];
	
	myMatrix[3]		= matrix[6];
	myMatrix[7]		= matrix[7];
	myMatrix[15]	= matrix[8];
	
	//finally lets multiply our matrix
	glMultMatrixf(myMatrix);
    
}

//--------------------------------------------------------------
void gamuzaMain::applyGridMesh(int xCalib, int yCalib, int w, int h){
	
	float xStep = w/gridRes;
	float yStep = h/gridRes;
	
	glBegin(GL_QUADS);
	for(int x=0; x < gridRes; x++) {
		for(int y=0; y < gridRes; y++) {
			int revY =  y;
			ofPoint mp;
			
			mp = finalTextureMapping.points[(x)+(y+1)*res];
			glTexCoord2f(x*xStep, (revY+1)*yStep);
			glVertex3f(xCalib+mp.x,yCalib+mp.y,0);
			
			mp = finalTextureMapping.points[(x+1)+(y+1)*res];
			glTexCoord2f((x+1)*xStep, (revY+1)*yStep);
			glVertex3f(xCalib+mp.x,yCalib+mp.y,0);
			
			mp = finalTextureMapping.points[(x+1)+(y)*res];
			glTexCoord2f((x+1)*xStep, (revY)*yStep);
			glVertex3f(xCalib+mp.x,yCalib+mp.y,0);
			
			mp = finalTextureMapping.points[(x)+(y)*res];
			glTexCoord2f(x*xStep, (revY)*yStep);
			glVertex3f(xCalib+mp.x,yCalib+mp.y,0);
			
		}
	}
	glEnd();
	
}

#endif
