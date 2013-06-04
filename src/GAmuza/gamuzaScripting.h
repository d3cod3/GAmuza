#ifndef _GAMUZASCRIPTING
#define _GAMUZASCRIPTING

#include "gamuzaConstants.h"
#include "gamuzaWrapper.h"


//--------------------------------------------------------------
void gamuzaMain::setupScripting(){
    
    ///////////////////////////////////////////////
	// load livecoding fonts
    for(int i=1;i<141;i++){
        ofTrueTypeFont	tempF;
        tempF.loadFont(GAMUZA_LIVECODING_FONT, i, true, true);
        liveCodingFont.push_back(tempF);
    }
	///////////////////////////////////////////////
    
    // adding lua language to live coding
    ofAddListener(doCompileEvent, this, &gamuzaMain::renderScript);
    
    printError		= false;
    
    for(int i=0;i<5;i++){
        errorVector.push_back(" ");
    }
    
    if(autoLoadScript){
        loadScript(autoScriptFile);
    }else{
        loadScript("scripts/emptyExample.ga");
    }
}

//--------------------------------------------------------------
void gamuzaMain::updateScripting(){
    ofPushView();
    ofPushMatrix();
    ofPushStyle();
        lua.scriptUpdate();
    ofPopStyle();
    ofPopMatrix();
    ofPopView();
}

//--------------------------------------------------------------
//-- LIVE CODING exec script from ofxGlEditor to ofxLua --------
//--------------------------------------------------------------
void gamuzaMain::loadScript(string _script){
	
    // reset incoming OSC messages
    resetIncomingOSC();
    // reset outgoing OSC messages
    resetOutgoingOSC();
    
	// reset the audio output stream
    if(computeAudioOutput  && audioOutputChannels > 0){
        resetAudioOutput();
    }
    
    // reset timeline
    gaTL->timeline.reset();
    gaTL->timeline.timelineResizeWithWindow(
                                            ofxNSWindower::instance()->getWindowPtr("Timeline")->getWidth(),
                                            ofxNSWindower::instance()->getWindowPtr("Timeline")->getHeight());
	
	// init the lua state
	lua.scriptExit();
	lua.init(true,true);
	// bind OF007, GAmuza & openGL2.1 api to lua
	lua.bind<ofGamuzaWrapper>();
	// exec the script from editor
	lua.doScript(_script);
    
    ofPushView();
    ofPushMatrix();
    //ofPushStyle();
        lua.scriptSetup();
    //ofPopStyle();
    ofPopMatrix();
    ofPopView();
    
    // reset frames counter & time
    gaFrameCounter      = 0;
    
    printError = true;
	
}

//--------------------------------------------------------------
void gamuzaMain::renderScript(string & _script){
	
    // reset incoming OSC messages
    resetIncomingOSC();
    // reset outgoing OSC messages
    resetOutgoingOSC();
    
	// reset the audio output stream
    if(computeAudioOutput && audioOutputChannels > 0){
        resetAudioOutput();
    }
    
    // reset timeline
    gaTL->timeline.reset();
    gaTL->timeline.timelineResizeWithWindow(
                                            ofxNSWindower::instance()->getWindowPtr("Timeline")->getWidth(),
                                            ofxNSWindower::instance()->getWindowPtr("Timeline")->getHeight());
	
	// init the lua state
	lua.scriptExit();
	lua.init(true,true);
	// bind OF007, GAmuza & openGL2.1 api to lua
	lua.bind<ofGamuzaWrapper>();
	// exec the script from editor
	lua.doString(_script);
    
	ofPushView();
    ofPushMatrix();
    //ofPushStyle();
        lua.scriptSetup();
    //ofPopStyle();
    ofPopMatrix();
    ofPopView();
    
    // reset frames counter & time
    gaFrameCounter      = 0;
    
    printError = true;
    
}

//--------------------------------------------------------------
string gamuzaMain::readScript(string _scriptFile,bool dialog){
	
	string		content;
	ifstream	scriptFile;
	char		_c;
	
	if(dialog){
		scriptFile.open(_scriptFile.c_str(), ifstream::in);
	}else{
		scriptFile.open(ofToDataPath(_scriptFile).c_str(), ifstream::in);
	}
	
	if(scriptFile.is_open()){
		while(scriptFile.good()){
			_c = (char)scriptFile.get();
			if(scriptFile.good()){
				content += _c;
			}
		}
		scriptFile.close();
	}
	
	return content;
	
}

//--------------------------------------------------------------
void gamuzaMain::checkErrors(){
    if(printError){
        // print scripting errors into logger
        if(lua.lastError != "Script has no errors"){
            ofStringReplace(lua.lastError,"[string \"...\"]:","at line: ");
            ofStringReplace(lua.lastError,"custom ","");
            ofStringReplace(lua.lastError,"\n",": ");
            errorVector = ofSplitString(lua.lastError, ": ");
            
            if(lua.errorLine > 0){
                //sprintf(temp_error," Error at line: %i", lua.errorLine+7);
                //sendPrivateMessage(GAMUZA_CONSOLE_ERROR, temp_error);
                for(int i=2;i<errorVector.size();i++){
                    sprintf(temp_error,"  %s", errorVector[i].c_str());
                    sendPrivateMessage(GAMUZA_CONSOLE_ERROR, temp_error);
                }
                sendPrivateMessage(GAMUZA_CONSOLE_ERROR, " ");
            }else{
                sendPrivateMessage(GAMUZA_CONSOLE_ERROR, " Error: ");
                for(int i=0;i<errorVector.size();i++){
                    sprintf(temp_error,"  %s", errorVector[i].c_str());
                    sendPrivateMessage(GAMUZA_CONSOLE_ERROR, temp_error);
                }
                sendPrivateMessage(GAMUZA_CONSOLE_ERROR, " ");
            }
        }else{
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ----------------");
            sprintf(temp_error," %s : %s", ofGetTimestampString().c_str(), lua.lastError.c_str());
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, temp_error);
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ----------------");
        }
        printError = false;
    }
}

//--------------------------------------------------------------
//--------------------------------------------------------------

#endif
