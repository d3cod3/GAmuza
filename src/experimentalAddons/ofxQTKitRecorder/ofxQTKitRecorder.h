//  Modified by Seth Hunter (hunters@mit.edu) on 8/14/12. 
//  2012 MIT Media Lab - use it as you please. 
//


#pragma once  
  
#ifndef QTKIT_MOVIE_RECORDER_H  
#define QTKIT_MOVIE_RECORDER_H  
  
#include <string>  
#include "ofImage.h"  
#if __OBJC__  
#include "GL/glew.h"  
#include <QTKit/QTKit.h>  
#endif // __OBJC__  
  
class ofxQTKitRecorder {  
    public: ofxQTKitRecorder();  
    public: ~ofxQTKitRecorder();  
  
    public: void setup(std::string filePath);  
    public: void addFrame(ofPixels& framePixels);  
    public: void flushToFile();  
    public: void addAudioTrack(char* videoPath);
    public: void releaseRecording(); 
    public: void removeTempFiles(char* audioPath,char* videoPath);
  
    private: void outputFrame(ofPixels& frameImage, unsigned long frameDurationMS);  
    
    public: void loadAudioTrack(char* filename); 
    
    bool audioFileWritten; 
  
#if __OBJC__  
    private: QTMovie* qtMovie;  
    private: QTMovie* insertion;
#else // __OBJC__  
    private: void* qtMovie;
    private: void* insertion;
#endif // __OBJC__  
    private: ofPixels previousFrame;  
    private: unsigned long previewFrameTimestampMS;  
};  
  
  
#endif