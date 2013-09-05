
#pragma once

// includes
#include "gamuzaIncludes.h"

// constants
#include "gamuzaConstants.h"

// External windows
#include "gaVideoPreview.h"

// GUI PANELS
#include "gaTimeline.h"

/////////////////////////////////
extern gaVideoPreview   *gaVP; // OUTPUT TEXTURE PREVIEW

extern gaTimeline       *gaTL; // TIMELINE PANEL WINDOW external reference
/////////////////////////////////

class gamuzaMain : public ofxNSWindowApp, public ofxMidiListener, public pd::PdReceiver, public pd::PdMidiReceiver{
    
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
	
    //////////////////////////////////// RECEIVERS
    /////////////////////////////////////////////////////////////////////
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
    
    // LIBPD / PURE DATA /////////////// --> gamuzaPD.h
    void setupPD();
    // pd message receiver callbacks
    void receiveBang(const std::string& dest);
    void receiveFloat(const std::string& dest, float value);
    void receiveSymbol(const std::string& dest, const std::string& symbol);
    void receiveList(const std::string& dest, const pd::List& list);
    void receiveMessage(const std::string& dest, const std::string& msg, const pd::List& list);
    // pd midi receiver callbacks
    void receiveNoteOn(const int channel, const int pitch, const int velocity);
    void receiveControlChange(const int channel, const int controller, const int value);
    void receiveProgramChange(const int channel, const int value);
    void receivePitchBend(const int channel, const int value);
    void receiveAftertouch(const int channel, const int value);
    void receivePolyAftertouch(const int channel, const int pitch, const int value);
    void receiveMidiByte(const int port, const int byte);
    ////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////
	
	// APP ///////////////////////////// --> gamuzaApp.h
    void cleanMemory();
    void resetApp();
    void sendHardwareInfo(vector<string> &aInD,vector<int> &aInDID,
                          vector<string> &aOutD,vector<int> &aOutDID,
                          vector<string> &mD,vector<string> &sD,
                          vector<string> &aOutCh, vector<string> &aInCh);
    void getScreenInfo(int w, int h);
    void getScreensData(vector<ofRectangle> screensData);
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
    
    // AUDIO /////////////////////////// --> gamuzaAudio.h
    void setupAudio();
    void addAudioModule(int _wT, float _freq);
    void addAudioModule(int _wT, float _freq, int _ch);
    void addAudioSample(string _file);
    void addInputRecording();
    void resetAudioOutput();
    void resetSoundStream();
    
    // CONSOLE /////////////////////////// --> gamuzaConsole.h
    void sendGALog(string _message);
    void sendPrivateMessage(int _type, string _message);
    
    // FBO ///////////////////////////// --> gamuzaFBO.h
    void setupFBO();
    void updateFBO();
    void drawFBO();
    void drawIntoFBO();
    void setColorCorrection(float gamma, float bright, float sat,
                            float contr, float filmB, float tech,
                            float whiteD, float expos, float diff);
    
    // GUI ///////////////////////////// --> gamuzaGui.h
    void setupGui();
    void updateGui();
    void drawGui();
    void gamuzaFullscreen(int actualScreen);
    ofVec2f reduceToAspectRatio(int _w, int _h);
    
    // MAPPING ///////////////////////// --> gamuzaMapping.h
    void setupMapping();
    void updateMapping();
    void drawMapping();
    void resetMappingPoints();
    void loadMappingPoints();
    void saveMappingPoints();
    void toggleDrawGrid();
    bool switchMouseKeyControl();
    void manualPointEditON();
    void manualPointEditOFF();
    void northMappingPoint();
    void southMappingPoint();
    void eastMappingPoint();
    void westMappingPoint();
    
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
    void resetIncomingOSC();
    void resetOutgoingOSC();
    void sendBuffer();
    void cleanBuffer();
    
    // SCRIPTING /////////////////////// --> gamuzaScripting.h
    void    setupScripting();
    void    updateScripting();
    void    receiveScript(string script);
    void    receiveScriptFile(string scriptFile);
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
    vector<ofRectangle>         _screensData;
    int                         _actualScreen;
    int                         _mainScreenW;
    int                         _mainScreenH;
    ofSerial	                _serial;
    vector<string>              _videoDevices;
    vector<ofSerialDeviceInfo>  _deviceList;
    vector<string>			    _serialDev;
    vector<string>			    _audioDev;
    vector<string>			    _audioInDev;
    vector<string>			    _audioOutDev;
    vector<int>                 _audioInDevID;
    vector<int>                 _audioOutDevID;
    vector<string>			    _midiDev;
    vector<string>				_inputCH;
    vector<string>				_outputCH;
    int                         _fboMaxSamples;
    char                        _windowTitle[256];
    string                      _bundleDataPath;
    
    ////////////////////////////////////////////// //////////////////////////////////////////////
    ////////////////////////////////////////////// //////////////////////////////////////////////
    // SETTINGS vars from gamuzaSettings.xml
    
    // SCREENS settings
    int                     projectionScreenW;
    int                     projectionScreenH;
    float					INVprojectionScreenW;
    float					INVprojectionScreenH;
    
    // MAPPING settings
    int                     gridRes;
    int                     fboNumSamples;
    
    // AUTOMATION settings
    bool					autoPilot;
    int                     autoPilotScreen;
    bool					autoLoadScript;
    bool					autoLoadMapping;
    string					autoScriptFile;
    string					autoMappingFile;
    
    // TRACKING settings
    int                     workingW;
    int                     workingH;
    int                     totPixels;
    
    // AUDIO settings
    int                     audioInDevID;
    int                     audioOutDevID;
    int                     audioOutputChannels;
    int                     audioInputChannels;
    int                     audioSamplingRate;
    int                     audioBufferSize;
    int                     audioNumBuffers;
    int                     fftWindowUse;
    
    // MIDI settings
    int                     midiPortNumber;
    
    // ARDUINO settings
    string					serialDevice;
    int                     baudRate;
    
    // OSC settings
    string					host_number;
    string					host_port;
    string                  server_port;
    
    ////////////////////////////////////////////// //////////////////////////////////////////////
    ////////////////////////////////////////////// //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // ARDUINO --> gamuzaArduino.h
    ofArduino				arduino;
    bool					useArduino;
    bool                    isArduinoConnected;
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
    
    ofxPd                   pd;
    vector<string>          pdPatches;
    
    vector<ofxAUPlugin*>    auPlugins;
    vector<string*>         gamuzaAUList;
    
    ofQTKitGrabber          fakeAudioTrack;
    vector<string>          gamuzaAudioCodecsList;
	
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
    string                  currentLog;
    string                  currentErrorLog;
    string                  currentGlobalLog;
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // FBO --> gamuzaFBO.h
    ofFbo					drawingFbo;
    ofFbo                   gamuzaFbo;
    ofxFastFboReader        pixelsReader;
    ofPixels                gamuzaPixels;
    ofShader				shaderColorCorrection;
    ofImage                 tempFrame;
    
    float                   fboDrawingW;
    float                   fboDrawingH;
    float                   fboDrawingPosX;
    float                   fboDrawingPosY;
    
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
    ofTexture				emptyTexture;
    ofVec2f                 asRatio;
    ofImage                 _hueWheel;
    bool                    isFullscreen;
    
    float                   scaledMouseX;
    float                   scaledMouseY;
    
    //////////////////////////////////////////////
    // Video Tracking vars
    ofPtr<ofQTKitGrabber>	vidRecorder;
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // MAPPING --> gamuzaMapping.h
    int                     res;
    int                     realRes;
    bool                    saveMappingSettings;
    bool                    drawGrid;
    
    matrixAreas             finalTextureMapping;
    int                     totalMappingPoints;
    int                     actualMappingPoint;
    bool                    manualEditMappingPoint;
    bool                    activateMouseMapping;
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
    ofxOscReceiver          receiver;
    
    ofxOscMessage           received_message;
    ofxOscMessage			osc_message;
    ofxOscBundle			osc_bundle;
    
    ofxUDPManager           connectionTest;
    vector<string>          oscReceivingLabels;
    vector<string>          *oscReceivingValues;
    vector<string>          oscSendingLabels;
    vector<string>          oscSendingValues;
    vector<int>             oscSendingTypes;
    vector<bool>            oscSendingActive;
    int                     oscIndex;
    bool                    connectionUP;
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // SCRIPTING --> gamuzaScripting.h
    ofxLua                      lua;
    int                         liveKey;
    string                      GAscriptFileName;
    
    char                        temp_error[512];
    vector<string>              errorVector;
    bool                        printError;
    int                         gaFrameCounter;
    //////////////////////////////////////////////
    
private:
    ofxXmlSettings			setting_data;
    bool                    flagSystemLoaded;
	
};