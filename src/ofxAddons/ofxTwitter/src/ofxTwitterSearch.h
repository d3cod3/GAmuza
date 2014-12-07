//
//  ofxTwitterSearch.h
//  twitterapp
//
//  Created by Pelayo on 13/12/13.
//
//

#pragma once

#include "ofMain.h"

class ofxTwitterSearch {
    
    public:
    
    string query; // required
    ofVec2f geocode; // x. latitude / y. longitude
    bool bUseMiles;
    int geocode_radius;
    string lang; // ISO 639-1 http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
    string locale; // only 'ja' is efective here
    string result_type;  // valid values: mixed, recent, popular
    int count; // default 15 . maximun 100
    string until; // YYYY-MM-DD ej:2012-09-01
    int since_id;
    int max_id;
    bool include_entities;
    
    ofxTwitterSearch()
    {
        geocode = ofVec2f(0,0);
        bUseMiles = false;
        geocode_radius = 1;
        count = 15;
        since_id = -1;
        max_id = -1;
        include_entities = true;
        
    }
    
};