
#ifndef _INSTRUMENT_SEQUENCER
#define _INSTRUMENT_SEQUENCER

#include "ofMain.h"

//---------------------------------------------------------------
class instrumentSequencer: public ofThread{

	public:
	
		instrumentSequencer();
		
		int					instrumentID;
		vector<int>			tempSequence;
		vector<int>			activeSequence;
		bool				mute;
		bool				playing;
		bool				newSequence;
		bool				checker;
		int					thisTime;
		int					stepper;
		
		void setupSequence(int _id);
		void resetSequence();
		void receiveSequence(int _time);
		void applySequence();
		void muteSequence();
		
		void randomizeSequence(float randFactor, float randBound); 
		
		void playSequence();
		void threadedFunction();
		void playSequenceThreaded();
		void stopSequenceThreaded();
		
};
//---------------------------------------------------------------

#endif
