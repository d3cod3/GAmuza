
#include "gaAudioModule.h"


//--------------------------------------------------------------
gaAudioModule::gaAudioModule(int windowW, int windowH){
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
    
    winW = windowW;
    winH = windowH;
    
}

//--------------------------------------------------------------
gaAudioModule::~gaAudioModule(){
    
}

//--------------------------------------------------------------
void gaAudioModule::setup(){
    ofSetWindowShape(winW,winH);
    
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
    ///////////////////////////////////////////////
    
    audioInputChannels = gapp->audioInputChannels;
    setupGui();
}

//--------------------------------------------------------------
void gaAudioModule::update() {
    updateGui();
    gui.update();
}

//--------------------------------------------------------------
void gaAudioModule::draw() {
    ofBackground(20);
	gui.draw();
    drawGui();
}

//--------------------------------------------------------------
void gaAudioModule::restart(){
    audioInputChannels = gapp->audioInputChannels;
    gui.reset();
    setupGui();
}

//--------------------------------------------------------------
void gaAudioModule::setupGui() {
    char xml_name[256];
	char temp[128];
	
	gui.loadFont("fonts/D3Litebitmapism.ttf", 8);
	gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
	gui.setTextColor(gamuzaWhiteColor,simpleColor(240, 240, 240, 225));
	gui.setOutlineColor(simpleColor(0,0,0,255));
    
    gui.setup(" ", 0, 0,winW,winH);
	gui.setDraggable(false);
    
    for(unsigned int i=0;i<audioInputChannels;i++){
        gapp->inputAudioCH[i].loadNoiseFilter();
        //////////////////////////////////////////////
        sprintf(temp," AUDIO INPUT [CHANNEL %i]",i);
        gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
        gui.setOutlineColor(simpleColor(0,0,0, 255));
        gui.addPanel(temp, 5);
        gui.setWhichPanel(temp);
        gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
        gui.setOutlineColor(simpleColor(0,0,0,255));
        
        gui.setWhichColumn(0);
        //////////////////////////////////////////////
        gui.setTextColor(gamuzaMainColor);
        gui.addLabel("GENERAL SETTINGS");
        
        gui.setTextColor(gamuzaMarkColor);
        sprintf(xml_name,"USE_AUDIO_INPUT_%i",i);
        gui.addToggle("USE INPUT CHANNEL", xml_name, false);
        gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        
        sprintf(xml_name,"VOLUME_AUDIO_INPUT_%i",i);
        gui.addSlider("VOLUME", xml_name, gapp->inputAudioCH[i]._volume,0.01f,1.0f,false);
        sprintf(xml_name,"MUTE_AUDIO_INPUT_%i",i);
        gui.addToggle("MUTE", xml_name, false);
        //////////////////////////////////////////////
        gui.setTextColor(gamuzaMainColor);
        gui.addLabel("NOISE REDUCTION SETTINGS");
        gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        
        sprintf(xml_name,"REC_NOISE_FILTER_%i",i);
        gui.addToggle("REC NOISE", xml_name, false);
        sprintf(xml_name,"NOISE_REDUX_FACTOR_%i",i);
        gui.addSlider("REDUX FACTOR", xml_name, gapp->inputAudioCH[i].reduxFactor,1.0f,10.0f,false);
        //////////////////////////////////////////////
        gui.setBackgroundColor(gamuzaChartBackColor);
        gui.addChartPlotter("VOLUME CHART", guiStatVarPointer("CHANNEL VOLUME", &gapp->inputAudioCH[i]._osc_chVolume, GUI_VAR_FLOAT, true, 2), 180, 80, 200, 0.0f, 1.0f);
        gui.addChartPlotter("PITCH CHART", guiStatVarPointer("CHANNEL PITCH", &gapp->inputAudioCH[i]._s_chPitch, GUI_VAR_FLOAT, true, 2), 180, 80, 200, 20.0f, 20000.0f);
        
        gui.setWhichColumn(1);
        //////////////////////////////////////////////
        gui.setTextColor(gamuzaMainColor);
        gui.addLabel("OSC DATA SETTINGS");
        gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        
        sprintf(xml_name,"SMOOTHING_FACTOR_AUDIOCH_%i",i);
        gui.addSlider("SMOOTHING FACTOR",xml_name,gapp->inputAudioCH[i]._smoothingFactor,0.01f,0.99f,false);
        //////////////////////////////////////////////
        gui.setTextColor(gamuzaMainColor);
        gui.addLabel("PARAMETRIC EQUALIZATION");
        gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        
        sprintf(xml_name,"EQ_BAND1_CENTER_%i",i);
        gui.addSlider("BAND 1 CENTER [BIN]", xml_name, gapp->inputAudioCH[i].eqLOWCenter,0.0f,gapp->audioBufferSize/2.0f,false);
        sprintf(xml_name,"EQ_BAND1_AMPLITUDE_%i",i);
        gui.addSlider("BAND 1 AMPLITUDE [DB]", xml_name, gapp->inputAudioCH[i].eqLOWAmplitude,-3.0f,6.0f,false);
        sprintf(xml_name,"EQ_BAND1_WIDTH_%i",i);
        gui.addSlider("BAND 1 WIDTH [Q]", xml_name, gapp->inputAudioCH[i].eqLOWWidth,0.01f,gapp->audioBufferSize/4.0f,false);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND2_CENTER_%i",i);
        gui.addSlider("BAND 2 CENTER [BIN]", xml_name, gapp->inputAudioCH[i].eqMIDCenter,0.0f,gapp->audioBufferSize/2.0f,false);
        sprintf(xml_name,"EQ_BAND2_AMPLITUDE_%i",i);
        gui.addSlider("BAND 2 AMPLITUDE [DB]", xml_name, gapp->inputAudioCH[i].eqMIDAmplitude,-3.0f,6.0f,false);
        sprintf(xml_name,"EQ_BAND2_WIDTH_%i",i);
        gui.addSlider("BAND 2 WIDTH [Q]", xml_name, gapp->inputAudioCH[i].eqMIDWidth,0.01f,gapp->audioBufferSize/4.0f,false);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND3_CENTER_%i",i);
        gui.addSlider("BAND 3 CENTER [BIN]", xml_name, gapp->inputAudioCH[i].eqHICenter,0.0f,gapp->audioBufferSize/2.0f,false);
        sprintf(xml_name,"EQ_BAND3_AMPLITUDE_%i",i);
        gui.addSlider("BAND 3 AMPLITUDE [DB]", xml_name, gapp->inputAudioCH[i].eqHIAmplitude,-3.0f,6.0f,false);
        sprintf(xml_name,"EQ_BAND3_WIDTH_%i",i);
        gui.addSlider("BAND 3 WIDTH [Q]", xml_name, gapp->inputAudioCH[i].eqHIWidth,0.01f,gapp->audioBufferSize/4.0f,false);
        //////////////////////////////////////////////
    }
    
    gui.loadSettings("settings/guiSettings.xml");
    
    //////////////////////////////////////////////
	// GUI Events
	gui.setupEvents();
	gui.enableEvents();
    
    for(unsigned int i=0;i<audioInputChannels;i++){ // for each audio input channel
        // create event for noise filtering
        sprintf(temp,"REC_NOISE_FILTER_%i",i);
        ofAddListener(gui.createEventGroup(temp), this, &gaAudioModule::recordNoise);
    }
    
}

//--------------------------------------------------------------
void gaAudioModule::updateGui() {
    char xml_name[256];
    
    for(unsigned int i=0;i<audioInputChannels;i++){
        sprintf(xml_name,"USE_AUDIO_INPUT_%i",i);
        gapp->inputAudioCH[i].captureAudio = gui.getValueI(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"VOLUME_AUDIO_INPUT_%i",i);
        gapp->inputAudioCH[i]._volume = gui.getValueF(xml_name);
        sprintf(xml_name,"MUTE_AUDIO_INPUT_%i",i);
        gapp->inputAudioCH[i]._mute = gui.getValueI(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"NOISE_REDUX_FACTOR_%i",i);
        gapp->inputAudioCH[i].reduxFactor = gui.getValueF(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND1_CENTER_%i",i);
        gapp->inputAudioCH[i].eqLOWCenter = gui.getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND1_AMPLITUDE_%i",i);
        gapp->inputAudioCH[i].eqLOWAmplitude = gui.getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND1_WIDTH_%i",i);
        gapp->inputAudioCH[i].eqLOWWidth = gui.getValueF(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND2_CENTER_%i",i);
        gapp->inputAudioCH[i].eqMIDCenter = gui.getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND2_AMPLITUDE_%i",i);
        gapp->inputAudioCH[i].eqMIDAmplitude = gui.getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND2_WIDTH_%i",i);
        gapp->inputAudioCH[i].eqMIDWidth = gui.getValueF(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"EQ_BAND3_CENTER_%i",i);
        gapp->inputAudioCH[i].eqHICenter = gui.getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND3_AMPLITUDE_%i",i);
        gapp->inputAudioCH[i].eqHIAmplitude = gui.getValueF(xml_name);
        sprintf(xml_name,"EQ_BAND3_WIDTH_%i",i);
        gapp->inputAudioCH[i].eqHIWidth = gui.getValueF(xml_name);
        //////////////////////////////////////////////
        sprintf(xml_name,"SMOOTHING_FACTOR_AUDIOCH_%i",i);
        gapp->inputAudioCH[i]._smoothingFactor = gui.getValueF(xml_name);
    }
    
}

//--------------------------------------------------------------
void gaAudioModule::drawGui() {
    char temp[128];
    
    ////////////////////////////////////
	// panel tabs colorize
	if(!gui.minimize){
		ofEnableAlphaBlending();
		ofFill();
        
        glColor4f(1.0,0.906,0.463,1.0);
        for(unsigned int i=0;i<audioInputChannels;i++){
            ofRect(gui.panelTabs[i].x+1, gui.panelTabs[i].y+1, gui.panelTabs[i].width-2, gui.panelTabs[i].height-2);
        }
        ofDisableAlphaBlending();
        
        //////////////////////////////////////////////
        // AUDIO input  Additional GUI
        
        for(unsigned int i=0;i<audioInputChannels;i++){
            sprintf(temp," AUDIO INPUT [CHANNEL %i]",i);
            if(gui.getSelectedPanelName() == temp){
                if(gapp->inputAudioCH[i].noiseRec){
                    ofSetColor(216, 64, 64);
                    fontSmall.drawString("RECORDING NOISE", 872,52);
                    fontSmall.drawString("RECORDING | CLICK TO STOP", 48,248);
                }
                gapp->inputAudioCH[i].drawChannel(460,16,320,120);
            }
        }
        
        //////////////////////////////////////////////
        
    }
    
}

//--------------------------------------------------------------
void gaAudioModule::recordNoise(guiCallbackData & data){
	char temp[256];
    sprintf(temp,"REC_NOISE_FILTER_%i",gui.getSelectedPanel());
    if(data.isElement(temp) && data.getInt(0) == 1){
        gapp->inputAudioCH[gui.getSelectedPanel()].recNoiseFilter();
        gui.setValueB(temp, false);
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
	gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void gaAudioModule::mousePressed(int x, int y, int button) { 
	gui.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void gaAudioModule::mouseReleased() { 
	gui.mouseReleased();
}

//--------------------------------------------------------------
void gaAudioModule::mouseReleased(int x, int y, int button ){ 
	gui.mouseReleased();
}

//--------------------------------------------------------------
void gaAudioModule::mouseScrolled(float x, float y) { 
	
}

