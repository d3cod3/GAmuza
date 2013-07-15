/**
	Defines a thread that receives a frame over TCP.
	@author: Jan Christian Hjorth Hansen - rocknrolldk@gmail.com
 */

#include "ofxKinectClient.h"

#include <cstdio>
using std::cout;
using std::endl;

ofxKinectClient::ofxKinectClient() : activity(this, &ofxKinectClient::runActivity) {
	ofxKinectClient(DEFAULT_IP, DEFAULT_PORT, RECEIVER_FRAME_WIDTH, RECEIVER_FRAME_HEIGHT);
}

ofxKinectClient::ofxKinectClient(string _ip, int _port, int _width, int _height) : activity(this, &ofxKinectClient::runActivity) {
	this->ip = _ip;
	this->port = _port;
	this->width = _width;
	this->height = _height;
	this->size = _width * _height * 3;
	
	pixels = new char[size];
    string shaderProgram = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    \
    vec3 src = texture2DRect(tex, pos).rgb;\
    \
    float clampFactor = 1.0/3.0;\
    \
    float depth = 0.0;\
    \
    depth = src.r*clampFactor + src.g*clampFactor + src.b*clampFactor;\
    \
    gl_FragColor = vec4( depth, depth, depth , 1.0);\
    }";
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram(); 
    
    texture.allocate(width, height, GL_RGB);
    fbo.allocate(width, height, GL_RGB);
    fbo.begin();
    ofClear(0);
    fbo.end();
	
	cout << "try to initialize receiver" << endl;
	
	connected = client.setup(ip, port, true);
	client.setVerbose(true); // remove when done testing
    
	cout << "Receiver initialized" << endl;
	
	newFrame = false;
	
}

ofxKinectClient::~ofxKinectClient() {
	delete [] pixels;
}

void ofxKinectClient::update() {
    if (isConnected() && isFrameNew()){
        
        if (rwlock.tryReadLock()) {
            texture.loadData((unsigned char*)pixels, width, height, GL_RGB);
            rwlock.unlock();
        }
        
        fbo.begin();
        ofClear(0);
        ofSetColor(255);
        
        shader.begin();
        shader.setUniformTexture("tex", texture, 0);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(width, 0); glVertex3f(width, 0, 0);
        glTexCoord2f(width, height); glVertex3f(width, height, 0);
        glTexCoord2f(0,height);  glVertex3f(0,height, 0);
        glEnd();
        shader.end();
        
        fbo.end();
        
        fbo.getTextureReference().readToPixels(floatPixels);
	}
}

//------------------------------------
float ofxKinectClient::getDistanceAt(int x, int y) {
	//  TODO: take near and far points to map the ofFloatPixels 
    //  and send it back to the freenect_camera_to_world
    
    return pixels[y * width + x];
    
    //return -1.0 ;
}

//------------------------------------
float ofxKinectClient::getDistanceAt(const ofPoint & p) {
	return getDistanceAt(p.x, p.y);
}

//------------------------------------
ofVec3f ofxKinectClient::getWorldCoordinateAt(int x, int y) {
	return getWorldCoordinateAt(x, y, getDistanceAt(x, y));
}

//------------------------------------
ofVec3f ofxKinectClient::getWorldCoordinateAt(float cx, float cy, float wz) {
    /*
    double ref_pix_size = dev->registration.zero_plane_info.reference_pixel_size;
	double ref_distance = dev->registration.zero_plane_info.reference_distance;
	double factor = 2 * ref_pix_size * wz / ref_distance;
	*wx = (double)(cx - DEPTH_X_RES/2) * factor;
	*wy = (double)(cy - DEPTH_Y_RES/2) * factor;
     */

    float XtoZ = 1.11146; // tan( 1.0144686 / 2.0 ) * 2.0;
    float YtoZ = 0.83359; // tan( 0.7898090 / 2.0 ) * 2.0;
    
    float nearClipping = 500;
    float farClipping = 4000;
    
    float z = (1.0 - wz);// * (farClipping - nearClipping) + nearClipping;
    ofVec3f rta;
    rta.x = -( cx / width - 0.5 ) * z * XtoZ;
    rta.y = ( cy / height - 0.5 ) * z * YtoZ;
    rta.z = z;// + zOffset;
    
	return rta;
}

bool ofxKinectClient::isFrameNew(){
	if(newFrame){
		newFrame = false;
		return connected;
	}
	return false;
}

void ofxKinectClient::runActivity() {
	while (!activity.isStopped()) {
		if (client.isConnected()) {
            
			if (rwlock.tryWriteLock()) {
				//Receiving loop that must ensure a frame is received as a whole
				char* receivePos = pixels;
				int length = width * 3;
				int totalReceivedBytes = 0;
				while (totalReceivedBytes < size) {
					int receivedBytes = client.receiveRawBytes(receivePos, length); //returns received bytes
					totalReceivedBytes += receivedBytes;
					receivePos += receivedBytes;
				}
				
				newFrame = true;
				rwlock.unlock();
				
			}
		}
		else {
			cout << "NOT connected to server" << endl;
		}
        
		ofSleepMillis(RECEIVER_ACTIVITY_SLEEP);
	}
}

void ofxKinectClient::draw(int _x, int _y){
    fbo.draw(_x,_y);
}