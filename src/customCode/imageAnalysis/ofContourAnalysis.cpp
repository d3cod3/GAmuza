#include "ofContourAnalysis.h"


//-----------------------------------------
float getOrientation( vector <ofPoint> & contour )
{
    CvMoments* myMoments = (CvMoments*)malloc( sizeof(CvMoments) );

    // Allocate storage
    CvMemStorage*   storage = cvCreateMemStorage(0);
    CvSeq* seq = cvCreateSeq( CV_SEQ_POLYGON, sizeof(CvContour),sizeof(CvPoint), storage );


    for(unsigned int i = 0; i < contour.size(); i++)
    {
        CvPoint pt = cvPoint(contour[i].x,contour[i].y);
        cvSeqPush( seq, &pt );
    }

    cvMoments( seq, myMoments );

    double cm20 = cvGetCentralMoment(myMoments, 2, 0);
    double cm02 = cvGetCentralMoment(myMoments, 0, 2);
    double cm11 = cvGetCentralMoment(myMoments, 1, 1);

    if (cm11 == 0.0f) cm11 = 0.00001f;
    float d = (cm20 - cm02);
    float b = d/cm11;
    float quadratic = ((-1.0f*b) + sqrtf(b*b + 4.0f))/2.0f;
    float theta = atanf(quadratic);

    if (((d < 0) && (quadratic < 1.0f)) ||
        ((d > 0) && (quadratic > 1.0f))) { theta += HALF_PI;}

    // Free the storage memory.
	// Warning: do this inside this function otherwise you get a strange memory leak
	if (storage != NULL){
		cvReleaseMemStorage(&storage);
	}

    free(myMoments);

    return theta;
}

//-----------------------------------------
int getIndexOfBlobIAmIn( vector<ofxCvBlob> & blobs, ofPoint pt )
{
    for(unsigned int i = 0; i < blobs.size(); i++)
    {
        if( isPointInsideMe( pt.x, pt.y, blobs[i].pts) )
            return i;
    }

    return -1;

}
//-----------------------------------------
bool isPointInsideMe(float x, float y, vector <ofPoint>  & pts)
{

	// code via Zach Lieberman via Randolph Franklin...
	int i, j, c = 0;
	int nPts = pts.size();

	for (i = 0, j = nPts-1; i < nPts; j = i++) {
	if ((((pts[i].y <= y) && (y < pts[j].y)) ||
	     ((pts[j].y <= y) && (y < pts[i].y))) &&
	    (x < (pts[j].x - pts[i].x) * (y - pts[i].y) / (pts[j].y - pts[i].y) + pts[i].x))
	  c = !c;
	}
	return (bool) c;
}
//-----------------------------------------
void fitEllipse( vector <ofPoint>  & contour, CvBox2D32f & box )
{

    CvPoint2D32f* pointArray;

    // Alloc memory for contour point set.
    pointArray = (CvPoint2D32f*)malloc( contour.size()*sizeof(CvPoint2D32f) );

    for(unsigned int i = 0; i < contour.size(); i++)
    {
    	pointArray[i].x = 	contour[i].x;
    	pointArray[i].y =	contour[i].y;

    }

	// Fit ellipse
    cvFitEllipse(pointArray, contour.size(), &box);
    free(pointArray);


}

void drawBlob( float x, float y, ofxCvBlob & blob ) {


	// ---------------------------- draw the bounding rectangle
    glPushMatrix();
    glTranslatef( x, y, 0.0 );


	// ---------------------------- draw the blobs
	ofBeginShape();

    for( int j=0; j<blob.nPts; j++ )
    {
        ofVertex( blob.pts[j].x, blob.pts[j].y );
    }

    ofEndShape();


	glPopMatrix();
}



void findLines(vector <ofPoint>  & pts, vector<ofVec4f> & lines, float angleThreshold,float minLen, int res)
{

        //float   angleLast   = 0.f;
        //float   angle       = 0.f;
        int     startPt     = pts.size()-1;
        int     lastPt      = pts.size()-1;

        lines.clear();

        if( pts.size() > (unsigned int)res)
        {

            ofVec2f lineAB, lineCB;

            for( int i = pts.size()-1; i >= 0; i-= res)
            {

                ofVec2f ptA = ofVec2f( pts[startPt].x, pts[startPt].y ) ;
                ofVec2f ptB = ofVec2f( pts[lastPt].x, pts[lastPt].y ) ;
                ofVec2f ptC = ofVec2f( pts[i].x, pts[i].y ) ;

                lineAB = ptB - ptA;
                lineCB = ptC - ptB;

                lineAB = lineAB.normalized();
                lineCB = lineCB.normalized();

                float dot   = lineAB.x * lineCB.x + lineAB.y * lineCB.y;
                float cross = lineAB.x * lineCB.y - lineAB.y * lineCB.x;
                float theta = acos(dot);
                if (cross < 0) { theta = 0-theta; }

                if( theta > DEG_TO_RAD*angleThreshold )
                {
                    float len = (ptA - ptB).length();
                    if( len > minLen )
                        lines.push_back( ofVec4f( pts[startPt].x, pts[startPt].y, pts[lastPt].x, pts[lastPt].y ) );
                    startPt = lastPt;
                    lastPt = i;
                }else
                {
                    lastPt = i;
                }



            }

            lines.push_back( ofVec4f( pts[startPt].x, pts[startPt].y, pts[lastPt].x, pts[lastPt].y ) );



        }


}
