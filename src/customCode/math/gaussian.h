#ifndef GAUSSIAN
#define GAUSSIAN

#include "ofMain.h"
 
// <http://en.wikipedia.org/wiki/Gaussian_function>
// The graph of a Gaussian is a characteristic symmetric "bell curve"
// shape that quickly falls off towards plus/minus infinity.
// The parameter a (amplitude) is the height of the curve's peak, b (center) is the
// position of the centre of the peak, and c (width) controls the width of the "bell".                                                                                             
float gaussianFn(float x, float amplitude, float center, float width);                                                                                                  
 
#endif

