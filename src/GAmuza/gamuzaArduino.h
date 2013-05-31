#ifndef _GAMUZAARDUINO
#define _GAMUZAARDUINO

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupArduino(){
	
	// connect arduino board via serial port
	arduino.connect(serialDevice, baudRate);
	
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
	
	if(arduino.isArduinoReady()){
		// first pins setup
		if(!bSetupArduino){
			// init pins
			for(unsigned int i=2;i<14;i++){
				arduino.sendDigitalPinMode(i, digitalPinModes[i-2]);
				if(digitalPinModes[i-2] == ARD_PWM){
					arduino.sendPwm(i, digitalPinValuesOutput[i-2]);
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
	
    sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
    sendPrivateMessage(GAMUZA_CONSOLE_LOG, "ARDUINO Pins Mode SAVED");
    sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
	
}

//--------------------------------------------------------------
void gamuzaMain::changeAnalogPinMode(int mode){
	for(unsigned int i=0;i<6;i++){
        if(mode == 0){
            analogPinModes[i] = ARD_ON;
        }else if(mode == 1){
            analogPinModes[i] = ARD_OFF;
        }
        arduino.sendAnalogPinReporting(i, analogPinModes[i]);
	}
}

//--------------------------------------------------------------
void gamuzaMain::changeDigitalPinMode(int mode){
	for(unsigned int i=2;i<14;i++){
        if(i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11){
            if(mode == 0){
                digitalPinModes[i-2] = ARD_INPUT;
            }else if(mode == 1){
                digitalPinModes[i-2] = ARD_OUTPUT;
            }else if(mode == 2){
                digitalPinModes[i-2] = ARD_PWM;
            }
        }else{
            if(mode == 0){
                digitalPinModes[i-2] = ARD_INPUT;
            }else if(mode == 1){
                digitalPinModes[i-2] = ARD_OUTPUT;
            }
        }
        arduino.sendDigitalPinMode(i, digitalPinModes[i-2]);
	}
}

//--------------------------------------------------------------
void gamuzaMain::sendDigitalValue(int value){
	for(unsigned int i=2;i<14;i++){
        if(digitalPinModes[i-2] == ARD_OUTPUT){
            if(i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11){
                if(value == 0){
                    digitalPinValuesOutput[i-2] = value;
                }else{
                    digitalPinValuesOutput[i-2] = 1;
                }
                arduino.sendDigital(i, digitalPinValuesOutput[i-2]);
            }else{
                digitalPinValuesOutput[i-2] = value;
                arduino.sendDigital(i, digitalPinValuesOutput[i-2]);
            }
        }else if(digitalPinModes[i-2] == ARD_PWM){
            digitalPinValuesOutput[i-2] = value;
            arduino.sendPwm(i, digitalPinValuesOutput[i-2]);
        }
	}
}


#endif
