#pragma once

#include "ofxSimpleGuiControl.h"

#include "ofxSimpleGuiSliderBase.h"


class ofxSimpleGuiSliderInt : public ofxSimpleGuiSliderBase<int> {
	
public:
	ofxSimpleGuiSliderInt(string name, int &value, int min, int max, float smoothing = 0) : ofxSimpleGuiSliderBase<int>(name, value, min, max, smoothing) {
		controlType = "SliderInt";
	}

};
