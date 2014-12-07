//
//  ofxQTKitAVScreenRecorder.h
//  ofxQTKitAVScreenRecorder
//
//  Created by Seth Hunter (hunters@mit.edu) on 8/14/12. 
//  2012 MIT Media Lab - use it as you please. 
//

#pragma once  

#ifndef QTKIT_FBO_AUDIO_RECORDER_H  
#define QTKIT_FBO_AUDIO_RECORDER_H 

//#include "ofxQTKitVideoGrabber.h"
#include "ofQTKitGrabber.h"
#include "ofxQTKitRecorder.h"


class ofxQTKitAVScreenRecorder {  
public: 
    ofxQTKitAVScreenRecorder();  
    ~ofxQTKitAVScreenRecorder(); 
    void setup(string device, string compression);
    void update(); 
    void exit(); 
    void initAudio(string device, string compression); 
    void initAVRecording(string _file);
    void startNewRecording(string _file); 
    void finishMovie(bool exiting=false); 
    void addFrame(ofPixels& framePixels); 
    bool getIsRecording() { return isRecording; }
    
    string*	listAudioDevices();
    string*	listAudioCodecs();
    
    string audioFullPath;
    string videoFullPath;
    string selfContainedFullPath;
    
	ofxQTKitRecorder	 recorder;
    ofQTKitGrabber  audioTrack; 

private: 
    int addAudioTrack; 
    bool stopAddingFrames;
    bool isRecording; 
    void doWeNeedToAddAudio(); 

};  


#endif