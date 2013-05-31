
#include "notesUtils.h"

string notation[NOTES]	= {"C0","C#0","D0","D#0","E0","F0","F#0","G0","G#0","A0","A#0","B0",
							"C1","C#1","D1","D#1","E1","F1","F#1","G1","G#1","A1","A#1","B1",
							"C2","C#2","D2","D#2","E2","F2","F#2","G2","G#2","A2","A#2","B2",
							"C3","C#3","D3","D#3","E3","F3","F#3","G3","G#3","A3","A#3","B3",
							"C4","C#4","D4","D#4","E4","F4","F#4","G4","G#4","A4","A#4","B4",
							"C5","C#5","D5","D#5","E5","F5","F#5","G5","G#5","A5","A#5","B5",
							"C6","C#6","D6","D#6","E6","F6","F#6","G6","G#6","A6","A#6","B6",
							"C7","C#7","D7","D#7","E7","F7","F#7","G7","G#7","A7","A#7","B7",
							"C8","C#8","D8","D#8","E8","F8","F#8","G8","G#8","A8","A#8","B8"};

// 9 total octaves  --->  assuming A4 (central octave) = LA = 440 Hz
float freq[NOTES]		= {16.35f, 17.32f, 18.35f, 19.45f, 20.60f, 21.83f, 23.12f, 24.50f, 25.96f, 27.50f, 29.14f, 30.87f,
							32.70f, 34.65f, 36.71f, 38.89f, 41.20f, 43.65f, 46.25f, 49.00f, 51.91f, 55.00f, 58.27f, 61.74f,
							65.41f, 69.30f, 73.42f, 77.78f, 82.41f, 87.31f, 92.50f, 98.00f, 103.83f, 110.00f, 116.54f, 123.47f,
							130.81f, 138.59f, 146.83f, 155.56f, 164.81f, 174.61f, 185.00f, 196.00f, 207.65f, 220.00f, 233.08f, 246.94f,
							261.63f, 277.18f, 293.66f, 311.13f, 329.63f, 349.23f, 369.99f, 392.00f, 415.30f, 440.00f, 466.16f, 493.88f,
							523.25f, 554.37f, 587.33f, 622.25f, 659.26f, 698.46f, 739.99f, 783.99f, 830.61f, 880.00f, 932.33f, 987.77f,
							1046.50f, 1108.73f, 1174.66f, 1244.51f, 1318.51f, 1396.91f, 1479.98f, 1567.98f, 1661.22f, 1760.00f, 1864.66f, 1975.53f,
							2093.00f, 2217.46f, 2349.32f, 2489.02f, 2637.02f, 2793.83f, 2959.96f, 3135.96f, 3322.44f, 3520.00f, 3729.31f, 3951.07f,
							4186.01f, 4434.93f, 4698.64f, 4978.04f, 5274.05f, 5587.66f, 5919.92f, 6271.94f, 6644.88f, 7040.01f, 7458.63f, 7902.15f};

// The "Just Scale" (sometimes referred to as "harmonic tuning" or "Helmholtz's scale")
// occurs naturally as a result of the overtone series for simple systems such as vibrating
// strings or air columns. All the notes in the scale are related by rational numbers.
// Unfortunately, with Just tuning, the tuning depends on the scale you are using -
// the tuning for C Major is not the same as for D Major, for example. Just tuning is
// often used by ensembles (such as for choral or orchestra works) as the players match
// pitch with each other "by ear."
// corrected frequency[i] = freq[i] - _harmcorrection[i]
float _harmCorrection[NOTES]	= {0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f,
								0.17f, -0.08f, 0.07f, 0.18f, -0.08f, 0.29f, -0.28f, 0.17f, 0.06f, 0.00f, 0.48f, -0.24f,
								0.33f, -0.17f, 0.14f, 0.37f, -0.16f, 0.58f, -0.55f, 0.35f, 0.12f, 0.00f, 0.96f, -0.49f,
								0.67f, -0.33f, 0.29f, 0.73f, -0.33f, 1.16f, -1.10f, 0.69f, 0.24f, 0.00f, 1.92f, -0.98f,
								1.34f, -0.66f, 0.58f, 1.46f, -0.65f, 2.33f, -2.20f, 1.39f, 0.48f, 0.00f, 3.84f, -1.96f,
								2.67f, -1.32f, 1.16f, 2.93f, -1.30f, 4.66f, -4.40f, 2.78f, 0.97f, 0.00f, 7.67f, -3.91f,
								5.35f, -2.64f, 2.32f, 5.86f, -2.61f, 9.32f, -8.80f, 5.55f, 1.94f, 0.00f, 15.35f, -7.82f,
								10.69f, -5.29f, 4.64f, 11.71f, -5.22f, 18.64f, -17.60f, 11.11f, 3.88f, 0.00f, 30.70f, -15.65f,
								21.38f, -10.57f, 9.28f, 23.42f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f};

//--------------------------------------------------
float noteToFrequency(string _note){

	int _index = 0;
	for(int i=0;i<NOTES;i++){
		if(notation[i] == _note){
			_index = i;
		}
	}
	return freq[_index];

}

//--------------------------------------------------
float noteToFrequency(int _index){

	return freq[_index];

}

//--------------------------------------------------
float noteToHarmonicFrequency(string _note){
	
	int _index = 0;
	for(int i=0;i<NOTES;i++){
		if(notation[i] == _note){
			_index = i;
		}
	}
	return freq[_index] - _harmCorrection[_index];

}

//--------------------------------------------------
float noteToHarmonicFrequency(int _index){
	
	return freq[_index] - _harmCorrection[_index];

}