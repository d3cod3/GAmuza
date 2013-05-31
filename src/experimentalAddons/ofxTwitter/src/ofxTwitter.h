/*
 *  ofxTwitter.h
 *
 *  Created by Douglas Edric Stanley on 10/12/10
 *  cc-by-sa 2010 www.abstractmachine.net. Some rights reserved.
 *  http://creativecommons.org/licenses/by-sa/3.0/
 *
 *  Adapted from code by Paul Shen
 *  cf. http://in.somniac.me/2010/01/openframeworks-http-requests-xml-parser/
 *
 *  Edited by Andrew Vergara on 05/04/12
 *  Updated addon to fit most recent version of ofxHttpUtils addon. https://github.com/arturoc/ofxHttpUtils
 *
 * 
 */

#pragma once

#include "ofMain.h"

#include "ofxHttpUtils.h"
#include "ofxXmlSettings.h"

#include "TwitterDelegate.h"
#include "Tweet.h"

class ofxTwitter {
public:
	
	void setup();
	void setSearchDelegate(TwitterDelegate *_delegate) { delegate = _delegate; }
	
	void startQuery(string query);
	void startTwitterQuery(string keywords, int repliesPerPage=10, int queryIdentifier=0);
	
	vector<ofxTweet> getLatestResponse();
    ofxTweet getResponse(int _i);
    int getTotalResponse();
    
	void newResponse(ofxHttpResponse &response);
    
    void clear();

	ofxHttpUtils httpUtils;
    
    int tweetQueryIdentifier;
    
    int     totalResponse;
    bool    isInited;
    
private:
	
	TwitterDelegate *delegate;
	
	ofxXmlSettings xml;
	vector<ofxTweet> data;
	
};