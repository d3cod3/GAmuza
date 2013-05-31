#include "gaOscillator.h"


//--------------------------------------------------------------
gaOscillator::gaOscillator(){
	
	mBrown = 0.0f;
    mPink  = 0;
	mCount = 1;
    for (int i=0; i<NUM_PINK_BINS; i++){
		mPinkStore[i] = 0.0f;
    }
	
}

//--------------------------------------------------------------
gaOscillator::~gaOscillator(){
	
}

//--------------------------------------------------------------
void gaOscillator::setup(int _samplingRate, int _nChannels, int _waveType, float _freq, int _type, int _ch){
 
	sampleRate 			= _samplingRate;
	oscChannels			= _nChannels;
	channel				= _ch;
	ampType				= _type;
	
	mPhase 				= 0.0f;
	frequency			= _freq;
	tuning				= 0.5f; // 0.0 --------- 1.0
	duty				= 0.5f; // 0.0 --------- 1.0
	
	waveType			=_waveType;
	
}

//--------------------------------------------------------------
void gaOscillator::setWave(int _wT){
	waveType = _wT;
}

//--------------------------------------------------------------
void gaOscillator::setFrequency(float newFrequency){
	frequency = newFrequency;
}

//--------------------------------------------------------------
void gaOscillator::setTuning(float newTuning){
	tuning = newTuning;
}

//--------------------------------------------------------------
void gaOscillator::setDuty(float newDuty){
	duty = newDuty;
}

//--------------------------------------------------------------
void gaOscillator::addToSoundBuffer(float * _buffer, int _bufferSize){
	
	
	float	phase			= mPhase;
	float	phaseInc		= (frequency + (frequency / 10.0f) * tuning) / sampleRate;
	
	float	sample;
	
	switch (waveType) {
			
		case OSC_SINE_WAVE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				phase += phaseInc;
				
				if(phase > 1.0f){
					phase -= 1.0f;
				}
				
				sample = sin(phase * TWO_PI);
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_COSINE_WAVE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				phase += phaseInc;
				
				if(phase >= 1.0f){
					phase -= 1.0f;
				}
				
				sample = cos(phase * TWO_PI);
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_SAWTOOTH_WAVE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				phase += phaseInc;
				
				if(phase >= 1.0f){
					phase -= 2.0f;
				}
				
				sample = phase;
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_TRIANGLE_WAVE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				phase += phaseInc;
				
				if(phase >= 1.0f){
					phase -= 1.0f;
				}
				
				if(phase <= 0.5){
					sample = phase;
				}else{
					sample = (1-phase);
				}
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_RECT_WAVE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				phase += phaseInc;
				
				if(phase > 1.0f){
					phase -= 2.0f;
				}
				
				sample = phase > 0 ? 1.0 : -1.0;
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_WHITE_NOISE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				sample = (rand()/(float)RAND_MAX)*2 - 1;
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_PINK_NOISE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				float prevr;
				float r;
				unsigned long k;
				k = CTZ(mCount);
				k = k & NUM_PINK_BINS1;
				
				// get previous value of this octave 
				prevr = mPinkStore[k];
				
				while(true){
					r = (rand()/(float)RAND_MAX)*2 - 1;
					mPinkStore[k] = r;
					r -= prevr;
					mPink += r;
					
					if(mPink < -4.0f || mPink > 4.0f){
						mPink -= r;
					}else{
						break;
					}
				}
				mCount++;
				
				sample = (((rand()/(float)RAND_MAX)*2 - 1) + mPink)*0.125f;
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_BROWN_NOISE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				while(true){
					float r = (rand()/(float)RAND_MAX)*2 - 1;
					mBrown += r;
					if(mBrown < -8.0f || mBrown > 8.0f ){
						mBrown -= r;
					}else{
						break;
					}
				}
				sample =  mBrown*0.0625f;
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_PHASOR:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				phase += phaseInc;
				
				if(phase >= 1.0f){
					phase -= 1.0f;
				}
				
				sample = phase;
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		case OSC_PULSE:
			for (int i = 0; i < _bufferSize; i++){
				
				/////////////////////
				// PHASE
				phase += phaseInc;
				
				if(phase >= 1.0f){
					phase -= 1.0f;
				}
				
				if(phase < duty){
					sample = -1.0;
				}
				if(phase > duty){
					sample = 1.0;
				}
				/////////////////////
				
				for(int c=0;c<oscChannels;c++){
					if(ampType == AMP_TYPE_MONO){
						if(c == channel){
							_buffer[i*oscChannels + c]   += sample;
						}else{
							_buffer[i*oscChannels + c]   += DENORMAL_BUFFER;
						}
					}else if(ampType == AMP_TYPE_MULTI){
						_buffer[i*oscChannels + c]   += sample;
					}
				}
				
			}
			break;
			
		default:
			break;
	}
	
	mPhase		= phase;
	
}