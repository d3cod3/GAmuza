#include "audioModule.h"


//--------------------------------------------------------------
audioModule::audioModule(){
	vol = 0;
	
}

//--------------------------------------------------------------
audioModule::~audioModule(){
	
}

//--------------------------------------------------------------
void audioModule::setup(int _samplingRate, int _nChannels, int _waveType, float _freq, int _type, int _channel){
	moduleType  = _type;
	channel		= _channel;
	waveType	= _waveType;
	freq		= _freq;
	osc.setup(_samplingRate, _nChannels, waveType, _freq, moduleType, channel);
	if(moduleType == AMP_TYPE_MULTI){
		amp.setup(_nChannels);
	}else if(moduleType == AMP_TYPE_MONO){
		amp.setup(_nChannels,channel);
	}
}

//--------------------------------------------------------------
void audioModule::setWave(int _waveType){
	osc.setWave(_waveType);
	waveType = _waveType;
}

//--------------------------------------------------------------
void audioModule::setFrequency(float _freq){
	osc.setFrequency(_freq);
	freq = _freq;
}

//--------------------------------------------------------------
void audioModule::setVolume(float _vol){
	vol = _vol;
}

//--------------------------------------------------------------
void audioModule::setTuning(float _tuning){
	osc.setTuning(_tuning);
}

//--------------------------------------------------------------
void audioModule::addToSoundBuffer(float * _buffer, int _bufferSize, int* _numOscXCh){
	osc.addToSoundBuffer(_buffer, _bufferSize);
	amp.addToSoundBuffer(_buffer, _bufferSize, vol, _numOscXCh);
}