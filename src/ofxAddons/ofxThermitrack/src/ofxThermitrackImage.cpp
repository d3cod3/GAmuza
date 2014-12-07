/*

    Thermitrack Camera addon
    http://www.thermitrack.com

    v1.5
    May 2011

*/

#include "ofxThermitrackImage.h"

ofxThermitrackImage::ofxThermitrackImage(){

    pixels = new unsigned char[THERMITRACK_PIXEL_WIDTH*THERMITRACK_PIXEL_WIDTH];

    image.allocate(THERMITRACK_PIXEL_WIDTH, THERMITRACK_PIXEL_WIDTH, OF_IMAGE_GRAYSCALE);

}
// ----------------------------------------------------------------------------
ofxThermitrackImage::~ofxThermitrackImage(){
}
// ----------------------------------------------------------------------------
void ofxThermitrackImage::setup(int _imgsize){
}
// ----------------------------------------------------------------------------
void ofxThermitrackImage::update(ofxThermitrack * camera){

    for(int i=0; i<THERMITRACK_PIXEL_WIDTH*THERMITRACK_PIXEL_WIDTH; i++){

        // copy the pixel values (0-255) from ofxThermitrack
        camPixelVals[i] = camera->camPixelVals[i];

        // set the pixels
        pixels[i] = (unsigned char)camPixelVals[i];
    }
    //camPixelVals

    image.setFromPixels(pixels, THERMITRACK_PIXEL_WIDTH, THERMITRACK_PIXEL_WIDTH, OF_IMAGE_GRAYSCALE);

}
// ----------------------------------------------------------------------------
/*void ofxThermitrack::processDataImage(){

    int imageBytesSize = dataIn.size();

    if(imageBytesSize == 258){
        int counter = 0;
        float gridsize = (myCamSize/(float)hardwareCamSize);

        for(int i=0; i<hardwareCamSize; i++){ // y
            for(int j=0; j<hardwareCamSize; j++){ // x

                int x1 = j*gridsize;
                int y1 = i*gridsize;
                int x2 = x1 + (int)gridsize;
                int y2 = y1 + (int)gridsize;

                 // ignore camera id, and I char
                int tb = dataIn[counter+2];

                // this pixel val
                camPixelVals[counter] = tb;

                // draw a rectangle into the image
                cvRectangle(image.getCvImage(), cvPoint(x1, y1), cvPoint(x2, y2), cvScalar(tb,tb,tb), CV_FILLED);

                counter++;

            }
        }
    }

    // image flip
    //image.mirror(flipv, fliph);

}*/
// ----------------------------------------------------------------------------
void ofxThermitrackImage::draw(int tx, int ty, int tw, int th){

    image.draw(tx, ty, tw, th);

    /*
    ofFill();
    ofSetColor(255,255,255);

    glPushMatrix();
    glTranslatef( tx, ty, 0.0 );

        image.draw(0,0);

    glPopMatrix();
    */

}

