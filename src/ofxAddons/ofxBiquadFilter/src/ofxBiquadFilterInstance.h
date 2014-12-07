//
//  ofxBiquadFilterInstance.h
//
//  ofxAddon by Nikolaj Møbius (DZL) && Jonas Jongejan (halfdanj)
//  Original C++ code by Nigel Redmon on 11/24/12
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the Biquad code:
//  http://www.earlevel.com/main/2012/11/26/Biquad-c-source-code/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code
//  for your own purposes, free or commercial.
//

#pragma once

enum ofxBiquadFilterType {
    OFX_BIQUAD_TYPE_LOWPASS = 0,
    OFX_BIQUAD_TYPE_HIGHPASS,
    OFX_BIQUAD_TYPE_BANDPASS,
    OFX_BIQUAD_TYPE_NOTCH,
    OFX_BIQUAD_TYPE_PEAK,
    OFX_BIQUAD_TYPE_LOWSHELF,
    OFX_BIQUAD_TYPE_HIGHSHELF
};

class ofxBiquadFilterInstance {
public:


    ofxBiquadFilterInstance(ofxBiquadFilterType type=OFX_BIQUAD_TYPE_LOWPASS,
                            double Fc=0.50,
                            double Q=0.707,
                            double peakGainDB=0.0);

    ~ofxBiquadFilterInstance();
    
    void setBiquad(ofxBiquadFilterType type, double Fc, double Q, double peakGain);
    
    void setType(ofxBiquadFilterType type);
    void setQ(double Q);
    void setFc(double Fc);
    void setPeakGain(double peakGainDB);
    
    float process(float in);
    
    
    ofxBiquadFilterType type;
    double a0, a1, a2, b1, b2;
    double Fc, Q, peakGain;
    double z1, z2;
    

protected:
    void calcBiquad(void);


};

inline float ofxBiquadFilterInstance::process(float in)
{

    double out = in * a0 + z1;
    z1 = in * a1 + z2 - b1 * out;
    z2 = in * a2 - b2 * out;
    return out;
}


