#ifndef ADAPTIVE_SIMPSON
#define ADAPTIVE_SIMPSON

#include "ofMain.h"
 
//
// Recursive auxiliary function for adaptiveSimpsons() function below
//                                                                                                 
double adaptiveSimpsonsAux(double (*f)(double), double a, double b, double epsilon,double S, double fa, double fb, double fc, int bottom);
 
//
// Adaptive Simpson's Rule
//
double adaptiveSimpsons(double (*f)(double),   // ptr to function
                           double a, double b,  // interval [a,b]
                           double epsilon,  // error tolerance
                           int maxRecursionDepth);                                                                                                  
 
#endif

/* USAGE EXAMPLE

 double I = adaptiveSimpsons(sin, 0, 1, 0.000000001, 10); // compute integral of sin(x)
                                                          // from 0 to 1 and store it in 
                                                          // the new variable I
*/

