#ifndef _GAMUZAAUDIO
#define _GAMUZAAUDIO

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupAudio(){
	
	//////////////////////////////////////////
	// inicializo el DSP de audio
	computeAudioInput		= false;
	computeAudioOutput		= false;
	outputBufferCounter		= 0;
	inputBufferCounter		= 0;
	audioModulesNum			= 0;
    inputRecordingsNum      = 0;
	outputBufferCopy		= new float[audioBufferSize*audioOutputChannels];
    recChannel              = 0;
    recordingInput          = false;
	
	printf("\n");
	soundStream.setDeviceID(audioDevID);
	soundStream.setup(audioOutputChannels,audioInputChannels,audioSamplingRate,audioBufferSize, audioNumBuffers);
	
	inputAudioCH = new audioInputChannel[audioInputChannels];
	
	for(int i=0; i<audioInputChannels; i++){
		inputAudioCH[i].setupChannel(i,audioSamplingRate,audioBufferSize,audioInputChannels,fftWindowUse);
	}
	
	soundStream.stop();
	
	if(audioOutputChannels > 0){
		gamuzaDSP.setupDSP(audioOutputChannels);
		gamuzaAMP.setup(audioOutputChannels);
	}
	//////////////////////////////////////////
	
}

//--------------------------------------------------------------
void gamuzaMain::audioIn(float * input, int bufferSize, int nChannels){
	// samples are "interleaved"
	//  L	R	L	R	L	R
	// CH1 CH2 CH1 CH2 CH1 CH2
	//  0   1   2   3   4   5
	if(computeAudioInput){
		if(audioInputChannels > 0){
			///////////////////////////////////////////
			// audio analysis here
			for(int i = 0; i < audioInputChannels; i++){
				if(inputAudioCH[i].captureAudio && inputAudioCH[i].computeChannel){
					inputAudioCH[i].captureChannel(input);
                    
                    // input recording (MONO CHANNEL)
                    if(recordingInput && i == recChannel){
                        for (int j = 0; j < bufferSize; j++){
                            recBuffer.push_back(input[j*nChannels + recChannel]);
                        }
                    }
                    
				}
			}
			///////////////////////////////////////////
			inputBufferCounter++;
		}
	}
}

//--------------------------------------------------------------
void gamuzaMain::audioOut(float * output, int bufferSize, int nChannels){
	// samples are "interleaved"
	//  L	R	L	R	L	R
	// CH1 CH2 CH1 CH2 CH1 CH2
	//  0   1   2   3   4   5
	if(computeAudioOutput){
		if(audioOutputChannels > 0){
			gamuzaDSP.clearBuffer(output, bufferSize);
			///////////////////////////////////////////
            
			// audio synthesis
			for(int i = 0; i < audioModules.size(); i++){
				audioModules[i].addToSoundBuffer(output, bufferSize, gamuzaDSP.numOscInCh);
			}
            
            // audio input recordings
            for(int i = 0; i < inputRecSamples.size(); i++){
                if(inputRecSamples[i].getIsPlaying()){
                    inputRecSamples[i].addToSoundBuffer(output, bufferSize);
                }
            }
            
			///////////////////////////////////////////
			gamuzaAMP.addToSoundBuffer(output, bufferSize, 1.0);
            
            ///////////////////////////////////////////
            // visualizing output signal
			if(ofGetFrameNum()%2 == 0){
				memcpy(outputBufferCopy, output, bufferSize * nChannels * sizeof(float));
			}
            ///////////////////////////////////////////
			
			outputBufferCounter++;
		}
	}
}

//--------------------------------------------------------------
void gamuzaMain::addAudioModule(int _wT, float _freq){
	audioModule	aM;
	aM.setup(audioSamplingRate,audioOutputChannels, _wT, _freq, AMP_TYPE_MULTI);
	audioModules.push_back(aM);
	gamuzaDSP.addOsc();
	audioModulesNum++;
}

//--------------------------------------------------------------
void gamuzaMain::addAudioModule(int _wT, float _freq,int _ch){
	if(_ch < audioOutputChannels){
		audioModule	aM;
		aM.setup(audioSamplingRate,audioOutputChannels, _wT, _freq, AMP_TYPE_MONO, _ch);
		audioModules.push_back(aM);
		gamuzaDSP.addOsc(_ch);
		audioModulesNum++;
	}
}

//--------------------------------------------------------------
void gamuzaMain::addInputRecording(){
    if(recBuffer.size() > 0){
        audioSample	iR;
        iR.setup(recBuffer,audioOutputChannels);
        inputRecSamples.push_back(iR);
        inputRecordingsNum++;
        recBuffer.clear();
    }
}

//--------------------------------------------------------------
void gamuzaMain::resetAudioOutput(){
    if(audioModules.size() > 0){
        audioModules.clear();
    }
    if(inputRecSamples.size() > 0){
        inputRecSamples.clear();
    }
    if(recBuffer.size() > 0){
		recBuffer.clear();
    }
    
	audioModulesNum = 0;
    inputRecordingsNum = 0;
    
	gamuzaDSP.resetOsc();
}

#endif
