#ifndef _GAMUZAPD
#define _GAMUZAPD

#include "gamuzaConstants.h"


//--------------------------------------------------------------
void gamuzaMain::setupPD() {
    // some PD setup if needed
}

//--------------------------------------------------------------
void gamuzaMain::receiveBang(const std::string& dest) {
	cout << "OF: bang " << dest << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receiveFloat(const std::string& dest, float value) {
	cout << "OF: float " << dest << ": " << value << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receiveSymbol(const std::string& dest, const std::string& symbol) {
	cout << "OF: symbol " << dest << ": " << symbol << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receiveList(const std::string& dest, const pd::List& list) {
	cout << "OF: list " << dest << ": ";
    
	// step through the list
	for(int i = 0; i < list.len(); ++i) {
		if(list.isFloat(i))
			cout << list.getFloat(i) << " ";
		else if(list.isSymbol(i))
			cout << list.getSymbol(i) << " ";
	}
    
	// you can also use the built in toString function or simply stream it out
	// cout << list.toString();
	// cout << list;
    
	// print an OSC-style type string
	cout << list.types() << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receiveMessage(const std::string& dest, const std::string& msg, const pd::List& list) {
	cout << "OF: message " << dest << ": " << msg << " " << list.toString() << list.types() << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receiveNoteOn(const int channel, const int pitch, const int velocity) {
	cout << "OF MIDI: note on: " << channel << " " << pitch << " " << velocity << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receiveControlChange(const int channel, const int controller, const int value) {
	cout << "OF MIDI: control change: " << channel << " " << controller << " " << value << endl;
}

//--------------------------------------------------------------
// note: pgm nums are 1-128 to match pd
void gamuzaMain::receiveProgramChange(const int channel, const int value) {
	cout << "OF MIDI: program change: " << channel << " " << value << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receivePitchBend(const int channel, const int value) {
	cout << "OF MIDI: pitch bend: " << channel << " " << value << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receiveAftertouch(const int channel, const int value) {
	cout << "OF MIDI: aftertouch: " << channel << " " << value << endl;
}

//--------------------------------------------------------------
void gamuzaMain::receivePolyAftertouch(const int channel, const int pitch, const int value) {
	cout << "OF MIDI: poly aftertouch: " << channel << " " << pitch << " " << value << endl;
}

//--------------------------------------------------------------
// note: pd adds +2 to the port num, so sending to port 3 in pd to [midiout],
//       shows up at port 1 in ofxPd
void gamuzaMain::receiveMidiByte(const int port, const int byte) {
	cout << "OF MIDI: midi byte: " << port << " " << byte << endl;
}


#endif
