//
//  ofxOceanRenderer.h
//  NMMVisualizer
//
//  Created by Jim on 4/11/11.
//  Copyright 2011 FlightPhase. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxOcean.h"

class ofxOceanTile;
class ofxOceanRenderer
{
  public:
    ofxOceanRenderer();
    ~ofxOceanRenderer();
    
	ofVec3f cameraPosition;
	
    //ocean must already be initialized. # of tiles set level of detail
    void setup(ofxOcean* ocean, int tilesWide, int tilesTall);
    void setup(int tilesWide, int tilesTall);
    void update();
	
    void draw(); //uses shader
    void drawWireframe();
    void drawVertices();
	
    void clearTiles();

	//extent of the whole ocean
	float getWidth();
	float getHeight();
	
    int vertexCount;
	int frameCount;
  protected:
    
    ofxOcean* ocean;
    bool allocated;

    int max_LOD;
	vector< vector<ofxOceanTile*> > tiles_LOD;
    
    int tiles_x;
    int tiles_y;        
};
