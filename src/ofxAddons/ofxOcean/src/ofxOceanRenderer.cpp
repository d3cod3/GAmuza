//
//  ofxOceanRenderer.cpp
//  NMMVisualizer
//
//  Created by Jim on 4/11/11.
//  Copyright 2011 FlightPhase. All rights reserved.
//


#include "ofxOceanRenderer.h"
#include "ofxOceanTile.h"

ofxOceanRenderer::ofxOceanRenderer()
{
	
    allocated = false;;
    ocean = NULL;
    max_LOD = 4;
	frameCount = 0;
	
//	reflectSquish = 1.0;
//	reflectOffset = ofVec2f(0,0);

}

ofxOceanRenderer::~ofxOceanRenderer()
{
//    if(bumpTexture != NULL){
//        delete bumpTexture;
//    }
    
    clearTiles();
}

void ofxOceanRenderer::clearTiles()
{
    if(allocated) {
        for(int LOD = 0; LOD < max_LOD; LOD++) {
            for(int k = 0; k < tiles_LOD[LOD].size(); k++) {
                delete tiles_LOD[LOD][k];
            }
        }
		tiles_LOD.clear();
    }
	allocated = false;
}

//extent of the whole ocean
float ofxOceanRenderer::getWidth()
{
	return tiles_x * ocean->size.x;
}

float ofxOceanRenderer::getHeight()
{
	return tiles_y * ocean->size.z;
}

void ofxOceanRenderer::setup(ofxOcean* o, int tilesWide, int tilesTall)
{
    
    clearTiles();

    ocean = o;
    tiles_x = tilesWide;
    tiles_y = tilesTall;
    vertexCount = ocean->vertexCount;
    
    for(int i = 0; i < max_LOD; i++){
        tiles_LOD.push_back(vector<ofxOceanTile*>());
    }

    
	ofxOceanTile* tile;
	for (int y = 0; y < tiles_y; y++) {
		for (int x = 0; x < tiles_x; x++) {
			int chDist = MAX(fabs(tiles_y/2 - y), fabs(tiles_x/2 - x));
			chDist = chDist > 0 ? chDist-1 : 0;
			int cy = y-tiles_y/2;
			int cx = x-tiles_x/2;
            
			tile = new ofxOceanTile();
			tile->position = ofVec3f(cx * ocean->size.x, -2.0 * chDist,  cy * ocean->size.z);
			tiles_LOD[chDist].push_back(tile);
		}
	}
        
	ofVec3f* verticesLOD;
    ofVec2f* uvLOD;
    int idx;
    int width = ocean->width;
    int height = ocean->height;
    int g_width = ocean->g_width;
    int g_height = ocean->g_height;
	for (int LOD = 0; LOD < max_LOD; LOD++) {
        int vcountLOD = (height/pow(float(2),float(LOD)) + 1) * (width/pow(float(2),float(LOD)) + 1);
		verticesLOD = new ofVec3f[vcountLOD];
		uvLOD = new ofVec2f[vcountLOD];
		idx = 0;
		
		for (int y = 0; y < g_height; y += pow(float(2),float(LOD) )) {
			for (int x = 0; x < g_width; x += pow(float(2),float(LOD))) {
				verticesLOD[idx] = ocean->getVertices()[g_width * y + x];
				uvLOD[idx++] = ocean->getUVs()[g_width * y + x];
			}			
		}
        
		for(int k = 0; k < tiles_LOD[LOD].size(); k++) {
			ofxOceanTile* tile = tiles_LOD[LOD][k];
            tile->vertexcount = vcountLOD;
            tile->vertices = new ofVec3f[vcountLOD];
            memcpy(tile->vertices, verticesLOD, sizeof(ofVec3f)*vcountLOD);
            tile->uvs = new ofVec2f[vertexCount];
            memcpy(tile->uvs, uvLOD, sizeof(ofVec2f)*vcountLOD);
            tile->tangents = new ofVec4f[vcountLOD];
            tile->normals = new ofVec3f[vcountLOD];
		}
        
        delete verticesLOD;
        delete uvLOD;
	}
	
	// Build triangle indices: 3 indices into vertex array for each triangle
	for (int LOD = 0; LOD < max_LOD; LOD++) {
		int index = 0;
        int denom_LOD = pow(float(2),float(LOD));
		int width_LOD = width / denom_LOD + 1;
        int indexCount = (height/denom_LOD) * (width/denom_LOD) * 6;
		GLuint* indeces = new GLuint[indexCount];
		for(int y = 0; y < height/denom_LOD; y++) {
			for(int x = 0; x < width/denom_LOD; x++) {
                
				// For each grid cell output two triangles
				indeces[index++] = (y     * width_LOD) + x;
				indeces[index++] = ((y+1) * width_LOD) + x;
				indeces[index++] = (y     * width_LOD) + x + 1;
				
				indeces[index++] = ((y+1) * width_LOD) + x;
				indeces[index++] = ((y+1) * width_LOD) + x + 1;
				indeces[index++] = (y     * width_LOD) + x + 1;
			}
		}
		
        for (int k = 0 ; k < tiles_LOD[LOD].size(); k++) {
            ofxOceanTile* tile = tiles_LOD[LOD][k];
            tile->indeces = new GLuint[indexCount];
            tile->indexcount = indexCount;
            memcpy(tile->indeces, indeces, sizeof(GLuint)*indexCount);
            tile->setup();
		}
        
        delete indeces;
	}
    
    allocated = true;
}

void ofxOceanRenderer::update()
{
    
    for(int LOD = 0; LOD < max_LOD; LOD++) {
		int den = pow(float(2), float(LOD) );
		int itemcount = (ocean->height/den+1) * (ocean->width/den+1);
        
        ofVec4f* tangentsLOD = new ofVec4f[itemcount]; 
        ofVec3f* verticesLOD = new ofVec3f[itemcount];
        ofVec3f* normalsLOD  = new ofVec3f[itemcount];
        
		int idx = 0;
		for (int y = 0; y < ocean->g_height; y += den) {
			for (int x = 0; x < ocean->g_width; x += den) {
				int idx2 = ocean->g_width * y + x;
				verticesLOD[idx] = ocean->getVertices()[idx2];
				tangentsLOD[idx] = ocean->getTangents()[idx2];
				normalsLOD[idx] = ocean->getNormals()[idx2];
                idx++;
			}
		}
        
		for(int k = 0; k < tiles_LOD[LOD].size(); k++) {
			ofxOceanTile* tile = tiles_LOD[LOD][k];
			memcpy(tile->vertices, verticesLOD, sizeof(ofVec3f)*itemcount);
			memcpy(tile->normals, normalsLOD, sizeof(ofVec3f)*itemcount);
			memcpy(tile->tangents, tangentsLOD, sizeof(ofVec4f)*itemcount);
            tile->update();
		}
        
        delete tangentsLOD;
        delete normalsLOD;
        delete verticesLOD;
	}
    
    frameCount++;
}

void ofxOceanRenderer::draw()
{
//	ofPushMatrix();
//	ofTranslate(ocean->cameraPosition);
	for(int LOD = 0; LOD < max_LOD; LOD++) {
        for(int k = 0; k < tiles_LOD[LOD].size(); k++) {
            ofxOceanTile* tile = tiles_LOD[LOD][k];
            tile->draw();
        }
    }
//	ofPopMatrix();
    
}

void ofxOceanRenderer::drawWireframe(){
    
//	ofPushMatrix();
//	ofTranslate(ocean->cameraPosition);
	
	for(int LOD = 0; LOD < max_LOD; LOD++) {
        for(int k = 0; k < tiles_LOD[LOD].size(); k++) {
            ofxOceanTile* tile = tiles_LOD[LOD][k];
            tile->drawWireframe();
        }
    }
// 	ofPopMatrix();
}

void ofxOceanRenderer::drawVertices(){
//	ofPushMatrix();
//	ofTranslate(ocean->cameraPosition);

	for(int LOD = 0; LOD < max_LOD; LOD++) {
        for(int k = 0; k < tiles_LOD[LOD].size(); k++) {
            ofxOceanTile* tile = tiles_LOD[LOD][k];
            tile->drawVertices();
        }
    }
    
//	ofPopMatrix();
}
