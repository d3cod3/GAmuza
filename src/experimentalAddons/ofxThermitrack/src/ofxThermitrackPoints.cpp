/*

    Thermitrack Camera addon
    http://www.thermitrack.com

    v1.5
    May 2011

*/

/*
#include "ofxThermitrackPoint.h"

ofxThermitrackPointofxThermitrackPoint(){
    timeBorn = ofGetElapsedTimeMillis();
    maxHistorySize = 50;
}
ofxThermitrackPoint::~ofxThermitrackPoint(){


}
ofxThermitrackPoint::update(ofxPoint2f newpos){

    int now = ofGetElapsedTimeMillis();
            millisAge = now - timeBorn;

            // push current pos into history
            if(posHistory.size() < maxHistorySize){
                posHistory.push_back( pos );
            }else{
                for(int i=0; i<posHistory.size()-1; i++){
                    posHistory[i] = posHistory[i+1];
                }
                posHistory[maxHistorySize-1] = pos;

            }

            // update current pos
            pos = newpos;

}
void ofxThermitrackPoint::draw(int x, int y){

    int arrowsize = 3;
    char tstring[300];
    ofSetColor(0,255,0);
    ofNoFill();

    glPushMatrix();
    glTranslatef( x, y, 0.0 );

    // arrow
    ofLine(pos.x-arrowsize, pos.y, pos.x+arrowsize, pos.y);
    ofLine(pos.x, pos.y-arrowsize, pos.x, pos.y+arrowsize);

    // id
    sprintf(tstring, "%i", (int)id);
    ofDrawBitmapString(tstring, pos.x, pos.y + 12);

    // age
    sprintf(tstring, "%i", (int)(millisAge/1000.0));
    ofDrawBitmapString(tstring, pos.x, pos.y + 22);

    // history
    ofEnableAlphaBlending();
    ofSetColor(0,255,0, 200);
    int histSize = posHistory.size();
    if(histSize > 2){
        for(int i=0; i<histSize-1; i++){
            ofLine(posHistory[i].x, posHistory[i].y, posHistory[i+1].x, posHistory[i+1].y);
        }
    }
    ofDisableAlphaBlending();
    glPopMatrix();

}


class ofxThermitrackPoint{

	public:
        ofxThermitrackPoint();
        ~ofxThermitrackPoint();

        irisysTrackPoint(){

        }
        ~irisysTrackPoint(){
        }

        void draw(int x, int y){


        }
        void update(ofxPoint2f newpos){


        }
        int id;
        ofxPoint2f pos;
        ofxPoint2f posNormalised;
        vector <ofxPoint2f> posHistory;
        int timeBorn;
        int millisAge;
        int maxHistorySize;
};
*/
