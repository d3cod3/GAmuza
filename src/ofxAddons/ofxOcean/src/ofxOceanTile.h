/*
 *  ofxOceanTile.h
 *  NMMOcean
 *
 *  Created by James George on 3/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class ofxOceanTile
{
  public:
    
    ofxOceanTile();
    ~ofxOceanTile();
    
    void setup();
    void update();
    void draw();
    void drawWireframe();
    void drawVertices();
	
	ofVec3f position;
    
    int vertexcount;
    int indexcount;
    //GLint tangentAttributeLoc;
    
    ofVbo* mesh;
    
    //placeholder
    ofColor* colors;
    
    ofVec3f* vertices;
    ofVec3f* normals;    
    ofVec2f* uvs;
    ofVec4f* tangents;
    GLuint* indeces;
};