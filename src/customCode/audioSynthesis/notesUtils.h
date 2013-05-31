#ifndef NOTES_UTILS
#define NOTES_UTILS

#include "ofMain.h"
// constants
#include "gamuzaConstants.h"

/*enum{

	DO_0,			// index 0
	DOB0,			// index 1
	RE_0,			// index 2
	REB_0,			// index 3
	MI_0,			// index 4
	FA_0,			// index 5
	FAB_0,			// index 6
	SOL_0,			// index 7
	SOLB_0,			// index 8
	LA_0,			// index 9
	LAB_0,			// index 10
	SI_0,			// index 11
	DO_1,			// index 12
	DOB1,			// index 13
	RE_1,			// index 14
	REB_1,			// index 15
	MI_1,			// index 16
	FA_1,			// index 17
	FAB_1,			// index 18
	SOL_1,			// index 19
	SOLB_1,			// index 20
	LA_1,			// index 21
	LAB_1,			// index 22
	SI_1,			// index 23
	DO_2,			// index 24
	DOB2,			// index 25
	RE_2,			// index 26
	REB_2,			// index 27
	MI_2,			// index 28
	FA_2,			// index 29
	FAB_2,			// index 30
	SOL_2,			// index 31
	SOLB_2,			// index 32
	LA_2,			// index 33
	LAB_2,			// index 34
	SI_2,			// index 35
	DO_3,			// index 36
	DOB3,			// index 37
	RE_3,			// index 38
	REB_3,			// index 39
	MI_3,			// index 40
	FA_3,			// index 41
	FAB_3,			// index 42
	SOL_3,			// index 43
	SOLB_3,			// index 44
	LA_3,			// index 45
	LAB_3,			// index 46
	SI_3,			// index 47
	DO_4,			// index 48
	DOB4,			// index 49
	RE_4,			// index 50
	REB_4,			// index 51
	MI_4,			// index 52
	FA_4,			// index 53
	FAB_4,			// index 54
	SOL_4,			// index 55
	SOLB_4,			// index 56
	LA_4,			// index 57  440 Hz
	LAB_4,			// index 58
	SI_4,			// index 59
	DO_5,			// index 60
	DOB5,			// index 61
	RE_5,			// index 62
	REB_5,			// index 63
	MI_5,			// index 64
	FA_5,			// index 65
	FAB_5,			// index 66
	SOL_5,			// index 67
	SOLB_5,			// index 68
	LA_5,			// index 69
	LAB_5,			// index 70
	SI_5,			// index 71
	DO_6,			// index 72
	DOB6,			// index 73
	RE_6,			// index 74
	REB_6,			// index 75
	MI_6,			// index 76
	FA_6,			// index 77
	FAB_6,			// index 78
	SOL_6,			// index 79
	SOLB_6,			// index 80
	LA_6,			// index 81
	LAB_6,			// index 82
	SI_6,			// index 83
	DO_7,			// index 84
	DOB7,			// index 85
	RE_7,			// index 86
	REB_7,			// index 87
	MI_7,			// index 88
	FA_7,			// index 89
	FAB_7,			// index 90
	SOL_7,			// index 91
	SOLB_7,			// index 92
	LA_7,			// index 93
	LAB_7,			// index 94
	SI_7,			// index 95
	DO_8,			// index 96
	DOB8,			// index 97
	RE_8,			// index 98
	REB_8,			// index 99
	MI_8,			// index 100
	FA_8,			// index 101
	FAB_8,			// index 102
	SOL_8,			// index 103
	SOLB_8,			// index 104
	LA_8,			// index 105
	LAB_8,			// index 106
	SI_8			// index 107

};*/

// english musical notation: C  C#  D  D#  E  F  F#  G   G#   A  A#  B
// latin musical notation:	 DO DO# RE RE# MI FA FA# SOL SOL# LA LA# SI
// indian musical notation:  SA SA# RE RE# GA MA MA# PA  PA#  DA DA# NI

//--------------------------------------------------
	float noteToFrequency(string _note);
	float noteToFrequency(int _index);
	float noteToHarmonicFrequency(string _note);
	float noteToHarmonicFrequency(int _index);

#endif

