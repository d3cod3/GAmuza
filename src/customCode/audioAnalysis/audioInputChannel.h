#ifndef _AUDIO_INPUT_CHANNEL
#define _AUDIO_INPUT_CHANNEL

#include "ofMain.h"
#include "gamuzaConstants.h"
#include "ofxXmlSettings.h"

// Wraps FFTW and KISS FFT [from Kyle McDonald <http://code.google.com/p/kyle/>]
#include "ofxFft.h"
// calculate gaussian "bell curve" f(x) = (a * exp(-pow(x-b, 2)/(2*c*c)))
#include "gaussian.h"
// notes/frequency reference
#include "notesUtils.h"



//---------------------------------------------------------------
class audioInputChannel{

	public:
	
		audioInputChannel();
	
		void setupChannel(int _id,int _sampleRate,int _bufferSize,int _nChannels,int fftWindow);
		
		// update & draw
		void drawChannel(int x, int y, int w, int h);
		void captureChannel(float *input); // update
		void doAutoCorrelation();
		void detectVolume();
		void detectPitch();
		void updateFilter();
		void setupBarkScale();
		void updateBarkScale(int i);
		
		// noise filter functions
		void recNoiseFilter();
        void resetNoiseFilter();
		void loadNoiseFilter();
		void saveNoiseFilter();
		
		// utils functions
		void smoothingValues();												// smoothing numerical data
		void normalizeValues();												// normalize numerical data
		
		/////////////////////////////////////
		// audio buffers
		float				*chRaw;
		float				*chClean;
		float				*autoCorrelation;
		float				*autoCorrelationNorm;
		float				*fftBins;
		float				*noiseFilterStep;
		float				*noiseFilter;
		float				*eqGaussianLOW;
		float				*eqGaussianMID;
		float				*eqGaussianHI;
		float				*gaussianFilter;
		float				*binsFiltered;
		int					*binsToBark;
		float				*barkBins;
		int					*barkGrouped;
		
		/////////////////////////////////////
		// parametric EQ vars
		float				eqLOWAmplitude;
		float				eqLOWCenter;
		float				eqLOWWidth;
		float				eqMIDAmplitude;
		float				eqMIDCenter;
		float				eqMIDWidth;
		float				eqHIAmplitude;
		float				eqHICenter;
		float				eqHIWidth;
		
		/////////////////////////////////////
		// fft vars
		ofMutex				fft_mutex;
		ofxFft				*fft;
		float				fft_binSizeHz;
		int					fft_StrongestBinIndex;
		float				fft_StrongestBinValue;
		int					fft_pitchBin;
		bool				noiseRec;
		float				reduxFactor;
		int					bufferRecCounter;
		
		/////////////////////////////////////
		// audio channel vars
		int					chID;
		int					sampleRate;
		int					bufferSize;
		int					numChannels;
		bool				captureAudioCH;
		bool				applyCorrelation;
		bool				applyNormalize;
		float				_volume;
		bool				_mute;
		float				_internalMute;
		bool				captureAudio;
		bool				drawGraphics;
		bool				computeChannel;
	
		float				chVolume;
		float				chPitch;
	
		/////////////////////////////////////
		// osc vars
		float				_smoothingFactor;
		
		float				_s_chVolume;
		float				_s_chPitch;
		float				*_s_barkBins;
		float				_osc_chVolume;
		float				_osc_chPitch;
		float				*_osc_barkBins;
	
		// OSC flags
		bool				sendOsc_VD;	// send volume detection flag
		bool				sendOsc_PD;	// send pitch detection flag
		bool				sendOsc_BK;	// send bark scale bins flag
	
	private:
		
		ofxXmlSettings		noiseReduxXml;
		ofImage				signalBackground;
		ofImage				eqBackground;
		ofImage				timeFreq;
		ofTrueTypeFont		font;
		
};
//---------------------------------------------------------------


static inline float hardClip(float x)
{
	float x1 = fabsf(x + 1.0f);
	float x2 = fabsf(x - 1.0f);
	
	return 0.5f * (x1 - x2);
}

#endif
