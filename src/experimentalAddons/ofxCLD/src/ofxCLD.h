#ifndef _OFX_CLD_H
#define _OFX_CLD_H

#include "ofMain.h"

#include "imatrix.h"
#include "ETF.h"
#include "fdog.h"
#include "myvec.h"


class ofxCLD{
public:
    ofxCLD();
    ~ofxCLD();
    
    void setup(int _w, int _h);
    ofTexture& getCLDTextureRef(unsigned char* _pix,int _black, float _sigma1, float _sigma2, float _tau, float _thresh);
    
    unsigned char           *cld_pixels;
    imatrix                 cld_img;
    ETF                     cld_e;
    ofTexture               cld_texture;
    unsigned char           *finalPixels;
    
    int _width,_height;
    
};

#endif
