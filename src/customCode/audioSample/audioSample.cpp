#include "audioSample.h"


//--------------------------------------------------------------
audioSample::audioSample(){
	vol = 0;
	looping = true;
}

//--------------------------------------------------------------
audioSample::~audioSample(){
	
}

//--------------------------------------------------------------
void audioSample::setup(vector<float> _buf, int _nChannels){
	
    sample.load(_buf);
    
    outputChannels = _nChannels;
    amp.setup(outputChannels);
	
}

//--------------------------------------------------------------
void audioSample::play(){
    sample.play();
}

//--------------------------------------------------------------
void audioSample::stop(){
    sample.stop();
}

//--------------------------------------------------------------
void audioSample::setVolume(float _vol){
	vol = _vol;
}

//--------------------------------------------------------------
void audioSample::setLooping(bool _l){
	looping = _l;
    sample.setLooping(looping);
}

//--------------------------------------------------------------
void audioSample::setPaused(bool _p){
	sample.setPaused(_p);
}

//--------------------------------------------------------------
void audioSample::setPosition(float _p){
	sample.setPosition(_p);
}

//--------------------------------------------------------------
void audioSample::setSpeed(float _s){
	sample.setSpeed(_s);
}

//--------------------------------------------------------------
float audioSample::getPosition(){
	return sample.getPosition();
}

//--------------------------------------------------------------
float audioSample::getSpeed(){
	return sample.getSpeed();
}

//--------------------------------------------------------------
bool audioSample::getIsPlaying(){
	return sample.getIsPlaying();
}

//--------------------------------------------------------------
void audioSample::drawWaveform(int x, int y, int w, int h){
    sample.drawWaveForm(x,y,w,h);
}

//--------------------------------------------------------------
void audioSample::drawHead(int x, int y, int w, int h){
    sample.drawHead(x,y,w,h);
}

//--------------------------------------------------------------
void audioSample::addToSoundBuffer(float * _buffer, int _bufferSize){
    float smp;
    
    for (int i = 0; i < _bufferSize; i++){
        smp = sample.update();
        for(int c=0;c<2;c++){
            _buffer[i*outputChannels + c]   += smp;
        }
    }
    
	amp.addToSoundBuffer(_buffer, _bufferSize, vol);
}