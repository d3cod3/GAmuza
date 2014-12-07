#ifndef _GAMUZAFBO
#define _GAMUZAFBO

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupFBO(){
    ///////////////////////////
	// FBO setup
    drawingFbo.allocate(projectionScreenW,projectionScreenH,GL_RGBA32F_ARB);
    gamuzaFbo.allocate(projectionScreenW,projectionScreenH,GL_RGB);
    gamuzaPixels.allocate(projectionScreenW,projectionScreenH,OF_PIXELS_RGB);
    
    drawingFbo.begin();
    ofClear(255,255,255, 0);
    drawingFbo.end();
    
    gamuzaFbo.begin();
    ofClear(255,255,255, 0);
    gamuzaFbo.end();
    ///////////////////////////
    
    ///////////////////////////
	// SHADER setup
    // check graphic card shader support
    char _m[256];
	sprintf(_m," OpenGL version: %s", glGetString (GL_VERSION));
    sendGALog(_m);
	if(GL_ARB_shader_objects){
		sprintf(_m," GL_ARB_shader SUPPORTED by your Graphic Card: %s\n\n", glGetString (GL_RENDERER));
	}else{
		sprintf(_m," GL_ARB_shader NOT SUPPORTED by your Graphic Card: %s\n\n", glGetString (GL_RENDERER));
	}
    sendGALog(_m);
    
    shaderColorCorrection.load(GAMUZA_SHADER);
    
    shaderColorCorrection.begin();
        shaderColorCorrection.setUniform1f("tex_w",projectionScreenW);
        shaderColorCorrection.setUniform1f("tex_h",projectionScreenH);
    shaderColorCorrection.end();
    ///////////////////////////
}

//--------------------------------------------------------------
void gamuzaMain::updateFBO(){
    
}

//--------------------------------------------------------------
void gamuzaMain::drawFBO(){
    
    char temp[128];
    
    drawingFbo.begin();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
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
    //glPushAttrib(GL_ALL_ATTRIB_BITS);
        lua.scriptDraw();
    //glDisable(GL_DEPTH_TEST);
    //glPopAttrib();
    ofPopStyle();
    ofPopMatrix();
    ofPopView();
    
    checkErrors();
    ///////////////////////////
    //////////////////////////////////
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void gamuzaMain::setColorCorrection(float gamma, float bright, float sat,
                        float contr, float filmB, float tech,
                        float whiteD, float expos, float diff){
    fbo_gammaCorrection = gamma;
    fbo_brightness = bright;
    fbo_saturation = sat;
    fbo_contrast = contr;
    fbo_filmBleach = filmB;
    fbo_techniColor = tech;
    fbo_whiteDiffusion = whiteD;
    fbo_exposure = expos;
    fbo_diffusion = diff;
}



#endif
