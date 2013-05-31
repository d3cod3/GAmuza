/*

    Thermitrack Camera addon
    http://www.thermitrack.com

    v1.5
    May 2011

*/
#ifndef _THERMITRACK_IMAGE
#define _THERMITRACK_IMAGE

#include "ofMain.h"

#include "ofxThermitrack.h"
#include "ofxThermitrackTypes.h"

class ofxThermitrackImage{

	public:
        ofxThermitrackImage();
        ~ofxThermitrackImage();

        void            setup(int _imgsize);
        void            update(ofxThermitrack * camera);
        void            draw(int tx, int ty, int tw, int th);

    protected:

        ofImage         image;
        int             camPixelVals[THERMITRACK_PIXEL_WIDTH*THERMITRACK_PIXEL_WIDTH];
        unsigned char * pixels;


};

#endif
