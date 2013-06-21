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
    
    // Audio Unit AU plugins setup
    ofxAUPlugin::init(audioSamplingRate,audioBufferSize);
    gamuzaAUList = ofxAUPlugin::getPluginsList();
	
    // Sound Stream Init
	soundStream.setInDeviceID(audioInDevID);
    soundStream.setOutDeviceID(audioOutDevID);
    soundStream.setInput(this);
	soundStream.setOutput(this);
	soundStream.setup(audioOutputChannels,audioInputChannels,audioSamplingRate,audioBufferSize, audioNumBuffers);
    
    // Pure Data libPD Init
    int ticksPerBuffer = (int)audioBufferSize/64;
    pd.init(audioOutputChannels,audioInputChannels,audioSamplingRate,ticksPerBuffer);
	
    if(audioInputChannels > 0){
        inputAudioCH = new audioInputChannel[audioInputChannels];
        for(int i=0; i<audioInputChannels; i++){
            inputAudioCH[i].setupChannel(i,audioSamplingRate,audioBufferSize,audioInputChannels,fftWindowUse);
        }
    }
    
    // ACTIVATE AUDIO STREAMING
    char _tempString[256];
    soundStream.start();
    sendGALog(" --> AUDIO STREAMING STARTED");
    sendGALog(" ");
    sendGALog(" --> PURE DATA SYNTHESIS ENGINE STARTED");
    sendGALog(" ");
    sendGALog(" AUDIO UNIT PLUGINS AVAILABLE");
    sendGALog(" ");
    for(unsigned int i = 0; i < gamuzaAUList.size(); i++){
        string _t = *gamuzaAUList[i];
        sprintf(_tempString,"  %i - %s",i,_t.c_str());
        sendGALog(_tempString);
        sendGALog(" ");
    }
    for(unsigned int i = 0; i < audioInputChannels; i++){
        inputAudioCH[i].computeChannel = true;
    }
    computeAudioInput	= true;
    computeAudioOutput	= true;
	
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
            
            ///////////////////////////////////////////
            // PD Synthesis Engine
            if(pdPatches.size() > 0){
                pd.audioIn(input, bufferSize, nChannels);
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
			// GA audio synthesis
			for(unsigned int i = 0; i < audioModules.size(); i++){
				audioModules[i].addToSoundBuffer(output, bufferSize, gamuzaDSP.numOscInCh);
			}
            
            // GA audio input recordings
            for(unsigned int i = 0; i < inputRecSamples.size(); i++){
                if(inputRecSamples[i].getIsPlaying()){
                    inputRecSamples[i].addToSoundBuffer(output, bufferSize);
                }
            }
			///////////////////////////////////////////
			gamuzaAMP.addToSoundBuffer(output, bufferSize, 1.0);
            
            ///////////////////////////////////////////
            // PD Synthesis Engine (libPD)
            if(pdPatches.size() > 0){
                pd.audioOut(output, bufferSize, nChannels);
            }
            ///////////////////////////////////////////
            
            ///////////////////////////////////////////
            // Audio Unit AU Plugins effects
            if(auPlugins.size() > 0){
                for(unsigned int i = 0; i < auPlugins.size(); i++){
                    auPlugins.at(i)->process(output,output);
                }
            }
            ///////////////////////////////////////////
            
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
