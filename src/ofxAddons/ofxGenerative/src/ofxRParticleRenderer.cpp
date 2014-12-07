//
//  ofxRParticleRenderer.cpp
//  Rezanator
//
//  Created by Syed Reza Ali on 4/17/13.
//
//

#include "ofxRParticleRenderer.h"

ofxRParticleRenderer::ofxRParticleRenderer()
{
    init();    
}

void ofxRParticleRenderer::init()
{
    pointSize = new float;
    setPointSize(1.0);
    bAdditiveBlending = false; 
}

void ofxRParticleRenderer::setup()
{

}

ofxRParticleRenderer::~ofxRParticleRenderer()
{
    delete pointSize;
}

void ofxRParticleRenderer::draw()
{
    if(bAdditiveBlending)
    {
        ofEnableBlendMode(OF_BLENDMODE_ADD); 
    }
    else
    {
        ofEnableAlphaBlending();
    }

    glDisable(GL_DEPTH_TEST);
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    glVertexPointer( 3, GL_FLOAT, sizeof(ofxRParticle), &(*particles)[0].pos);
    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(ofxRParticle),  &(*particles)[0].color );
    glPointSize(*pointSize);
    glDrawArrays( GL_POINTS, 0, (*particles).size() );
    
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
}

void ofxRParticleRenderer::setParticlesPtr(vector<ofxRParticle> *_particles)
{
    particles = _particles;
}

void ofxRParticleRenderer::setPointSize(float _pointSize)
{
    *pointSize = _pointSize;
}

float* ofxRParticleRenderer::getPointSizePtr()
{
    return pointSize;
}

void ofxRParticleRenderer::setAdditiveBlending(bool _bAdditiveBlending)
{
    bAdditiveBlending = _bAdditiveBlending;
}

bool *ofxRParticleRenderer::getAdditiveBlendingPtr()
{
    return &bAdditiveBlending; 
}