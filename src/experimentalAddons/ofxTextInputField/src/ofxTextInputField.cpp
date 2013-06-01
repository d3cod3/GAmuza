//
//  textInput.cpp
//
//  Created by Elliot Woods on 09/12/2011.
//  Copyright 2011 Kimchi and Chips.
//
//  modified by James George 12/2/2011
//  modified by Momo the Monster 7/10/2012
//  swappable fonts added by James George 9/11/2012
//
//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//

#include "ofxTextInputField.h"


ofxTextInputField::ofxTextInputField() {
	text = "";
	cursorPosition = 0;
	cursorx = 0;
	cursory = 0;
	fontRef = NULL;
    isEnabled = false;
	isEditing = false;
    bounds = ofRectangle(0,0,100,18);
    drawCursor = false;
	autoClear = false;
	mouseDownInRect = false;
    //isSetup = false;
}

ofxTextInputField::~ofxTextInputField(){
	if(isEnabled){
        disable();
    }

}

void ofxTextInputField::setup(){
	enable();
}


void ofxTextInputField::enable(){
	if(!isEnabled){
		ofAddListener(ofEvents().mousePressed, this, &ofxTextInputField::mousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &ofxTextInputField::mouseReleased);
		isEnabled = true;
	}
}

void ofxTextInputField::disable(){
	if(isEditing){
		endEditing();
	}
	if(isEnabled){
        ofRemoveListener(ofEvents().mousePressed, this, &ofxTextInputField::mousePressed);
		ofRemoveListener(ofEvents().mouseReleased, this, &ofxTextInputField::mouseReleased);
		isEnabled = false;
    }
	
}
void ofxTextInputField::beginEditing() {
    if(!isEditing){
        ofAddListener(ofEvents().keyPressed, this, &ofxTextInputField::keyPressed);
        ofSendMessage(TEXTFIELD_IS_ACTIVE);
        isEditing = true;
        drawCursor = true;
		if(autoClear){
			clear();
		}
		else{
			cursory = 0;
			cursorPosition = cursorx = text.size();
		}
    }
}

void ofxTextInputField::endEditing() {
    if(isEditing){
        ofRemoveListener(ofEvents().keyPressed, this, &ofxTextInputField::keyPressed);
        ofSendMessage(TEXTFIELD_IS_INACTIVE);
        ofNotifyEvent(textChanged, text, this);
        isEditing = false;
        drawCursor = false;
    }
}

void ofxTextInputField::setFont(OFX_TEXTFIELD_FONT_RENDERER& font){
	fontRef = &font;
}

bool ofxTextInputField::getIsEditing(){
    return isEditing;
}

bool ofxTextInputField::getIsEnabled(){
	return isEnabled;
}

void ofxTextInputField::draw() {
    
	ofPushMatrix();
	ofTranslate(bounds.x, bounds.y);
	
	//draw text
	if(fontRef == NULL){
		//boo don't use this
		ofDrawBitmapString(text, 5, 12);
	}
	else{
		fontRef->drawString(text, 5, fontRef->getLineHeight());
	}

	//draw cursor line
    if(drawCursor) {
        ofPushStyle();
        float timeFrac = 0.5 * sin(3.0f * ofGetElapsedTimef()) + 0.5;
        
        ofColor col = ofGetStyle().color;
        
		int cursorPos = fontRef == NULL ? 8*cursorx + 10: fontRef->stringWidth(text.substr(0,cursorx))+13;
        ofSetColor(col.r * timeFrac, col.g * timeFrac, col.b * timeFrac);
        ofSetLineWidth(3.0f);
		int lineBottom = fontRef == NULL ? 13.7*cursory+12 : 13.7*cursory+fontRef->getLineHeight()+3;
		//TODO: multiline with fontRef
        ofLine(cursorPos, 13.7*cursory+2,
			   cursorPos, lineBottom);
        ofPopStyle();
    }
	
	ofPopMatrix();
}

void ofxTextInputField::mousePressed(ofMouseEventArgs& args){
	mouseDownInRect = bounds.inside(args.x, args.y);
}

void ofxTextInputField::mouseReleased(ofMouseEventArgs& args){

    if(bounds.inside(args.x, args.y)) {
        if(!isEditing && mouseDownInRect){
	        beginEditing();
        }
    }
    else if(isEditing){
		endEditing();
	}
}

void ofxTextInputField::keyPressed(ofKeyEventArgs& args) {	
	//ew: add charachter (non unicode sorry!)
	//jg: made a step closer to this with swappable renderers and ofxFTGL -- but need unicode text input...
	
	int key = args.key;
	if (key == OF_KEY_RETURN) {
        endEditing();
        return;
	}
	
	if (key >=32 && key <=126) {
		text.insert(text.begin()+cursorPosition, key);
		cursorPosition++;
	}
	
	
	if (key==OF_KEY_BACKSPACE) {
		if (cursorPosition>0) {
			text.erase(text.begin()+cursorPosition-1);
			--cursorPosition;
		}
	}
	
	if (key==OF_KEY_DEL) {
		if (text.size() > cursorPosition) {
			text.erase(text.begin()+cursorPosition);
		}
	}
	
	if (key==OF_KEY_LEFT){
		if (cursorPosition>0){
			--cursorPosition;
		}
	}
	
	if (key==OF_KEY_RIGHT){
		if (cursorPosition<text.size()){
			++cursorPosition;	
		}
	}
	
	//for multiline:
	cursorx = cursory = 0;
	if(text.size() > 0){
		for (int i=0; i<cursorPosition; ++i) {
			if (*(text.begin()+i) == '\n') {
				++cursory;
				cursorx = 0;
			} else {
				cursorx++;
			}
		}
	}
}

void ofxTextInputField::clear() {
	text.clear();
	cursorx = cursory = 0;
	cursorPosition = 0;
}
