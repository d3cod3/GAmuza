/*
 *  ofRange.h
 *  SFEditor
 *
 *  Created by Jim on 1/15/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

//JG Added for slider ranges
//----------------------------------------------------------
// ofRange
//----------------------------------------------------------
#pragma once

class ofRange {
  public:
	virtual ~ofRange(){}
	
	ofRange( float _min=0.0f, float _max=1.0f){
		min = _min;
		max = _max;
	}
	
	void set(float _min, float _max){
		min = _min;
		max = _max;
	}
	
	void setMin(float _min){
		min = MIN(_min, max);
	}
	
	void setMax(float _max){
		max = MAX(min, _max);
	}
	
    bool operator==( const ofRange& rg ) {
        return (min == rg.min) && (max == rg.max);
    }
	
    bool operator!=( const ofRange& rg ) {
        return (min != rg.min) || (max != rg.max);
    }
	
	float span(){
		return max - min;
	}
	
    union  {
        struct {
            float min;
            float max;
        };
        float r[2];
    };	
};