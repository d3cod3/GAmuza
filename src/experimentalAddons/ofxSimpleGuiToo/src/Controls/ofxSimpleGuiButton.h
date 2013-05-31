#pragma once

#include "ofxSimpleGuiControl.h"


class ofxSimpleGuiButton : public ofxSimpleGuiControl {
public:
	bool*			value;
	
	bool			beToggle;
	bool			beenPressed;
	
	ofxSimpleGuiButton(string name, bool &value);	
	void setup();
	void loadFromXML(ofxXmlSettings &XML);	
	void saveToXML(ofxXmlSettings &XML);
	void keyPressed( int key );
	bool getValue();
	void set(bool b);
	void toggle();
	void setToggleMode(bool b);
	void onPress(int x, int y, int button);
	void onRelease(int x, int y, int button);
	void draw(float x, float y);
};
