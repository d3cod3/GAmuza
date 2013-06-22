//
//  ofxBox2dBaseJoint.cpp
//
//  Created by TORU URAKAWA on 2012/10/21.
//
//

#include "ofxBox2dBaseJoint.h"
//----------------------------------------
ofxBox2dBaseJoint::ofxBox2dBaseJoint(){
    world = NULL;
    alive = false;
}

//----------------------------------------
void ofxBox2dBaseJoint::destroy()
{
    alive = false;
}

//----------------------------------------
void ofxBox2dBaseJoint::setWorld(b2World *w){
    world = w;
}

//----------------------------------------
bool ofxBox2dBaseJoint::isAlive()
{
    return alive;
}