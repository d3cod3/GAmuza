#ifndef _GAMUZAFBO
#define _GAMUZAFBO

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupFBO(){
    ///////////////////////////
	// FBO setup
    drawingFbo.allocate(projectionScreenW,projectionScreenH,GL_RGBA32F_ARB);
    gamuzaFbo.allocate(projectionScreenW,projectionScreenH,GL_RGBA32F_ARB);
    gamuzaPixels.allocate(projectionScreenW,projectionScreenH,OF_IMAGE_COLOR_ALPHA);
    
    drawingFbo.begin();
    ofClear(255,255,255, 0);
    drawingFbo.end();
    
    gamuzaFbo.begin();
    ofClear(255,255,255, 0);
    gamuzaFbo.end();
    ///////////////////////////
    
    ///////////////////////////
	// SHADER setup
    shaderColorCorrection.load(GAMUZA_SHADER);
    
    shaderColorCorrection.begin();
        shaderColorCorrection.setUniform1f("tex_w",projectionScreenW);
        shaderColorCorrection.setUniform1f("tex_h",projectionScreenH);
    shaderColorCorrection.end();
    
    fbo_gammaCorrection = 1.0;
    fbo_brightness = 1.0;
    fbo_saturation = 1.0;
    fbo_contrast = 1.0;
    fbo_filmBleach = 0.0;
    fbo_techniColor = 0.0;
    fbo_whiteDiffusion = 0.0;
    fbo_exposure = 0.0;
    fbo_diffusion = 0.0;
    ///////////////////////////
}

//--------------------------------------------------------------
void gamuzaMain::updateFBO(){
    
    // pass the output FBO to the external video preview window
    gaVP->getPreview(drawingFbo);
}

//--------------------------------------------------------------
void gamuzaMain::drawFBO(){
    
    char temp[128];
    
    drawingFbo.begin();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    drawIntoFBO();
    glDisable(GL_BLEND);
    glPopAttrib();
    drawingFbo.end();
    
    gamuzaFbo.begin();
    // clear the FBO texture
    ofClear(0,0,0,255);
    // compute matrix homografy
    applyHomography();
    
    shaderColorCorrection.begin();
    
    sprintf(shaderName,"gamma");
    shaderColorCorrection.setUniform1f(shaderName,fbo_gammaCorrection); // 1.0 - 4.0
    sprintf(shaderName,"brightness");
    shaderColorCorrection.setUniform1f(shaderName,fbo_brightness); // 0.0 - 4.0
    sprintf(shaderName,"saturation");
    shaderColorCorrection.setUniform1f(shaderName,fbo_saturation); // 0.0 - 4.0
    sprintf(shaderName,"contrast");
    shaderColorCorrection.setUniform1f(shaderName,fbo_contrast); // 0.0 - 1.0
    sprintf(shaderName,"filmBleach");
    shaderColorCorrection.setUniform1f(shaderName,fbo_filmBleach); // 0.0 - 2.0
    sprintf(shaderName,"technicolor");
    shaderColorCorrection.setUniform1f(shaderName,fbo_techniColor); // 0.0 - 2.0
    sprintf(shaderName,"whiteDiffusion");
    shaderColorCorrection.setUniform1f(shaderName,fbo_whiteDiffusion); // 0.0 - 1.0
    sprintf(shaderName,"exposure");
    shaderColorCorrection.setUniform1f(shaderName,fbo_exposure); // 0.0 - 10.0
    sprintf(shaderName,"diffusion");
    shaderColorCorrection.setUniform1f(shaderName,fbo_diffusion); // 0.0 - 4.0
    
    shaderColorCorrection.setUniformTexture("texBase", drawingFbo, 0);
    
    // apply mapping mesh
    applyGridMesh(0,0,projectionScreenW,projectionScreenH);
    
    shaderColorCorrection.end();
    
    gamuzaFbo.end();
    
    //////////////////////////////////////
    // OUTPUT TEXTURE
    gamuzaFbo.draw(fboDrawingPosX,fboDrawingPosY,fboDrawingW,fboDrawingH);
    //////////////////////////////////////

}

//--------------------------------------------------------------
void gamuzaMain::drawIntoFBO(){
	ofEnableAlphaBlending();
	//////////////////////////////////
    ///////////////////////////
    // LIVE CODING CONSOLE render
    ofPushView();
    ofPushMatrix();
    ofPushStyle();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable(GL_MULTISAMPLE_ARB);
        lua.scriptDraw();
    glDisable(GL_MULTISAMPLE_ARB);
    glPopAttrib();
    ofPopStyle();
    ofPopMatrix();
    ofPopView();
    
    checkErrors();
    ///////////////////////////
    //////////////////////////////////
	ofDisableAlphaBlending();
	
}

#endif
