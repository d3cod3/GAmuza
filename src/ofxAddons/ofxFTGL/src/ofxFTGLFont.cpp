#include "ofxFTGLFont.h"

ofxFTGLFont::ofxFTGLFont()
{
    loaded = false;
    font = NULL;
}

ofxFTGLFont::~ofxFTGLFont()
{
//	unload();
}

void ofxFTGLFont::unload()
{
    if (font != NULL) {
        delete font;
        font = NULL;
    }
    
    loaded = false;
}

bool ofxFTGLFont::loadFont(string filename, float fontsize, float depth, bool bUsePolygons)
{
	unload();
    
    fontsize *= 2;
    
    if (depth != 0) {
        font = new FTExtrudeFont(ofToDataPath(filename).c_str());
        font->Depth(depth);
    }
    else if (bUsePolygons) {
        font = new FTPolygonFont(ofToDataPath(filename).c_str());
    }
    else {
        font = new FTTextureFont(ofToDataPath(filename).c_str());
    }
    
    font->CharMap(ft_encoding_unicode);

    if(font->Error()){
        ofLogError("ofxFTGLFont") << "Error loading font " << filename;
        delete font;
		return false;
    }    
    
    if(!font->FaceSize(fontsize)){
        ofLogError("ofxFTGLFont") << "Failed to set font size";
        delete font;
		return false;
    }
    
    loaded = true;
    return true;
}

float ofxFTGLFont::getSpaceSize(){
	return stringWidth(" ");
}

float ofxFTGLFont::stringWidth(string c)
{
    if (c.compare(" ") == 0) {
        // FTGL won't measure a space width properly, so we
        // have to use this hack to get that value.
        return (stringWidth("A A") - stringWidth("AA"));
    }
    else {
        ofRectangle rect = getStringBoundingBox(c, 0,0);
        return rect.width;
    }
}

float ofxFTGLFont::stringHeight(string c) {
    ofRectangle rect = getStringBoundingBox(c, 0,0);
    return rect.height;
}

bool ofxFTGLFont::isLoaded(){
    return loaded;
}

void ofxFTGLFont::setSize(int size){
    if(loaded){
	    font->FaceSize(size);
    }
}

int ofxFTGLFont::getSize(){
	return font->FaceSize();
}

void ofxFTGLFont::setTracking(float tracking)
{
    trackingPoint.X(tracking);
}

float ofxFTGLFont::getTracking() const
{
    return trackingPoint.Xf();
}

float ofxFTGLFont::getLineHeight() const
{
    if (loaded) {
        return font->LineHeight();
    }
    return 0;
}

float ofxFTGLFont::getAscender() const
{
    if (loaded) {
        return font->Ascender();
    }
    return 0;
}

float ofxFTGLFont::getDescender() const
{
    if (loaded) {
        return font->Descender();
    }
    return 0;
}

float ofxFTGLFont::getXHeight() const
{
    if (loaded) {
        return font->LineHeight() - font->Ascender() - font->Descender();
    }
    return 0;
}

ofRectangle ofxFTGLFont::getStringBoundingBox(string s, float x, float y){
    if(loaded){
    	FTBBox bbox = font->BBox(s.c_str(), -1, FTPoint(), trackingPoint);
	    return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
    }
	return ofRectangle();
}

ofRectangle ofxFTGLFont::getStringBoundingBox(wstring s, float x, float y){
    if(loaded){
    	FTBBox bbox = font->BBox((wchar_t*)s.c_str(), -1, FTPoint(), trackingPoint);
	    return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
    }
	return ofRectangle();
}

void ofxFTGLFont::drawString(string s, float x, float y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1,-1,1);

    font->Render(s.c_str(), -1, FTPoint(), trackingPoint);
    glPopMatrix();
}

void ofxFTGLFont::drawString(wstring s, float x, float y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1,-1,1);
    font->Render((wchar_t*)s.c_str(), -1, FTPoint(), trackingPoint);
    glPopMatrix();
}
