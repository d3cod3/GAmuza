//
//  ofxBiquadFilter.cpp
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

#include "ofxBiquadFilter.h"

template<class VectorType>
ofxBiquadFilter_<VectorType>::ofxBiquadFilter_(ofxBiquadFilterType type,
                                               double Fc,
                                               double Q,
                                               double peakGainDB){
    
    
    dimensions = sizeof(VectorType) / 4;
    
    
    for(int i=0;i<dimensions;i++){
        instances.push_back(ofxBiquadFilterInstance(type, Fc, Q, peakGainDB));
    }
    
}

template<class VectorType>
VectorType ofxBiquadFilter_<VectorType>::update(VectorType inputValue){
    VectorType outValue;
    
    float * intIt = (float *) &inputValue;
    float * outIt = (float *) &outValue;
    for(int i=0;i<dimensions;i++){
        if(!isnan(*intIt)){
            *outIt = instances[i].process(*intIt);
        }
        intIt++; outIt++;
    }

    lastValue = inputValue;

    _value = outValue;
    return _value;
}

template<class VectorType>
VectorType ofxBiquadFilter_<VectorType>::updateDegree(VectorType inputValue, float circleSize){
    VectorType outValue;
    
    float * intIt = (float *) &inputValue;
    float * outIt = (float *) &outValue;
    float * lastIt = (float *) &lastValue;
    
    for(int i=0;i<dimensions;i++){
        float _inVal = *intIt;
        
        while(fabs(_inVal - *lastIt) > circleSize*0.5){
            if(_inVal > *lastIt){
                _inVal -= circleSize;
            }
            else {
                _inVal += circleSize;
            }
        }
        
        if(!isnan(_inVal)){
            *outIt = instances[i].process(_inVal);
        }

        *lastIt = _inVal;
        
        while(*outIt < 0){
            *outIt += circleSize;
        }
        while(*outIt > circleSize){
            *outIt -= circleSize;
        }
        intIt++; outIt++; lastIt++;
    }
    
    _value = outValue;
    return _value;
}

template<class VectorType>
VectorType ofxBiquadFilter_<VectorType>::ofxBiquadFilter_::value(){
    return _value;
}


template<class VectorType>
void ofxBiquadFilter_<VectorType>::setType(ofxBiquadFilterType type){
    for(int i=0;i<dimensions;i++){
        instances[i].setType(type);
    }
}

template<class VectorType>
void ofxBiquadFilter_<VectorType>::setFc(double Fc){
    for(int i=0;i<dimensions;i++){
        instances[i].setFc(Fc);
    }
}

template<class VectorType>
void ofxBiquadFilter_<VectorType>::setQ(double Q){
    for(int i=0;i<dimensions;i++){
        instances[i].setQ(Q);
    }
}

template<class VectorType>
void ofxBiquadFilter_<VectorType>::setPeakGain(double peakGainDB){
    for(int i=0;i<dimensions;i++){
        instances[i].setPeakGain(peakGainDB);
    }
}



template class ofxBiquadFilter_<float>;
template class ofxBiquadFilter_<ofVec2f>;
template class ofxBiquadFilter_<ofVec3f>;
template class ofxBiquadFilter_<ofVec4f>;
template class ofxBiquadFilter_<ofFloatColor>;
