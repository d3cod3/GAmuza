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

#include "ofxTwitter.h"

//--------------------------------------------------------------
ofxTwitter::ofxTwitter():
bDiskCacheActive(false),
bLoadUserProfileImageOnMemory(false),
bLoadUserBannerImageOnMemory(false)
{

}

//--------------------------------------------------------------
ofxTwitter::~ofxTwitter(){
    
}

//--------------------------------------------------------------
void ofxTwitter::appExits(ofEventArgs& args) {
    
    ofLogNotice("ofxTwitter::appExits") << "Clearing Twitter client...";
    ofUnregisterURLNotification(this);
    ofRemoveAllURLRequests();
    
}

//--------------------------------------------------------------
void ofxTwitter::setConfigFiles(const string& certificate, const string& credentials){
    oauth.setSSLCACertificateFile(certificate);
    oauth.setCredentialsPathname(credentials);
}

//--------------------------------------------------------------
void ofxTwitter::authorize(const string& consumerKey, const string& consumerSecret) {
    
    ofLogNotice("ofxTwitter::authorize") << "Authorizing app...";
    oauth.setup("https://api.twitter.com", consumerKey, consumerSecret);
    
    ofRegisterURLNotification(this);
    //ofAddListener(ofEvents().exit,this,&ofxTwitter::appExits);
	
}

//--------------------------------------------------------------
void ofxTwitter::resetTwitter() {
    
    ofLogNotice("ofxTwitter::appExits") << "Clearing Twitter client...";
    ofUnregisterURLNotification(this);
    ofRemoveAllURLRequests();
    
}

//--------------------------------------------------------------
bool ofxTwitter::isAuthorized() {
    
    return oauth.isAuthorized();

}

//--------------------------------------------------------------
void ofxTwitter::startQuery(string keywords, int count) {
    
    if(oauth.isAuthorized()) {
        string query = "/1.1/search/tweets.json?count="+ofToString(count)+"?q=";
        query += keywords;
        dataRequested = "";
        dataRequested = oauth.get(query);
        ofAddListener(ofEvents().update,this,&ofxTwitter::newResponse);
    } else {
        ofLogError("ofxTwitter::startQuery") << "App not authorized.";
    }
    
}

//--------------------------------------------------------------
void ofxTwitter::startSearch(ofxTwitterSearch search) {
    
    if(oauth.isAuthorized()) {
        string query;
        query+= "/1.1/search/tweets.json?";
        if(search.query.empty()) {
            ofLogError("ofxTwitter::startSearch") << "Query is required.";
            return;
        }
        query+= "q="+search.query;
        if(search.geocode.x != 0 and search.geocode.y != 0) {
            query+= "&geocode="+ofToString(search.geocode.x)+","+ofToString(search.geocode.y);
            query+= ","+ofToString(search.geocode_radius);
            if(search.bUseMiles) {
                query+= "mi";
            } else {
                query+= "km";
            }
        }
        if(!search.lang.empty()) query+= "&lang="+search.lang;
        if(!search.locale.empty()) query+= "&locale="+search.locale;
        if(!search.result_type.empty()) query+= "&result_type="+search.result_type;
        if(search.count > 0 && search.count != 15) query+= "&count="+ofToString(search.count);
        if(!search.until.empty()) query+= "&until="+search.until;
        if(search.since_id > 0) query+= "&since_id="+ofToString(search.since_id);
        if(search.max_id > 0) query+= "&max_id="+ofToString(search.max_id);
        if(!search.include_entities) {
            query+= "&include_entities=false";
        }
        dataRequested = "";
        dataRequested = oauth.get(query);
        ofAddListener(ofEvents().update,this,&ofxTwitter::newResponse);
    } else {
        ofLogError("ofxTwitter::startQuery") << "App not authorized.";
    }
    
}


//--------------------------------------------------------------
void ofxTwitter::loadCacheFile() {
    
    ofLogNotice("ofxTwitter::loadCacheFile") << "Loading local file 'cache.json'";
    ofxJSONElement result;
    bool parsingSuccessful = result.openLocal("cache.json");
    if (parsingSuccessful) {
        parseResponse(result);
    } else {
        ofLogError("ofxTwitter::loadCacheFile") << "Failed to load JSON";
    }
    
}

//--------------------------------------------------------------
void ofxTwitter::setDiskCache(bool newSaveCache) {
    
    bDiskCacheActive = newSaveCache;
    
}

//--------------------------------------------------------------
bool ofxTwitter::diskCacheIsActive() {
    
    return bDiskCacheActive;

}

//--------------------------------------------------------------
void ofxTwitter::newResponse(ofEventArgs& args) {
    
    if(dataRequested != "") {
    
        ofxJSONElement result;
        bool parsingSuccessful = result.parse(dataRequested);
        if (parsingSuccessful) {
            if(bDiskCacheActive) result.save("cache.json",true);
            ofLogNotice("ofxTwitter::newResponse") << "Tweets JSON parsed.";
            //cout << result.getRawString() << endl;
            parseResponse(result);
        } else {
            ofLogError("ofxTwitter::newResponse") << "Failed to parse JSON" << endl;
        }
        
        dataRequested = "";
        ofRemoveListener(ofEvents().update,this,&ofxTwitter::newResponse);
    
    }
	
}

//--------------------------------------------------------------
void ofxTwitter::parseResponse(ofxJSONElement result) {
    
    if(result.isMember("statuses")) {
        
        data.clear();
        
        ofxJSONElement trends = result["statuses"];
        
        for(int i = 0; i < trends.size(); i++) {
            
            ofxTwitterTweet tweet;
            
            tweet.id_str = trends[i]["id_str"].asString();
            tweet.created_at = trends[i]["created_at"].asString();
            tweet.language = trends[i]["language"].asString();
            tweet.text = trends[i]["text"].asString();
            
            if(trends[i]["geo"] != NULL) {
                tweet.geo = trends[i]["geo"]["type"].asString();
                tweet.coordinates.x = trends[i]["geo"]["coordinates"][0].asFloat();
                tweet.coordinates.y = trends[i]["geo"]["coordinates"][1].asFloat();
            }
            
            tweet.source = trends[i]["source"].asString();
            tweet.retweet_count = trends[i]["retweet_count"].asInt();
            tweet.truncated = trends[i]["truncated"].asBool();
            
            ofxJSONElement author = trends[i]["user"];
            
            tweet.user_id_str = author["id_str"].asString();
            tweet.user_uri = "https://twitter.com/"+author["screen_name"].asString();
            
            tweet.user_name = author["name"].asString();
            tweet.user_screen_name = author["screen_name"].asString();
            tweet.user_description = author["description"].asString();
            if(author["location"].asString() != " ") {
                tweet.user_location = author["location"].asString();
            }
            tweet.user_lang = author["lang"].asString();
            tweet.user_url = author["url"].asString();
            
            tweet.user_default_profile = author["default_profile"].asBool();
            tweet.user_default_profile_image = author["default_profile_image"].asBool();
            tweet.user_geo_enabled = author["geo_enabled"].asBool();
            
            tweet.user_profile_image_url = author["profile_image_url"].asString();
            if(author["profile_image_url"] != NULL && bLoadUserProfileImageOnMemory) {
                ofLoadURLAsync(tweet.user_profile_image_url, "profile_"+tweet.user_id_str);
            }
            
            tweet.user_profile_banner_url = author["profile_banner_url"].asString();
            if(author["profile_banner_url"] != NULL && bLoadUserBannerImageOnMemory) {
                ofLoadURLAsync(tweet.user_profile_banner_url, "banner_"+tweet.user_id_str);
            }
            
            tweet.user_profile_background_image_url = author["profile_background_image_url"].asString();
            tweet.user_profile_background_color = author["profile_background_color"].asString();
            
            tweet.user_profile_background_tile  = author["profile_background_tile"].asBool();
            tweet.user_profile_use_background_image  = author["profile_use_background_image"].asBool();
            
            data.push_back( tweet );
            //tweet.print();
            
        }
        
        ofLogNotice("ofxTwitter::parseResponse") << "(" << data.size() << ") Tweets ready";
        
    }

}

//--------------------------------------------------------------
void ofxTwitter::setAutoLoadImages(bool newLoadUserProfileImageOnMemory, bool newLoadUserProfileBannerOnMemory) {
    
    bLoadUserProfileImageOnMemory = newLoadUserProfileImageOnMemory;
    bLoadUserBannerImageOnMemory = newLoadUserProfileBannerOnMemory;
    
}

//--------------------------------------------------------------
ofxTwitterTweet ofxTwitter::getTweetByIndex(int index) {
    
    return data[index];
    
}

//--------------------------------------------------------------
void ofxTwitter::urlResponse(ofHttpResponse & response){
    
        if(response.status==200){
            ofLogNotice("ofxTwitter::urlResponse") << response.request.name << " loaded ok.";
            for(int i = 0; i < data.size(); i++) {
                
                vector<string> request_info = ofSplitString(response.request.name, "_");
                if(data[i].user_id_str == request_info[1]) {
                    if(request_info[0] == "profile") {
                        data[i].user_profile_image.loadImage(response.data);
                        data[i].user_profile_image_url_loaded = true;
                    }
                    if(request_info[0] == "banner") {
                        data[i].user_profile_banner.loadImage(response.data);
                        data[i].user_profile_banner_url_loaded = true;
                    }
                }
                
            }
        }else{
            ofLogError("ofxTwitter::urlResponse") << response.status << " " << response.error;
            if(response.status == -1 || response.status == 404) ofRemoveURLRequest(response.request.getID());
        }
    
}

//--------------------------------------------------------------
void ofxTwitter::printDebugInfo() {

    string info;
    info += "ofxTwitter . ";
    info += "App Authorized: " + ofToString(isAuthorized());
    info += " . Tweets loaded: " + ofToString(getTotalLoadedTweets());
    
    ofPushStyle();
        ofSetColor(0);
        ofDrawBitmapString(info, ofPoint(20,ofGetHeight()-15));
        ofSetColor(125,125,125,125);
        ofRect(0, ofGetHeight()-40, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
}



