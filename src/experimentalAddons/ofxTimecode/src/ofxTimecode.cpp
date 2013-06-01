/**
 * ofxTimecode
 * James George 2012
 *
 * Created as part of the Duration + ofxTimeline project
 * Supported by YCAM InterLab Guest Research Project ( http://interlab.ycam.jp/en/ )
 *
 */

#include "ofxTimecode.h"

ofxTimecode::ofxTimecode(){
    fps = 30;
}
    
void ofxTimecode::setFPS(float _fps){
    if(fps < 1){
        ofLogError("ofxTimecode::setFPS invalid FPS set");
        return;
    }
	fps = _fps;
}

float ofxTimecode::getFPS(){
    return fps;
}
    
//expects format HH:MM:SS:MLS
unsigned long long ofxTimecode::millisForTimecode(string timecode){
    int times[4];
    if(decodeString(timecode, times)){
               //hours						
    	return times[0] * 60 * 60 * 1000 + 
               //minutes
               times[1] * 60 * 1000 +
               //seconds
               times[2] * 1000 +
               //millis
               times[3];
        
    }
	return -1;
}

string ofxTimecode::timecodeForMillis(unsigned long long millis, string millisDelimiter){
    char buf[512];
	sprintf(buf, "%02d:%02d:%02d%s%03d", int(millis / (60 * 60 * 1000)),  //hours
            						    int((millis / (60 * 1000)) % 60), //minutes
            						    int((millis / 1000) % 60), 		//seconds
            							millisDelimiter.c_str(),
                                        int(millis % 1000));
//    sprintf(buf, "%ld", millis);

    return string(buf);
}

//expects format HH:MM:SS:FR
float ofxTimecode::secondsForTimecode(string timecode){
    return millisForTimecode(timecode) / 1000.;
}

int ofxTimecode::frameForSeconds(float timeInSeconds){
    return timeInSeconds * fps;
}

int ofxTimecode::frameForMillis(unsigned long long timeInMillis){
    return timeInMillis * fps / 1000;
}

float ofxTimecode::secondsForFrame(int frame){
	return frame / fps;
}

unsigned long long ofxTimecode::millisForFrame(int frame){
	return frame * 1000 / fps;    
}

int ofxTimecode::frameForTimecode(string timecode){
    return frameForMillis(millisForTimecode(timecode));
}

string ofxTimecode::timecodeForSeconds(float seconds, string millisDelimiter){
    return timecodeForMillis(seconds*1000, millisDelimiter);
}
    
string ofxTimecode::timecodeForFrame(int frame, string millisDelimiter){
    return timecodeForMillis(millisForFrame(frame), millisDelimiter);
}

bool ofxTimecode::decodeString(string time, int* times){
	ofStringReplace(time, ",", ":");
    ofStringReplace(time, ";", ":");
    vector<string> split = ofSplitString(time, ":");
    if(split.size() != 4){
        ofLogError("ofxTimecode::decodeString -- incorrect timecode");
        return false;
    }
    for(int i = 0; i < split.size(); i++){
    	times[i] = ofToInt(split[i]);
    }
    return true;
}
