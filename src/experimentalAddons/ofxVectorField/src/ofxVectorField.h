
// ----------------------------------------------------------------
// ofxVectorField
// a vector field generator & animator
// by Jeremy Rotsztain
// http://www.manitssa.ca
// ----------------------------------------------------------------

#ifndef OFX_VECTOR_FIELD
#define OFX_VECTOR_FIELD

#include "ofMain.h"

#define OFX_VECFIELD_DEFALT_SPACING			5

class ofxVectorField {
	
public:
	
	ofxVectorField();
	~ofxVectorField();
	
	void setup(int w, int h, int spacing);
	void deallocate();
	
	// draw for debugging
	void draw();

	// creating the vector field
	void setFromImage(ofImage & image);
	void randomize();
	void animate(float speed = 0.002);
	
	// getting values from the vector field
	ofVec2f getVector(int x, int y);
	ofVec2f getVectorInterpolated(int x, int y, int gridW, int gridH);
	
	// adjusting the vector field
	void normalize(bool individually=false);
	void map(float min, float max, bool normalize);
	void scale(float amt);
	void bias(float amt);
	void bias(float xAmt, float yAmt);
	void blur();
	void smudge(ofVec2f pos, ofVec2f vector);
	
	int width, height;
	
private:

	ofVec2f * vectorField;

	int spacing;
	int numElements;
	
	bool bIsAllocated;
};

#endif