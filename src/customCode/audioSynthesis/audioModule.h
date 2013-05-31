#ifndef 	_AUDIOMODULE_H
#define 	_AUDIOMODULE_H

#include "ofMain.h"
// constants
#include "gamuzaConstants.h"
#include "gaOscillator.h"
#include "gaAmplifier.h"


class audioModule{

	public:
	
		audioModule();
		~audioModule();
		
		void	setup(int _samplingRate, int _nChannels, int _waveType, float _freq, int _type, int _channel=0);
		void	setWave(int _waveType);
		void	setFrequency(float _freq);
		void	setVolume(float _vol);
		void	setTuning(float _tuning);
		void	addToSoundBuffer(float * _buffer, int _bufferSize, int* _numOscXCh);
	
		gaOscillator	osc;
		gaAmplifier		amp;
	
		float			vol;
		float			freq;
		int				channel;
		int				moduleType;
		int				waveType;
		


};

#endif
