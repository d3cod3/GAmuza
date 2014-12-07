/*
 *  ofxSubtitles.h
 *  Colaborama
 *
 *  Created by Patricio González Vivo on 22/10/10.
 *  Copyright 2010 PatricioGonzalezVivo.com. All rights reserved.
 *
 */
#ifndef _ofxSUBTITLES
#define _ofxSUBTITLES

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

#include <iomanip>
//#include <strstream>

#include <iostream>
#include <fstream>
#include <vector>

//using namespace std; 

typedef struct {
	float	inSec;
	float	outSec;
	string	text;
}subTitle;

class ofxSubtitles{
public:
	vector<subTitle>	subtitles;

	ofxSubtitles();
	
	void		load(const string& filePath);
	void		save(const string& filePath);
		
	void		add(float inSec, string text);
	void		add(float inSec, float outSec, string text);
	
	int			getHowMany(float _fromSec, float _untilSec);
	int			getFirstSubN(float _fromSec );
	string		getLineAt(float _inSec){subTitle s = getSubTitleAt(_inSec); return s.text; };
	subTitle	getSubTitleAt(float _inSec);
	
	bool		isStringAt(string search, float sec);
	
	void		replace(string searchString, string replaceFor, float sec);
	
	ofxTrueTypeFontUC	font;
	void		loadfont(string fontPath,int dim){font.loadFont(fontPath,dim,true,true,true);};
	
	int			screenWidth, screenHeight;
	void		setScreen(int width, int height){screenWidth = width; screenHeight = height; };
	
	ofColor		color;
	void		setColor(int r, int g, int b){color.r = r; color.g = g; color.b = b;};
	void		setColor(int r, int g, int b, int a){color.r = r; color.g = g; color.b = b; color.a = a;};
	
	void		draw(float inSec){draw(0,0,screenWidth,screenHeight,inSec);};
	void		draw(int x, int y, float inSec){draw(x,y,screenWidth,screenHeight,inSec);};
	void		draw(int x, int y, int w, int h, float inSec);
};
#endif 
