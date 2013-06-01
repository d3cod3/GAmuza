
#pragma once

// includes
#include "gamuzaIncludes.h"

// constants
#include "gamuzaConstants.h"

// External windows
#include "gaVideoPreview.h"

extern gaVideoPreview  *gaVP;

class gamuzaMain : public ofxNSWindowApp, public ofxMidiListener{

public:
    
    ////////////////////////////////////////////////
    //////////////////////////////////////////////// CONSTRUCTOR
    ////////////////////////////////////////////////
    
	gamuzaMain() {}
	~gamuzaMain() {}
    
    ////////////////////////////////////////////////
    //////////////////////////////////////////////// FUNCTIONS
    ////////////////////////////////////////////////
	
    ////////////////////////////////////
    // standard OF functions
	void setup();
	void update();
	void draw();
	void close();
	
    // KEYBOARD //////////////////////// --> gamuzaKeyboard.h
	void keyPressed(int key);
	void keyReleased(int key);
	// MOUSE /////////////////////////// --> gamuzaMouse.h
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(float x, float y);
    
    // AUDIO /////////////////////////// --> gamuzaAudio.h
    void audioIn(float *input, int bufferSize, int nChannels);
    void audioOut(float *output, int bufferSize, int nChannels);
    ////////////////////////////////////
	
	// APP ///////////////////////////// --> gamuzaApp.h
    void resetApp();
    void getScreenInfo(int w, int h);
    void setScriptPath(string path);
    void dataInsideBundle();
    void loadGamuzaSettings();
    void retrieveHardwaredata();
    void listWebcamDevices();
    void listAudioDevices();
    void listMidiDevices();
    void listSerialDevices();
    
    // ARDUINO /////////////////////////// --> gamuzaArduino.h
    void setupArduino();
    void updateArduino();
    void prepareArduinoOscData();
    void loadArduinoSetting();
    void saveArduinoSetting();
    void changeAnalogPinMode(int mode);
    void changeDigitalPinMode(int mode);
    void sendDigitalValue(int value);
    
    // AUDIO /////////////////////////// --> gamuzaAudio.h
    void setupAudio();
    void addAudioModule(int _wT, float _freq);
    void addAudioModule(int _wT, float _freq, int _ch);
    void addAudioSample(string _file);
    void addInputRecording();
    void resetAudioOutput();
    
    // CONSOLE /////////////////////////// --> gamuzaConsole.h
    void sendGALog(string _message);
    void sendPrivateMessage(int _type, string _message);
    
    // FBO ///////////////////////////// --> gamuzaFBO.h
    void setupFBO();
    void updateFBO();
    void drawFBO();
    void drawIntoFBO();
    
    // GUI ///////////////////////////// --> gamuzaGui.h
    void setupGui();
    void updateGui();
    void drawGui();
    void gamuzaFullscreen();
    void resetWarpingPoints(int actualPanel);
    
    // MAPPING ///////////////////////// --> gamuzaMapping.h
    void setupMapping();
    void updateMapping();
    void drawMapping();
    void resetMappingPoints();
    void loadMappingPoints();
    void saveMappingPoints();
    void toggleDrawGrid();
    
    void applyHomography();
    void applyGridMesh(int xCalib, int yCalib, int w, int h);
    
    // MIDI //////////////////////////// --> gamuzaMidi.h
    void setupMidi();
    void updateMidi();
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    // OSC ///////////////////////////// --> gamuzaOSC.h
    void checkNetConnection();
    void setupOSC();
    void updateOSC();
    void receiveOSC();
    void receiveScript(string script);
    void receiveScriptFile(string scriptFile);
    void resetIncomingOSC();
    void resetOutgoingOSC();
    void sendBuffer();
    void cleanBuffer();
    
    // SCRIPTING /////////////////////// --> gamuzaScripting.h
    void    setupScripting();
    void    updateScripting();
    void    loadScript(string _script);
    void    renderScript(string & _script);
    string  readScript(string _scriptFile,bool dialog);
    void    checkErrors();
     
    ofEvent<string> doCompileEvent;
    
    ////////////////////////////////////////////////
    //////////////////////////////////////////////// VARIABLES
    ////////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // APP --> gamuzaApp.h
    int                         _screenW;
    int                         _screenH;
    ofSerial	                _serial;
    vector<ofSerialDeviceInfo>  _deviceList;
    vector<string>			    _screenSizesMain;
    vector<string>			    _screenSizesProj;
    int                         _autoPilot;
    int                         _autoloadScript;
    string                      _scriptFile;
    vector<string>			    _oniLedState;
    vector<string>			    _serialDev;
    vector<string>			    _baudRateS;
    vector<string>			    _audioDev;
    vector<string>			    _midiDev;
    vector<string>				_inputCH;
    vector<string>				_outputCH;
    vector<string>			    _samplingRates;
    vector<string>			    _bufferSizes;
    int                         _openniModule;
    int                         _trackingModule;
    int                         _audioModule;
    int                         _arduinoModule;
    int                         _mainScreenW;
    int                         _mainScreenH;
    int                         _secondaryScreenW;
    int                         _secondaryScreenH;
    int                         _fboMaxSamples;
    int                         _mappingGridRes;
    int                         _loadVideoTest;
    string                      _videoTestFile;
    string                      _haarCascadeFile;
    int                         _useInfrared;
    int                         _ledState;
    int                         _audioDevice;
    int                         _midiDevice;
    string						_inputChannels;
    string						_outputChannels;
    string                      _samplingRate;
    string                      _bufferSize;
    string                      _baudRate;
    string                      _serialPort;
    char                        _windowTitle[256];
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // ARDUINO --> gamuzaArduino.h
    ofArduino				arduino;
    bool					useArduino;
    int						arduinoIndex;
    int						*digitalPinModes;
    int						*analogPinModes;
    int						*digitalPinValuesInput;
    int						*digitalPinValuesOutput;
    int						*analogPinValues;
    float					arduino_smoothingFactor;
    float					*_s_analogPinValues;
    float					*_osc_analogPinValues;
    int						*_osc_digitalPinValuesInput;
    bool					sendOsc_AAP;
    bool					sendOsc_ADP;
    
    ofxXmlSettings			pinsSettings;
    bool					bSetupArduino;
    bool					saveArduinoPinsState;
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // AUDIO --> gamuzaAudio.h
    ofSoundStream			soundStream;
    audioInputChannel		*inputAudioCH;
    int						audioInputStartIndex;
	
    gaDsp					gamuzaDSP;
    gaAmplifier				gamuzaAMP;
    
    vector<audioModule>		audioModules;
    int						audioModulesNum;
    
    vector<audioSample>     inputRecSamples;
    int                     inputRecordingsNum;
    vector<float>           recBuffer;
    int                     recChannel;
    bool                    recordingInput;
    
    float					*outputBufferCopy;
	
    bool					computeAudioInput;
    bool					computeAudioOutput;
    
    int						outputBufferCounter;
    int						inputBufferCounter;
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // CONSOLE --> gamuzaConsole.h
    string                      currentLog;
    string                      currentErrorLog;
    string                      currentGlobalLog;
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // FBO --> gamuzaFBO.h
     ofFbo					drawingFbo;
     ofFbo                  gamuzaFbo;
     ofxFastFboReader       pixelsReader;
     ofPixels               gamuzaPixels;
     ofShader				shaderColorCorrection;
     bool					useSecondaryScreen;
     ofImage				tempFrame;
    
     float                  fboDrawingW;
     float                  fboDrawingH;
     float                  fboDrawingPosX;
     float                  fboDrawingPosY;
    
     char					shaderName[64];
     float					fbo_gammaCorrection;
     float					fbo_brightness;
     float					fbo_saturation;
     float					fbo_contrast;
     float					fbo_filmBleach;
     float					fbo_techniColor;
     float					fbo_whiteDiffusion;
     float					fbo_exposure;
     float					fbo_diffusion;
     //////////////////////////////////////////////
     
     //////////////////////////////////////////////
     // GUI --> gamuzaGui.h
     ofxKeyMap				gamuzaKmap;
     ofTexture				emptyTexture;
     ofImage                _hueWheel;
     bool                   isFullscreen;
    
     float                  scaledMouseX;
     float                  scaledMouseY;
    
        //////////////////////////////////////////////
        // Video Tracking vars
        ofPtr<ofQTKitGrabber>	vidRecorder;
        vector<string>          videoDevices;
        sourceTracking          inputCam;
        //////////////////////////////////////////////
    
     //////////////////////////////////////////////
     
     //////////////////////////////////////////////
     // MAPPING --> gamuzaMapping.h
     int					res;
     int					realRes;
     bool                   saveMappingSettings;
     bool                   drawGrid;
     
     matrixAreas			finalTextureMapping;
     int                    totalMappingPoints;
     int                    actualMappingPoint;
     bool                   manualEditMappingPoint;
     bool                   activateMouseMapping;
     //////////////////////////////////////////////
     
     //////////////////////////////////////////////
     // MIDI --> gamuzaMidi.h
     ofxMidiOut              midiOut;
     ofxMidiIn               midiIn;
     vector<ofVec3f>         midiMapping;
     ofxMidiMessage          midiMessage;
     MidiStatus              midi_status;
     int                     midi_channel;
     int                     midi_pitch;
     int                     midi_velocity;
     int                     midi_control;
     int                     midi_value;
     double                  midi_deltatime;
     //////////////////////////////////////////////
     
     //////////////////////////////////////////////
     // OSC --> gamuzaOSC.h
     ofxOscSender			sender;
     ofxOscReceiver         receiver;
     
     ofxOscMessage          received_message;
     ofxOscMessage			osc_message;
     ofxOscBundle			osc_bundle;
    
     ofxUDPManager          connectionTest;
     vector<string>         oscReceivingLabels;
     vector<string>         *oscReceivingValues;
     vector<string>         oscSendingLabels;
     vector<string>         oscSendingValues;
     vector<int>            oscSendingTypes;
     vector<bool>           oscSendingActive;
     int					oscIndex;
     bool                   connectionUP;
     //////////////////////////////////////////////
     
     //////////////////////////////////////////////
     // SCRIPTING --> gamuzScripting.h
     ofxLua                      lua;
     vector<ofTrueTypeFont>      liveCodingFont;
     vector<float>               guiVectorFloat;
     vector<int>                 guiVectorInt;
     vector<bool>                guiVectorBool;
     int                         liveKey;
     string                      GAscriptFileName;
    
     char                        temp_error[512];
     vector<string>              errorVector;
     bool                        printError;
     int                         gaFrameCounter;
     //////////////////////////////////////////////
     
     
     //////////////////////////////////////////////
     // SETTINGS vars for gamuzaSettings.xml
     
     // SCREENS settings
     int					mainScreenW;
     int					mainScreenH;
     int					projectionScreenW;
     int					projectionScreenH;
     float					INVprojectionScreenW;
     float					INVprojectionScreenH;
     
     // AUTOMATION settings
     bool					autoPilot;
     bool					autoLoadScript;
     string					autoScriptFile;
     
     // FBO settings
     int					gridRes;
     int					fboNumSamples;
     
     // TRACKING settings
     bool					trackingActivated;
     bool					openniActivated;
     bool					useVideoTest;
     int					workingW;
     int					workingH;
     int					totPixels;
     string					haarFinderFile;
     
     // KINECT settings
     int					sensorKinectLedState;
     bool					useKinectInfrared;
     
     // AUDIO settings
     bool					audioActivated;
     int					audioDevID;
     int					audioOutputChannels;
     int					audioInputChannels;
     int					audioSamplingRate;
     int					audioBufferSize;
     int					audioNumBuffers;
     int					fftWindowUse;
     
     // ARDUINO settings
     bool					arduinoActivated;
     string					serialDevice;
     int					baudRate;
     
     // OSC settings
     string					host_number;
     string					host_port;
     string                 server_port;
     
     // MIDI settings
     int                    midiPortNumber;
     
     //////////////////////////////////////////////
    
private:
    ofxXmlSettings			setting_data;
    bool                    flagSystemLoaded;
	
};