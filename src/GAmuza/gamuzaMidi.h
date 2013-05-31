#ifndef _GAMUZAMIDI
#define _GAMUZAMIDI

#include "gamuzaConstants.h"

//////////////////////////////////////////////
// MIDI vars

//////////////////////////////////////////////

//--------------------------------------------------------------
void gamuzaMain::setupMidi(){
	midiIn.listPorts();
	midiIn.openPort(midiPortNumber);
    midiIn.ignoreTypes(false, false, false);
	midiIn.addListener(this);
}

//--------------------------------------------------------------
void gamuzaMain::newMidiMessage(ofxMidiMessage& eventArgs){
    
    midiMessage = eventArgs;
    
    midi_status          = midiMessage.status;
    midi_channel         = midiMessage.channel;
    midi_pitch           = midiMessage.pitch;
    midi_velocity        = midiMessage.velocity;
    midi_control         = midiMessage.control;
    midi_value           = midiMessage.value;
    midi_deltatime       = midiMessage.deltatime;
    
    bool exist = false;
    
    for(int i=0; i<midiMapping.size();i++){
        if(midiMapping[i].x == midi_channel && midiMapping[i].y == midi_control){
            exist = true;
            break;
        }
    }
    
    if(exist){
        for(int i=0; i<midiMapping.size();i++){
            if(midiMapping[i].x == midi_channel && midiMapping[i].y == midi_control){
                midiMapping[i].z = midi_value;
                break;
            }
        }
    }else{
        ofVec3f _temp;
        _temp.set(midi_channel,midi_control,midi_value);
        midiMapping.push_back(_temp);
    }
    
}

#endif
