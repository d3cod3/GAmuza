#define GAMUZA_RELEASE                  "0426"

// MAIN.CPP WINDOW VARS
#define MAIN_WINDOW_W					854
#define MAIN_WINDOW_H					480

// SETTINGS
#define	GAMUZA_LIVECODING_FONT          "fonts/Anonymous_Pro_B.ttf"
#define	GAMUZA_SETTINGS					"settings/gamuzaSettings.xml"
#define	GAMUZAGUI_SETTINGS				"settings/guiSettings.xml"
#define	GAMUZA_SPLASH					"img/gamuza04_splash.png"
#define GAMUZA_VIDEOTEST				"videos/video.mov"
#define GAMUZA_MAPPING_FILE				"settings/projection/mapping.xml"
#define GAMUZA_SHADER					"shaders/gamuzaShader"
#define GAMUZA_ARDUINO_PINS				"settings/arduino/arduinoPins.xml"

// EXTERNAL TEXT EDITOR COMUNICATION
#define GAMUZA_CONSOLE_LOG              0
#define GAMUZA_CONSOLE_ERROR            1

// OSC
#define GA_OSC_MAX_SENDING_VARIABLES    1000

// OPENNI SensorKinect
#define USE_IR
#define NUM_KINECT_USERS				2

// MOTION TRIGGER AREAS
#define	TRIGGER_AREAS_NUM				9

// COUNTOUR FINDER
#define	MAX_NUM_CONTOURS_TO_FIND		20
#define MAX_CONTOUR_LENGTH				1024

// ADVANCED BLOB TRACKING
#define AJ_THRESH						0
#define AJ_BLOBMIN						1
#define AJ_BLOBMAX						2
#define AJ_UOFFSETX						3
#define AJ_UOFFSETY						4

#define MAX_USERS_HARDLIMIT				MAX_NUM_CONTOURS_TO_FIND

#define USER_JOINED						0
#define USER_MOVED						1
#define USER_LEFT						2
#define USER_MOOD						3
#define USER_PTBLOB_TEST				4
#define SCENE_MOOD_USER					99

#define B_DEAD							0
#define B_ALIVE_IN_AREA					1
#define B_ALIVE_OUT_AREA				2

#define IMGTOP							0
#define IMGLEFT							0
#define MAX_LINE_SIZE					30

// OPTICAL FLOW
#define		CAM_VELOCITY_BLUR			15 // how much to blur the cam velocity

// HAAR FINDER
#define		GAMUZA_HAAR_DEFAULT			"settings/haarXML/haarcascade_frontalface_alt.xml"

// AUDIO INPUT
#define		BARK_SCALE_CRITICAL_BANDS	24

// AUDIO SYNTH
#define		DENORMAL_BUFFER				1e-15f

#define		OSC_SINE_WAVE				0
#define		OSC_COSINE_WAVE				1
#define		OSC_SAWTOOTH_WAVE			2
#define		OSC_TRIANGLE_WAVE			3
#define		OSC_RECT_WAVE				4
#define		OSC_WHITE_NOISE				5
#define		OSC_PINK_NOISE				6
#define		OSC_BROWN_NOISE				7
#define		OSC_PHASOR					8
#define		OSC_PULSE					9

#define		AMP_TYPE_MONO				0
#define		AMP_TYPE_MULTI				1

#define		NOTES						108

#define		DO_0 0
#define		DOB0 1
#define		RE_0 2
#define		REB_0 3
#define		MI_0 4
#define		FA_0 5
#define		FAB_0 6
#define		SOL_0 7
#define		SOLB_0 8
#define		LA_0 9
#define		LAB_0 10
#define		SI_0 11
#define		DO_1 12
#define		DOB1 13
#define		RE_1 14
#define		REB_1 15
#define		MI_1 16
#define		FA_1 17
#define		FAB_1 18
#define		SOL_1 19
#define		SOLB_1 20
#define		LA_1 21
#define		LAB_1 22
#define		SI_1 23
#define		DO_2 24
#define		DOB2 25
#define		RE_2 26
#define		REB_2 27
#define		MI_2 28
#define		FA_2 29
#define		FAB_2 30
#define		SOL_2 31
#define		SOLB_2 32
#define		LA_2 33
#define		LAB_2 34
#define		SI_2 35
#define		DO_3 36
#define		DOB3 37
#define		RE_3 38
#define		REB_3 39
#define		MI_3 40
#define		FA_3 41
#define		FAB_3 42
#define		SOL_3 43
#define		SOLB_3 44
#define		LA_3 45
#define		LAB_3 46
#define		SI_3 47
#define		DO_4 48
#define		DOB4 49
#define		RE_4 50
#define		REB_4 51
#define		MI_4 52
#define		FA_4 53
#define		FAB_4 54
#define		SOL_4 55
#define		SOLB_4 56
#define		LA_4 57
#define		LAB_4 58
#define		SI_4 59
#define		DO_5 60
#define		DOB5 61
#define		RE_5 62
#define		REB_5 63
#define		MI_5 64
#define		FA_5 65
#define		FAB_5 66
#define		SOL_5 67
#define		SOLB_5 68
#define		LA_5 69
#define		LAB_5 70
#define		SI_5 71
#define		DO_6 72
#define		DOB6 73
#define		RE_6 74
#define		REB_6 75
#define		MI_6 76
#define		FA_6 77
#define		FAB_6 78
#define		SOL_6 79
#define		SOLB_6 80
#define		LA_6 81
#define		LAB_6 82
#define		SI_6 83
#define		DO_7 84
#define		DOB7 85
#define		RE_7 86
#define		REB_7 87
#define		MI_7 88
#define		FA_7 89
#define		FAB_7 90
#define		SOL_7 91
#define		SOLB_7 92
#define		LA_7 93
#define		LAB_7 94
#define		SI_7 95
#define		DO_8 96
#define		DOB8 97
#define		RE_8 98
#define		REB_8 99
#define		MI_8 100
#define		FA_8 101
#define		FAB_8 102
#define		SOL_8 103
#define		SOLB_8 104
#define		LA_8 105
#define		LAB_8 106
#define		SI_8 107


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////// MATH

#define		EULER						2.718281828459


/////////////////////////////////////////////////////////////////////////////////////////////////////
