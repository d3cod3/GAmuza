/**
 * ofxTimecode
 * James George 2012
 *
 * Created as part of the Duration + ofxTimeline project
 * Supported by YCAM InterLab Guest Research Project ( http://interlab.ycam.jp/en/ )
 *
 */

#pragma once

#include "ofMain.h"

class ofxTimecode {
  public:
    ofxTimecode();
    
    void setFPS(float fps); //default is 30;
    float getFPS();
    
    //these functions expect format HH:MM:SS:MLS
    //and negative value if improperly formatted
	static unsigned long long millisForTimecode(string timecode);
    static float secondsForTimecode(string timecode);
    int frameForTimecode(string timecode);
    
    int frameForSeconds(float timeInSeconds);
    int frameForMillis(unsigned long long timeInMillis);
    
    float secondsForFrame(int frame);
    unsigned long long millisForFrame(int frame);
    
    //returns format HH:MM:SS:FR
    static string timecodeForMillis(unsigned long long millis, string millisDelimiter = ":");
    static string timecodeForSeconds(float seconds, string millisDelimiter = ":");
    string timecodeForFrame(int frame, string millisDelimiter = ":");
    
  protected:
    float fps;
    static bool decodeString(string time, int* times);
};
