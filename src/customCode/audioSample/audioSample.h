#ifndef 	_AUDIOSAMPLE_H
#define 	_AUDIOSAMPLE_H

#include "ofMain.h"
// constants
#include "gamuzaConstants.h"

#include "ofxAudioSample.h"
#include "gaAmplifier.h"


class audioSample{

	public:
	
		audioSample();
		~audioSample();
		
        void    setup(vector<float> _buf, int _nChannels);
        void    play();
        void    stop();
    
		void	setVolume(float _vol);
        void	setLooping(bool _l);
        void    setPaused(bool _p);
        void    setPosition(float _p);
        void    setSpeed(float _s);
    
        float   getPosition();
        float   getSpeed();
        bool    getIsPlaying();
    
		void	addToSoundBuffer(float * _buffer, int _bufferSize);
    
        void    drawWaveform(int x, int y, int w, int h);
        void    drawHead(int x, int y, int w, int h);
	
        ofxAudioSample  sample;
        gaAmplifier		amp;
    
		float			vol;
        bool            looping;
        int             outputChannels;


};

#endif
