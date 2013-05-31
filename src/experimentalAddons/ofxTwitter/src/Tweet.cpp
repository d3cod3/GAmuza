/*
 *  Tweet.cpp
 *
 *  Created by Douglas Edric Stanley on 10/12/10
 *  cc-by-sa 2010 www.abstractmachine.net. Some rights reserved.
 *  http://creativecommons.org/licenses/by-sa/3.0/
 *
 *  Adapted from code by Paul Shen
 *  cf. http://in.somniac.me/2010/01/openframeworks-http-requests-xml-parser/
 *
 */

#include "Tweet.h"


ofxTweet::ofxTweet(){

}

ofxTweet::ofxTweet(string defaultString){
    title = defaultString;
}

string ofxTweet::getTitle(){
    return title;
}

string ofxTweet::getLink(){
    return link;
}

string ofxTweet::getDate(){
    return published;
}

string ofxTweet::getUpdated(){
    return updated;
}

string ofxTweet::getID(){
    return id;
}

string ofxTweet::getLanguage(){
    return language;
}

string ofxTweet::getAuthorName(){
    return author.name;
}

string ofxTweet::getAvatar(){
    return author.imageUri;
}

string ofxTweet::getAuthorUrl(){
    return author.uri;
}