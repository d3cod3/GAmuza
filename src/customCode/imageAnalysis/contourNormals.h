#pragma once



#include "ofMain.h"
#include "ofxVectorMath.h"
#include "ofxOpenCv.h"

class contourNormals{

	public:
		contourNormals(){

		}

		//------------------------------
		void makeNormals(vector <ofVec2f> &contourIn, vector <ofVec2f> &normalsOut, int direction = 1){
			int length = contourIn.size();

			normalsOut.clear();
			normalsOut.assign(length, ofVec2f() );

			ofVec2f normal;
			ofVec2f delta;
			for(int i = 1; i < length; i++){
                delta = contourIn[i] - contourIn[i-1];
                delta.normalize();

                if(direction){
                    normal.set(delta.y, -delta.x);
                }else{
                    normal.set(-delta.y, delta.x);
                }

                normalsOut[i] = normal;
			}

		}


};
