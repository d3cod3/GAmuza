
#include "gaOSCModule.h"


//--------------------------------------------------------------
gaOSCModule::gaOSCModule(int windowW, int windowH){
    ofSetDataPathRoot(gapp->_bundleDataPath);
    
    winW = windowW;
    winH = windowH;
    
}

//--------------------------------------------------------------
gaOSCModule::~gaOSCModule(){
    
}

//--------------------------------------------------------------
void gaOSCModule::setup(){
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
    
    setupGui();
}

//--------------------------------------------------------------
void gaOSCModule::update() {
    updateGui();
    gui.update();
}

//--------------------------------------------------------------
void gaOSCModule::draw() {
    ofBackground(20);
	gui.draw(1);
    drawGui();
}

//--------------------------------------------------------------
void gaOSCModule::restart(){
    char temp[128];
    
}

//--------------------------------------------------------------
void gaOSCModule::setupGui() {
    char xml_name[256];
	char temp[128];
	
	gui.loadFont("fonts/D3Litebitmapism.ttf", 8);
	gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
	gui.setTextColor(gamuzaWhiteColor,simpleColor(240, 240, 240, 225));
	gui.setOutlineColor(simpleColor(0,0,0,255));
    
    gui.setup(" ", 0, 0,winW,winH);
	gui.setDraggable(false);
    
    gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
    gui.setOutlineColor(simpleColor(0,0,0,255));
    sprintf(temp," OSC MODULE");
    gui.addPanel(temp, 5);
    
    gui.setWhichPanel(temp);
    gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    gui.setOutlineColor(simpleColor(0,0,0,255));
    //////////////////////////////////////////////
    
    gui.loadSettings("settings/oscGuiSettings.xml");
    
    //////////////////////////////////////////////
	// GUI Events
	gui.setupEvents();
	gui.enableEvents();
    
    
}

//--------------------------------------------------------------
void gaOSCModule::updateGui() {
    char xml_name[256];
    
    
    
}

//--------------------------------------------------------------
void gaOSCModule::drawGui() {
    char temp[128];
    ////////////////////////////////////
	// panel tabs colorize
	if(!gui.minimize){
		ofEnableAlphaBlending();
		ofFill();
        
        
        
        ofDisableAlphaBlending();
        
    }
}

//--------------------------------------------------------------
void gaOSCModule::keyPressed(int key) { 
	
}

//--------------------------------------------------------------
void gaOSCModule::keyReleased(int key) { 
	
}

//--------------------------------------------------------------
void gaOSCModule::mouseMoved(int x, int y) { 
	
}

//--------------------------------------------------------------
void gaOSCModule::mouseDragged(int x, int y, int button) {
	gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void gaOSCModule::mousePressed(int x, int y, int button) { 
	gui.mousePressed(x, y, button);
    
    if(gui.saveDown){
        
    }
}

//--------------------------------------------------------------
void gaOSCModule::mouseReleased() { 
	
}

//--------------------------------------------------------------
void gaOSCModule::mouseReleased(int x, int y, int button ){ 
	gui.mouseReleased();
}

//--------------------------------------------------------------
void gaOSCModule::mouseScrolled(float x, float y) { 
	
}

