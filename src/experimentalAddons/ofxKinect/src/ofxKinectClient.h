/**
	Defines a thread that receives a frame over TCP.
	@author: Jan Christian Hjorth Hansen - rocknrolldk@gmail.com
 */

#ifndef OFXKINECTCLIENT
#define OFXKINECTCLIENT

#include <string>
using std::string;

#include "ofMain.h"
#include "ofxNetwork.h"

//  Kinect stuff
#include "ofxBase3DVideo.h"

//  Streamming stuff
#include "Poco/Activity.h"
#include "Poco/RWLock.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 11999
/**
	This setting defines the length of the wait in each thread loop.
	Optimize for performance.
 */
#define RECEIVER_ACTIVITY_SLEEP 50
#define RECEIVER_FRAME_WIDTH 640
#define RECEIVER_FRAME_HEIGHT 480

class ofxKinectClient {
public:
	ofxKinectClient();
	ofxKinectClient(string ip, int port, int frameWidth, int frameHeight);
	~ofxKinectClient();
	
    void    setDepthClipping(float nearClip=500, float farClip=4000);
    bool    setCameraTiltAngle(float angleInDegrees);
    
	float   getNearClipping();
	float   getFarClipping();
	float   getCurrentCameraTiltAngle();
	float   getTargetCameraTiltAngle();
	float   getDistanceAt(int x, int y);
	float   getDistanceAt(const ofPoint & p);
	ofVec3f getWorldCoordinateAt(int cx, int cy);
	ofVec3f getWorldCoordinateAt(float cx, float cy, float wz);
	bool	isFrameNew();
    
    bool    isConnected(){return client.isConnected();};
    
	void    start(){activity.start();};
	void    stop(){activity.stop();};
	
    void    update();
	void    draw(int _x = 0, int _y = 0);
    
	bool	connected;
	bool	newFrame;
	
private:
    void runActivity(); //the main thread function
	
    Poco::Activity<ofxKinectClient> activity;
	Poco::RWLock rwlock;
	
	ofxTCPClient    client;
    ofTexture       texture;
    ofFbo           fbo;
    ofShader        shader;
    ofFloatPixels   floatPixels;
    
    string ip;
    
    int             width, height, port, size;
    char            *pixels;
};

#endif
