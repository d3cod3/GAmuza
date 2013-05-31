#ifndef _GAAMPLIFIER
#define _GAAMPLIFIER


#include "ofMain.h"
// constants
#include "gamuzaConstants.h"


class gaAmplifier{
	
	public:
		
		gaAmplifier();
		~gaAmplifier();
		
		void	setup(int _nChannels);
		void	setup(int _nChannels, int _ch);
		void	trigger();
		void	release();
		void	setADSR(float _a, float _d, float _s, float _r);
		
		void	addToSoundBuffer(float * _buffer, int _bufferSize, float _level);
		void	addToSoundBuffer(float * _buffer, int _bufferSize, float _level, int* _numOscXCh);
	
		float	mLevel;
		int		numChannels;
		int		ampType;
		int		monoChannel;
		
		
	protected:
	
		float	a, d, s, r;
		float	inv_a, inv_d, inv_s, inv_r;
		int		offset;
		bool	noteOn;
		bool	adsrSet;
	
	
};

#endif	