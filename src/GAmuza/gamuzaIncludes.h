#ifdef TARGET_WIN32
    
#endif

#ifdef TARGET_LINUX
	
#endif

#ifdef TARGET_OSX
	
#endif

//////////////////////////////////////
// main core of OpenFrameworks
#include "ofMain.h"

//////////////////////////////////////
// official addons
#include "ofx3DModelLoader.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "ofxKinect.h"
#include "ofxNetwork.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "ofxSvg.h"
#include "ofxThreadedImageLoader.h"
#include "ofxVectorGraphics.h"
#include "ofxXmlSettings.h"

//////////////////////////////////////
// experimental addons

// COCOA
#include "ofxNSWindowApp.h"

// LIVE CODING
#include "ofxLua.h"

// GUI
#include "ofxControlPanel.h"
#include "ofxMSAInteractiveObject.h"
#include "ofxUI.h"
#include "ofxShowGrid.h"

// GPU
#include "ofxPBO.h"
#include "ofxFastFboReader.h"

// Cyphers
#include "ofxCrypto.h"

// Computer Vision
#include "ofxCV.h"
#include "ofxFaceTracker.h"
#include "ofxOpticalFlowFarneback.h"
#include "ofxARToolkitPlus.h"
#include "ofxLibdc.h"

// Thermal Cameras Tracking
#include "ofxThermitrack.h"
#include "ofxThermitrackImage.h"

// AUDIO
#include "ofxPd.h"
#include "ofxAudioSample.h"			// reading&writing audio sample from hard drive with libsndfile
#include "ofxAUPlugin.h"

// MIDI
#include "ofxMidi.h"                // MIDI input/output

// DMX
#include "ofxDmx.h"                 // DMX input/output

// SYSTEM
#include "ofxMissing.h"				// Date/Time, INI Reader, Recursive file listing. Roxlu missing utils
#include "ofxStringEncoders.h"		// Html string encoders (UTF8, unquote)
#include "ofxSubtitles.h"           // load/save .srt subtitles files

// PHYSICS
#include "ofxBox2d.h"
#include "ofxVectorField.h"

// MATH
#include "ofxGaussian.h"            // A Gaussian random number generator

// Pixels manipulators
#include "ofxChromaKey.h"
#include "ofxDither.h"

// IMAGE
#include "ofxQRCodeGenerator.h"

// VIDEO
#include "ofxAbsoluteFrame.h"
#include "ofxPBOVideoPlayer.h"
#include "ofxQTKitAVScreenRecorder.h"

// MAPPING
#include "ofxMtlMapping2D.h"

// SHADERS
#include "ofxFX.h"
#include "ofxPostProcessing.h"

// TEXT
#include "ofxArcText.h"
#include "ofxTrueTypeFontUC.h"

// GRAPHICS
#include "ofxGenerative.h"
#include "ofxDelaunay.h"
#include "ofxSlitScan.h"            // simple utility for creating slit scan effects and video time delays

// 3D
#include "ofxDOF.h"
#include "ofxGrabCam.h"
#include "ofxOcean.h"
#include "ofxOceanCamera.h"
#include "ofxOceanRenderer.h"
#include "ofxOceanTile.h"

// NET
#include "ofxTwitter.h"

// STREAMING
#include "ofxSyphon.h"
#include "ofxIpVideoGrabber.h"

// EXTRAS
#include "ofxExtras.h"
#include "ofxRegex.h"

// UTILS
#include "ofxBiquadFilter.h"

//////////////////////////////////////
// CUSTOM CODE

// Computer Vision
#include "gaKinectTracking.h"
#include "gaSourceTracking.h"
#include "matrixAreas.h"		

// Audio Input
#include "audioInputChannel.h"

// Audio Synthesis
#include "gaDsp.h"
#include "gaAmplifier.h"
#include "gaOscillator.h"
#include "audioSample.h"
#include "audioModule.h"

// Random Utils
#include "randomUtils.h"

// Video
#include "videoDelayEffect.h"

