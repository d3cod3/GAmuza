#ifndef _GAMUZAARDUINO
#define _GAMUZAARDUINO

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupArduino(){
	
	// connect arduino board via serial port
	arduino.connect(serialDevice, baudRate);
    // wait for firmware respose and verify we have an arduino connected
    isArduinoConnected = arduino.isArduinoReady();
    if(isArduinoConnected){
        sendGALog(" ARDUINO connection established");
        sendGALog(" ");
    }else{
        sendGALog(" ARDUINO NOT CONNECTED");
        sendGALog(" ");
    }
	
	// pins status/values arrays setup
	digitalPinModes					= new int[12];
	digitalPinValuesInput			= new int[12];
	digitalPinValuesOutput			= new int[12];
	analogPinModes					= new int[6];
	analogPinValues					= new int[6];
	
	loadArduinoSetting();
	
	bSetupArduino                   = false;
	saveArduinoPinsState            = false;
	
	// osc data vars setup
	_s_analogPinValues				= new float[6];
	_osc_analogPinValues			= new float[6];
	_osc_digitalPinValuesInput		= new int[12];
	
	sendOsc_AAP                     = false;
	sendOsc_ADP                     = false;
	
}

//--------------------------------------------------------------
void gamuzaMain::updateArduino(){
	
	if(isArduinoConnected){
		// first pins setup
		if(!bSetupArduino){
			// init pins
			for(unsigned int i=2;i<14;i++){
				arduino.sendDigitalPinMode(i, digitalPinModes[i-2]);
				if(digitalPinModes[i-2] == ARD_PWM){
					arduino.sendPwm(i, digitalPinValuesOutput[i-2]);
				}else if(digitalPinModes[i-2] == ARD_SERVO){
					arduino.sendServo(i, digitalPinValuesOutput[i-2]);
				}else if(digitalPinModes[i-2] == ARD_OUTPUT){
					arduino.sendDigital(i, digitalPinValuesOutput[i-2]);
				}
			}
			for(unsigned int i=0;i<6;i++){
				arduino.sendAnalogPinReporting(i, analogPinModes[i]);
			}
			bSetupArduino = true;
		}
		
		if(useArduino){
			arduino.update();
			
			// manage digital pins readings
			for(unsigned int i=2;i<14;i++){
				if(digitalPinModes[i-2] == ARD_INPUT){
					digitalPinValuesInput[i-2] = arduino.getDigital(i);
				}else if(digitalPinModes[i-2] == ARD_PWM){
					digitalPinValuesInput[i-2] = arduino.getPwm(i);
				}else if(digitalPinModes[i-2] == ARD_SERVO){
					digitalPinValuesInput[i-2] = arduino.getServo(i);
				}else if(digitalPinModes[i-2] == ARD_OUTPUT){
					digitalPinValuesInput[i-2] = digitalPinValuesOutput[i-2];
				}
			}
			
			// manage analog pins readings
			for(unsigned int i=0;i<6;i++){
				if(analogPinModes[i] == ARD_ON){
					analogPinValues[i] = arduino.getAnalog(i);
				}else{
					analogPinValues[i] = 0;
				}
			}
			
			if(saveArduinoPinsState){
				saveArduinoSetting();
				saveArduinoPinsState = false;
			}
			
			// prepare data for osc sending(eventually)
			prepareArduinoOscData();
		}
		
	}
	
}

//--------------------------------------------------------------
void gamuzaMain::prepareArduinoOscData(){
	
	for(unsigned int i=0;i<6;i++){
		_s_analogPinValues[i]	= _s_analogPinValues[i]*arduino_smoothingFactor + (1.0-arduino_smoothingFactor)*(float)analogPinValues[i];
		_osc_analogPinValues[i] = ofNormalize(_s_analogPinValues[i],0.0,1023.0);
	}
	
	for(unsigned int i=0;i<12;i++){
		_osc_digitalPinValuesInput[i] = digitalPinValuesInput[i];
	}
	
}

//--------------------------------------------------------------
void gamuzaMain::loadArduinoSetting(){
	
	char temp[128];
	
	pinsSettings.loadFile(GAMUZA_ARDUINO_PINS);
	
	for(unsigned int i=0;i<6;i++){
		sprintf(temp,"analog_%i",i);
		analogPinModes[i] = pinsSettings.getValue(temp, 0, 0);
	}
	
	for(unsigned int i=2;i<14;i++){
		sprintf(temp,"digital_%i",i);
		digitalPinModes[i-2] = pinsSettings.getValue(temp, 0, 0);
		sprintf(temp,"digital_%i_value",i);
		digitalPinValuesOutput[i-2] = pinsSettings.getValue(temp, 0, 0);
	}
	
}

//--------------------------------------------------------------
void gamuzaMain::saveArduinoSetting(){
	
	char temp[128];
	
	for(unsigned int i=0;i<6;i++){
		sprintf(temp,"analog_%i",i);
		pinsSettings.setValue(temp,analogPinModes[i]);
	}
	
	for(unsigned int i=2;i<14;i++){
		sprintf(temp,"digital_%i",i);
		pinsSettings.setValue(temp,digitalPinModes[i-2]);
		sprintf(temp,"digital_%i_value",i);
		pinsSettings.setValue(temp,digitalPinValuesInput[i-2]);
	}
	
	pinsSettings.saveFile(GAMUZA_ARDUINO_PINS);
	
    sendGALog("ARDUINO Pins Mode SAVED");
	
}


#endif
