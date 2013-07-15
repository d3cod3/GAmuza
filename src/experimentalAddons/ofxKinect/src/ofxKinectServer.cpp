/**
	Implements a thread that sends frames over TCP. A frame can be an image or a
	frame from a video which results in streaming simulation.
	@author: Jan Christian Hjorth Hansen - rocknrolldk@gmail.com
 */

#include "ofxKinectServer.h"

#include <cstdio>
using std::cout;
using std::endl;

ofxKinectServer::ofxKinectServer() : activity(this, &ofxKinectServer::runActivity) {
	ofxKinectServer(DEFAULT_PORT, SENDER_FRAME_WIDTH, SENDER_FRAME_HEIGHT);
}

ofxKinectServer::ofxKinectServer(int _port, int _width, int _height) : activity(this, &ofxKinectServer::runActivity) {
	this->port = _port;
	this->width = _width;
	this->height = _height;
    
    oscReceiver.setup( DEFAULT_OSC_PORT );
    
#ifdef FAKEKINECT
    grabber.initGrabber(_width,_height,true);
    
#else
    kinect.setRegistration(false);
	kinect.enableDepthNearValueWhite(true);
    
	// ir:false, rgb:false, texture:true
	kinect.init(false, false, true);
	kinect.open();
#endif
    
    pixels.allocate(width, height, 3);
    
    string shaderProgram = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    \
    float channels = 3.0;\
    float clampFactor = 1.0/channels;\
    float doubleClampFactor = clampFactor*2.0;\
    \
    float depth = texture2DRect(tex, pos).r;\
    vec3 color = vec3(0.0);\
    \
    if ( depth < clampFactor ){\
    color.r = depth * channels;\
    } else if ( depth < doubleClampFactor){\
    color.r = 1.0;\
    color.g = (depth - clampFactor)*3.0;\
    } else {\
    color.r = 1.0;\
    color.g = 1.0;\
    color.b = (depth - doubleClampFactor)*3.0;\
    }\
    \
    gl_FragColor = vec4( color , 1.0);\
    }";
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram(); 
    
    fbo.allocate(_width, _height, GL_RGB);
    fbo.begin();
    ofClear(0);
    fbo.end();
	
	server.setup(_port, true);  //this causes OS X to ask for permission to receive from network
	server.setVerbose(true);    //NOTE: Remove when done testing
}

ofxKinectServer::~ofxKinectServer() {
    
}

/*
	Writes a new frame into the buffer frame that gets sent via TCP.
 */

/*
void ofxKinectServer::setPixelsSrc(ofPixels &pixels) throw (length_error) {
	if (pixels.getWidth() > frameWidth || pixels.getHeight() > frameHeight) {
		throw length_error("ofxKinectServer::updateFrame: Frame size is bigger than the size of the buffer.");
	}
	
	if (rwlock.tryWriteLock()) {
        buffer = &pixels; 
		rwlock.unlock();
	}
}*/

void ofxKinectServer::update(){
#ifdef FAKEKINECT
    grabber.update();
    if(grabber.isFrameNew()){
        fbo.begin();
        ofClear(0);
        ofSetColor(255);
        
        shader.begin();
        shader.setUniformTexture("tex", grabber.getTextureReference(), 0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(width, 0); glVertex3f(width, 0, 0);
        glTexCoord2f(width, height); glVertex3f(width, height, 0);
        glTexCoord2f(0,height);  glVertex3f(0,height, 0);
        glEnd();
        shader.end();
        
        fbo.end();
        
        fbo.getTextureReference().readToPixels( pixels );
    }
#else
    kinect.update();
    if(kinect.isFrameNew()){
        fbo.begin();
        ofClear(0);
        ofSetColor(255);
        
        shader.begin();
        
        kinect.getDepthTextureReference().bind();
//        shader.setUniformTexture("tex", kinect.getDepthTextureReference(), 0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(width*2.0, 0); glVertex3f(width, 0, 0);
        glTexCoord2f(width*2.0, height*2.0); glVertex3f(width, height, 0);
        glTexCoord2f(0,height*2.0);  glVertex3f(0,height, 0);
        glEnd();
        kinect.getDepthTextureReference().unbind();
        
        shader.end();
        
        fbo.end();
        
        fbo.getTextureReference().readToPixels( pixels );
    }
    
    while(oscReceiver.hasWaitingMessages()){
        
        //  Get the next message
        //
        ofxOscMessage m;
        oscReceiver.getNextMessage(&m);
        
        //  Check & do from OSC messages
        //
        if(m.getAddress() == "/remoteKinect/min"){
            minDist = m.getArgAsFloat(0);
            kinect.setDepthClipping(minDist, maxDist);
        } else if(m.getAddress() == "/remoteKinect/max"){
            maxDist = m.getArgAsFloat(0);
            kinect.setDepthClipping(minDist, maxDist);
        } 
    }
#endif
}

void ofxKinectServer::runActivity() {    
	while (!activity.isStopped()) {
		//only the first connected client will be considered: id=0
		//if (server.isClientConnected(0)) {
		if(server.isConnected()){
			for(int i = 0; i < server.getLastID(); i++){
				if( !server.isClientConnected(i) )continue;
		
				if (rwlock.tryReadLock()) {
					//Send frame by throttling, ie splitting frame up into chunks (rows) and sending them sequentially
					
					const char* index = (const char*)pixels.getPixels(); //start at beginning of pixel array
					int length = pixels.getWidth() * 3;//length of one row of pixels in the image
					int size = pixels.getHeight() * pixels.getWidth() * 3;
					
					int pixelCount = 0;
					
					while (pixelCount < size ) {
						server.sendRawBytes(i, index, length); //send the first row of the image
						//server.sendRawBytes(0, index, length); //send the first row of the image
						index += length; //increase pointer so that it points to the next image row
						pixelCount += length; //increase pixel count by one row
					}
					
					rwlock.unlock();
				}
				
				
			}
		} else {
			//cout << "NOT" << endl;
		}
		
		ofSleepMillis(SENDER_ACTIVITY_SLEEP);
	}
}

void ofxKinectServer::draw(int _x, int _y){
    fbo.draw(_x,_y);
}

void ofxKinectServer::close(){
#ifdef FAKEKINECT
	grabber.close();
#else
    kinect.close();
#endif
	activity.stop();
}


