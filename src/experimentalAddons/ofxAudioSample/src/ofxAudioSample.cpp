#include "ofxAudioSample.h"


//--------------------------------------------------------------
ofxAudioSample::ofxAudioSample(){
    output = 0.0f;
    position = 0.0f;
    speed = 1.0f;
    mainSpeed = 1.0f;
    resampligFactor = 1.0f;
    isLooping   = false;
    isPlaying   = false;
    isPaused    = false;
    
}

//--------------------------------------------------------------
ofxAudioSample::~ofxAudioSample(){
    
}

//--------------------------------------------------------------
void ofxAudioSample::load(vector<float> _buf) {
    samples = _buf;
    position = 0.0f;
}

//--------------------------------------------------------------
float ofxAudioSample::update(){
    
    if(!isPlaying){
        output = 0.0f;
    }else if(isPlaying && isPaused){
        output = 0.0f;
    }else if(isPlaying && !isPaused){
        
        // update position
        position += speed;
        
        // check if reached EOF
        if(position > samples.size()-1) {
            if(isLooping) {
                position=0.0;
            }else{
                isPlaying = false;
                return 0.0f;
            }
        }
        
        //check if position less than zero (reverse)
        if (position < 0.0) {
            if(isLooping) {
                position = samples.size()-1;
            }else{
                isPlaying = false;
                return 0.0f;
            }
        }
        
        if(position+1 < samples.size()-1){
            output = samples[1+position];
        }
        
    }
    
    return(output);
    
}

//--------------------------------------------------------------
void ofxAudioSample::stop(){
    position = 0;
    isPlaying = false;
}

//--------------------------------------------------------------
void ofxAudioSample::play(){
    if(speed > 0){
        position = 0;
    }else{
        position = getLength();
    }
    isPlaying = true;
}

//--------------------------------------------------------------
void ofxAudioSample::setPaused(bool bPaused){
    isPaused    = bPaused;
}

//--------------------------------------------------------------
void ofxAudioSample::setSpeed(float spd){
    mainSpeed = spd;
    speed     = mainSpeed/resampligFactor;
}

//--------------------------------------------------------------
void ofxAudioSample::setLooping(bool loop){
    isLooping   = loop;
}

//--------------------------------------------------------------
void ofxAudioSample::setPosition(float _position){
	float pct = ofClamp(_position,0.0,1.0);
	position = pct * getLength();
}

//--------------------------------------------------------------
float ofxAudioSample::getSpeed(){
    return mainSpeed;
}

//--------------------------------------------------------------
bool ofxAudioSample::getIsPlaying(){
    return isPlaying;
}

//--------------------------------------------------------------
long ofxAudioSample::getLength(){
	long length;
	length=samples.size()-1;
	return(length);
}

//--------------------------------------------------------------
float ofxAudioSample::getPosition(){
    float pos = position/getLength();
    pos = ofClamp(pos,0.0,1.0);
	return pos;
}

//--------------------------------------------------------------
void ofxAudioSample::drawWaveForm(int _x, int _y, int _w, int _h){
    
    float waveFormZoomX = (float)_waveForm.size()/(float)(_w+1.0);
    float waveFormDisplayScale = samples.size()/(_w+1.0);
    
	ofPushMatrix();
    ofTranslate(_x, _y, 0);
    
    ofEnableAlphaBlending();
	for (unsigned int i = 1; i < _waveForm.size(); i++){
            ofSetColor(255,231,118,120);
            ofLine((i-1)/waveFormZoomX, _h + (int)(_waveForm[i-1].x*_h), i/waveFormZoomX, _h +  (int)(_waveForm[i].y*_h));
            ofSetColor(118,118,118,70);
            ofLine(i/waveFormZoomX, _h + (int)(_waveForm[i].y*_h), i/waveFormZoomX, _h + (int) (_waveForm[i].x*_h));
	}
    ofDisableAlphaBlending();
    
	ofSetColor(216,64,64);
    ofLine(position/waveFormDisplayScale, -(float)_h*0.0, position/waveFormDisplayScale, (float)_h*2.0);
    
	ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofxAudioSample::drawHead(int _x, int _y, int _w, int _h){
    
    float waveFormDisplayScale = samples.size()/(_w+1.0);
    
    ofPushMatrix();
    ofTranslate(_x, _y, 0);
    
    ofSetColor(216,64,64);
    ofLine(position/waveFormDisplayScale, -(float)_h*0.0, position/waveFormDisplayScale, (float)_h*2.0);
    
	ofPopMatrix();
}