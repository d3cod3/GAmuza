#ifndef _GAMUZAGETTERS
#define _GAMUZAGETTERS

// constants
#include "gamuzaConstants.h"
#include "gamuzaMain.h"

extern gamuzaMain   *gapp; // external reference to gamuza app, declared in AppDelegate.h
extern gaTimeline   *gaTL; // external reference to TIMELINE GUI Panel, declared in AppDelegate.h

//--------------------------------------------------------------
// SYSTEM SECTION
//--------------------------------------------------------------
ofPixels gaGetOutputPixels(){
    gapp->pixelsReader.readToPixels(gapp->gamuzaFbo, gapp->gamuzaPixels);
    return gapp->gamuzaPixels;
}

ofTexture gaGetOutputTexture(){
    return gapp->drawingFbo.getTextureReference();
}

void gaSaveFrame(string _name){
    gapp->pixelsReader.readToPixels(gapp->gamuzaFbo, gapp->gamuzaPixels);
    gapp->tempFrame.setFromPixels(gapp->gamuzaPixels);
    gapp->tempFrame.saveImage(_name.c_str());
}

void gaSaveFrame(string _name,ofTexture _tex){
    ofImage             _img;
    ofPixels 			_pix;
    _tex.readToPixels(_pix);
    _img.setFromPixels(_pix);
    _img.saveImage(_name.c_str());
}

void gaLog(string _log){
    gapp->sendPrivateMessage(GAMUZA_CONSOLE_LOG, " "+_log);
}

string gaGetOSCSendingIP(){
    return gapp->host_number;
}

int gaGetFrameNum(){
    return ofGetFrameNum() - gapp->gaFrameCounter;
}

string gaGetLocalDataPath(string _file){
    string correctedPath;
    string finalPath;
    string path = gapp->GAscriptFileName;
    
    size_t cutPos = path.find_last_of("/");
    
    correctedPath = path.substr(0,cutPos);
    finalPath = correctedPath+"/data/"+_file;
    
    return finalPath;
}

//--------------------------------------------------------------
// GRAPHICS SECTION
//--------------------------------------------------------------
void gaBackground(float g, float a){
	ofFill();
	glColor4f(g,g,g,a);
	ofRect(0,0,gapp->projectionScreenW,gapp->projectionScreenH);
}

void gaBackground(float r, float g, float b, float a){
	ofFill();
	glColor4f(r,g,b,a);
	ofRect(0,0,gapp->projectionScreenW,gapp->projectionScreenH);
}

//--------------------------------------------------------------
// 3D SECTION
//--------------------------------------------------------------

void gaDrawAxis(float _size, ofColor _color, bool posNeg){
    ofPushStyle();
	ofSetLineWidth(3);
    
    if(posNeg){
        ofSetColor(_color);
        ofLine(0, 0, 0, _size, 0, 0);
        ofLine(0, 0, 0, 0, _size, 0);
        ofLine(0, 0, 0, 0, 0, _size);
        ofSetColor(127,127,127);
        ofLine(-_size, 0, 0, 0, 0, 0);
        ofLine(0, -_size, 0, 0, 0, 0);
        ofLine(0, 0, -_size, 0, 0, 0);
    }else{
        ofSetColor(_color);
        ofLine(0, 0, 0, _size, 0, 0);
        ofLine(0, 0, 0, 0, _size, 0);
        ofLine(0, 0, 0, 0, 0, _size);
    }
    
    ofPopStyle();
}

void gaDrawXAxis(float _size, ofColor _color, bool posNeg){
    ofPushStyle();
	ofSetLineWidth(3);
    
	// draw x axis
    if(posNeg){
        ofSetColor(_color);
        ofLine(0, 0, 0, _size, 0, 0);
        ofSetColor(127,127,127);
        ofLine(-_size, 0, 0, 0, 0, 0);
    }else{
        ofSetColor(_color);
        ofLine(0, 0, 0, _size, 0, 0);
    }
    
    ofPopStyle();
}

void gaDrawYAxis(float _size, ofColor _color, bool posNeg){
    ofPushStyle();
	ofSetLineWidth(3);
    
	// draw y axis
    if(posNeg){
        ofSetColor(_color);
        ofLine(0, 0, 0, 0, _size, 0);
        ofSetColor(127,127,127);
        ofLine(0, -_size, 0, 0, 0, 0);
    }else{
        ofSetColor(_color);
        ofLine(0, 0, 0, 0, _size, 0);
    }
    
    ofPopStyle();
}

void gaDrawZAxis(float _size, ofColor _color, bool posNeg){
    ofPushStyle();
	ofSetLineWidth(3);
    
	// draw z axis
    if(posNeg){
        ofSetColor(_color);
        ofLine(0, 0, 0, 0, 0, _size);
        ofSetColor(127,127,127);
        ofLine(0, 0, -_size, 0, 0, 0);
    }else{
        ofSetColor(_color);
        ofLine(0, 0, 0, 0, 0, _size);
    }
    
    ofPopStyle();
}

//--------------------------------------------------------------
// TIMELINE SECTION
//--------------------------------------------------------------
void gaSetupTimeline(string folder,string _name){
    gaTL->timeline.setWorkingFolder(folder);
    gaTL->timeline.setPageName(_name);
	gaTL->timeline.setCurrentPage(0);
}

void gaSetTimelinePageName(string _name){
    gaTL->timeline.setPageName(_name);
}

void gaSetTimelineCurrentPage(string _name){
    gaTL->timeline.setCurrentPage(_name);
}

void gaPlayTimeline(){
    gaTL->timeline.play();
}

void gaStopTimeline(){
    gaTL->timeline.stop();
}

void gaSetTimelineDurationInFrames(int frames){
    gaTL->timeline.setDurationInFrames(frames);
}

void gaSetTimelineDurationInSeconds(int seconds){
    gaTL->timeline.setDurationInSeconds(seconds);
}

void gaSetTimelineEnableSnap(bool _b){
    gaTL->timeline.enableSnapToOtherKeyframes(_b);
}

void gaSetTimelineLoopType(int _type){
    if(_type == OF_LOOP_NONE){
        gaTL->timeline.setLoopType(OF_LOOP_NONE);
    }else if(_type == OF_LOOP_NORMAL){
        gaTL->timeline.setLoopType(OF_LOOP_NORMAL);
    }
}

void gaTimelineSetFrameRate(int _fr){
    gaTL->timeline.setFrameRate(_fr);
}

void gaTimelineSetBPM(int _bpm){
    gaTL->timeline.setBPM(_bpm);
}

void gaTimelineEnableSnapToBPM(bool _b){
    gaTL->timeline.enableSnapToBPM(_b);
}

void gaTimelineSetShowBPMGrid(bool _b){
    gaTL->timeline.setShowBPMGrid(_b);
}

void gaTimelineSetTimecontrolTrack(string _name){
    gaTL->timeline.setTimecontrolTrack(_name);
}

void gaTimelineBringTrackToTop(string _name){
    gaTL->timeline.bringTrackToTop(_name);
}

void gaTimelineBringVideoTrackToTop(string _name){
    gaTL->timeline.bringTrackToTop(gaTL->timeline.getVideoTrack(_name));
}

void gaTimelineBringAudioTrackToTop(string _name){
    gaTL->timeline.bringTrackToTop(gaTL->timeline.getAudioTrack(_name));
}

void gaTimelineAddPage(string _name){
    gaTL->timeline.addPage(_name);
}

void gaTimelineAddCurves(string _name,int _min, int _max){
    gaTL->timeline.addCurves(_name, ofRange(_min, _max));
}

void gaTimelineAddBangs(string _name){
    gaTL->timeline.addBangs(_name);
}

void gaTimelineAddFlags(string _name){
    gaTL->timeline.addFlags(_name);
}

void gaTimelineAddColors(string _name){
    gaTL->timeline.addColors(_name);
}

void gaTimelineAddLFO(string _name){
    gaTL->timeline.addLFO(_name);
}

void gaTimelineAddSwitches(string _name){
    gaTL->timeline.addSwitches(_name);
}

void gaTimelineAddNotes(string _name){
    gaTL->timeline.addNotes(_name);
}

void gaTimelineAddAudioTrack(string _name, string _file){
    gaTL->timeline.addAudioTrack(_name, _file);
}

void gaTimelineAddVideoTrack(string _name, string _file){
    gaTL->timeline.addVideoTrack(_name, _file);
}

void gaTimelineAddCameraTrack(string _name){
    gaTL->timeline.addCameraTrack(_name);
}

float gaTimelineGetValue(string _name){
    return gaTL->timeline.getValue(_name);
}

bool gaTimelineGetSwitch(string _name){
    return gaTL->timeline.isSwitchOn(_name);
}

bool gaTimelineGetNote(string _name){
    return gaTL->timeline.isNoteOn(_name);
}

int gaTimelineGetNotePitch(string _name){
    return gaTL->timeline.getNotePitch(_name);
}

float gaTimelineGetNoteVelocity(string _name){
    return gaTL->timeline.getNoteVelocity(_name);
}

ofColor gaTimelineGetColor(string _name){
    return gaTL->timeline.getColor(_name);
}

string gaTimelineGetBang(){
    return gaTL->actualBang;
}

int gaTimelineGetINFrame(){
    return gaTL->timeline.getInFrame();
}

void gaTimelineSetINFrame(float _time){
    gaTL->timeline.setInPointAtSeconds(_time);
}

int gaTimelineGetOUTFrame(){
    return gaTL->timeline.getOutFrame();
}

void gaTimelineSetOUTFrame(float _time){
    gaTL->timeline.setOutPointAtSeconds(_time);
}

void gaTimelineClearINOUT(){
    gaTL->timeline.clearInOut();
}

ofxTLVideoTrack* gaTimelineGetVideoTrack(string _name){
    return gaTL->timeline.getVideoTrack(_name);
}

ofxTLAudioTrack* gaTimelineGetAudioTrack(string _name){
    return gaTL->timeline.getAudioTrack(_name);
}

ofxTLCameraTrack* gaTimelineGetCameraTrack(string _name){
    return gaTL->timeline.getCameraTrack(_name);
}

void gaTimelineSetCameraTrackCamera(string _name, ofCamera& _cam){
    gaTL->timeline.getCameraTrack(_name)->setCamera(_cam);
}

int gaTimelineGetAudioTrackDuration(string _name){
    return gaTL->timeline.getAudioTrack(_name)->getDuration();
}

int gaTimelineGetAudioTrackFFTSize(string _name){
    return gaTL->timeline.getAudioTrack(_name)->getFFTSize();
}

float gaTimelineGetAudioTrackFFTBin(string _name, int _bin){
    return gaTL->timeline.getAudioTrack(_name)->getFFT()[_bin];
}

int gaTimelineGetVideoTrackPosition(string _name){
    return gaTL->timeline.getVideoTrack(_name)->getPlayer()->getPosition();
}

int gaTimelineGetVideoTrackDuration(string _name){
    return gaTL->timeline.getVideoTrack(_name)->getPlayer()->getDuration();
}

int gaTimelineGetVideoTrackNumFrames(string _name){
    return gaTL->timeline.getVideoTrack(_name)->getPlayer()->getTotalNumFrames();
}

int gaTimelineGetVideoTrackCurrentFrame(string _name){
    return gaTL->timeline.getVideoTrack(_name)->getPlayer()->getCurrentFrame();
}

void gaTimelineVideoPlayerNextFrame(string _name){
    gaTL->timeline.getVideoPlayer(_name)->nextFrame();
}

void gaTimelineVideoPlayerUpdate(string _name){
    gaTL->timeline.getVideoPlayer(_name)->update();
}

void gaTimelineVideoPlayerDraw(string _name, ofRectangle _r){
    gaTL->timeline.getVideoPlayer(_name)->draw(_r);
}

//--------------------------------------------------------------
// MIDI SECTION
//--------------------------------------------------------------
int gaGetMidiChannel(){
    return gapp->midi_channel;
}

int gaGetMidiByteOne(){
    return gapp->midi_control;
}

int gaGetMidiByteTwo(){
    return gapp->midi_value;
}

int gaGetMidiPitch(){
    if(gapp->midi_status == MIDI_NOTE_ON){
        return gapp->midi_pitch;
    }else{
        return 0;
    }
}

int gaGetMidiVelocity(){
    if(gapp->midi_status == MIDI_NOTE_ON){
        return gapp->midi_velocity;
    }else{
        return 0;
    }
}

float gaGetMidiValue(int _channel, int _index){ // _index is midi_control
    for(int i=0; i<gapp->midiMapping.size();i++){
        if(gapp->midiMapping[i].x == _channel && gapp->midiMapping[i].y == _index){
            return gapp->midiMapping[i].z/127.0f;
            break;
        }
    }
}

//--------------------------------------------------------------
// OSC SECTION
//--------------------------------------------------------------
void gaReceiveOSCMessage(string _oscLabel,int numVar){
    gapp->oscReceivingLabels.push_back(_oscLabel);
    for(int i=0;i<numVar;i++){
        gapp->oscReceivingValues[gapp->oscReceivingLabels.size()-1].push_back("");
    }
}

string gaGetOSCValue(string _oscLabel,int var){
    for(int i=0;i<gapp->oscReceivingLabels.size();i++){
        if(_oscLabel == gapp->oscReceivingLabels[i]){
            if(var < gapp->oscReceivingValues[i].size()){
                return gapp->oscReceivingValues[i][var];
            }
            break;
        }
    }
}

int gaGetOSCValueNumVar(string _oscLabel){
    for(int i=0;i<gapp->oscReceivingLabels.size();i++){
        if(_oscLabel == gapp->oscReceivingLabels[i]){
            return gapp->oscReceivingValues[i].size();
        }
    }
}

void gaSendOSCMessage(string _oscLabel,int _type){
    gapp->oscSendingLabels.push_back(_oscLabel);
    gapp->oscSendingTypes.push_back(_type);
    gapp->oscSendingValues.push_back("");
    gapp->oscSendingActive.push_back(true);
}

void gaSetOSCValue(string _oscLabel,string _value){
    for(int i=0;i<gapp->oscSendingLabels.size();i++){
        if(_oscLabel == gapp->oscSendingLabels[i]){
            gapp->oscSendingValues[i] = _value;
        }
    }
}

void gaSetOSCActive(string _oscLabel,bool _value){
    for(int i=0;i<gapp->oscSendingLabels.size();i++){
        if(_oscLabel == gapp->oscSendingLabels[i]){
            if (gapp->oscSendingActive[i] != _value) {
                gapp->oscSendingActive[i] = _value;
            }
        }
    }
}

//--------------------------------------------------------------
// AUDIO UNIT AU PLUGINS EFFECTS --> ofxAUPlugin addon
//--------------------------------------------------------------
void auAddPlugin(string _filter){
    ofxAUPlugin     *newPlugin = new ofxAUPlugin();
    
    newPlugin->loadPlugin(_filter);
    gapp->auPlugins.push_back(newPlugin);
    
    map<string, ofVec2f> _pluginParams = ofxAUPlugin::getPluginParams(_filter);
    gapp->auPluginParams.push_back(_pluginParams);
}

void auAddPluginFromPreset(string _preset){
    ofxAUPlugin     *newPlugin = new ofxAUPlugin();
    
    string pluginName = newPlugin->loadPreset(_preset);
    gapp->auPlugins.push_back(newPlugin);
    
    map<string, ofVec2f> _pluginParams = ofxAUPlugin::getPluginParams(pluginName);
    gapp->auPluginParams.push_back(_pluginParams);
}

void auSavePluginPreset(string _plugin, string _path, string _name){
    for(int i = 0; i < gapp->auPlugins.size(); i++){
        if(_plugin == gapp->auPlugins[i]->pluginName){
            // save plugin preset
            gapp->auPlugins[i]->savePreset(_path,_name);
            break;
        }
    }
}

void auPluginSetParam(string _plugin, string _param, float _value){
    for(int i = 0; i < gapp->auPlugins.size(); i++){
        if(_plugin == gapp->auPlugins[i]->pluginName){
            // set plugin param
            gapp->auPlugins[i]->setParam(_param,_value);
            break;
        }
    }
}

void auListPlugins(){
    char _tempString[256];
    for(unsigned int i = 0; i < gapp->gamuzaAUList.size(); i++){
        string _t = *gapp->gamuzaAUList[i];
        sprintf(_tempString,"  %i - %s",i,_t.c_str());
        gapp->sendPrivateMessage(GAMUZA_CONSOLE_LOG,_tempString);
    }
}

void auListPluginParams(string _plugin){
    // list plugin params
    for(int i = 0; i < gapp->auPlugins.size(); i++){
        if(_plugin == gapp->auPlugins[i]->pluginName){
            map<string, ofVec2f>::iterator it = gapp->auPluginParams[i].begin();
            char _tempString[256];
            while (it != gapp->auPluginParams[i].end()){
                const string &n = (*it).first;
                const ofVec2f &param = (*it).second;
                sprintf(_tempString,"  %s [%f,%f]",n.c_str(),param.x,param.y);
                gapp->sendPrivateMessage(GAMUZA_CONSOLE_LOG,_tempString);
                it++;
            }
            break;
        }
    }
}

//--------------------------------------------------------------
// PURE DATA SYNTHESIS ENGINE SECTION --> ofxPD addon
//--------------------------------------------------------------
void pdAddToSearchPath(string _folder){
    string correctedPath;
    string finalPath;
    string path = gapp->GAscriptFileName;
    
    size_t cutPos = path.find_last_of("/");
    
    correctedPath = path.substr(0,cutPos);
    finalPath = correctedPath+"/data/"+_folder;
    gapp->pd.addToSearchPath(finalPath);
}

void pdOpenPatch(string _patch){
    gapp->pdPatches.push_back(_patch);
    gapp->pd.openPatch(_patch);
}

void pdClosePatch(string _patch){
    gapp->pd.closePatch(_patch);
}

void pdStart(){
    gapp->pd.start();
}

void pdStop(){
    gapp->pd.stop();
}

void pdComputeAudio(bool _c){
    gapp->pd.computeAudio(_c);
}

void pdSendBang(string _name){
    gapp->pd.sendBang(_name);
}

void pdSendFloat(string _name, float _value){
    gapp->pd.sendFloat(_name,_value);
}

void pdSendSymbol(string _name, string _value){
    gapp->pd.sendSymbol(_name,_value);
}

void pdStartMessage(){
    gapp->pd.startMessage();
}

void pdAddFloat(float _value){
    gapp->pd.addFloat(_value);
}

void pdAddSymbol(string _value){
    gapp->pd.addSymbol(_value);
}

void pdFinishList(string _name){
    gapp->pd.finishList(_name);
}

void pdFinishMessage(string _name, string _msg){
    gapp->pd.finishMessage(_name,_msg);
}

/// number ranges:
/// channel		1 - 16 * dev# (dev #0: 1-16, dev #1: 17-32, etc)
/// pitch 		0 - 127
/// velocity	0 - 127
/// control value	0 - 127
/// program value	1 - 128
/// bend value		-8192 - 8191
/// touch value		0 - 127
///
/// note, in pd:
/// [bendin] takes 0 - 16383 while [bendout] returns -8192 - 8192
/// [pgmin] and [pgmout] are 1 - 128

void pdSendNoteOn(int _ch, int _pitch, int _vel){
    gapp->pd.sendNoteOn(_ch,_pitch,_vel);
}

void pdSendControlChange(int _ch, int _controller, int _value){
    gapp->pd.sendControlChange(_ch,_controller,_value);
}

void pdSendProgramChange(int _ch,int _value){
    gapp->pd.sendProgramChange(_ch,_value);
}

void pdSendPitchBend(int _ch,int _value){
    gapp->pd.sendPitchBend(_ch,_value);
}

void pdSendAftertouch(int _ch,int _value){
    gapp->pd.sendAftertouch(_ch,_value);
}

void pdSendPolyAftertouch(int _ch,int _pitch,int _value){
    gapp->pd.sendPolyAftertouch(_ch,_pitch,_value);
}


//--------------------------------------------------------------
// AUDIO INPUT RECORDING SECTION
//--------------------------------------------------------------
void gaStartInputRecording(int _ch){
	if(_ch < gapp->audioInputChannels && gapp->audioInputChannels > 0){
		if(gapp->inputAudioCH[_ch].captureAudio && gapp->recordingInput == false){
            gapp->recChannel = _ch;
			gapp->recordingInput = true;
		}
	}
}

void gaStopInputRecording(){
	if(gapp->audioInputChannels > 0){
		gapp->recordingInput = false;
        gapp->addInputRecording();
	}
}

void gaInputRecPlay(int _pos){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->inputRecSamples.size()){
			gapp->inputRecSamples[_pos].play();
		}
	}
}

void gaInputRecStop(int _pos){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->inputRecSamples.size()){
			gapp->inputRecSamples[_pos].stop();
		}
	}
}

void gaSetInputRecVolume(int _pos, float _vol){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->inputRecSamples.size()){
			if(_vol > 1.0 || _vol < -1.0){
				gapp->inputRecSamples[_pos].setVolume(1.0);
			}else{
				gapp->inputRecSamples[_pos].setVolume(_vol);
			}
		}
	}
}

void gaSetInputRecLooping(int _pos, bool _l){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->inputRecSamples.size()){
			gapp->inputRecSamples[_pos].setLooping(_l);
		}
	}
}

void gaSetInputRecPaused(int _pos, bool _l){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->inputRecSamples.size()){
			gapp->inputRecSamples[_pos].setPaused(_l);
		}
	}
}

void gaSetInputRecSpeed(int _pos, float _speed){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->inputRecSamples.size()){
			if(_speed > 1.0){
				gapp->inputRecSamples[_pos].setSpeed(1.0);
			}else if(_speed < -1.0){
                gapp->inputRecSamples[_pos].setSpeed(-1.0);
            }else{
				gapp->inputRecSamples[_pos].setSpeed(_speed);
			}
		}
	}
}

void gaDrawInputRecHead(int _pos, int x, int y, int w, int h){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->inputRecSamples.size()){
			gapp->inputRecSamples[_pos].drawHead(x,y,w,h);
		}
	}
}

//--------------------------------------------------------------
// AUDIO SYNTH SECTION
//--------------------------------------------------------------
void gaSetupOSC(int _wt, float _freq){
	if(gapp->audioOutputChannels > 0){
		gapp->addAudioModule(_wt, _freq);
	}
}

void gaSetupMonoOSC(int _wt, float _freq, int _channel){
	if(gapp->audioOutputChannels > 0){
		gapp->addAudioModule(_wt, _freq, _channel);
	}
}

void gaSetOscVolume(int _pos, float _vol){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->audioModules.size()){
			if(_vol > 1.0 || _vol < -1.0){
				gapp->audioModules[_pos].setVolume(1.0);
			}else{
				gapp->audioModules[_pos].setVolume(_vol);
			}
		}
	}
}

void gaSetOscFrequency(int _pos, float _freq){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->audioModules.size()){
			gapp->audioModules[_pos].setFrequency(_freq);
		}
	}
}

void gaSetOscWaveType(int _pos, int _wt){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->audioModules.size()){
			gapp->audioModules[_pos].setWave(_wt);
		}
	}
}

void gaSetOscTuning(int _pos, int _tuning){
	if(gapp->audioOutputChannels > 0){
		if(_pos < gapp->audioModules.size()){
			if(_tuning <= 1.0 && _tuning >= 0.0){
				gapp->audioModules[_pos].setTuning(_tuning);
			}
		}
	}
}

float gaNote(int _note){
	if(_note <= SI_8 && _note >= DO_0){
		return noteToHarmonicFrequency(_note);
	}else{
		return 0.0f;
	}
}

//--------------------------------------------------------------
// AUDIO INPUT SECTION
//--------------------------------------------------------------
float gaGetVolume(int _ch){
	if(_ch < gapp->audioInputChannels){
		if(gapp->inputAudioCH[_ch].captureAudio){
			return gapp->inputAudioCH[_ch]._osc_chVolume;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaGetPitch(int _ch){
	if(_ch < gapp->audioInputChannels){
		if(gapp->inputAudioCH[_ch].captureAudio){
			return gapp->inputAudioCH[_ch]._osc_chPitch;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaGetFFTBand(int _ch, int _pos){
	if(_ch < gapp->audioInputChannels && _pos < BARK_SCALE_CRITICAL_BANDS){
		if(gapp->inputAudioCH[_ch].captureAudio){
			return gapp->inputAudioCH[_ch]._osc_barkBins[_pos];
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
	
}

float gaGetFFTBin(int _ch, int _pos){
	if(_ch < gapp->audioInputChannels && _pos < gapp->audioBufferSize){
		if(gapp->inputAudioCH[_ch].captureAudio){
			return  gapp->inputAudioCH[_ch].binsFiltered[_pos];
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaGetSoundGetSpectrum(int _index, int nBands){
    float *buf = ofSoundGetSpectrum(nBands);
    if(_index < nBands){
        return buf[_index];
    }else{
        return 0.0f;
    }
}

float gaGetAudioInputBuffer(int _ch, int _pos){
    if(gapp->audioInputChannels > 0 && _pos < gapp->audioBufferSize && _ch < gapp->audioInputChannels){
        return gapp->inputAudioCH[_ch].chRaw[_pos];
    }else{
		return 0.0f;
	}
}

float gaGetAudioOutputBuffer(int _pos){
    if(gapp->audioOutputChannels > 0 && _pos < gapp->audioBufferSize*gapp->audioOutputChannels){
        return gapp->outputBufferCopy[_pos];
    }else{
		return 0.0f;
	}
}

//--------------------------------------------------------------
// ARDUINO SECTION
//--------------------------------------------------------------
string gaGetSerialDevName(){
	return gapp->serialDevice;
}

float gaGetAArduinoPin(int _pin){
	if(_pin >= 0 && _pin <= 5){
		return gapp->_osc_analogPinValues[_pin];
	}else{
		return 0.0f;
	}
}

int gaGetDArduinoPin(int _pin){
	if(_pin >= 2 && _pin <= 13){
		return gapp->_osc_digitalPinValuesInput[_pin-2];
	}
}

void gaSetDArduinoPin(int _pin,int val){
	if(_pin >= 2 && _pin <= 13){
		if(gapp->digitalPinModes[_pin-2] == ARD_OUTPUT){
			if(val > 1){
				val = 1;
			}
			gapp->digitalPinValuesOutput[_pin-2] = val;
			gapp->arduino.sendDigital(_pin, gapp->digitalPinValuesOutput[_pin-2]);
		}else if(gapp->digitalPinModes[_pin-2] == ARD_PWM){
			gapp->digitalPinValuesOutput[_pin-2] = val;
			gapp->arduino.sendPwm(_pin, gapp->digitalPinValuesOutput[_pin-2]);
		}else if(gapp->digitalPinModes[_pin-2] == ARD_SERVO){
			gapp->digitalPinValuesOutput[_pin-2] = val;
			gapp->arduino.sendServo(_pin, gapp->digitalPinValuesOutput[_pin-2]);
		}
	}
}

void gaSetArduinoPinServo(int _pin,bool _state){
	if(gapp->digitalPinModes[_pin-2] == ARD_OUTPUT && (_pin == 9 || _pin == 10)){
        if(_state){
            gapp->arduino.sendServoAttach(_pin, 544, 2400, 180);
        }else{
            gapp->arduino.sendServoDetach(_pin);
        }
    }
}

void gaSetArduinoPinServoValue(int _pin,int val){
	if(gapp->digitalPinModes[_pin-2] == ARD_OUTPUT && (_pin == 9 || _pin == 10)){
        gapp->arduino.sendServo(_pin,val,false);
    }
}

#endif