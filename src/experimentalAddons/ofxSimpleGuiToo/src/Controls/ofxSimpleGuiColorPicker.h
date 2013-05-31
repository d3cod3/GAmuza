#pragma once

#include "ofxSimpleGuiControl.h"


class ofxSimpleGuiColorPicker : public ofxSimpleGuiControl {
public:
	
	float		*values;
	float		min, max;
	
	float		barwidth[4];
	float		pct[4];
	
	ofxSimpleGuiColorPicker(string name, float *values, float max = 1);
	void setup();
	void loadFromXML(ofxXmlSettings &XML);
	void saveToXML(ofxXmlSettings &XML);
	float getValue(int i);
	void set(float f, int i);
	void updateSlider();	
	void onPress(int x, int y, int button);
	void onDragOver(int x, int y, int button);
	void onDragOutside(int x, int y, int button);
	void update();
	void draw(float x, float y);
};
