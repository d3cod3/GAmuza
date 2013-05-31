/**
 *  ofxCLD.cpp
 *
*/

#include "ofxCLD.h"

ofxCLD::ofxCLD() {
   
}

ofxCLD::~ofxCLD() {
    
}

void ofxCLD::setup(int _w, int _h){
    _width  = _w;
    _height = _h;
    
    cld_texture.allocate(_w,_h,GL_RGB);
    cld_img.init(_w,_h);
    
    cld_pixels  = new unsigned char[_w*_h*3];
    finalPixels = new unsigned char[_w*_h*3];
    
}

ofTexture& ofxCLD::getCLDTextureRef(unsigned char* _pix,int _black, float _sigma1, float _sigma2, float _tau, float _thresh){
    
    if(_black < -255){
        _black = 255;
    }else if(_black > 255){
        _black = 255;
    }
    
    if(_sigma1 < 0.01f){
        _sigma1 = 0.01f;
    }else if(_sigma1 > 2.0f){
        _sigma1 = 2.0f;
    }
    
    if(_sigma2 < 0.01f){
        _sigma2 = 0.01f;
    }else if(_sigma2 > 10.0f){
        _sigma2 = 10.0f;
    }
    
    if(_tau < 0.8f){
        _tau = 0.8f;
    }else if(_tau > 1.0f){
        _tau = 1.0f;
    }
    
    if(_thresh < -1.0f){
        _thresh = -1.0f;
    }else if(_thresh > 1.0f){
        _thresh = 1.0f;
    }
    
    
    cld_pixels = _pix;
    
    for(int w=0; w<_width; w++) {
        for(int h=0; h<_height; h++) {
            int p = h*_width + w;
            cld_img[w][h] = cld_pixels[p*3] - _black;
        }
    }
    
    cld_e.init(_width, _height);
    cld_e.set(cld_img);
    cld_e.Smooth(4, 2);
    GetFDoG(cld_img, cld_e, _sigma1, _sigma2, _tau);
    GrayThresholding(cld_img, _thresh);
    
    for(int w=0; w<_width; w++) {
        for(int h=0; h<_height; h++) {
            
            int p = h*_width + w;
            finalPixels[p*3]      = CLAMP(cld_img[w][h], 0, 255);
            finalPixels[p*3+1]    = CLAMP(cld_img[w][h], 0, 255);
            finalPixels[p*3+2]    = CLAMP(cld_img[w][h], 0, 255);
        }
    }
    
    cld_texture.loadData(finalPixels, _width, _height, GL_RGB);
    
    return cld_texture;
    
}