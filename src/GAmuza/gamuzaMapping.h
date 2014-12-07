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
void gamuzaMain::gaussian_elimination(float *input, int n){
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
                for(int k=0; k<n; k++){
                    float aux = A[i*n+k];
                    A[i*n+k]=A[maxi*n+k];
                    A[maxi*n+k]=aux;
                }
            //Now A[i,j] will contain the old value of A[maxi,j].
            //divide each entry in row i by A[i,j]
            float A_ij=A[i*n+j];
            for(int k=0; k<n; k++){
                A[i*n+k]/=A_ij;
            }
            //Now A[i,j] will have the value 1.
            for(int u = i+1; u< m; u++){
                //subtract A[u,j] * row i from row u
                float A_uj = A[u*n+j];
                for(int k=0; k<n; k++){
                    A[u*n+k]-=A_uj*A[i*n+k];
                }
                //Now A[u,j] will be 0, since A[u,j] - A[i,j] * A[u,j] = A[u,j] - 1 * A[u,j] = 0.
            }
            
            i++;
        }
        j++;
    }
    
    //back substitution
    for(int i=m-2; i>=0; i--){
        for(int j=i+1; j<n-1; j++){
            A[i*n+m]-=A[i*n+j]*A[j*n+m];
        }
    }
}

//--------------------------------------------------------------
void gamuzaMain::findHomography(ofPoint src[4], ofPoint dst[4], float homography[16]){
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
    
    float P[8][9]=
    {
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
    float aux_H[]= { P[0][8],P[3][8],0,P[6][8], // h11  h21 0 h31
        P[1][8],P[4][8],0,P[7][8], // h12  h22 0 h32
        0      ,      0,0,0,       // 0    0   0 0
        P[2][8],P[5][8],0,1
    };      // h13  h23 0 h33
    
    for(int i=0; i<16; i++) homography[i] = aux_H[i];
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
