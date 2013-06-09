//
//  ofxRParticleGlowieRender.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/20/13.
//
//

#include "ofxRParticleGlowieRenderer.h"
#include "ofxRParticle.h"

ofxRParticleGlowieRenderer::ofxRParticleGlowieRenderer()
{
    setup(); 
}

ofxRParticleGlowieRenderer::~ofxRParticleGlowieRenderer()
{

}

void ofxRParticleGlowieRenderer::setup()
{
    objectLookAt = ofVec3f(0,0,1);    
}

void ofxRParticleGlowieRenderer::draw()
{
    if(bAdditiveBlending)
    {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        glDisable(GL_DEPTH_TEST);
    }
    else
    {
        ofEnableAlphaBlending();
    }

    ofSetRectMode(OF_RECTMODE_CENTER);
    for(vector<ofxRParticle>::iterator it = (*particles).begin(); it != (*particles).end(); it++)
    {
        glPushMatrix();
        ofVec3f pos = it->getPos();
        glTranslatef(pos.x, pos.y, pos.z);
        billBoard(); 
        ofSetColor(it->getColor());
        float r = it->getRadius();
        glow->draw(0, 0, r, r);
        glPopMatrix();
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
    
}

void ofxRParticleGlowieRenderer::setAxisAngleOffsets(ofx1DExtruder _xAxis, ofx1DExtruder _yAxis, ofx1DExtruder _zAxis)
{
    xAxis = &_xAxis;
    yAxis = &_yAxis;
    zAxis = &_zAxis;
}

void ofxRParticleGlowieRenderer::setCamPtr(ofEasyCam _cam)
{
    cam = &_cam;
}

void ofxRParticleGlowieRenderer::setGlowImage(ofImage _glow)
{
    glow = &_glow;
}

void ofxRParticleGlowieRenderer::billBoard()
{
    ofVec3f objToCam = cam->getGlobalPosition(); 
    objToCam.normalize();
    float theta = objectLookAt.angle(objToCam);
    ofVec3f axisOfRotation = objToCam.crossed(objectLookAt);
    axisOfRotation.normalize();
    
    glRotatef(-zAxis->getPos(), 0.0, 0.0, 1.0);
    glRotatef(-yAxis->getPos(), 0.0, 1.0, 0.0);
    glRotatef(-xAxis->getPos(), 1.0, 0.0, 0.0);
    glRotatef(-theta, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
}