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
void ofxTwitter::authorize(const string& consumerKey, const string& consumerSecret) {
    
    ofLogNotice("ofxTwitter::authorize") << "Authorizing app...";
    oauth.setup("https://api.twitter.com", consumerKey, consumerSecret);
    
    ofRegisterURLNotification(this);
    ofAddListener(ofEvents().exit,this,&ofxTwitter::appExits);
    
    checkHelpConfigurationFile();
    
}

//--------------------------------------------------------------
bool ofxTwitter::isAuthorized() {
    
    return oauth.isAuthorized();

}

// GET help/configuration
// https://dev.twitter.com/docs/api/1/get/help/configuration
// Returns the current configuration used by Twitter including twitter.com slugs which are not usernames,
// maximum photo resolutions, and t.co URL lengths.
//--------------------------------------------------------------

void ofxTwitter::checkHelpConfigurationFile() {
    
    ofFile file(ofToDataPath("ofxTwitter_configuration.json"));
    bool configFileNeedsUpdate = false;
    if(file.exists()) {
        Poco::File &filepoco = file.getPocoFile();
        Poco::Timestamp tfile = filepoco.getLastModified();
        time_t timer;
        time(&timer);
        double seconds;
        seconds = difftime(timer,tfile.epochTime());
        if(seconds < 86400) {
            configFileNeedsUpdate = false;
        } else {
            configFileNeedsUpdate = true;
        }
    } else {
        configFileNeedsUpdate = true;
    }
    
    if(!configFileNeedsUpdate) {
        ofLogNotice("ofxTwitter::authorize") << "Config up to date.";
        parseConfigurationFile();
    } else {
        updateHelpConfiguration();
    }

}

void ofxTwitter::updateHelpConfiguration() {
    
    if(oauth.isAuthorized()) {
        string query = "/1.1/help/configuration.json";
        dataRequested = "";
        dataRequested = oauth.get(query);
        ofAddListener(ofEvents().update,this,&ofxTwitter::onHelpConfigurationResponse);
    } else {
        ofLogError("ofxTwitter::updateHelpConfiguration") << "App not authorized.";
    }
    
}

void ofxTwitter::onHelpConfigurationResponse(ofEventArgs& args) {
    
    if(dataRequested != "") {
        
        ofxJSONElement result;
        bool parsingSuccessful = result.parse(dataRequested);
        
        // TODO: Common method for error checking:
        bool getSuccessful = parsingSuccessful;
        if (parsingSuccessful) {
            if(result.isMember("errors")) {
                getSuccessful = false;
                ofxJSONElement errors = result["errors"];
                for(int i = 0; i < errors.size(); i++) {
                    ofxJSONElement error = errors[i];
                    ofLogError("ofxTwitter::onHelpConfigurationResponse") << "error code: " << errors[i]["code"].asInt() << " message: " << error["message"].asString();
                }
            }
        }
        
        if (getSuccessful) {
            result.save("ofxTwitter_configuration.json",true);
            ofLogNotice("ofxTwitter::onHelpConfigurationResponse") << "Config updated.";
            parseConfigurationFile();
        } else {
            ofLogError("ofxTwitter::onHelpConfigurationResponse") << "Failed to update config file." << endl;
        }
        
        dataRequested = "";
        ofRemoveListener(ofEvents().update,this,&ofxTwitter::newResponse);
        
    }
    
}

void ofxTwitter::parseConfigurationFile() {
    
    ofxJSONElement result;
    bool parsingSuccessful = result.openLocal("ofxTwitter_configuration.json");
    if (parsingSuccessful) {
        
        config.characters_reserved_per_media = result["characters_reserved_per_media"].asInt();
        config.max_media_per_upload = result["max_media_per_upload"].asInt();
        ofxJSONElement non_username_paths = result["non_username_paths"];
        for(int i = 0; i < non_username_paths.size(); i++) {
            config.non_username_paths.push_back(non_username_paths[i].asString());
        }
        config.photo_size_limit = result["photo_size_limit"].asInt();
        
        ofxJSONElement photo_sizes_l = result["photo_sizes"]["large"];
        ofxTwitterPhotoSizes pl;
        pl.name = "large"; pl.w = photo_sizes_l["w"].asInt(); pl.h = photo_sizes_l["h"].asInt(); pl.resize = photo_sizes_l["resize"].asString();
        config.photo_sizes.push_back(pl);
        
        photo_sizes_l = result["photo_sizes"]["medium"];
        pl.name = "medium"; pl.w = photo_sizes_l["w"].asInt(); pl.h = photo_sizes_l["h"].asInt(); pl.resize = photo_sizes_l["resize"].asString();
        config.photo_sizes.push_back(pl);
        
        photo_sizes_l = result["photo_sizes"]["small"];
        pl.name = "small"; pl.w = photo_sizes_l["w"].asInt(); pl.h = photo_sizes_l["h"].asInt(); pl.resize = photo_sizes_l["resize"].asString();
        config.photo_sizes.push_back(pl);
        
        photo_sizes_l = result["photo_sizes"]["thumb"];
        pl.name = "thumb"; pl.w = photo_sizes_l["w"].asInt(); pl.h = photo_sizes_l["h"].asInt(); pl.resize = photo_sizes_l["resize"].asString();
        config.photo_sizes.push_back(pl);
        
        config.short_url_length = result["short_url_length"].asInt();
        config.short_url_length_https = result["short_url_length_https"].asInt();
        
    } else {
        ofLogError("ofxTwitter::parseConfigurationFile") << "Failed to load JSON";
    }
    
}

//--------------------------------------------------------------
/*
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
*/

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
void ofxTwitter::updateStatus(string msg, string imgpath) {
    
    // Update status API info.
    // https://dev.twitter.com/docs/api/1.1/post/statuses/update
    // https://dev.twitter.com/docs/api/1.1/post/statuses/update_with_media
    
    if(oauth.isAuthorized()) {
        string query;
        dataRequested = "";
        if(imgpath == "") {
            query = "/1.1/statuses/update.json";
            dataRequested = oauth.post(query,"status="+msg);
        } else {
            query = "/1.1/statuses/update_with_media.json";
            dataRequested = oauth.postfile_multipartdata(query,"status="+msg,"media[]",imgpath);
        }
        ofAddListener(ofEvents().update,this,&ofxTwitter::newStatusResponse);
    } else {
        ofLogError("ofxTwitter::updateStatus") << "App not authorized.";
    }
    
}

void ofxTwitter::postStatus(string msg) {
    
    updateStatus(msg);
    
}

void ofxTwitter::postStatus(string msg, string imgfile) {
    
    // Supported Formats PNG, JPG, GIF
    // (JPG is recompressed lossy by Twitter server)
    // (GIF is reformated as PNG)
    // (PNG will keep its quality)
    ofFile f(imgfile);
    if(f.getExtension() != "jpg" and f.getExtension() != "png" and f.getExtension() != "gif") {
         ofLogError("ofxTwitter::postStatus") << "Invalid file type.";
    } else {
        if(f.getExtension() == "jpg") {
            ofLogWarning("ofxTwitter::postStatus") << "The JPG image will be recompressed lossy by Twitter server.";
        }
        if(f.getExtension() == "gif") {
            ofLogWarning("ofxTwitter::postStatus") << "The GIF image will be reformated as png.";
        }
        string imgurl = ofToDataPath(imgfile,true);
        updateStatus(msg, imgurl);
    }
    
}

void ofxTwitter::newStatusResponse(ofEventArgs& args) {
    
    if(dataRequested != "") {
        
        ofxJSONElement result;
        bool parsingSuccessful = result.parse(dataRequested);
        //cout << result.getRawString() << endl;

        bool postSuccessful = parsingSuccessful;
        if (parsingSuccessful) {
            if(result.isMember("errors")) {
                postSuccessful = false;
                ofxJSONElement errors = result["errors"];
                for(int i = 0; i < errors.size(); i++) {
                     ofxJSONElement error = errors[i];
                     ofLogError("ofxTwitter::newStatusResponse") << "error code: " << errors[i]["code"].asInt() << " message: " << error["message"].asString();
                }
            }
        }
        
        if(result.isMember("entities")) {
            ofxJSONElement entities = result["entities"];
            if(entities.isMember("media")) {
                ofxJSONElement media = entities["media"];
                ofLogVerbose("ofxTwitter::newStatusResponse") << "Uploaded media info:";
                ofLogVerbose("ofxTwitter::newStatusResponse") << "type: " << media[0]["type"].asString();
                ofLogVerbose("ofxTwitter::newStatusResponse") << "url: " << media[0]["url"].asString();
                ofxJSONElement l = media[0]["sizes"]["large"];
                ofxJSONElement m = media[0]["sizes"]["medium"];
                ofxJSONElement s = media[0]["sizes"]["small"];
                ofxJSONElement t = media[0]["sizes"]["thumb"];
                ofLogVerbose("ofxTwitter::newStatusResponse") << "sizes(wxh) Large: " << l["w"].asInt() << "x" <<l["h"].asInt()
                << " Medium: " << m["w"].asInt() << "x" <<m["h"].asInt()<< " Small: " << s["w"].asInt() << "x" <<s["h"].asInt()<< " Thumb: " << t["w"].asInt() << "x" <<t["h"].asInt();
            }
        }
        
        if (postSuccessful) {
            ofLogNotice("ofxTwitter::newStatusResponse") << "Status published.";
        } else {
            ofLogError("ofxTwitter::newStatusResponse") << "Failed to publish new status." << endl;
        }
        
        dataRequested = "";
        ofRemoveListener(ofEvents().update,this,&ofxTwitter::newStatusResponse);
        
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
        
        bool getSuccessful = parsingSuccessful;
        if (parsingSuccessful) {
            if(result.isMember("errors")) {
                getSuccessful = false;
                ofxJSONElement errors = result["errors"];
                for(int i = 0; i < errors.size(); i++) {
                    ofxJSONElement error = errors[i];
                    ofLogError("ofxTwitter::newResponse") << "error code: " << errors[i]["code"].asInt() << " message: " << error["message"].asString();
                }
            }
        }
        
        if (getSuccessful) {
            if(bDiskCacheActive) result.save("cache.json",true);
            ofLogNotice("ofxTwitter::newResponse") << "Tweets received.";
            //cout << result.getRawString() << endl;
            parseResponse(result);
        } else {
            ofLogError("ofxTwitter::newResponse") << "Failed to get tweets" << endl;
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
            
            if(trends[i]["geo"] != Json::Value::null) {
                tweet.geo = trends[i]["geo"]["type"].asString();
                tweet.coordinates.x = trends[i]["geo"]["coordinates"][0].asFloat();
                tweet.coordinates.y = trends[i]["geo"]["coordinates"][1].asFloat();
            }
            
            tweet.source = trends[i]["source"].asString();
            tweet.retweet_count = trends[i]["retweet_count"].asInt();
            tweet.truncated = trends[i]["truncated"].asBool();
            
            ofxJSONElement author = trends[i]["user"];
            
            tweet.user.id_str = author["id_str"].asString();
            tweet.user.uri = "https://twitter.com/"+author["screen_name"].asString();
            
            tweet.user.name = author["name"].asString();
            tweet.user.screen_name = author["screen_name"].asString();
            tweet.user.description = author["description"].asString();
            if(author["location"].asString() != " ") {
                tweet.user.location = author["location"].asString();
            }
            tweet.user.lang = author["lang"].asString();
            tweet.user.url = author["url"].asString();
            
            tweet.user.default_profile = author["default_profile"].asBool();
            tweet.user.default_profile_image = author["default_profile_image"].asBool();
            tweet.user.geo_enabled = author["geo_enabled"].asBool();
            
            tweet.user.profile_image_url = author["profile_image_url"].asString();
            if(author["profile_image_url"] != Json::Value::null && bLoadUserProfileImageOnMemory) {
                ofLoadURLAsync(tweet.user.profile_image_url, "profile_"+tweet.user.id_str);
            }
            
            tweet.user.profile_banner_url = author["profile_banner_url"].asString();
            if(author["profile_banner_url"] != Json::Value::null && bLoadUserBannerImageOnMemory) {
                ofLoadURLAsync(tweet.user.profile_banner_url, "banner_"+tweet.user.id_str);
            }
            
            tweet.user.profile_background_image_url = author["profile_background_image_url"].asString();
            tweet.user.profile_background_color = author["profile_background_color"].asString();
            
            tweet.user.profile_background_tile  = author["profile_background_tile"].asBool();
            tweet.user.profile_use_background_image  = author["profile_use_background_image"].asBool();
            
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
                if(data[i].user.id_str == request_info[1]) {
                    if(request_info[0] == "profile") {
                        data[i].user.profile_image.loadImage(response.data);
                        data[i].user.profile_image_url_loaded = true;
                    }
                    if(request_info[0] == "banner") {
                        data[i].user.profile_banner.loadImage(response.data);
                        data[i].user.profile_banner_url_loaded = true;
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



