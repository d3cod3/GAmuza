#ifndef _GAMUZAAPP
#define _GAMUZAAPP

#include "gamuzaConstants.h"
#include "RtAudio.h"

void gamuzaMain::close() {
    
}

//--------------------------------------------------------------
void gamuzaMain::resetApp(){
    //////////////////////////////////////////////
    // APP
    // set data path inside biundle
    dataInsideBundle();
    // load settings from xml
    loadGamuzaSettings();
    // hardware
    retrieveHardwaredata();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// AUDIO
    setupAudio();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// GUI - include hardware setup
    setupGui();
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
void gamuzaMain::getScreenInfo(int w, int h){
    mainScreenW = _screenW = w;
    mainScreenH = _screenH = h;
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
    
    string newPath = appPathStr + "/" + resourcePathStr + "/"; // the absolute path to the resources folder
    
    ofSetDataPathRoot(newPath); // tell OF to look for resources here
    
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
	autoLoadScript			= setting_data.getValue("GAmuzaSettings:autoload_script",0,0);
	autoScriptFile			= setting_data.getValue("GAmuzaSettings:script_file"," ",0);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get SENSOR KINECT TRACKING settings
	useKinectInfrared		= setting_data.getValue("GAmuzaSettings:use_infrared",0,0);
	sensorKinectLedState	= setting_data.getValue("GAmuzaSettings:led_state",0,0);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get WEBCAM TRACKING settings
	useVideoTest			= setting_data.getValue("GAmuzaSettings:video_test",0,0);
    videoTestFile           = setting_data.getValue("GAmuzaSettings:video_test_file"," ",0);
	workingW				= setting_data.getValue("GAmuzaSettings:capture_width",0,0);
	workingH				= setting_data.getValue("GAmuzaSettings:capture_height",0,0);
	totPixels				= workingW*workingH;
	
	haarFinderFile			= setting_data.getValue("GAmuzaSettings:haar_finder_file"," ",0);
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get MAPPING settings
	gridRes					= setting_data.getValue("GAmuzaSettings:grid_res",0,0);
	fboNumSamples			= setting_data.getValue("GAmuzaSettings:fbo_num_samples",0,0);
	
	if(gridRes > 20){
		gridRes = 20;
	}
	if(gridRes < 1){
		gridRes = 1;
	}
	//////////////////////////////////////////////
	
	//////////////////////////////////////////////
	// get AUDIO settings
	audioDevID				= setting_data.getValue("GAmuzaSettings:audio_Dev_ID",0,0);
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
    
}

//--------------------------------------------------------------
void gamuzaMain::retrieveHardwaredata(){
    
    glGetIntegerv(GL_MAX_SAMPLES, &_fboMaxSamples);
    
    //////////////////////////////////////////////
    // retrieving midi devices info
    listMidiDevices();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // retrieving audio devices info
    listAudioDevices();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // retrieving serial devices info
    listSerialDevices();
    //////////////////////////////////////////////
    
}

//--------------------------------------------------------------
void gamuzaMain::listWebcamDevices(){
    ///////////////////////////////////////////////
    vidRecorder = ofPtr<ofQTKitGrabber>( new ofQTKitGrabber() );
    videoDevices = vidRecorder->listVideoDevices();
	///////////////////////////////////////////////
}

//--------------------------------------------------------------
void gamuzaMain::listAudioDevices(){
    ofPtr<RtAudio> audioTemp;
    audioTemp = ofPtr<RtAudio>(new RtAudio());
 	int devices = audioTemp->getDeviceCount();
    
    char _m[256];
    
	RtAudio::DeviceInfo info;
    
	for (int i=devices-1; i>= 0; i--) {
        info = audioTemp->getDeviceInfo(i);
        
        ostringstream srate;
        for(unsigned int j=0;j<info.sampleRates.size();j++){
            srate << info.sampleRates[j] << ",";
        }
        string _sr = srate.str();
        
        sprintf(_m," device: %i (%s)\n", i,ofToString(info.name).c_str());
        sendGALog(_m);
        sprintf(_m," output channels: %s", ofToString(info.outputChannels).c_str());
        sendGALog(_m);
        sprintf(_m," input channels: %s", ofToString(info.inputChannels).c_str());
        sendGALog(_m);
        sprintf(_m," sample rates: %s", ofToString(_sr).c_str());
        sendGALog(_m);
        
	}
    
    _audioDev.clear();
    _audioDev.assign(devices,string());
    _inputCH.clear();
    _inputCH.assign(devices,string());
    _outputCH.clear();
    _outputCH.assign(devices,string());
	for (int i=0; i<devices; i++) {
	    info = audioTemp->getDeviceInfo(i);
	    _audioDev[i] = ofToString(info.name);
		_inputCH[i] = ofToString(info.inputChannels);
		_outputCH[i] = ofToString(info.outputChannels);
	}
    
}

//--------------------------------------------------------------
void gamuzaMain::listMidiDevices(){
    
    char _m[256];
    
	for(int i=midiIn.getPortList().size()-1;i>=0;i--){
        sprintf(_m," MIDI device: %i (%s)", i,ofToString(midiIn.getPortName(i)).c_str());
        sendGALog(_m);
        sendGALog(" -----------------------");
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
    }
    
}

//--------------------------------------------------------------
void gamuzaMain::listSerialDevices(){
    char temp[128];
    char _m[256];
    
    _serial.listDevices();
    _deviceList.clear();
	_deviceList = _serial.getDeviceList();
    
    for(int k = 0; k < (int)_deviceList.size(); k++){
        sprintf(_m," /dev/%s", _deviceList[k].getDeviceName().c_str());
        sendGALog(_m);
	}
    
    _serialDev.clear();
    _serialDev.assign(_deviceList.size(),string());
    int i = 0;
	for(int k = (int)_deviceList.size()-1; k >= 0; k--){
	    sprintf(temp,"/dev/%s",_deviceList[k].getDeviceName().c_str());
        _serialDev[i] = ofToString(temp);
        i++;
	}
}

#endif
