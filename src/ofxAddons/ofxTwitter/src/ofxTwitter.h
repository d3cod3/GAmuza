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
 *  Edited by welovecode 14/06/12
 *  Added cache support for saving/load xml cache file.
 *  Added POST query method.
 * 
 *  Edited by Pelayo MŽndez on 09/12/13
 *  Migrated to Twitter API v1.1. https://dev.twitter.com/docs/api/1.1/overview
 *  Using Christopher Baker ofxOAuth adddon https://github.com/bakercp/ofxOAuth
 *  Using  ofxJSON for parsing data as XMl is not supported anymore https://github.com/jefftimesten/ofxJSON
 *
 */

#pragma once

#include "ofMain.h"
// addons
#include "ofxOAuth.h"
#include "ofxJSONElement.h"
// ofxTwitter
#include "ofxTwitterConfig.h"
#include "ofxTwitterTweet.h"
#include "ofxTwitterSearch.h"
// Poco
#include "Poco/Base64Encoder.h"

class ofxTwitter {

    public:
    
        ofxTwitter();
        ~ofxTwitter();
    
        void authorize(const string& consumerKey, const string& consumerSecret);
        bool isAuthorized();
    
        ofxTwitterConfig config; // TODO: Handle this in private.
    
        void loadCacheFile();
        void setDiskCache(bool newSaveCache);
        bool diskCacheIsActive();

        //void startQuery(string keywords, int count = 15);
        void startSearch(ofxTwitterSearch search);
        void newResponse(ofEventArgs& args);
        void parseResponse(ofxJSONElement result);
    
        void postStatus(string msg);
        void postStatus(string msg, string imgfile);
        void newStatusResponse(ofEventArgs& args);
    
        void setAutoLoadImages(bool newLoadUserProfileImageUrl, bool newLoadUserProfileBannerUrl);
        void urlResponse(ofHttpResponse & response);
        void appExits(ofEventArgs& args);
    
        ofxTwitterTweet getTweetByIndex(int index);
        int getTotalLoadedTweets() { return data.size(); }
    
        void printDebugInfo();
    
    private:
	
        ofxOAuth oauth;

        void checkHelpConfigurationFile();
        void updateHelpConfiguration();
        void onHelpConfigurationResponse(ofEventArgs& args);
        void parseConfigurationFile();
    
        string dataRequested;

        bool bDiskCacheActive;
        bool bLoadUserProfileImageOnMemory;
        bool bLoadUserBannerImageOnMemory;
    
        vector<ofxTwitterTweet> data;
    
        void updateStatus(string msg, string imgpath = "");
	
};