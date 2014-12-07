//
//  ofxQRCodeGenerator.h
//  ofxQRCodeGenerator addon
//
//  Created by Brett Renfer on 3/18/12.
//  Copyright (c) 2012 Robotconscience. All rights reserved.
//

#pragma once

#include "qrencode.h"

class ofxQRCodeGenerator {
public:
    
    ofxQRCodeGenerator() {}
    
    /**
     * Generate an OF Image from a string
     * @param str   the string you want to convert
     * @param width target width + height of the image you want to output (will resize proportionally to returned data)
     * @param caseSensive (optional) worry about converting the case. tends to return all uppercase if this is left false
     * @return ofImage with 
     */
    
    ofImage generate( string str, int width, bool caseSensitve=false ){
        
        // try to decode
        QRcode * q = QRcode_encodeString( str.c_str(), 0, QR_ECLEVEL_M, QR_MODE_8, caseSensitve ? 1 : 0);
        
        if ( q != NULL ){
            int goodWidth = width;
            
            // resize up to something the returned data will fit into nicely
            while ( goodWidth % q->width != 0 ){
                goodWidth++;
            }
            
            // letting you know if i resized your image (sorry!)
            if (goodWidth != width) ofLog( OF_LOG_WARNING, "Making your width fit the QR code: "+ofToString( goodWidth ));
            width = goodWidth;
            
            int ratio = width / q->width;
            
            ofPixels pix;
            pix.allocate( width, width, OF_IMAGE_GRAYSCALE );
            
            for (int y=0; y < q->width; y++){
                for (int x=0; x < q->width; x++){
                    //get least significant byte of the returned usigned char
                    // 1 == black, 0 == white
                    // (check out qrencode for more info)
                    int c = (int)q->data[ y*q->width + x ]&1;
                    
                    // make squares based on that data!
                    for (int y1=0; y1<ratio; y1++){
                        for (int x1=0; x1<ratio; x1++){
                            if ( c == 1){
                                pix[ (x*ratio + x1) + (y*ratio + y1)*width ] = 0;
                            } else {
                                pix[ (x*ratio + x1) + (y*ratio + y1)*width ] = 255;
                            }
                        }
                    }
                }
            }
            // free to encode another code!
            QRcode_free( q );
            
            return ofImage(pix);
            
        // hm, maybe you sent something weird?
        } else {
            ofLog( OF_LOG_ERROR, "Failed to encode");
            return ofImage();
        }
    }
    
};