
#include "gaVideoPreview.h"


//--------------------------------------------------------------
gaVideoPreview::gaVideoPreview(){
    fboW        = 320;
    fboH        = 240;
    previewW    = 320;
    previewH    = 240;
}

//--------------------------------------------------------------
gaVideoPreview::~gaVideoPreview(){
    
}

//--------------------------------------------------------------
void gaVideoPreview::resetPreview(){
    if(fboW < previewW){
        fboDrawingW         = (fboW*previewH)/fboH;
        fboDrawingH         = previewH;
        fboDrawingPosX      = (previewW-fboDrawingW)/2.0;
        fboDrawingPosY      = 0;
    }else{
        fboDrawingW         = previewW;
        fboDrawingH         = (fboH*previewW)/fboW;
        fboDrawingPosX      = 0;
        fboDrawingPosY      = (previewH-fboDrawingH)/2.0;
    }
    
    previewFbo.allocate(fboW,fboH,GL_RGBA);
}

//--------------------------------------------------------------
void gaVideoPreview::setFboDim(int w, int h){
    fboW = w;
    fboH = h;
    
    resetPreview();
}

//--------------------------------------------------------------
void gaVideoPreview::setPreviewDim(int w, int h){
    
    previewW = w;
    previewH = h;
    
    if(fboW < previewW){
        fboDrawingW         = (fboW*previewH)/fboH;
        fboDrawingH         = previewH;
        fboDrawingPosX      = (previewW-fboDrawingW)/2.0;
        fboDrawingPosY      = 0;
    }else{
        fboDrawingW         = previewW;
        fboDrawingH         = (fboH*previewW)/fboW;
        fboDrawingPosX      = 0;
        fboDrawingPosY      = (previewH-fboDrawingH)/2.0;
    }
}

//--------------------------------------------------------------
void gaVideoPreview::setup(){
    ofSetWindowShape(previewW,previewH);
    
    resetPreview();
}

//--------------------------------------------------------------
void gaVideoPreview::update() {
	

}

//--------------------------------------------------------------
void gaVideoPreview::draw() {
	ofBackground(0);
    ofSetColor(255,255,255);
	previewFbo.draw(fboDrawingPosX,fboDrawingPosY,fboDrawingW,fboDrawingH);
}

void gaVideoPreview::getPreview(ofFbo p){
    previewFbo = p.getTextureReference();
}

//--------------------------------------------------------------
void gaVideoPreview::keyPressed(int key) { 
	
}

//--------------------------------------------------------------
void gaVideoPreview::keyReleased(int key) { 
	
}

//--------------------------------------------------------------
void gaVideoPreview::mouseMoved(int x, int y) { 
	
}

//--------------------------------------------------------------
void gaVideoPreview::mouseDragged(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void gaVideoPreview::mousePressed(int x, int y, int button) { 
	
}

//--------------------------------------------------------------
void gaVideoPreview::mouseReleased() { 
	
}

//--------------------------------------------------------------
void gaVideoPreview::mouseReleased(int x, int y, int button ){ 
	
}

//--------------------------------------------------------------
void gaVideoPreview::mouseScrolled(float x, float y) { 
	
}

