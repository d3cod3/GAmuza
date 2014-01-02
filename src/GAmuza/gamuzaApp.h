#ifndef _GAMUZAAPP
#define _GAMUZAAPP

#include "gamuzaConstants.h"
#include "RtAudio.h"


//--------------------------------------------------------------
void gamuzaMain::close() {
    exitScripting();
}

//--------------------------------------------------------------
void gamuzaMain::cleanMemory(){
    
    // clean general memory
    
    // clean arduino memory
    
    // clean gui memory
    
    // clean audio memory
    resetSoundStream();
    
    // clean osc memory
    
    // clean mapping memory
    
    // clean fbo memory
    
    // clean midi memory
    
}

//--------------------------------------------------------------
void gamuzaMain::resetApp(){
    //////////////////////////////////////////////
    // APP - load settings from xml
    loadGamuzaSettings();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// ARDUINO
    setupArduino();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// GUI
    setupGui();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// AUDIO
    setupAudio();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// SCRIPTING - LUA -- OF binding
    setupScripting();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// NET
    checkNetConnection();
    setupOSC();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// MAPPING
    setupMapping();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// FBO
    setupFBO();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// MIDI
    setupMidi();
    //////////////////////////////////////////////
}

//--------------------------------------------------------------
void gamuzaMain::sendHardwareInfo(vector<string> &aInD, vector<int> &aInDID,
                                  vector<string> &aOutD, vector<int> &aOutDID,
                                  vector<string> &mD, vector<string> &sD,
                                  vector<string> &aOutCh, vector<string> &aInCh){
    // Audio devices
    aInD        = _audioInDev;
    aInDID      = _audioInDevID;
    aOutD       = _audioOutDev;
    aOutDID     = _audioOutDevID;
    
    aOutCh      = _inputCH;
    aInCh       = _outputCH;
    
    // Midi Devices
    mD = _midiDev;
    
    // Serial Devices
    sD = _serialDev;
    
}

//--------------------------------------------------------------
void gamuzaMain::getScreenInfo(int w, int h){
    _mainScreenW = w;
    _mainScreenH = h;
}

//--------------------------------------------------------------
void gamuzaMain::getScreensData(vector<ofRectangle> screensData){
    _screensData = screensData;
}

//--------------------------------------------------------------
void gamuzaMain::setScriptPath(string path){
    GAscriptFileName = path;
}

//--------------------------------------------------------------
void gamuzaMain::dataInsideBundle(){
    
    // STORE resource files inside bundle
    CFURLRef appUrl = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef appPath = CFURLCopyFileSystemPath(appUrl, kCFURLPOSIXPathStyle);
    const char *appPathChars = [(NSString *) appPath UTF8String];
    string appPathStr = string(appPathChars); // the path to the .app dir
    CFRelease(appUrl);
    CFRelease(appPath);
    
    CFURLRef resourceUrl = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    CFStringRef resourcePath = CFURLCopyFileSystemPath(resourceUrl, kCFURLPOSIXPathStyle);
    const char *resourcePathChars = [(NSString *) resourcePath UTF8String];
    string resourcePathStr = string(resourcePathChars); // the path from the .app dir to the resources folder
    CFRelease(resourcePath);
    CFRelease(resourceUrl);
    
    _bundleDataPath = appPathStr + "/" + resourcePathStr + "/"; // the absolute path to the resources folder
    
    ofSetDataPathRoot(_bundleDataPath); // tell OF to look for resources here
    
}

//--------------------------------------------------------------
void gamuzaMain::loadGamuzaSettings(){
	
	setting_data.loadFile(GAMUZA_SETTINGS);
	
	//////////////////////////////////////////////
	// get SCREENS settings
	projectionScreenW		= setting_data.getValue("GAmuzaSettings:ps_width",0,0);
	projectionScreenH		= setting_data.getValue("GAmuzaSettings:ps_height",0,0);
	INVprojectionScreenW	= 1.0f/projectionScreenW;
	INVprojectionScreenH	= 1.0f/projectionScreenH;
    
    sprintf(_windowTitle,"output @ %i x %i",projectionScreenW,projectionScreenH);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get AUTOMATION settings
	autoPilot				= setting_data.getValue("GAmuzaSettings:auto_pilot",0,0);
    autoPilotScreen         = setting_data.getValue("GAmuzaSettings:auto_pilot_screen",0,0);
	autoLoadScript			= setting_data.getValue("GAmuzaSettings:autoload_script",0,0);
	autoScriptFile			= setting_data.getValue("GAmuzaSettings:script_file"," ",0);
    autoLoadMapping         = setting_data.getValue("GAmuzaSettings:autoload_mapping",0,0);
    autoMappingFile			= setting_data.getValue("GAmuzaSettings:mapping_file"," ",0);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get MAPPING settings
	gridRes					= setting_data.getValue("GAmuzaSettings:grid_res",0,0);
	fboNumSamples			= setting_data.getValue("GAmuzaSettings:fbo_num_samples",0,0);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get AUDIO settings
	audioInDevID			= setting_data.getValue("GAmuzaSettings:audioIn_Dev_ID",0,0);
    audioOutDevID			= setting_data.getValue("GAmuzaSettings:audioOut_Dev_ID",0,0);
	audioOutputChannels		= setting_data.getValue("GAmuzaSettings:output_ch",0,0);
	audioInputChannels		= setting_data.getValue("GAmuzaSettings:input_ch",0,0);
	audioSamplingRate		= setting_data.getValue("GAmuzaSettings:sampling_rate",0,0);
	audioBufferSize			= setting_data.getValue("GAmuzaSettings:buffer_size",0,0);
	audioNumBuffers			= setting_data.getValue("GAmuzaSettings:num_buffers",0,0);
	fftWindowUse			= setting_data.getValue("GAmuzaSettings:fft_window",0,0);
	//////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// get MIDI settings
    midiPortNumber          = setting_data.getValue("GAmuzaSettings:midi_port",0,0);
    //////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get ARDUINO settings
	serialDevice			= setting_data.getValue("GAmuzaSettings:serial_device_name"," ",0);
	baudRate				= setting_data.getValue("GAmuzaSettings:baud_rate",0,0);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get OSC settings
	host_number				= setting_data.getValue("GAmuzaSettings:host_ip"," ",0);
	host_port				= setting_data.getValue("GAmuzaSettings:host_port"," ",0);
    server_port             = setting_data.getValue("GAmuzaSettings:server_port"," ",0);
	//////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// get COLOR CORRECTION settings
    fbo_gammaCorrection     = setting_data.getValue("GAmuzaSettings:gamma_correction",0,0);
    fbo_brightness          = setting_data.getValue("GAmuzaSettings:brightness",0,0);
    fbo_saturation          = setting_data.getValue("GAmuzaSettings:saturation",0,0);
    fbo_contrast            = setting_data.getValue("GAmuzaSettings:contrast",0,0);
    fbo_filmBleach          = setting_data.getValue("GAmuzaSettings:film_bleach",0,0);
    fbo_techniColor         = setting_data.getValue("GAmuzaSettings:technicolor",0,0);
    fbo_whiteDiffusion      = setting_data.getValue("GAmuzaSettings:force_bw",0,0);
    fbo_exposure            = setting_data.getValue("GAmuzaSettings:white_exposure",0,0);
    fbo_diffusion           = setting_data.getValue("GAmuzaSettings:white_diffusion",0,0);
    //////////////////////////////////////////////
    
}

//--------------------------------------------------------------
void gamuzaMain::retrieveHardwaredata(){
    
    glGetIntegerv(GL_MAX_SAMPLES, &_fboMaxSamples);
    
    //////////////////////////////////////////////
    // retrieving webcam devices info
    listWebcamDevices();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // retrieving audio devices info
    listAudioDevices();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // retrieving midi devices info
    listMidiDevices();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // retrieving serial devices info
    listSerialDevices();
    //////////////////////////////////////////////
    
}

//--------------------------------------------------------------
void gamuzaMain::listWebcamDevices(){
    
    char _m[256];
    
    sendGALog(" ------------------------------------------------ WEBCAM DEVICES");
    ///////////////////////////////////////////////
    vidRecorder = ofPtr<ofQTKitGrabber>(new ofQTKitGrabber());
    _videoDevices = vidRecorder->listVideoDevices();
    
    for(int k=0;k<(int)_videoDevices.size();k++){
        sprintf(_m," Device: %i (%s)", k,_videoDevices[k].c_str());
        sendGALog(_m);
    }
	///////////////////////////////////////////////
    sendGALog(" ");
}

//--------------------------------------------------------------
void gamuzaMain::listAudioDevices(){
    
    ofPtr<RtAudio> audioTemp;
	try {
		audioTemp = ofPtr<RtAudio>(new RtAudio());
	} catch (RtError &error) {
		return;
	}
 	int devices = audioTemp->getDeviceCount();
    char _m[256];
    
    _audioDev.clear();
    _audioInDev.clear();
    _audioOutDev.clear();
    _audioInDevID.clear();
    _audioOutDevID.clear();
    
    _audioDev.assign(devices,string());
    _inputCH.clear();
    _outputCH.clear();
    
	RtAudio::DeviceInfo info;
    int devCounter = 0;
    
    sendGALog(" ------------------------------------------------ AUDIO DEVICES");
    
	for (int i=0; i< devices; i++) {
		try {
			info = audioTemp->getDeviceInfo(i);
		} catch (RtError &error) {
			break;
		}
        
        ostringstream srate;
        for(unsigned int j=0;j<info.sampleRates.size();j++){
            srate << info.sampleRates[j] << ",";
        }
        string _sr = srate.str();
        
        if(_sr != ""){
            _audioDev[devCounter] = ofToString(info.name);
            
            if(info.inputChannels != 0){
                _audioInDev.push_back(ofToString(info.name));
                _audioInDevID.push_back(i);
                _inputCH.push_back(ofToString(info.inputChannels));
            }
            
            if(info.outputChannels != 0){
                _audioOutDev.push_back(ofToString(info.name));
                _audioOutDevID.push_back(i);
                _outputCH.push_back(ofToString(info.outputChannels));
            }
            
            sprintf(_m," Device: %i (%s)", devCounter,ofToString(info.name).c_str());
            sendGALog(_m);
            sprintf(_m," Output Channels: %s", ofToString(info.outputChannels).c_str());
            sendGALog(_m);
            sprintf(_m," Input Channels: %s", ofToString(info.inputChannels).c_str());
            sendGALog(_m);
            sprintf(_m," Sample Rates: %s", ofToString(_sr).c_str());
            sendGALog(_m);
            sendGALog(" ");
            devCounter++;
        }
        
	}
    
    sendGALog(" ");
    
}

//--------------------------------------------------------------
void gamuzaMain::listMidiDevices(){
    
    char _m[256];
    
    sendGALog(" ------------------------------------------------ MIDI DEVICES");
	for(int i=0;i<midiIn.getPortList().size();i++){
        sprintf(_m," Device: %i (%s)", i,ofToString(midiIn.getPortName(i)).c_str());
        sendGALog(_m);
        sendGALog(" ");
    }
    
    _midiDev.clear();
    if(midiIn.getPortList().size() > 0){
        _midiDev.assign(midiIn.getPortList().size(),string());
        for(int i=0;i<midiIn.getPortList().size();i++){
            _midiDev[i] = ofToString(midiIn.getPortList()[i]);
        }
    }else{
        _midiDev.assign(1,string());
        _midiDev[0] = "NO MIDI DEVICE CONNECTED";
         sendGALog(" NO MIDI DEVICE CONNECTED");
    }
    sendGALog(" ");
    
}

//--------------------------------------------------------------
void gamuzaMain::listSerialDevices(){
    
    char _m[256];
    char _t[256];
    
    //_serial.listDevices();
    _deviceList.clear();
	_deviceList = _serial.getDeviceList();
    _serialDev.clear();
    _serialDev.assign(_deviceList.size(),string());
    
    sendGALog(" ------------------------------------------------ SERIAL DEVICES");
    for(int k = 0; k < (int)_deviceList.size(); k++){
        sprintf(_m," Device: %i (/dev/%s)", k, _deviceList[k].getDeviceName().c_str());
        sendGALog(_m);
        sprintf(_t,"/dev/%s", _deviceList[k].getDeviceName().c_str());
        _serialDev[k] = ofToString(_t);
        sendGALog(" ");
	}
    sendGALog(" ");
    
}

#endif
