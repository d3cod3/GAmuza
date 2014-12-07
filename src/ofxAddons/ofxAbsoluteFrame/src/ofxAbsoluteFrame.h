//
//  ofxAbsoluteFrame.h
//  ofxAbsoluteFrame
//
//  Created by Onishi Yoshito on 3/24/13.
//
//

#ifndef __ofxAbsoluteFrame__ofxAbsoluteFrame__
#define __ofxAbsoluteFrame__ofxAbsoluteFrame__

class ofxAbsoluteFrame {
public:
    
    ofxAbsoluteFrame();
    
    void setup(float frameRate);
    void update();
    void reset();
    bool isFrameNew() const;
    unsigned long getFrame() const;
    
private:
    float mEpoch;
    float mFrameRate;
    unsigned long mFrame;
    unsigned long mLastFrame;
    
};

#endif /* defined(__ofxAbsoluteFrame__ofxAbsoluteFrame__) */
