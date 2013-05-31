#include "ofxArcText.h"

ofxArcText::ofxArcText() {
    align = CENTER;
    showDebug = false;
}

ofxArcText::ofxArcText(bool sD) {
    align = CENTER;
    showDebug = sD;
}

float ofxArcText::getCharacterWidth(char ch) {
    if (ch==' ') ch='i';
    return cps[ch-NUM_CHARACTER_TO_START].setWidth;
}

void ofxArcText::drawString(string text, float x, float y, float radius) {
    
    ofPushMatrix();
    ofTranslate(x,y);
    
    float angles[text.length()];
    float widths[text.length()];
    float totalAngle = 0;
    
    for (int i=0; i<text.length(); i++) {
        widths[i] = getCharacterWidth(text.at(i)) * letterSpacing;
        angles[i] = atan(widths[i]/radius);
        totalAngle += angles[i];
    }
    
    switch (align) {
        case LEFT: break;
        case CENTER: ofRotateZ(ofRadToDeg(totalAngle/2)); break;
        case RIGHT: ofRotateZ(ofRadToDeg(totalAngle)); break;
    }

    if (showDebug) {
        ofNoFill();
        ofCircle(0,0,radius);
        ofLine(0,0,0,radius);
        ofPushMatrix();
        for (int i=0; i<text.length(); i++) {
            ofRotateZ(-ofRadToDeg(angles[i]));
            ofLine(0,0,0,radius);
        }
        ofPopMatrix();
    }
    
    for (int i=0; i<text.length(); i++) {
        ofPushMatrix();
        ofTranslate(0, radius);
        ofRotateZ(-ofRadToDeg(angles[i])/2); //local rotation, use this or center letter before rotating
        ofTrueTypeFont::drawString(ofToString((char)text.at(i)),0,0);
        ofPopMatrix();
        ofRotateZ(-ofRadToDeg(angles[i]));
    }

    ofPopMatrix();

    //for (int i=0; i<text.length(); i++) {
    //    float opposite = getCharacterWidth(text.at(i)) * letterSpacing;
    //    float angle = atan(opposite/radius) / 2;
    //    ofRotateZ(-ofRadToDeg(angle));
    //    string s = ofToString((char)text.at(i));
    //    ofTrueTypeFont::drawString(s,-widths[i]/2,radius);
    //    ofRotateZ(-ofRadToDeg(angle));
    //}
}
