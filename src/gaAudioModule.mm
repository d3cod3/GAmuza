
#include "gaAudioModule.h"


//--------------------------------------------------------------
gaAudioModule::gaAudioModule(int windowW, int windowH){
    ofSetDataPathRoot(gapp->_bundleDataPath);
    
    winW = windowW;
    winH = windowH;
    
     isON = false;
    
}

//--------------------------------------------------------------
gaAudioModule::~gaAudioModule(){
    
}

//--------------------------------------------------------------
void gaAudioModule::setup(){
    ofSetWindowShape(winW,winH);
    ofSetEscapeQuitsApp(false);
    
    ///////////////////////////////////////////////
	// load fonts
	fontSmall.loadFont("fonts/D3Litebitmapism.ttf", 8, true, true);
	///////////////////////////////////////////////
    
    //////////////////////////////////////////////
	// Main GUI setup
	gamuzaMainColor         = simpleColor(9,147,211,255);
	gamuzaWhiteColor        = simpleColor(240,240,240,255);
	gamuzaMarkColor         = simpleColor(255,231,118,255);
    gamuzaChartBackColor    = simpleColor(40, 40, 40, 255);
    
    thisVolumes = new float[MAX_INPUT_CHANNELS];
    thisPitches = new float[MAX_INPUT_CHANNELS];
    
    gui = new ofxControlPanel();
    gui->loadFont("fonts/D3Litebitmapism.ttf", 8);
	gui->setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui->setBackgroundColor(simpleColor(20, 20, 20, 255));
	gui->setTextColor(gamuzaWhiteColor,simpleColor(240, 240, 240, 225));
	gui->setOutlineColor(simpleColor(0,0,0,255));
    
    gui->setup(" ", 0,0,winW,winH);
	gui->setDraggable(false);
    ///////////////////////////////////////////////
    
    moduleStarted = false;
    setupGui();
}

//--------------------------------------------------------------
void gaAudioModule::update(){
    if(moduleStarted){
        for(int i=0;i<MAX_INPUT_CHANNELS;i++){
            thisVolumes[i] = gapp->inputAudioCH[i]._osc_chVolume;
            thisPitches[i] = gapp->inputAudioCH[i]._s_chPitch;
        }
        if(isON){
            updateGui();
            gui->update();
        }
    }
}

//--------------------------------------------------------------
void gaAudioModule::draw() {
    if(moduleStarted && isON){
        ofBackground(20);
        gui->draw(audioInputChannels);
        drawGui();
    }
}

//--------------------------------------------------------------
void gaAudioModule::setModuleON(bool onOff){
    isON = onOff;
}

//--------------------------------------------------------------
void gaAudioModule::restart(){
    moduleStarted = false;
    audioInputChannels = gapp->audioInputChannels;
    moduleStarted = true;
}

//--------------------------------------------------------------
void gaAudioModule::setupGui() {
    char xml_name[256];
	char temp[128];
    
    audioInputChannels = gapp->audioInputChannels;
    
    for(int i=0;i<MAX_INPUT_CHANNELS;i++){
        //////////////////////////////////////////////
        sprintf(temp," AUDIO INPUT [CHANNEL %i]",i);
        gui->setBackgroundColor(simpleColor(20, 20, 20, 255));
        gui->setOutlineColor(simpleColor(0,0,0, 255));
        gui->addPanel(temp, 2);
        gui->setWhichPanel(temp);
        gui->setBackgroundColor(simpleColor(90, 90, 90, 255));
        gui->setOutlineColor(simpleColor(0,0,0,255));
        
        gui->setWhichColumn(0);
        //////////////////////////////////////////////
        gui->setTextColor(gamuzaMainColor);
        gui->addLabel("GENERAL SETTINGS");
        
        gui->setTextColor(gamuzaMarkColor);
        sprintf(xml_name,"USE_AUDIO_INPUT_%i",i);
        gui->addToggle("USE INPUT CHANNEL", xml_name, false);
        gui->setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        
        sprintf(xml_name,"VOLUME_AUDIO_INPUT_%i",i);
        gui->addSlider("VOLUME", xml_name, gapp->inputAudioCH[i]._volume,0.01f,1.0f,false);
        sprintf(xml_name,"MUTE_AUDIO_INPUT_%i",i);
        gui->addToggle("MUTE", xml_name, false);
        //////////////////////////////////////////////
        gui->setTextColor(gamuzaMainColor);
        gui->addLabel("OSC DATA SETTINGS");
        gui->setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        
        sprintf(xml_name,"SMOOTHING_FACTOR_AUDIOCH_%i",i);
        gui->addSlider("SMOOTHING FACTOR",xml_name,gapp->inputAudioCH[i]._smoothingFactor,0.01f,0.99f,false);
        //////////////////////////////////////////////
        gui->setBackgroundColor(gamuzaChartBackColor);
        gui->addChartPlotter("VOLUME CHART", guiStatVarPointer("CHANNEL VOLUME", &thisVolumes[i], GUI_VAR_FLOAT, true, 2), 180, 62, 200, 0.0f, 1.0f);
        gui->addChartPlotter("PITCH CHART", guiStatVarPointer("CHANNEL PITCH", &thisPitches[i], GUI_VAR_FLOAT, true, 2), 180, 62, 200, 20.0f, 20000.0f);
        
        gui->setWhichColumn(1);
        //////////////////////////////////////////////
        gui->setTextColor(gamuzaMainColor);
        gui->addLabel("PARAMETRIC EQUALIZATION");
        gui->setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        
        sprintf(xml_name,"EQ_BAND1_CENTER_%i",i);
        gui->addSlider("BAND 1 CENTER [BIN]", xml_name, gapp->inputAudioCH[i].eqLOWCenter,0.0f,gapp->audioBufferSize/2.0f,false);
        sprintf(xml_name,"EQ_BAND1_AMPLITUDE_%i",i);
        gui->addSlider("BAND 1 AMPLITUDE [DB]", xml_name, gapp->inputAudioCH[i].eqLOWAmplitude,-3.0f,6.0f,false);
        sprintf(xml_name,"EQ_BAND1_WIDTH_%i",i);
        gui->addSlider("BAND 1 WIDTH [Q]", xml_name, gapp->inputAudioCH[i].eqLOWWidth,0.01f,gapp->audioBufferSize/4.0f,false);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND2_CENTER_%i",i);
        gui->addSlider("BAND 2 CENTER [BIN]", xml_name, gapp->inputAudioCH[i].eqMIDCenter,0.0f,gapp->audioBufferSize/2.0f,false);
        sprintf(xml_name,"EQ_BAND2_AMPLITUDE_%i",i);
        gui->addSlider("BAND 2 AMPLITUDE [DB]", xml_name, gapp->inputAudioCH[i].eqMIDAmplitude,-3.0f,6.0f,false);
        sprintf(xml_name,"EQ_BAND2_WIDTH_%i",i);
        gui->addSlider("BAND 2 WIDTH [Q]", xml_name, gapp->inputAudioCH[i].eqMIDWidth,0.01f,gapp->audioBufferSize/4.0f,false);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND3_CENTER_%i",i);
        gui->addSlider("BAND 3 CENTER [BIN]", xml_name, gapp->inputAudioCH[i].eqHICenter,0.0f,gapp->audioBufferSize/2.0f,false);
        sprintf(xml_name,"EQ_BAND3_AMPLITUDE_%i",i);
        gui->addSlider("BAND 3 AMPLITUDE [DB]", xml_name, gapp->inputAudioCH[i].eqHIAmplitude,-3.0f,6.0f,false);
        sprintf(xml_name,"EQ_BAND3_WIDTH_%i",i);
        gui->addSlider("BAND 3 WIDTH [Q]", xml_name, gapp->inputAudioCH[i].eqHIWidth,0.01f,gapp->audioBufferSize/4.0f,false);
        //////////////////////////////////////////////
    }
    
    gui->loadSettings("settings/audioGuiSettings.xml");
    
    //////////////////////////////////////////////
	// GUI Events
	//gui->setupEvents();
	//gui->enableEvents();
    
    moduleStarted = true;
    
}

//--------------------------------------------------------------
void gaAudioModule::updateGui() {
    char xml_name[256];
    
    for(unsigned int i=0;i<audioInputChannels;i++){
        sprintf(xml_name,"USE_AUDIO_INPUT_%i",i);
        gapp->inputAudioCH[i].captureAudio = gui->getValueI(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"VOLUME_AUDIO_INPUT_%i",i);
        gapp->inputAudioCH[i]._volume = gui->getValueF(xml_name);
        sprintf(xml_name,"MUTE_AUDIO_INPUT_%i",i);
        gapp->inputAudioCH[i]._mute = gui->getValueI(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"SMOOTHING_FACTOR_AUDIOCH_%i",i);
        gapp->inputAudioCH[i]._smoothingFactor = gui->getValueF(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND1_CENTER_%i",i);
        gapp->inputAudioCH[i].eqLOWCenter = gui->getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND1_AMPLITUDE_%i",i);
        gapp->inputAudioCH[i].eqLOWAmplitude = gui->getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND1_WIDTH_%i",i);
        gapp->inputAudioCH[i].eqLOWWidth = gui->getValueF(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND2_CENTER_%i",i);
        gapp->inputAudioCH[i].eqMIDCenter = gui->getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND2_AMPLITUDE_%i",i);
        gapp->inputAudioCH[i].eqMIDAmplitude = gui->getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND2_WIDTH_%i",i);
        gapp->inputAudioCH[i].eqMIDWidth = gui->getValueF(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND3_CENTER_%i",i);
        gapp->inputAudioCH[i].eqHICenter = gui->getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND3_AMPLITUDE_%i",i);
        gapp->inputAudioCH[i].eqHIAmplitude = gui->getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND3_WIDTH_%i",i);
        gapp->inputAudioCH[i].eqHIWidth = gui->getValueF(xml_name);
    }
    
}

//--------------------------------------------------------------
void gaAudioModule::drawGui() {
    char temp[128];
    
    ////////////////////////////////////
	// panel tabs colorize
	if(!gui->minimize){
		ofEnableAlphaBlending();
		ofFill();
        
        glColor4f(1.0,0.906,0.463,0.6);
        for(unsigned int i=0;i<audioInputChannels;i++){
            ofRect(gui->panelTabs[i].x+1, gui->panelTabs[i].y+1, gui->panelTabs[i].width-2, gui->panelTabs[i].height-2);
        }
        ofDisableAlphaBlending();
        //////////////////////////////////////////////
        // AUDIO input  Additional GUI
        for(unsigned int i=0;i<audioInputChannels;i++){
            sprintf(temp," AUDIO INPUT [CHANNEL %i]",i);
            if(gui->getSelectedPanelName() == temp){
                gapp->inputAudioCH[i].drawChannel(460,30,320,120);
            }
        }
        //////////////////////////////////////////////
        if(audioInputChannels == 0){
            ofSetColor(255);
            fontSmall.drawString("NO AUDIO INPUT CHANNELS SELECTED", 20,20);
        }
        
    }
    
}

//--------------------------------------------------------------
void gaAudioModule::keyPressed(int key) { 
	
}

//--------------------------------------------------------------
void gaAudioModule::keyReleased(int key) { 
	
}

//--------------------------------------------------------------
void gaAudioModule::mouseMoved(int x, int y) { 
	
}

//--------------------------------------------------------------
void gaAudioModule::mouseDragged(int x, int y, int button) {
	gui->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void gaAudioModule::mousePressed(int x, int y, int button) { 
	gui->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void gaAudioModule::mouseReleased() { 
	gui->mouseReleased();
}

//--------------------------------------------------------------
void gaAudioModule::mouseReleased(int x, int y, int button ){ 
	gui->mouseReleased();
}

//--------------------------------------------------------------
void gaAudioModule::mouseScrolled(float x, float y) { 
	
}

