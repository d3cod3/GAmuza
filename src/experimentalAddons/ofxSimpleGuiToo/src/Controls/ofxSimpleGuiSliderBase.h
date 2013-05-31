#pragma once

#include "ofxSimpleGuiControl.h"



template <typename Type> class ofxSimpleGuiSliderBase : public ofxSimpleGuiControl {
public:

	Type		*value;
	Type		min, max;

	float		barwidth;
	float		pct;

	float		lerpSpeed;
	Type		targetValue;
	Type		oldValue;

	//--------------------------------------------------------------------- construct
	ofxSimpleGuiSliderBase(string name, Type &value, Type min, Type max, float smoothing = 0) : ofxSimpleGuiControl(name) {
		this->value = &value;
		this->min	= min;
		this->max	= max;

		lerpSpeed	= 1.0f - smoothing * 0.99;		// so smoothing :1 still results in some motion!
		targetValue	= value;
		oldValue	= targetValue;
		controlType = "SliderBase";
		setup();
	}

	void setup() {
		setSize(config->gridSize.x - config->padding.x, config->sliderHeight + config->sliderTextHeight);
		pct		 = ofMap((*value), min, max, 0.0, width);
		barwidth = pct;
	}

	void loadFromXML(ofxXmlSettings &XML) {
		set((Type)XML.getValue("controls:" + controlType + "_" + key + ":value", 0.0f));
	}

	void saveToXML(ofxXmlSettings &XML) {
		XML.addTag(controlType + "_" + key);
		XML.pushTag(controlType + "_" + key);
		XML.addValue("name", name);
		XML.addValue("value", getValue());
		XML.popTag();
	}



	Type getValue() {
		return (*value);
	}


	void set(Type f) {
		if(f < min) f = min;
		else if(f > max) f = max;
		(*value) = f;
	}

	void add() {
		pct += .05f;
		float temp = ofMap(pct, 0.0, width, min, max);

		//VALUE CLAMP
		if(temp >= max)			temp = max;
		else if(temp <= min)	temp = min;

		targetValue = (Type)temp;
		oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
	}

	void sub() {
		pct -= .05f;
		float temp = ofMap(pct, 0.0, width, min, max);

		//VALUE CLAMP
		if(temp >= max)			temp = max;
		else if(temp <= min)	temp = min;

		targetValue = (Type)temp;
		oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
	}


	void updateSlider() {
		if(!enabled) return;

		if(pct > width) {
			pct = width;
		}
		else {
			pct = getMouseX() - x;
			float temp = ofMap(pct, 0.0, (float)width, min, max);

			//VALUE CLAMP
			if(temp >= max)			temp = max;
			else if(temp <= min)	temp = min;

			targetValue = (Type)temp;
			oldValue = *value;		// save oldValue (so the draw doesn't update target but uses it)
		}
	}

	void onPress(int x, int y, int button) {
		updateSlider();
	}

	void onDragOver(int x, int y, int button) {
		updateSlider();
	}

	void onDragOutside(int x, int y, int button) {
		updateSlider();
	}



	void onKeyRight() {
		add();
	}

	void onKeyLeft() {
		sub();
	}


	//--------------------------------------------------------------------- update
	void update() {
		if(!enabled) return;

		if(lock) {
			updateSlider();
		}

//		enabled = false;

	}

	//--------------------------------------------------------------------- draw
	void draw(float x, float y) {

//		enabled = true;

		if(oldValue != *value) {					// if value has changed programmatically by something else
			oldValue = targetValue = *value;			// save the value in target and oldvalue
		} else {									// otherwise lerp
			*value += (Type)((targetValue - *value) * lerpSpeed);
			oldValue = *value;							// and save oldvalue
		}

		//update postion of gui object
		setPos(x, y);

		//VALUE CLAMP
		barwidth = ofMap((*value), min, max, 0.0, (float)width);
		if(barwidth > width) barwidth = width;
		else if(barwidth < 0) barwidth = 0;

		ofEnableAlphaBlending();
		glPushMatrix();
		glTranslatef(x, y, 0);
		ofFill();

		setEmptyColor();
		ofRect(0, 0, width, config->sliderHeight);


		setFullColor();
		ofRect(0, 0, barwidth, config->sliderHeight);

		setTextBGColor();
		ofRect(0, config->sliderHeight, width, config->sliderTextHeight);

		setTextColor();
		string s = name + ": " + ofToString((*value));
		ofDrawBitmapString(s, 3, config->sliderHeight + 14);
		ofDisableAlphaBlending();
		glPopMatrix();
	}



};
