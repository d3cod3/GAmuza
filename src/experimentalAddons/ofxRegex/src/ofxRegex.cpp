#include "Poco/RegularExpression.h"
using Poco::RegularExpression;

// Some explanation on regular expressions
// http://gnosis.cx/publish/programming/regular_expressions.html

// more info 
// http://www.regular-expressions.info/reference.html



#include "ofxRegex.h"

// -----------------------------------------------------------------------------
ofxRegex::ofxRegex(){
}

// -----------------------------------------------------------------------------
ofxRegex::~ofxRegex(){
}

// -----------------------------------------------------------------------------
void ofxRegex::getMatchedStrings (string contents, string regex ){
    
    RegularExpression regEx(regex);
    RegularExpression::Match match;
    
    while(regEx.match(contents, match) != 0) {
        
        // we get the sub string from the content
        // and then trim the content so that we
        // can continue to search 
        string foundStr = contents.substr(match.offset, match.length);
        contents = contents.substr(match.offset + match.length);
        
        results.push_back(foundStr);
        
    }
    
    return results;
}

// -----------------------------------------------------------------------------
int ofxRegex::getNumWords(){
    return results.size();
}

// -----------------------------------------------------------------------------
string ofxRegex::getStringAtIndex(int index){
    return results[index];
}


