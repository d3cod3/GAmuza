#ifndef OFXBLUESCREEN_H
#define OFXBLUESCREEN_H

#include "ofMain.h"

class ofxChromaKey: public ofImage {

public:
	ofxChromaKey();
	~ofxChromaKey();

	void setPixels(ofPixelsRef pixels);
	void setPixels(unsigned char*, int w, int h);
	void learnBgColor(ofPixelsRef pixels);
	void setBgColor(ofColor col);
	ofColor getBgColor();
	void setThreshold(float thresh);
	void drawBgColor(int x=0, int y=0, int w=10, int h=10);
	void draw(int x, int y, int w, int h, bool checkers=true);
	float getThreshold();
private:
	void update();
	void drawCheckers(int x, int y, int w, int h);

	ofPixels pixelSource;
	ofColor bgColor;
	float threshold;
	int highestKey;
	bool checkForHighest;
};

#endif // OFXBLUESCREEN_H
