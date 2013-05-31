#include "gaAmplifier.h"


//--------------------------------------------------------------
gaAmplifier::gaAmplifier(){
	
	mLevel		= 0.0f;
	noteOn		= false;
	adsrSet		= false;
	
	a = d = s = r = 0;
	
}

//--------------------------------------------------------------
gaAmplifier::~gaAmplifier(){
	
}

//--------------------------------------------------------------
void gaAmplifier::setup(int _nChannels){
	numChannels = _nChannels;
	ampType		= AMP_TYPE_MULTI;
	monoChannel	= 0;
}

//--------------------------------------------------------------
void gaAmplifier::setup(int _nChannels, int _ch){
	numChannels = _nChannels;
	ampType		= AMP_TYPE_MONO;
	monoChannel	= _ch;
}

//--------------------------------------------------------------
void gaAmplifier::trigger(){
	offset = 0;
	noteOn = true;
}

//--------------------------------------------------------------
void gaAmplifier::release(){
	noteOn = false;
}

//--------------------------------------------------------------
void gaAmplifier::setADSR(float _a, float _d, float _s, float _r){
	
	a=_a; d=_d; s=_s; r=_r;
	inv_a = 1./a; inv_d = 1./d; inv_s = 1./s; inv_r=1./r;
	adsrSet		= true;
}

//--------------------------------------------------------------
void gaAmplifier::addToSoundBuffer(float * _buffer, int _bufferSize, float _level){
	
	float	level			= _level;
	
	if(level > 1.0){
		level = 1.0;
	}
	
	float	ramp			= 1.0f / _bufferSize;
	
	float	l_level			= mLevel;
	float	levelDelta		= (level - l_level) * ramp;
	
	float	*output = new float[numChannels];
	
	while(_bufferSize--){
		
		if(!adsrSet){
			l_level	   += levelDelta;
			
			if(ampType == AMP_TYPE_MULTI){
				for(int c=0;c<numChannels;c++){
					output[c]	= _buffer[c];
					output[c]	= output[c] * l_level;
				}
			}else if(ampType == AMP_TYPE_MONO){
				for(int c=0;c<numChannels;c++){
					if(c == monoChannel){
						output[c] = _buffer[c];
						output[c] = output[c] * l_level;
					}else {
						output[c] = _buffer[c];
					}
					
				}
			}
			
		}
		
		//////////////////////////////////
		// assign values to buffer
		for(int c=0;c<numChannels;c++){
			*_buffer++	= output[c];
		}
		//////////////////////////////////
		
	}
	
	mLevel		= l_level;
	
}

//--------------------------------------------------------------
void gaAmplifier::addToSoundBuffer(float * _buffer, int _bufferSize, float _level, int* _numOscXCh){
	
	float	level			= _level;
	
	if(level > 1.0){
		level = 1.0;
	}
	
	float	ramp			= 1.0f / _bufferSize;
	
	float	l_level			= mLevel;
	float	levelDelta		= (level - l_level) * ramp;
	
	float	*output = new float[numChannels];
	
	while(_bufferSize--){
		
		if(!adsrSet){
			l_level	   += levelDelta;
			
			if(ampType == AMP_TYPE_MULTI){
				for(int c=0;c<numChannels;c++){
					output[c]	= _buffer[c];
					output[c]	= output[c] * (float)(l_level/(_numOscXCh[c]/1.4));
				}
			}else if(ampType == AMP_TYPE_MONO){
				for(int c=0;c<numChannels;c++){
					if(c == monoChannel){
						output[c] = _buffer[c];
						output[c] = output[c] * (float)(l_level/(_numOscXCh[c]/1.4));
					}else {
						output[c] = _buffer[c];
					}

				}
			}
			
			
		 // TODO : ADJUST ADSR for MULTICHANNEL
		}/* else{
			if(offset<a){											// attack
				output = ((float)offset)*inv_a;
				offset++;
			}else if (offset>a&&offset<a+d) {						// decay
				output = ofLerp(1.0, s, ((float)offset-a)*inv_d);
				offset++;
			}else if(noteOn){										// sustain
				output = s;
			}else if(offset<a+d+r){									// release
				output = ofLerp(s, 0.0, (float)(offset-a-d)*inv_r);
				offset++;
			}else {
				output = 0;
			}
		}*/
		
		//////////////////////////////////
		// assign values to buffer
		for(int c=0;c<numChannels;c++){
			*_buffer++	= output[c];
		}
		//////////////////////////////////
		
	}
	
	mLevel		= l_level;
	
}
