//
// ofxShowGrid.cpp
// ofxShowGrid
//
// Created by Nicolas Boillot on 13-12-05.
// Copyright 2013 fluate.net All rights reserved.
//

#include "ofxShowGrid.h"


void ShowGoldenRatio(int widthG, int heightG, int decalX, int decalY) {
	double phi = (1 + sqrt(5)) / 2; // 1.61803 Golden number
	double phiHat = (1 - sqrt(5)) / 2; // Inv Golden number, ca. 0.61803398874
    
	int FibNumberH = (heightG + (phiHat * heightG)); // 1st golden number
	int FibNumberW = (widthG  + (phiHat * widthG));
    
	int FibNumberH2 = -(phiHat * heightG); // 2nd golden number
	int FibNumberW2 = -(phiHat * widthG);
    
	int FibNumberH3 = FibNumberH2 - FibNumberH; // 3rd golden number
	int FibNumberW3 = FibNumberW2 - FibNumberW;
    
	ofSetHexColor(0x00ff00); // 1st golden number lines green
    
	ofLine(decalX, decalY + heightG - FibNumberH, decalX + widthG, decalY + heightG - FibNumberH);
	ofLine(decalX, decalY + FibNumberH, decalX + widthG, decalY + FibNumberH);
	ofLine(decalX + widthG - FibNumberW, decalY, decalX + widthG - FibNumberW, heightG + decalY);
	ofLine(decalX + FibNumberW, decalY, decalX + FibNumberW, heightG + decalY);
    
	ofSetHexColor(0xcccccc); // 3rd golden number lines gray
    
	ofLine(decalX, decalY + heightG - FibNumberH3, decalX + widthG, decalY + heightG - FibNumberH3);
	ofLine(decalX, decalY + FibNumberH3, decalX + widthG, decalY + FibNumberH3);
	ofLine(decalX + widthG - FibNumberW3, decalY, decalX + widthG - FibNumberW3, heightG + decalY);
	ofLine(decalX + FibNumberW3, decalY, decalX + FibNumberW3, heightG + decalY);
    
	ofSetHexColor(0xffffff);
}

void ShowThirdRatio(int widthG, int heightG, int decalX, int decalY) {
	int ThirdRatioH = heightG / 3;
	int ThirdRatioW = widthG / 3;
    
	ofSetHexColor(0xff0000); // Third Ratio lines red
    
	ofLine(decalX, decalY + heightG - ThirdRatioH, decalX + widthG, decalY + heightG - ThirdRatioH);
	ofLine(decalX, decalY + ThirdRatioH, decalX + widthG, decalY + ThirdRatioH);
    
	ofLine(decalX + widthG - ThirdRatioW, decalY, decalX + widthG - ThirdRatioW, heightG + decalY);
	ofLine(decalX + ThirdRatioW, decalY, decalX + ThirdRatioW, heightG + decalY);
    
	ofSetHexColor(0xffffff);
}

void ShowCenter(int widthG, int heightG, int decalX, int decalY) {
	int CenterRatioH = heightG / 2;
	int CenterRatioW = widthG / 2;
    
	ofSetHexColor(0xffffff); // Center lines white
    
	ofLine(decalX, decalY + CenterRatioH, decalX + widthG, decalY + CenterRatioH);
	ofLine(decalX + CenterRatioW, decalY, decalX + CenterRatioW, heightG + decalY);
    
	ofSetHexColor(0xffffff);
}

void ShowGrid(int widthG, int heightG, int sizeW, int sizeH, int decalX, int decalY) {
	ofSetHexColor(0x0000ff); // Grid lines blue
    
	for (int i = 0; i <= (widthG + decalX); i += sizeW) {
		if (i < (widthG + decalX)) {
			ofLine(decalX + i, decalY, decalX + i, heightG + decalY);
		}
	}
    
	for (int i = 0; i <= (widthG + decalX); i += sizeH) {
		if (i < (heightG + decalY)) {
			ofLine(decalX, decalY + i, decalX + widthG, decalY + i);
		}
	}
    
	ofSetHexColor(0xffffff);
}
