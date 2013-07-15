/**
	Defines a thread that sends frames over TCP. A frame can be an image or a
	frame from a video which results in streaming simulation.
	@author: Jan Christian Hjorth Hansen - rocknrolldk@gmail.com
 */


#ifndef OFXKINECTSERVER
#define OFXKINECTSERVER

//#define FAKEKINECT

#include <stdexcept>
using std::length_error;

#include "ofMain.h"
#include "ofxOsc.h"

#ifndef FAKEKINECT
#include "ofxKinect.h"
#endif

//  Streaming stuff
#include "Poco/Activity.h"
#include "Poco/RWLock.h"
#include "ofxNetwork.h"

#define DEFAULT_PORT 11999
#define DEFAULT_OSC_PORT 3435
/**
	This setting defines the length of the wait in each thread loop.
	Optimize for performance.
 */
#define SENDER_ACTIVITY_SLEEP 100
#define SENDER_FRAME_WIDTH 640
#define SENDER_FRAME_HEIGHT 480

class ofxKinectServer {
public:
	ofxKinectServer();
	ofxKinectServer(int port, int frameWidth, int frameHeight);
	~ofxKinectServer();
    
    void    setDepthClipping(float nearClip=500, float farClip=4000){
#ifndef FAKEKINECT
        kinect.setDepthClipping(nearClip, farClip);
#endif
    };
    
    int     getNumClients(){ return server.getNumClients();};
    
	void    start(){activity.start();};
	void    stop(){activity.stop();};
    void    close();
    
    void    update();
    
    void    draw(int _x = 0, int _y = 0);
    
private:	
    void    runActivity();     //the main thread function
    
    Poco::Activity<ofxKinectServer> activity;
	Poco::RWLock                    rwlock;
    
#ifdef FAKEKINECT
    ofVideoGrabber  grabber;
#else
    ofxKinect       kinect;
    int             minDist, maxDist;
#endif
    
    ofxTCPServer    server;
    ofxOscReceiver  oscReceiver;
    
    ofPixels        pixels;
    ofShader        shader;
    ofFbo           fbo;
    
    int             port, width, height;
};

#endif