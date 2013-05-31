/*
 *  Tweet.h
 *
 *  Created by Douglas Edric Stanley on 10/12/10
 *  cc-by-sa 2010 www.abstractmachine.net. Some rights reserved.
 *  http://creativecommons.org/licenses/by-sa/3.0/
 *
 *  Adapted from code by Paul Shen
 *  cf. http://in.somniac.me/2010/01/openframeworks-http-requests-xml-parser/
 *
 */

#pragma once

#include "ofMain.h"

struct TweetAuthor {
	string name;
	string uri;
	string imageUri;
};

class ofxTweet {
    
public:
	
	ofxTweet();
	ofxTweet(string defaultString);
    
    string getTitle();
    string getLink();
    string getDate();
    string getUpdated();
    string getID();
    string getLanguage();
    string getAuthorName();
    string getAvatar();
    string getAuthorUrl();
    
    string id;
	string link;
	string published;
	string updated;
	string title;
	string language;
	
	TweetAuthor author;
	
};