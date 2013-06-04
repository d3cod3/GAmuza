/*
 * ofxPBOVideoPlayer.cpp
 *
 *  Created on: 08/04/2012
 *      Author: arturo
 */

#include "ofxPBOVideoPlayer.h"

void ofxPBOVideoPlayer::load(string path){
	usePBO = true;
	//player.setPixelFormat(OF_PIXELS_BGRA);
	//ofPtr<ofGstVideoPlayer> gstPlayer(new ofGstVideoPlayer);
	//ofAddListener(gstPlayer->getGstVideoUtils()->bufferEvent,this,&VideoPlayer::newFrame);
	player.setUseTexture(false);
	//player.setPlayer(gstPlayer);
	player.loadMovie(path);

	if(usePBO){
		//cout << player.getPixelsRef().getNumChannels() << endl;
		tex.allocate(player.getPixelsRef());
		//tex.texData.glType = GL_BGRA;
		pbo.allocate(tex,1);
	}else{
		fbo.allocate(player.getWidth(),player.getHeight(),GL_RGB);
		tex = fbo.getTextureReference();
	}
	updateTex = false;

}

void ofxPBOVideoPlayer::newFrame(ofPixels & pixels){
	pbo.loadData(player.getPixelsRef());
	updateTex = true;
}

void ofxPBOVideoPlayer::play(){
	player.play();
}


void ofxPBOVideoPlayer::update(){
	player.update();
	if(player.isFrameNew()){
		if(usePBO){
			//cout << "new frame" << endl;
			//time = ofGetElapsedTimeMicros();
			//cout << "time tex" << ofGetElapsedTimeMicros() - time << endl;
			//int time = ofGetElapsedTimeMicros();
			pbo.loadData(player.getPixelsRef());
			//cout << ofGetElapsedTimeMicros() - time << endl;
			updateTex = true;
		}else{
			//int time = ofGetElapsedTimeMicros();
			fbo.begin();
			glDrawPixels(player.getWidth(),player.getHeight(),GL_RGB, GL_UNSIGNED_BYTE, player.getPixels());
			fbo.end();
			//cout << ofGetElapsedTimeMicros() - time << endl;
		}
	}else{
		//cout << "not new frame" << endl;
	}
}

bool ofxPBOVideoPlayer::isFrameNew(){
	return player.isFrameNew();
}

void ofxPBOVideoPlayer::draw(){
	if(updateTex){
		pbo.updateTexture();
		updateTex = false;
	}
	tex.draw(0,0);
}
