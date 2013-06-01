//
//  textInput.h
//  textInput
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

#pragma once

#include "ofMain.h"

//For lack of a type abstraction, this lets you #define a font renderer so
//(like ofxFTGL or ofxFont)
//to use ofxFTGL use somethinglike this:
//#define OFX_TEXTFIELD_FONT_RENDERER ofxFTGLFont
//#define OFX_TEXTFIELD_FONT_RENDERER "ofxFTGLFont.h"

#ifndef OFX_TEXTFIELD_FONT_RENDERER
#define OFX_TEXTFIELD_FONT_RENDERER ofTrueTypeFont
#endif 

#ifdef OFX_TEXTFIELD_FONT_INCLUDE
#include OFX_TEXTFIELD_FONT_INCLUDE
#endif

#define TEXTFIELD_IS_ACTIVE "textfieldIsActive"
#define TEXTFIELD_IS_INACTIVE "textfieldIsInactive"

class ofxTextInputField {
  public:
	ofxTextInputField();
	virtual ~ofxTextInputField();
	//swap in a font!
	void setFont(OFX_TEXTFIELD_FONT_RENDERER& font);
    
    void setup();
	
	void enable();
	void disable();
    bool getIsEnabled();
	
	bool getIsEditing();
	void beginEditing();
	void endEditing();
	
    //can be set manually or otherwise is controlled by enable/disable
    bool drawCursor;
    
    ofRectangle bounds;
	
    void draw();
	void clear();
	
	string text;
	int cursorPosition;
	
	ofEvent<string> textChanged;
	void keyPressed(ofKeyEventArgs &a);
	
	bool autoClear;
	
  protected:
	
	OFX_TEXTFIELD_FONT_RENDERER* fontRef;
	
    bool 	isEnabled;
	bool	isEditing;
	bool	mouseDownInRect;
	void    mousePressed(ofMouseEventArgs& args);
    void    mouseReleased(ofMouseEventArgs& args);
	int		cursorx, cursory;
};
