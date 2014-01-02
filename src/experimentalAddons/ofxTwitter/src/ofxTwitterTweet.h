/*
 *  ofxTwitterTweet.h
 *
 *  Created by Douglas Edric Stanley on 10/12/10
 *  cc-by-sa 2010 www.abstractmachine.net. Some rights reserved.
 *  http://creativecommons.org/licenses/by-sa/3.0/
 *
 *  Adapted from code by Paul Shen
 *  cf. http://in.somniac.me/2010/01/openframeworks-http-requests-xml-parser/
 *
 *  10/12/2013 Adapted to Twitter API 1.1 by Pelayo MŽndez
 *
 */

#pragma once

#include "ofMain.h"

class ofxTwitterTweetAuthor {
    
    public:
    
        ofxTwitterTweetAuthor() { }
        
        string id_str;
        string uri;
        
        string name;
        string screen_name;
        string description;
        string location;
        string lang;
        string url;
        
        bool default_profile;
        bool default_profile_image;
        bool geo_enabled;
        
        string profile_image_url;
        ofImage profile_image;
        bool profile_image_url_loaded = false;
        
        string profile_banner_url;
        ofImage profile_banner;
        bool profile_banner_url_loaded = false;
        
        string profile_background_image_url;
        string profile_background_color;
        bool profile_background_tile;
        bool profile_use_background_image;
     
};

class ofxTwitterTweet {
    
    public:
    
        ofxTwitterTweet() { }
        ofxTwitterTweet(string defaultString)	: text(defaultString) { }

        string id_str;
        string created_at;
        string language;
        string text;
        string geo;
        ofPoint coordinates;
        string source;
        int retweet_count;
        
        bool truncated;
        
        ofxTwitterTweetAuthor user;
    
        string user_id_str;
        string user_uri;
        
        string user_name;
        string user_screen_name;
        string user_description;
        string user_location;
        string user_lang;
        string user_url;
        
        bool user_default_profile;
        bool user_default_profile_image;
        bool user_geo_enabled;
        
        string user_profile_image_url;
        ofImage user_profile_image;
        bool user_profile_image_url_loaded = false;
        
        string user_profile_banner_url;
        ofImage user_profile_banner;
        bool user_profile_banner_url_loaded = false;
        
        string user_profile_background_image_url;
        string user_profile_background_color;
        bool user_profile_background_tile;
        bool user_profile_use_background_image;
    
    
    
        void print() {
            
            string str;
            
            str +=  "\n";
            str +=  "\n--- Tweet ---";
            str += "\nid_str: " + id_str;
            str +=  "\ncreated_at: " + created_at;
            str +=  "\nlanguage: " + language;
            str +=  "\ntext: " + text;
            str +=  "\ngeo: " + geo;
            str +=  "\ncoordinates: " + ofToString(coordinates.x) + "/" + ofToString(coordinates.y);
            str +=  "\nsource: " + source;
            str +=  "\nretweet_count: " + ofToString(retweet_count);
            str +=  "\n--- User ---";
            str +=  "\nuser:name: " + user_name;
            str +=  "\nuser:screen_name: "+ user_screen_name;
            str +=  "\nuser:uri: " + user_uri;
            str +=  "\nuser:imageUri: " + user_profile_image_url;
            str +=  "\nuser:description: " + user_description;
            str +=  "\nuser:location: " + user_location;
            str +=  "\nuser:lang: " + user_lang;
            str +=  "\nuser:url:" + user_url;
            
            cout << str;

        }
        
        bool isProfileImageLoaded() {
            if (user_profile_image.isAllocated() && user_profile_image_url_loaded) {
                return true;
            } else {
                return false;
            }
        }
        
        bool isBannerImageLoaded() {
            if (user_profile_banner.isAllocated() && user_profile_banner_url_loaded) {
                return true;
            } else {
                return false;
            }
        }
	
};