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
    
        ofxTwitterSearch() { }
        
        string query;
        // required
        ofPoint geocode = ofPoint(0,0);
        // x. latitude / y. longitude
        bool bUseMiles = false;
        int geocode_radius = 1;
        string lang;
        // ISO 639-1 http://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
        string locale;
        // only 'ja' is efective here
        string result_type;
        // valid values: mixed, recent, popular
        int count = 15;
        // default 15 . maximun 100
        string until;
        // YYYY-MM-DD ej:2012-09-01
        int since_id = -1;
        int max_id = -1;
        bool include_entities = true;
        //string callback; 
    
};