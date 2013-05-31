#ifndef _MATRIX_AREAS
#define _MATRIX_AREAS


#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "gamuzaConstants.h"

class matrixAreas{

	public:

		matrixAreas();
		matrixAreas(int w, int h);


		int _width, _height;
	
		float scalew, scaleh;
	
		int numAreas;
	
		int resOrigin;

		ofPoint					*points;
		float					*diameters;
		bool					*imOver;
		
		ofTrueTypeFont		automatFont;

		//--------------------------------------------------------
		void setup(float x, float y, float w, float h, int _nAreas);
		void reset(float w, float h);
    
        void update(bool manualEdit,int actualPoint);

		float 		xCalib, yCalib, wCalib, hCalib;
		int 		pointBeingCalibrated;
		int			diameterBeingCalibrated;
		int			areaON;
		
		
		void 		mouseMoved(float x, float y);
		void 		mousePressed(float x, float y);
		void 		mouseDragged(float x, float y);
		void 		mouseReleased(float x, float y);
		
		void		isPointInside(float x, float y);
		//--------------------------------------------------------

		void loadSettings(string filename_);
		void saveSettings(string filename_);


		void draw();
		void draw(bool* _areas);
		void drawMinimal();
		void drawMinimalWithLines();
		void drawMinimalGrid();
        void drawMinimalGrid(int pX, int pY);



};

#endif
