#pragma once

#include "ofMain.h"

class ofxArcText : public ofTrueTypeFont {
public:

    ofxArcText();
    ofxArcText(bool sD);
    
    void drawString(string s, float x, float y, float radius);
    float getCharacterWidth(char ch);

    enum { LEFT, CENTER, RIGHT } align;
    bool showDebug;
};
