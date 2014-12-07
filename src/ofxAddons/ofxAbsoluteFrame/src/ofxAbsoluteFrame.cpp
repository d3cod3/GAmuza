//
//  ofxAbsoluteFrame.cpp
//  ofxAbsoluteFrame
//
//  Created by Onishi Yoshito on 3/24/13.
//
//

#include "ofxAbsoluteFrame.h"

#include "ofMain.h"

ofxAbsoluteFrame::ofxAbsoluteFrame() {
    
}

void ofxAbsoluteFrame::setup(float frameRate)
{
    mFrameRate = frameRate;
    reset();
}

void ofxAbsoluteFrame::update()
{
    const float current = ofGetElapsedTimef()-mEpoch;
    mLastFrame = mFrame;
    mFrame = static_cast<const unsigned long>(current*mFrameRate);
}

void ofxAbsoluteFrame::reset()
{
    mEpoch = ofGetElapsedTimef();
}

bool ofxAbsoluteFrame::isFrameNew() const
{
    return mLastFrame != mFrame;
}

unsigned long ofxAbsoluteFrame::getFrame() const
{
    return mFrame;
}
