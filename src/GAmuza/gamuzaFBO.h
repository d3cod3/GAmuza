#ifndef _GAMUZAFBO
#define _GAMUZAFBO

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::setupFBO(){
    ///////////////////////////
	// FBO setup
    drawingFbo.allocate(projectionScreenW,projectionScreenH,GL_RGBA32F_ARB); // GL_RGB, GL_RGBA32F_ARB
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
    // MAPPER OUTPUT setup
    mapperModuleFbo.allocate(projectionScreenW,projectionScreenH,GL_RGB);
    
    mapperModuleFbo.begin();
    ofClear(255,255,255, 0);
    mapperModuleFbo.end();
    
    switchMapperOutput = false;
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
    
    ///////////////////////////
	// GRID setup
    setupGrid();
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
    //glEnable(GL_BLEND);
    //glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    drawIntoFBO();
    //glDisable(GL_BLEND);
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
    
    shaderColorCorrection.setUniformTexture("tex0", drawingFbo, 0);
    
    // apply mapping mesh
    applyGridMesh(0,0,projectionScreenW,projectionScreenH);
    
    shaderColorCorrection.end();
    
    gamuzaFbo.end();
    
    //////////////////////////////////////
    // OUTPUT TEXTURE
    if(switchMapperOutput){
        mapperModuleFbo.draw(fboDrawingPosX,fboDrawingPosY,fboDrawingW,fboDrawingH);
    }else{
        gamuzaFbo.draw(fboDrawingPosX,fboDrawingPosY,fboDrawingW,fboDrawingH);
    }
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
        lua.scriptDraw();
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

//--------------------------------------------------------------
void gamuzaMain::getMapperModuleOutput(ofFbo mp){
    mapperModuleFbo = mp;
}

//--------------------------------------------------------------
void gamuzaMain::setupGrid(){
    GoldenRatio = false;
    CenterRatio = false;
    ThirdRatio = false;
    GridDraw = false;
    gridWGap = 50;
    gridHGap = 50;
}

//--------------------------------------------------------------
void gamuzaMain::showGrid(){
    ofPushMatrix();
    ofTranslate(fboDrawingPosX,fboDrawingPosY,0);
    if (GoldenRatio) {
		ShowGoldenRatio(fboDrawingW,fboDrawingH);
	}
    
	if (CenterRatio) {
		ShowCenter(fboDrawingW,fboDrawingH);
	}
    
	if (ThirdRatio) {
		ShowThirdRatio(fboDrawingW,fboDrawingH);
	}
    
	if (GridDraw) {
		ShowGrid(fboDrawingW,fboDrawingH, gridWGap, gridHGap);
	}
    ofPopMatrix();
}

//--------------------------------------------------------------
void gamuzaMain::setGridSettings(bool gr, bool cr, bool tr, bool gd, int gWGap, int gHGap){
    GoldenRatio = gr;
    CenterRatio = cr;
    ThirdRatio = tr;
    GridDraw = gd;
    gridWGap = gWGap;
    gridHGap = gHGap;
}



#endif
