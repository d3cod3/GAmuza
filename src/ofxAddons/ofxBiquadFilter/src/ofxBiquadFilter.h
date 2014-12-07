//
//  ofxBiquadFilter.h
//
//  ofxAddon by Nikolaj MÃ¸bius (DZL) && Jonas Jongejan (halfdanj)
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

#include "ofMain.h"
#include "ofxBiquadFilterInstance.h"


/*!
 @class ofxBiquadFilter_
 @discussion Object that stores the value over time. 
 It can store multiple dimensions (vec2f, vec3f etc)
 */

template<class VectorType>
class ofxBiquadFilter_ {
public:
    
    ofxBiquadFilter_(ofxBiquadFilterType type=OFX_BIQUAD_TYPE_LOWPASS,
                    double Fc=0.50,
                    double Q=0.707,
                    double peakGainDB=0.0);
    

    /*!
     This will update the filter, 
     call this continuously 
     @param inputValue The value you want to filter
     @return The filtered output value
    */
    VectorType update(VectorType inputValue);

    
    /*!
     This is a variant of update for handling degrees in the case around 0 - ° it will wrap correctly
     @param inputValue The value you want to filter, value between 0 and circleSize
     @param circleSize The value to wrap at (default 360)
     @return The filtered output value
     */
    VectorType updateDegree(VectorType inputValue, float circleSize=360);
    
    /*!
     Returns the filtered value
     */
    VectorType value();
    
    
    
    
    /*!
     Set the type of filter, most common types are OFX_BIQUAD_TYPE_LOWPASS and OFX_BIQUAD_TYPE_HIGHPASS
     */
    void setType(ofxBiquadFilterType type);
    
    /*!
     Set the cut-off frequency. A value of 1 represents the frequence values are being
     added to the filter, and a value of 0.5 represent the half. For example adding values 
     every frame 60 frames per second (60Hz), and having a fc value of 0.5, means a cutoff
     frequency of 30Hz.
     */
    void setFc(double Fc);
    
    /*!
     Set the Peak Gain value of the filter. Can be used to amplify values, but most usually left at 0.
     */
    void setPeakGain(double peakGainDB);
    /*!
     Overwrite the Q value of the filter. Usually 0.707
     */
    void setQ(double Q);

    
    vector<ofxBiquadFilterInstance> instances;

private:
    int dimensions;
    VectorType lastValue;
    VectorType _value;
};




//
//The types of filters supported:
//
typedef ofxBiquadFilter_<float> ofxBiquadFilter1f;
typedef ofxBiquadFilter_<ofVec2f> ofxBiquadFilter2f;
typedef ofxBiquadFilter_<ofVec3f> ofxBiquadFilter3f;
typedef ofxBiquadFilter_<ofVec4f> ofxBiquadFilter4f;
typedef ofxBiquadFilter_<ofFloatColor> ofxBiquadFilterColor;

