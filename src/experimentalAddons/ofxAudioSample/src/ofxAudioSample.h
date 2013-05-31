#ifndef _OFXAUDIOSAMPLE
#define _OFXAUDIOSAMPLE

#include "ofMain.h"

class ofxAudioSample{
	
	public:
	
		
		ofxAudioSample();
		~ofxAudioSample();
	
        void	load(vector<float> _buf);
        
        float   update();
		void	play();
		void    stop();
    
        void	setLooping(bool loop);
        void	setPosition(float _position);
        void    setPaused(bool bPaused);
        void    setSpeed(float speed);
		
		long	getLength();
        float	getPosition();
        float   getSpeed();
        bool    getIsPlaying();
    
        void    drawWaveForm(int _x, int _y, int _w, int _h);
        void    drawHead(int _x, int _y, int _w, int _h);
        
    
        int             bufferSize;
        float           resampligFactor;
    
		float			position;
		float			speed;
        float           mainSpeed;
		float			output;
		bool			isLooping;
        bool            isPlaying;
        bool            isPaused;
    
        vector<float>   samples;
        vector<ofVec2f> _waveForm;
	
};

#endif