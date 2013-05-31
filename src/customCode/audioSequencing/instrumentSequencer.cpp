#include "instrumentSequencer.h"


//---------------------------------------------------------------
instrumentSequencer::instrumentSequencer(){
	

}

//---------------------------------------------------------------
void instrumentSequencer::setupSequence(int _id){
	instrumentID = _id;
	mute = false;
	newSequence = false;
	playing = false;
	checker = false;
	thisTime = 0;
}

//---------------------------------------------------------------
void instrumentSequencer::resetSequence(){
	tempSequence.clear();
	activeSequence.clear();
	activeSequence.assign(tempSequence.begin(),tempSequence.end());
	checker = false;
	playing = false;
	mute = false;
	newSequence = false;
	thisTime = 0;
}

//---------------------------------------------------------------
void instrumentSequencer::receiveSequence(int _time){
	tempSequence.push_back(_time);
	printf("tempSequence%i : %i\n", instrumentID, _time);
}

//---------------------------------------------------------------
void instrumentSequencer::applySequence(){
	activeSequence.clear();
	activeSequence.assign(tempSequence.begin(),tempSequence.end());
	tempSequence.clear();
	newSequence = true;
}

//---------------------------------------------------------------
void instrumentSequencer::randomizeSequence(float randFactor, float randBound){
	float tempBound = ofRandomuf();
	if(tempBound < randBound){
		for(int i=0;i<activeSequence.size();i++){
			float tempRand = ofRandomuf();
			if(tempRand < randFactor){
				activeSequence[i] = (int)ofRandom(activeSequence[i]/2,activeSequence[i]*2);
			}
		}
	}
}

//---------------------------------------------------------------
void instrumentSequencer::playSequence(){
	stepper = 0;
	if(!mute){
		thisTime = ofGetElapsedTimeMillis();
		newSequence = false;
		while(stepper < activeSequence.size() && !activeSequence.empty()){
			//printf("analyzing pos %i\n",stepper);
			checker = false;
			//printf("WAIT %i ms\n",activeSequence.at(stepper));
			if(stepper == 0){
				checker = true;
				//printf("Writing on Serial Port\n");
				ofSleepMillis(40); // time for writing on serial port
			}
			while(ofGetElapsedTimeMillis() - thisTime < activeSequence[stepper]){
				if(stepper%2 == 0){
					playing = true;
				}else{
					playing = false;
				}
				
			}
			if(stepper == activeSequence.size()-1 | activeSequence.empty()){
				stepper = 0; // loop
			}else{
				stepper++;
			}
			if(newSequence == true){
				// reload new sequence data
				stepper = 0;
				newSequence = false;
			}
			thisTime = ofGetElapsedTimeMillis();
			checker = true;
			//printf("Writing on Serial Port\n");
			ofSleepMillis(40); // time for writing on serial port
		}
	}else{
		playing = false;
		checker = false;
	}
}

//---------------------------------------------------------------
void instrumentSequencer::threadedFunction(){
	if(lock()) {
		if(mute==false){
			playSequence();
		}
		unlock();
		ofSleepMillis(1000/60);
	}else{
		//printf("instrumentSequencer - cannot compute instrumentSequencer cos I'm locked");
	}
	stopThread();
}

//---------------------------------------------------------------
void instrumentSequencer::playSequenceThreaded(){
	startThread(false, false);   // blocking, verbose
}

//---------------------------------------------------------------
void instrumentSequencer::stopSequenceThreaded(){
	stopThread();
}

//---------------------------------------------------------------
void instrumentSequencer::muteSequence(){
	mute = !mute;
}