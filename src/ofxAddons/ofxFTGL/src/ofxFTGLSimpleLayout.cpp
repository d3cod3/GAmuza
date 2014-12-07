#include "ofxFTGLSimpleLayout.h"

ofxFTGLSimpleLayout::ofxFTGLSimpleLayout()
: ofxFTGLFont()
{
    layout = NULL;
}

ofxFTGLSimpleLayout::~ofxFTGLSimpleLayout()
{
//	unload();
}

void ofxFTGLSimpleLayout::unload()
{
    ofxFTGLFont::unload();
    
    if (layout != NULL) {
        delete layout;
        layout = NULL;
    }
}

bool ofxFTGLSimpleLayout::loadFont(string filename, float fontsize, float depth, bool bUsePolygons)
{
    if (ofxFTGLFont::loadFont(filename, fontsize, depth, bUsePolygons)) {
        layout = new FTSimpleLayout();
        layout->SetFont(font);
    
        return true;
    }
    
    return false;
}

float ofxFTGLSimpleLayout::getLineLength() const
{
	return layout->GetLineLength();
}

void ofxFTGLSimpleLayout::setLineLength(float length)
{
    layout->SetLineLength(length);
}

float ofxFTGLSimpleLayout::getLineSpacing() const
{
	return layout->GetLineSpacing();
}

void ofxFTGLSimpleLayout::setLineSpacing(float spacing)
{
    layout->SetLineSpacing(spacing);
}

ofxFTGLTextAlignment ofxFTGLSimpleLayout::getAlignment() const
{
    return layout->GetAlignment();
}

void ofxFTGLSimpleLayout::setAlignment(ofxFTGLTextAlignment alignment)
{
    layout->SetAlignment(alignment);
}

ofRectangle ofxFTGLSimpleLayout::getStringBoundingBox(string s, float x, float y)
{
    if (loaded) {
    	FTBBox bbox = layout->BBox(s.c_str());
	    return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
    }
	return ofRectangle();
}

ofRectangle ofxFTGLSimpleLayout::getStringBoundingBox(wstring s, float x, float y)
{
    if (loaded) {
    	FTBBox bbox = layout->BBox((wchar_t*)s.c_str());
	    return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
    }
	return ofRectangle();
}

void ofxFTGLSimpleLayout::drawString(string s, float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1,-1,1);
    layout->Render(s.c_str());
    glPopMatrix();
}

void ofxFTGLSimpleLayout::drawString(wstring s, float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1,-1,1);
    layout->Render((wchar_t*)s.c_str());
    glPopMatrix();
}
