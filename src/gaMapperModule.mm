
#include "gaMapperModule.h"


//--------------------------------------------------------------
gaMapperModule::gaMapperModule(int windowW, int windowH){
    ofSetDataPathRoot(gapp->_bundleDataPath);
    
    winW = windowW;
    winH = windowH;
    
    xMargin = 360;
    yMargin = 80;
    
    fboBoxW = winW - xMargin;
    fboBoxH = winH - yMargin;
    
    setFboDim(gapp->projectionScreenW,gapp->projectionScreenH);
    
    isON = false;
}

//--------------------------------------------------------------
gaMapperModule::~gaMapperModule(){
    
}

//--------------------------------------------------------------
void gaMapperModule::resetPreview(){
    if(fboW > fboBoxW && fboH > fboBoxH){ // width & height bigger than window
        if(fboW > fboH){ // horizontal texture
            fboDrawingW         = fboBoxW;
            fboDrawingH         = (fboH*fboDrawingW)/fboW;
            fboDrawingPosX      = 0;
            fboDrawingPosY      = (fboBoxH-fboDrawingH)/2.0;
        }else{ // vertical texture
            fboDrawingH         = fboBoxH;
            fboDrawingW         = (fboW*fboDrawingH)/fboH;
            fboDrawingPosX      = (fboBoxW-fboDrawingW)/2.0;
            fboDrawingPosY      = 0;
        }
    }else if(fboW > fboBoxW && fboH <= fboBoxH){ // width bigger
        // horizontal texture only (due to landscape window nature)
        fboDrawingW         = fboBoxW;
        fboDrawingH         = (fboH*fboDrawingW)/fboW;
        fboDrawingPosX      = 0;
        fboDrawingPosY      = (fboBoxH-fboDrawingH)/2.0;
    }else if(fboW <= fboBoxW && fboH > fboBoxH){ // height bigger
        fboDrawingH         = fboBoxH;
        fboDrawingW         = (fboW*fboDrawingH)/fboH;
        fboDrawingPosX      = (fboBoxW-fboDrawingW)/2.0;
        fboDrawingPosY      = 0;
    }else{ // smaller than window
        if(fboW > fboH){ // horizontal texture
            if((fboW/fboH) < 1.5){
                fboDrawingH         = fboBoxH;
                fboDrawingW         = (fboW*fboDrawingH)/fboH;
                fboDrawingPosX      = (fboBoxW-fboDrawingW)/2.0;
                fboDrawingPosY      = 0;
            }else{
                fboDrawingW         = fboBoxW;
                fboDrawingH         = (fboH*fboDrawingW)/fboW;
                fboDrawingPosX      = 0;
                fboDrawingPosY      = (fboBoxH-fboDrawingH)/2.0;
            }
        }else{ // vertical texture
            fboDrawingW         = fboBoxW;
            fboDrawingH         = (fboH*fboDrawingW)/fboW;
            fboDrawingPosX      = 0;
            fboDrawingPosY      = (fboBoxH-fboDrawingH)/2.0;
        }
    }
    
    fboDrawingPosX += xMargin/2;
    fboDrawingPosY += yMargin/2;
    
    previewFbo.allocate(fboW,fboH,GL_RGBA);
}

//--------------------------------------------------------------
void gaMapperModule::setFboDim(int w, int h){
    fboW = w;
    fboH = h;
    
    resetPreview();
}

//--------------------------------------------------------------
void gaMapperModule::setup(){
    ofSetWindowShape(winW,winH);
    ofSetEscapeQuitsApp(false);
    
    resetPreview();
    
    mapping = new ofxMtlMapping2D();
    mapping->init(fboW,fboH, "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
    mapping->toggle();
    
}

//--------------------------------------------------------------
void gaMapperModule::update() {
    mapping->update();
    
    gapp->mapperModuleFbo.begin();
    ofClear(0,0,0,255);
    
    ofPushMatrix();
    ofScale(fboW/fboDrawingW,fboH/fboDrawingH,1);
    ofTranslate(-fboDrawingPosX,-fboDrawingPosY,0);
        mapping->renderInsideFBO();
    ofPopMatrix();
    gapp->mapperModuleFbo.end();
    
}

//--------------------------------------------------------------
void gaMapperModule::draw(){
    if(gapp->switchMapperOutput || isON){
        ofBackground(0);
        ofSetColor(255,255,255);
        
        mapping->bind();
            // draw the output texture
            previewFbo.draw(fboDrawingPosX,fboDrawingPosY,fboDrawingW,fboDrawingH);
        mapping->unbind();
        
        mapping->draw();
        
        ofNoFill();
        ofRect(fboDrawingPosX,fboDrawingPosY,fboDrawingW,fboDrawingH);
        ofFill();
    }
}

//--------------------------------------------------------------
void gaMapperModule::setModuleON(bool onOff){
    isON = onOff;
}

//--------------------------------------------------------------
void gaMapperModule::getPreview(ofFbo p){
    if(gapp->switchMapperOutput || isON){
        previewFbo = p.getTextureReference();
    }
}

//--------------------------------------------------------------
void gaMapperModule::keyPressed(int key) { 
	mapping->keyPressed(key);
}

//--------------------------------------------------------------
void gaMapperModule::keyReleased(int key) { 
	
}

//--------------------------------------------------------------
void gaMapperModule::mouseMoved(int x, int y) { 
	mapping->mouseMoved(x,y);
}

//--------------------------------------------------------------
void gaMapperModule::mouseDragged(int x, int y, int button) {
	mapping->mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void gaMapperModule::mousePressed(int x, int y, int button) { 
	mapping->mousePressed(x,y,button);
}

//--------------------------------------------------------------
void gaMapperModule::mouseReleased() { 
	
}

//--------------------------------------------------------------
void gaMapperModule::mouseReleased(int x, int y, int button ){ 
	mapping->mouseReleased(x,y,button);
}

//--------------------------------------------------------------
void gaMapperModule::mouseScrolled(float x, float y) { 
	
}

