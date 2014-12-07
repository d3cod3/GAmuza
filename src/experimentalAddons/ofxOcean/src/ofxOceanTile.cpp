/*
 *  ofxOceanTile.cpp
 *  NMMOcean
 *
 *  Created by James George on 3/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxOceanTile.h"

ofxOceanTile::ofxOceanTile()
{
	mesh = new ofVbo();
    vertices = NULL;
    tangents = NULL;
    uvs = NULL;
    indeces = NULL;
}
 
 
ofxOceanTile::~ofxOceanTile()
{
    delete mesh;
    
    delete[] vertices;
    delete[] normals;
    delete[] uvs;
    delete[] indeces;
    delete[] tangents;
}

void ofxOceanTile::setup()
{
	
    mesh->setVertexData(vertices, vertexcount, GL_DYNAMIC_DRAW);
    mesh->setNormalData(normals, vertexcount, GL_DYNAMIC_DRAW);
    mesh->setTexCoordData(uvs, vertexcount, GL_STATIC_DRAW);
    mesh->setIndexData(indeces, indexcount, GL_STATIC_DRAW);
    
    
//    mesh->setAttributeData(tangentAttributeLoc, tangents, vertexcount, GL_DYNAMIC_DRAW);
}

void ofxOceanTile::update()
{
    for(int i = 0; i < vertexcount; i++){
        vertices[i] += position;
    }
    
    mesh->updateVertexData(vertices, vertexcount);
    mesh->updateNormalData(normals, vertexcount);
//    mesh->updateAttributeData(tangents, vertexcount);
    
}

void ofxOceanTile::draw()
{    
    //mesh->drawElements(GL_TRIANGLE_STRIP, indexcount);
    mesh->drawElements(GL_TRIANGLES, indexcount);
}

void ofxOceanTile::drawWireframe(){
	mesh->drawElements(GL_LINES, indexcount);
	
}

void ofxOceanTile::drawVertices(){
	mesh->drawElements(GL_POINTS, indexcount);
}

