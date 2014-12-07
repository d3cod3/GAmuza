#pragma once

// OF
#include "ofMain.h"


class ofxRegex {
    
    
    public:
    
        ofxRegex();
        ~ofxRegex();
    
        //vector < string > getMatchedStrings (string stringToParse, string regex );
    
        void getMatchedStrings (string stringToParse, string regex );
    
        string getStringAtIndex(int index);
    
        int getNumWords();
    
        vector<string> results;
	
};