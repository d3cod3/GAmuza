
#include "ofxVectorField.h"

// -----------------------------------------------------------------
// ofxVectorField()
// the constructor
// -----------------------------------------------------------------

ofxVectorField::ofxVectorField(){
	
	bIsAllocated = false;
}

// -----------------------------------------------------------------
// ofxVectorField()
// the deconstructor
// automatically clears vector field
// -----------------------------------------------------------------

ofxVectorField::~ofxVectorField(){

	if( bIsAllocated ){
	
		deallocate();
	}
}

// -----------------------------------------------------------------
// setup()
// allocates the vector field
// @param x - the # of columns in the vector field
// @param y - the # of rows in the vector field
// @param spacing - the spacing between neighboring rows and colums
// -----------------------------------------------------------------

void ofxVectorField::setup(int w, int h, int spac){
	
	if(!bIsAllocated) {
		
		width = w/spac;
		height = h/spac;
		
		spacing = spac;
		
		int numVectors = width * height;
		
		//printf("allocating!\n");
		
		vectorField = new ofVec2f[numVectors];
		
		bIsAllocated = true;
	
	} else {
		
		printf("vector field is already allocated");
	}
}

// -----------------------------------------------------------------
// deallocate()
// frees the memory in the vector field
// -----------------------------------------------------------------

void ofxVectorField::deallocate(){
	
	if(bIsAllocated){
		
		//printf("deallocating!\n");
	
		delete [] vectorField;
		vectorField = NULL;
	
		bIsAllocated = false;
	}
}

// -----------------------------------------------------------------
// draw()
// draws the vector field, which is super-useful for debugging
// -----------------------------------------------------------------

void ofxVectorField::draw(){
	
	glPushMatrix();
	
	//ofSetColor(255, 255, 255);
	
	glTranslatef(spacing/2, spacing/2, 0);

	for(int y=0; y<height; y+=2){
		for(int x=0; x<width; x+=2){
			
			int pos = y * width + x;
			int startX = x * spacing;
			int startY = y * spacing;
			
			ofLine(startX, startY, startX+vectorField[pos].x*spacing, startY+vectorField[pos].y*spacing);
		}
	}
	
	glPopMatrix();
}

// -----------------------------------------------------------------
// getVector()
// get the vector at a certain position in the vector field
// -----------------------------------------------------------------

ofVec2f ofxVectorField::getVector(int x, int y){
	
	int pos = y * width + x;
	
	return vectorField[pos];
}

// -----------------------------------------------------------------
// getVectorInterpolated()
// get the vector at an interpolated position in the vector field
// @param x -- search position x
// @param y -- search position y
// @param gridW - the width of the particle world (usually ofGetWidth())
// @param gridH - the height of the particle world (usually ofGetHeight())
// -----------------------------------------------------------------

ofVec2f ofxVectorField::getVectorInterpolated(int x, int y, int gridW, int gridH){
	
	ofVec2f newVector;
	
	float pctX = float(x)/gridW;
	float pctY = float(y)/gridH;
	
	int stepX = pctX * width;
	int stepY = pctY * height;
	
	pctX = float(stepX % spacing)/spacing;
	pctY = float(stepY % spacing)/spacing;
	
	stepX = ofClamp(stepX, 0, width-1);
	stepY = ofClamp(stepY, 0, height-1);
	
	newVector.x = vectorField[stepY * width + stepX + 1].x * pctX +  vectorField[stepY * width + stepX].x  * (1.0 - pctX);
	newVector.y = vectorField[(stepY + 1) * width + stepX].y * pctY +  vectorField[stepY * width + stepX].y  * (1.0 - pctY);
	
	//printf("testing %i %i %f %f\n", stepX, stepY, pctX, pctY);
	return newVector;
}

// -----------------------------------------------------------------
// setFromImage()
// creates a vector field from an image 
// accepts OF_IMAGE_GRAYSCALE, OF_IMAGE_COLOR, and OF_IMAGE_COLOR_ALPHA
// -----------------------------------------------------------------

void ofxVectorField::setFromImage(ofImage & image){

	int imgW = image.width;
	int imgH = image.height;
	int imgPixelCount = imgW * imgH;
	
	if( !bIsAllocated){
		
		printf("ofxVectorField not allocated -- allocating automatically using default spacing\n");
		setup(imgW, imgH, OFX_VECFIELD_DEFALT_SPACING);
	}
	
	// storage for brightness
	unsigned char * imagePixels = image.getPixels();
	unsigned char brightness[imgPixelCount];
	
	if( image.getPixelsRef().getImageType() == OF_IMAGE_GRAYSCALE){
		
		for(int x=0; x<imgW; x++){
			for(int y=0; y<imgH; y++){
				
				int srcPos = y * imgW + x;

				unsigned char b = imagePixels[srcPos];
				
				brightness[srcPos] = b;
			}
		}
		
	} else {
		
		// convert RGB to luma
		unsigned char * imagePixels = image.getPixels();
		unsigned char brightness[imgPixelCount];
		int bpp = image.getPixelsRef().getBytesPerPixel();
		
		for(int x=0; x<imgW; x++){
			for(int y=0; y<imgH; y++){
				
				int dstPos = y * imgW + x;
				int srcPos = dstPos * 3;
				
				unsigned char r = imagePixels[srcPos];
				unsigned char g = imagePixels[srcPos+1];
				unsigned char b = imagePixels[srcPos+2];
				
				brightness[dstPos] = ( r * 0.299) + (.587 * g) + (.114 * b);
			}
		}
	}
	
	// detetermine the vector at each position in the image

	for(int x=1; x<width-1; x++){
		for(int y=1; y<height-1; y++){
	
			int vecPos = y * width + x;
			char areaPixels[9];
			
			// loop through the area pixels
			for(int i=-1; i<=1; i++){
				for(int j=-1; j<=1; j++){
					
					// determine where to read from in the area (not optimized)
					int readPos = ((y + j) * spacing * imgW + (x + i)*spacing) * 3;
					
					unsigned char R = imagePixels[readPos];
					unsigned char G = imagePixels[readPos+1];
					unsigned char B = imagePixels[readPos+2];
					
					char BR = (0.299 * R) + (.587 * G) + (.114 * B);
					
					int writePos = (j+1) * 3 + (i + 1);
					
					areaPixels[writePos] = BR;
				}
			}
			
			float dX = (areaPixels[0] + areaPixels[3] + areaPixels[6])/3 - (areaPixels[2] + areaPixels[5] + areaPixels[8])/3;
			float dY = (areaPixels[0] + areaPixels[1] + areaPixels[2])/3 - (areaPixels[6] + areaPixels[7] + areaPixels[8])/3;
			
			vectorField[vecPos].x = dY;
			vectorField[vecPos].y = dX;
		}
	}
	
	// copy pixels to the top and bottom
	
	for(int x=0; x<width; x++){
	
		int dstPos = x;
		int srcPos = x + width;
		
		vectorField[dstPos].x = vectorField[srcPos].x;
		vectorField[dstPos].y = vectorField[srcPos].y;
		
		dstPos = x + (height-1)*width;
		srcPos = x + (height-2)*width;
		
		vectorField[dstPos].x = vectorField[srcPos].x;
		vectorField[dstPos].y = vectorField[srcPos].y;
	}
	
	// copy pixels to the left and right sides
	
	for(int y=0; y<height; y++){
		
		int dstPos = y * width;
		int srcPos = y * width + 1;
		
		vectorField[dstPos].x = vectorField[srcPos].x;
		vectorField[dstPos].y = vectorField[srcPos].y;
		
		dstPos = y * width + width-1;
		srcPos = y * width + width-2;
		
		vectorField[dstPos].x = vectorField[srcPos].x;
		vectorField[dstPos].y = vectorField[srcPos].y;
	}
	
	// copy pixels to the corners
	
	// top left
	vectorField[0].x = vectorField[width+1].x;
	vectorField[0].y = vectorField[width+1].y;
	
	// top right
	vectorField[width-1].x = vectorField[width+width-2].x;
	vectorField[width-1].y = vectorField[width+width-2].y;
	
	// bottom right
	vectorField[(height-1)*width+width-1].x = vectorField[(height-2)*width+width-2].x;
	vectorField[(height-1)*width+width-1].y = vectorField[(height-2)*width+width-2].y;
	
	// bottom left
	vectorField[(height-1)*width].x = vectorField[(height-2)*width+1].x;
	vectorField[(height-1)*width].y = vectorField[(height-2)*width+1].y;
}


// -----------------------------------------------------------------
// randomize()
// generate smoothed random vector field using signed noise
// -----------------------------------------------------------------

void ofxVectorField::randomize(){
	
	float t1 = ofRandom(0,30);
	float t2 = ofRandom(0,30);
	float spacing = 0.0077;
	
	int numVectors = width * height;
	
	for(int i=0; i<numVectors; i++){
		
		int xPos = i % width;
		int yPos = i / width;
		
		vectorField[i].x = ofSignedNoise(xPos*spacing, yPos*spacing, t1);
		vectorField[i].y = ofSignedNoise(xPos*spacing, yPos*spacing, t2);
	}
}

// -----------------------------------------------------------------
// animate()
// generate smoothed time-based random vector field using signed noise
// @param speed - change of values per frame (should be low -- around 0.002)
// -----------------------------------------------------------------

void ofxVectorField::animate(float speed){
	
	float t = (float)ofGetFrameNum() * speed;
	float spacing = 0.017;
	
	int numVectors = width * height;
	
	for(int i=0; i<numVectors; i++){
		
		int xPos = i % width;
		int yPos = i / width;
		
		vectorField[i].x = ofSignedNoise(xPos*spacing, yPos*spacing, t);
		vectorField[i].y = ofSignedNoise(xPos*spacing, yPos*spacing, 10+t);
	}
}

// -----------------------------------------------------------------
// normalize()
// normalizes the vector field
// @param individually - normalizes vector field based on min/max or normalizes individual vectors
// -----------------------------------------------------------------

void ofxVectorField::normalize( bool individually){
	
	int numVectors = width * height;
	
	if(individually){
		
		// adjust on a vector by vector basis
		for(int i=0; i<numVectors; i++){
			
			vectorField[i].normalize();
		}
		
	} else {
		
		// adjust by the maximum distance
		float maxDist = 0;
		
		for(int i=0; i<numVectors; i++){
			
			float dist = sqrt(vectorField[i].x*vectorField[i].x + vectorField[i].y * vectorField[i].y);
			
			if(dist > maxDist){
				
				maxDist = dist;
			}
		}
		
		if(maxDist > 0){
	
			for(int i=0; i<numVectors; i++){
				
				vectorField[i].x /= maxDist;
				vectorField[i].y /= maxDist;
			}
		}
	}	
}

// -----------------------------------------------------------------
// scale()
// scales the vector field
// @param amt - amt to scale the vector field by
// -----------------------------------------------------------------

void ofxVectorField::scale(float amt){
	
	int numVectors = width * height;

	for(int i=0; i<numVectors; i++){
		
		vectorField[i].x *= amt;
		vectorField[i].y *= amt;
	}
}

// -----------------------------------------------------------------
// bias()
// bias the vector field
// @param amt - amt to add to the vector field
// -----------------------------------------------------------------

void ofxVectorField::bias(float amt){
	
	bias(amt, amt);
}

// -----------------------------------------------------------------
// bias()
// bias the vector field
// @param xAmt - amt to add to the columns of the vector field
// @param yAmt - amt to add to the rows of the vector field 
// -----------------------------------------------------------------

void ofxVectorField::bias(float xAmt, float yAmt){
	
	int numVectors = width * height;
	
	for(int i=0; i<numVectors; i++){
		
		vectorField[i].x += xAmt;
		vectorField[i].y += yAmt;
	}
}

// -----------------------------------------------------------------
// map()
// map the values in the vector field to a given range
// @param min - desired min value in vector field
// @param max - desired max value in vector field
// @param bNormalize - perform normalization on vector field
// -----------------------------------------------------------------

void ofxVectorField::map(float min, float max, bool bNormalize){
	
	int numVectors = width * height;
	
	if( bNormalize ){
	
		normalize(false);
		
		for(int i=0; i<numVectors; i++){
			
			int directionX = vectorField[i].x < 0 ? -1 : 1;
			int directionY = vectorField[i].y < 0 ? -1 : 1;
			
			vectorField[i].x = ofMap(fabs(vectorField[i].x), 0., 1., min, max, true) * directionX;
			vectorField[i].y = ofMap(fabs(vectorField[i].y), 0., 1., min, max, true) * directionY;
		}
	
	} else {
	
		float maxDist = 0;
		
		for(int i=0; i<numVectors; i++){
			
			float dist = sqrt(vectorField[i].x*vectorField[i].x + vectorField[i].y * vectorField[i].y);
			
			if(dist > maxDist){
				
				maxDist = dist;
			}
		}
		
		if(maxDist > 0){
			
			for(int i=0; i<numVectors; i++){
				
				vectorField[i].x /= maxDist;
				vectorField[i].y /= maxDist;
			}
		}
	}
}


// -----------------------------------------------------------------
// blur()
// blurs the vector field
// -----------------------------------------------------------------

void ofxVectorField::blur(){

	int vectorCount = width * height;
	
	ofVec2f *tmpArray;
    
    tmpArray = new ofVec2f[vectorCount];
	
	float blurVals[] =  {
	
		0.3, 0.5, 0.3,
		0.5, 0.3, 0.5,
		0.3, 0.5, 0.3
	};
	
	float blurTotal = 0.0;
	
	for(int i=0; i<9; i++) blurTotal += blurVals[i];
	
	for(int i=0; i<vectorCount; i++) tmpArray[i].set(0, 0);
	
	for(int x=1; x<width-1; x++){
		for(int y=1; y<height-1; y++){
	
			int dstPos = y * width + x;
			
			for(int i=-1; i<=1; i++){
				for(int j=-1; j<=1; j++){
			
					int srcPos = (y + j) * width + x + i;
					int arrayPos = (j + 1) * 3 + i + 1;
					
					tmpArray[dstPos] += vectorField[srcPos] * blurVals[arrayPos];
				}
			}
		}
	}
	
	for(int x = 0; x<width; x++) tmpArray[x] = vectorField[x];
	for(int x = 0; x<width; x++) tmpArray[(height-1)*width+x] = vectorField[(height-1)*width+x];
	for(int y = 0; y<height; y++) tmpArray[y*width] = vectorField[y*width];
	for(int y = 0; y<height; y++) tmpArray[y*width+width-1] = vectorField[y*width+width-1];
	
	for(int i=0; i<vectorCount; i++) { 
		
		vectorField[i] = tmpArray[i] / blurTotal;
	}
}

// -----------------------------------------------------------------
// smudge()
// smudges the vector field in a certain position
// @param mousePosition - where to smudge
// @param mouseVector - direction of smudge
// -----------------------------------------------------------------

void ofxVectorField::smudge(ofVec2f mousePos, ofVec2f mouseVec){

	int smudgeSize = 3;
	//float smudgeStep = 1.0/(smudgeSize*2);
	
	for(int i = -smudgeSize; i<=smudgeSize; i++){
		for(int j = -smudgeSize; j<=smudgeSize; j++){
			
			//float pct = percentages[(j + 2) * 5 + i + 2];
			
			//if( i + x / vecFieldSpacing > 0 && i + x / vecFieldSpacing < vecFieldW){
			
			int xPos = int(mousePos.x)/spacing+i;
			int yPos = int(mousePos.y)/spacing+j;
			int pos =  yPos * width + xPos;
			
			float dist = sqrt(i*i + j*j);
			float pct = dist/(smudgeSize*2+1);
			//pct *= pct;
			
			if(xPos >= 0 && xPos < width && yPos >=0 && yPos < height){
				
				//printf("pos %i - %i %i\n", pos, xPos, yPos);
				
				vectorField[pos].x = mouseVec.x * pct + vectorField[pos].x * (1.0 - pct);
				vectorField[pos].y = mouseVec.y * pct + vectorField[pos].y * (1.0 - pct);
				
			}
			
			//vectorField[pos].x = fmax(vectorField[pos].x, 0.01);
			//vectorField[pos].y = fmax(vectorField[pos].y, 0.01);
			//}
		}
	}
}