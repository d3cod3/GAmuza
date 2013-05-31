//
//  ofxTextInputField.cpp
//  ofxTextInputField
//
//  Created by Elliot Woods on 12/09/2011.
//  Copyright 2011 Kimchi and Chips.
//
//  modified by James George 2/12/2011

//	MIT license
//	http://www.opensource.org/licenses/mit-license.php
//
//

#include "ofxTextInputField.h"


ofxTextInputField::ofxTextInputField() {
	text="";
    _name = "";
	cursorPosition=0;
	cursorx=0;
	cursory=0;
    
    bounds.set(0,0,130,16);
    
    font.loadFont("fonts/D3Litebitmapism.ttf", 8);
    selected = false;
    isOver = false;
}

void ofxTextInputField::setup(string name){
    _name = name;
}

void ofxTextInputField::enable() {
	ofAddListener(ofEvents().keyPressed, this, &ofxTextInputField::keyPressed);
}

void ofxTextInputField::disable() {
	ofRemoveListener(ofEvents().keyPressed, this, &ofxTextInputField::keyPressed);
}

void ofxTextInputField::draw(int x, int y) {
    
    ofEnableAlphaBlending();
    
    // draw bounding box
    ofNoFill();
    
    bounds.set(x,y,130,16);
    
    ofSetColor(240,240,240,30);
    ofRect(bounds.x,bounds.y,bounds.width,bounds.height);
    
    ofFill();
	
    ofPushMatrix();
    ofTranslate(x, y);
    
    // Draw name
    ofSetColor(240,240,240,255);
    font.drawString(_name,0,-1);
    
    //draw text
    ofSetColor(255);
    //ofDrawBitmapString(text, 10,10);
    font.drawString(text,10,10);
    
	
    if(selected){
        //draw cursor line
        ofPushStyle();
        float timeFrac = 0.5 * sin(9.0f * ofGetElapsedTimef()) + 0.5;
        
        ofColor col = ofGetStyle().color;
        
        ofSetColor(col.r, col.g, col.b, col.a * timeFrac);
        ofSetLineWidth(2.0f);
        ofLine(cursorx*4.3 + 10, 13.7*cursory, cursorx*4.3 + 10, 10+13.7*cursory);
        ofPopStyle();
    }
	
	ofPopMatrix();
    
    ofDisableAlphaBlending();
}

void ofxTextInputField::mouseMoved(int x, int y ){
    if(bounds.inside(x,y)){
        isOver = true;
    }else{
        isOver = false;
    }
}

void ofxTextInputField::mouseReleased(int x, int y ){
    if(isOver){
        if(selected){
            selected = false;
            disable();
        }else{
            selected = true;
            enable();
        }
    }else{
        if(selected){
            selected = false;
            disable();
        }
    }
}

void ofxTextInputField::keyPressed(ofKeyEventArgs& args) {	
	//add charachter (non unicode sorry!)
    
	int key = args.key;
	if (key == OF_KEY_RETURN) {
		return;
        //		ofNotifyEvent(evtEnter, text, this);
        //		if (evtEnter.empty()) {
        //			text.insert(text.begin()+cursorPosition, '\n');
        //			cursorPosition++;
        //		}
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
	for (int i=0; i<cursorPosition; ++i) {
		if (*(text.begin()+i) == '\n') {
			++cursory;
			cursorx = 0;
		} else {
			cursorx++;
		}
	}
}

void ofxTextInputField::clear() {
	text.clear();
	cursorPosition=0;
}
