
#include "gaArduinoModule.h"


//--------------------------------------------------------------
gaArduinoModule::gaArduinoModule(int windowW, int windowH){
    
    ofSetDataPathRoot(gapp->_bundleDataPath);
    
    winW = windowW;
    winH = windowH;
    
    isON = false;
    
}

//--------------------------------------------------------------
gaArduinoModule::~gaArduinoModule(){
    
}

//--------------------------------------------------------------
void gaArduinoModule::setup(){
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
    ///////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // vector<string> of ardDigitalPinModes list
    ardDigitalPinModes.assign(2, string());
	ardDigitalPinModes[0] = "INPUT";
	ardDigitalPinModes[1] = "OUTPUT";
	// vector<string> of ardDigitalPinModesPWM list
    ardDigitalPinModesPWM.assign(3, string());
	ardDigitalPinModesPWM[0] = "INPUT";
	ardDigitalPinModesPWM[1] = "OUTPUT";
	ardDigitalPinModesPWM[2] = "PWM";
    // vector<string> of ardDigitalPinModesSERVO list
    ardDigitalPinModesSERVO.assign(4, string());
	ardDigitalPinModesSERVO[0] = "INPUT";
	ardDigitalPinModesSERVO[1] = "OUTPUT";
	ardDigitalPinModesSERVO[2] = "PWM";
    ardDigitalPinModesSERVO[3] = "SERVO";
	// vector<string> of ardAnalogPinModes list
    ardAnalogPinModes.assign(2, string());
	ardAnalogPinModes[0] = "REPORT ON";
	ardAnalogPinModes[1] = "REPORT OFF";
    //////////////////////////////////////////////
    
    analogPinValues					= new int[6];
    digitalPinValuesInput           = new int[12];
    
    setupGui();
    
}

//--------------------------------------------------------------
void gaArduinoModule::update() {
    
    for(unsigned int i=0;i<6;i++){
        analogPinValues[i] = gapp->_s_analogPinValues[i];
    }
    for(unsigned int i=2;i<14;i++){
        digitalPinValuesInput[i-2] = gapp->_osc_digitalPinValuesInput[i-2];
    }
    if(isON){
        updateGui();
        gui.update();
    }
}

//--------------------------------------------------------------
void gaArduinoModule::draw() {
    if(isON){
        ofBackground(20);
        gui.draw(1);
        drawGui();
    }
}

//--------------------------------------------------------------
void gaArduinoModule::setModuleON(bool onOff){
    isON = onOff;
}

//--------------------------------------------------------------
void gaArduinoModule::initPins(){
    char temp[128];
    // configure ARDUINO PIN MODES from settings
    for(unsigned int i=2;i<14;i++){
        sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_MODE",i);
        if(i == 3 || i == 5 || i == 6 || i == 11){
            if(gui.getValueI(temp) == 0){
                gapp->digitalPinModes[i-2] = ARD_INPUT;
            }else if(gui.getValueI(temp) == 1){
                gapp->digitalPinModes[i-2] = ARD_OUTPUT;
            }else if(gui.getValueI(temp) == 2){
                gapp->digitalPinModes[i-2] = ARD_PWM;
            }
        }else if(i == 9 || i == 10){
            if(gui.getValueI(temp) == 0){
                gapp->digitalPinModes[i-2] = ARD_INPUT;
            }else if(gui.getValueI(temp) == 1){
                gapp->digitalPinModes[i-2] = ARD_OUTPUT;
            }else if(gui.getValueI(temp) == 2){
                gapp->digitalPinModes[i-2] = ARD_PWM;
            }else if(gui.getValueI(temp) == 3){
                gapp->digitalPinModes[i-2] = ARD_SERVO;
            }
        }else{
            if(gui.getValueI(temp) == 0){
                gapp->digitalPinModes[i-2] = ARD_INPUT;
            }else if(gui.getValueI(temp) == 1){
                gapp->digitalPinModes[i-2] = ARD_OUTPUT;
            }
        }
    }
    for(unsigned int i=0;i<6;i++){
		sprintf(temp,"ARDUINO_ANALOG_PIN_%i_MODE",i);
		if(gui.getValueI(temp) == 0){
            gapp->analogPinModes[i] = ARD_ON;
        }else if(gui.getValueI(temp) == 1){
            gapp->analogPinModes[i] = ARD_OFF;
        }
	}
    
}

//--------------------------------------------------------------
void gaArduinoModule::restart(){
    char temp[128];
    if(gapp->isArduinoConnected){
        sprintf(temp," ARDUINO DEVICE CONNECTED AT SERIAL PORT %s | WITH BAUDRATE %i", gapp->serialDevice.c_str(), gapp->baudRate);
    }else{
        sprintf(temp," ARDUINO DEVICE NOT CONNECTED");
    }
    gui.panels[0]->name = temp;
    
    initPins();
    gapp->bSetupArduino = false;
    
}

//--------------------------------------------------------------
void gaArduinoModule::setupGui() {
    char xml_name[256];
	char temp[128];
	
	gui.loadFont("fonts/D3Litebitmapism.ttf", 8);
	gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
	gui.setTextColor(gamuzaWhiteColor,simpleColor(240, 240, 240, 225));
	gui.setOutlineColor(simpleColor(0,0,0,255));
    
    gui.setup(" ", 0, 0,winW,winH);
	gui.setDraggable(false);
    
    arduinoGraphics.loadImage("img/arduino.png");
    gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
    gui.setOutlineColor(simpleColor(0,0,0, 255));
    if(gapp->isArduinoConnected){
        sprintf(temp," ARDUINO DEVICE CONNECTED AT SERIAL PORT %s | WITH BAUDRATE %i", gapp->serialDevice.c_str(), gapp->baudRate);
    }else{
        sprintf(temp," ARDUINO DEVICE NOT CONNECTED");
    }
    
    gui.addPanel(temp, 5);
    gui.setWhichPanel(temp);
    gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    gui.setOutlineColor(simpleColor(0,0,0,255));
    
    gui.setWhichColumn(0);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("ANALOG VALUES READING [0 | 5]");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    gui.setBackgroundColor(gamuzaChartBackColor);
    for(unsigned int i=0;i<6;i++){
        sprintf(temp,"ANALOG PIN %i ",i);
        gui.addChartPlotter(temp, guiStatVarPointer("READING", &analogPinValues[i], GUI_VAR_INT, true, 2), 180, 70, 200, 0.0, 1023.0);
    }
    gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    
    gui.setWhichColumn(1);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("ANALOG PINS CONTROL [0 | 5]");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
    for(unsigned int i=0;i<6;i++){
        sprintf(xml_name,"ARDUINO_ANALOG_PIN_%i_MODE",i);
        sprintf(temp,"PIN %i ",i);
        gui.addTextDropDown(temp, xml_name, gapp->analogPinModes[i], ardAnalogPinModes);
    }
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
    
    gui.setWhichColumn(2);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    sprintf(temp,"ARDUINO BOARD");
    gui.addLabel(temp);
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    gui.setTextColor(gamuzaMarkColor);
    sprintf(xml_name,"USE_ARDUINO");
    gui.addToggle("ACTIVE", xml_name, true);
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    gui.addDrawableRect(" ", &arduinoGraphics, 360, 475);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("OSC DATA SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    sprintf(xml_name,"SMOOTHING_FACTOR_ARDUINO");
    gui.addSlider("SMOOTHING FACTOR",xml_name,gapp->arduino_smoothingFactor,0.01f,0.99f,false);
    
    gui.setWhichColumn(3);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("DIGITAL PINS CONTROL [2 | 13]");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    //////////////////////////////////////////////
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
    for(unsigned int i=2;i<14;i++){
        sprintf(xml_name,"ARDUINO_DIGITAL_PIN_%i_MODE",i);
        if(i == 3 || i == 5 || i == 6 || i == 11){
            sprintf(temp,"PIN [PWM] %i ",i);
            gui.addTextDropDown(temp, xml_name, gapp->digitalPinModes[i-2], ardDigitalPinModesPWM);
        }else if(i == 9 || i == 10){
            sprintf(temp,"PIN [SERVO] %i ",i);
            gui.addTextDropDown(temp, xml_name, gapp->digitalPinModes[i-2], ardDigitalPinModesSERVO);
        }else{
            sprintf(temp,"PIN %i ",i);
            gui.addTextDropDown(temp, xml_name, gapp->digitalPinModes[i-2], ardDigitalPinModes);
        }
    }
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
    
    gui.setWhichColumn(4);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("DIGITAL VALUES WRITING [2 | 13]");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    
    //////////////////////////////////////////////
    for(unsigned int i=2;i<14;i++){
        sprintf(xml_name,"ARDUINO_DIGITAL_PIN_%i_VALUE",i);
        if(i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11){
            sprintf(temp,"PIN %i PWM [0 254]",i);
            gui.panels.at(gui.currentPanel)->setElementYSpacing(-5);
            gui.addSlider(temp,xml_name,gapp->digitalPinValuesOutput[i-2],0,254,true);
            gui.setTextColor(simpleColor(0,0,0, 0));
            gui.setForegroundColor(simpleColor(90, 90, 90, 100),simpleColor(0, 255, 20, 255));
            gui.setBackgroundColor(simpleColor(90, 90, 90, 55));
            gui.panels.at(gui.currentPanel)->setElementYSpacing(15);
            gui.addChartPlotter(temp, guiStatVarPointer(" ", &digitalPinValuesInput[i-2], GUI_VAR_INT, true, 2), 180, 8, 200, 0, 255);
            gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
            gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
            gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        }else{
            sprintf(temp,"PIN %i LOW | HIGH",i);
            gui.panels.at(gui.currentPanel)->setElementYSpacing(-5);
            gui.addToggle(temp, xml_name, true);
            gui.setTextColor(simpleColor(0,0,0, 0));
            gui.setForegroundColor(simpleColor(90, 90, 90, 100),simpleColor(0, 255, 20, 255));
            gui.setBackgroundColor(simpleColor(90, 90, 90, 55));
            gui.panels.at(gui.currentPanel)->setElementYSpacing(15);
            gui.addChartPlotter(temp, guiStatVarPointer(" ", &digitalPinValuesInput[i-2], GUI_VAR_INT, true, 2), 180, 8, 200, 0, 1);
            gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
            gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
            gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
        }
    }
    //////////////////////////////////////////////
    
    gui.loadSettings("settings/arduinoGuiSettings.xml");
    
    //////////////////////////////////////////////
	// GUI Events
	gui.setupEvents();
	gui.enableEvents();
    
    // enable all events for gui logger
	//ofAddListener(gui.guiEvent, this, &gaArduinoModule::eventsIn);
    
    // Serial GUI [Arduino] ANALOG PINS
    for(unsigned int i=0;i<6;i++){
        sprintf(temp,"ARDUINO_ANALOG_PIN_%i_MODE",i);
        ofAddListener(gui.createEventGroup(temp),this, &gaArduinoModule::changeAnalogPinMode);
    }
	
    // Serial GUI [Arduino] DIGITAL PINS
    for(unsigned int i=2;i<14;i++){
        sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_MODE",i);
        ofAddListener(gui.createEventGroup(temp),this, &gaArduinoModule::changeDigitalPinMode);
        sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_VALUE",i);
        ofAddListener(gui.createEventGroup(temp),this, &gaArduinoModule::sendDigitalValue);
        
    }
    
    initPins();
    
}

//--------------------------------------------------------------
void gaArduinoModule::updateGui() {
    char xml_name[256];
    
    sprintf(xml_name,"USE_ARDUINO");
    gapp->useArduino = gui.getValueI(xml_name);
    //////////////////////////////////////////////
    sprintf(xml_name,"SMOOTHING_FACTOR_ARDUINO");
    gapp->arduino_smoothingFactor = gui.getValueF(xml_name);
    
}

//--------------------------------------------------------------
void gaArduinoModule::drawGui() {
    char temp[128];
    ////////////////////////////////////
	// panel tabs colorize
	if(!gui.minimize){
		ofEnableAlphaBlending();
		ofFill();
        
        glColor4f(0.0,0.3,1.0,0.6);
        ofRect(gui.panelTabs[0].x+1, gui.panelTabs[0].y+1, gui.panelTabs[0].width-2, gui.panelTabs[0].height-2);
        
        ofDisableAlphaBlending();
        
    }
}

//--------------------------------------------------------------
void gaArduinoModule::changeAnalogPinMode(guiCallbackData & data){
	
	char temp[256];
	for(unsigned int i=0;i<6;i++){
		sprintf(temp,"ARDUINO_ANALOG_PIN_%i_MODE",i);
		if(data.isElement(temp)){
			if(atoi(data.getString(0).c_str()) == 0){
				gapp->analogPinModes[i] = ARD_ON;
			}else if(atoi(data.getString(0).c_str()) == 1){
				gapp->analogPinModes[i] = ARD_OFF;
			}
			gapp->arduino.sendAnalogPinReporting(i, gapp->analogPinModes[i]);
		}
	}
}

//--------------------------------------------------------------
void gaArduinoModule::changeDigitalPinMode(guiCallbackData & data){
	
	char temp[256];
	for(unsigned int i=2;i<14;i++){
		sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_MODE",i);
		if(data.isElement(temp)){
			if(i == 3 || i == 5 || i == 6 || i == 11){
				if(atoi(data.getString(0).c_str()) == 0){
					gapp->digitalPinModes[i-2] = ARD_INPUT;
				}else if(atoi(data.getString(0).c_str()) == 1){
					gapp->digitalPinModes[i-2] = ARD_OUTPUT;
				}else if(atoi(data.getString(0).c_str()) == 2){
					gapp->digitalPinModes[i-2] = ARD_PWM;
				}
			}else if(i == 9 || i == 10){
                if(atoi(data.getString(0).c_str()) == 0){
					gapp->digitalPinModes[i-2] = ARD_INPUT;
				}else if(atoi(data.getString(0).c_str()) == 1){
					gapp->digitalPinModes[i-2] = ARD_OUTPUT;
				}else if(atoi(data.getString(0).c_str()) == 2){
					gapp->digitalPinModes[i-2] = ARD_PWM;
				}else if(atoi(data.getString(0).c_str()) == 3){
					gapp->digitalPinModes[i-2] = ARD_SERVO;
				}
            }else{
				if(atoi(data.getString(0).c_str()) == 0){
					gapp->digitalPinModes[i-2] = ARD_INPUT;
				}else if(atoi(data.getString(0).c_str()) == 1){
					gapp->digitalPinModes[i-2] = ARD_OUTPUT;
				}
			}
			gapp->arduino.sendDigitalPinMode(i, gapp->digitalPinModes[i-2]);
		}
	}
}

//--------------------------------------------------------------
void gaArduinoModule::sendDigitalValue(guiCallbackData & data){
	char temp[256];
	for(unsigned int i=2;i<14;i++){
		sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_VALUE",i);
		if(data.isElement(temp)){
			if(gapp->digitalPinModes[i-2] == ARD_OUTPUT){
				if(i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11){
					if(data.getInt(0) == 0){
						gapp->digitalPinValuesOutput[i-2] = data.getInt(0);
					}else{
						gapp->digitalPinValuesOutput[i-2] = 1;
					}
					gapp->arduino.sendDigital(i, gapp->digitalPinValuesOutput[i-2]);
				}else{
					gapp->digitalPinValuesOutput[i-2] = data.getInt(0);
					gapp->arduino.sendDigital(i, gapp->digitalPinValuesOutput[i-2]);
				}
			}else if(gapp->digitalPinModes[i-2] == ARD_PWM){
				gapp->digitalPinValuesOutput[i-2] = data.getInt(0);
				gapp->arduino.sendPwm(i, gapp->digitalPinValuesOutput[i-2]);
			}else if(gapp->digitalPinModes[i-2] == ARD_SERVO){
				gapp->digitalPinValuesOutput[i-2] = data.getInt(0);
				gapp->arduino.sendServo(i, gapp->digitalPinValuesOutput[i-2]);
			}
		}
	}
    
}

//--------------------------------------------------------------
void gaArduinoModule::keyPressed(int key) { 
	
}

//--------------------------------------------------------------
void gaArduinoModule::keyReleased(int key) { 
	
}

//--------------------------------------------------------------
void gaArduinoModule::mouseMoved(int x, int y) { 
	
}

//--------------------------------------------------------------
void gaArduinoModule::mouseDragged(int x, int y, int button) {
	gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void gaArduinoModule::mousePressed(int x, int y, int button) { 
	gui.mousePressed(x, y, button);
    
    if(gui.saveDown){
        if(gapp->useArduino){
            gapp->saveArduinoPinsState = true;
        }
    }
}

//--------------------------------------------------------------
void gaArduinoModule::mouseReleased() { 
	
}

//--------------------------------------------------------------
void gaArduinoModule::mouseReleased(int x, int y, int button ){ 
	gui.mouseReleased();
}

//--------------------------------------------------------------
void gaArduinoModule::mouseScrolled(float x, float y) { 
	
}

