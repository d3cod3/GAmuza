#pragma once

#include "ofMain.h"
#include "ftgl.h"

class ofxFTGLFont
{    
    public:
        ofxFTGLFont();
        ~ofxFTGLFont();

        virtual void unload();
        virtual bool loadFont(string filename, float fontsize, float depth = 0, bool bUsePolygons = false);
        bool isLoaded();

        void setSize(int size);
        int getSize();
    
        void setTracking(float tracking);
        float getTracking() const;

        float getLineHeight() const;
        float getAscender() const;
        float getDescender() const;
        float getXHeight() const;

        virtual ofRectangle getStringBoundingBox(wstring s, float x, float y);
        virtual ofRectangle getStringBoundingBox(string s, float x, float y);
        float stringHeight(string c);
        float stringWidth(string c);
		float getSpaceSize();
        virtual void drawString(wstring s, float x, float y);
        virtual void drawString(string s, float x, float y);

        FTFont* font;
    
    protected:
        bool loaded;
        FTPoint trackingPoint;
};

