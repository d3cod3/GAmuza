#ifndef _GAOSCILLATOR
#define _GAOSCILLATOR


#include "ofMain.h"
// constants
#include "gamuzaConstants.h"

#define		NUM_PINK_BINS		16
#define		NUM_PINK_BINS1		NUM_PINK_BINS - 1


class gaOscillator{
	
	public:
		
		gaOscillator();
		~gaOscillator();
	
		void	setup(int _samplingRate, int _nChannels, int _waveType, float _freq, int _type, int _ch);
		void	setWave(int _wT);
		void	setFrequency(float newFrequency);
		void	setTuning(float newTuning);
		void	setDuty(float newDuty);
		void	addToSoundBuffer(float * _buffer, int _bufferSize);
	
		
		int		sampleRate;
		int		oscChannels;
		int		channel;
		int		ampType;
	
		int		waveType;
		float	frequency;
		float	tuning;
		float	duty;
		
	private:
	
		float	mPhase;
		
		unsigned long	mCount;
		float			mPink;
		float			mBrown;
		float			mPinkStore[NUM_PINK_BINS];
	
};

int inline CTZ(int num){
    int i=0;
    while (((num>>i)&1)==0 && i<sizeof(int)) i++;
    return i;
}

#endif	