//
//  ofxTwitterConfig.h
//  ofxTwitter
//
//  Created by Pelayo on 13/03/14.
//
//

#pragma once

#include "ofMain.h"

struct ofxTwitterPhotoSizes {
    
    int w;
    int h;
    string resize;
    string name;
    
};

class ofxTwitterConfig {
    
    public:
    
        void checkHelpConfigurationFile();
        void updateHelpConfiguration();
        void onHelpConfigurationResponse(ofEventArgs& args);
        void parseConfigurationFile();
    
        int getPhotoSizeLimit();
        int getMaxMediaPerUpload();
    
        void printPhotoSizesInfo();
    
        int characters_reserved_per_media;
        int max_media_per_upload;
        vector<string> non_username_paths;
        int photo_size_limit;
        vector<ofxTwitterPhotoSizes> photo_sizes;
        int short_url_length;
        int short_url_length_https;
    
    private:
    
    
};