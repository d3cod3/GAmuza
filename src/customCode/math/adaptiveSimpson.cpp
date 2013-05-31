
#include "adaptiveSimpson.h"

//--------------------------------------------------
// Recursive auxiliary function for adaptiveSimpsons() function below
//                                                                                                 
double adaptiveSimpsonsAux(double (*f)(double), double a, double b, double epsilon,double S, double fa, double fb, double fc, int bottom) {
  double c = (a + b)/2, h = b - a;                                                                  
  double d = (a + c)/2, e = (c + b)/2;                                                              
  double fd = f(d), fe = f(e);                                                                      
  double Sleft = (h/12)*(fa + 4*fd + fc);                                                           
  double Sright = (h/12)*(fc + 4*fe + fb);                                                          
  double S2 = Sleft + Sright;                                                                       
  if (bottom <= 0 || fabs(S2 - S) <= 15*epsilon){                                                   
    return S2 + (S2 - S)/15;
  }
  return adaptiveSimpsonsAux(f, a, c, epsilon/2, Sleft,  fa, fc, fd, bottom-1) + adaptiveSimpsonsAux(f, c, b, epsilon/2, Sright, fc, fb, fe, bottom-1);
}         
 
//--------------------------------------------------
// Adaptive Simpson's Rule
//
double adaptiveSimpsons(double (*f)(double),double a, double b,double epsilon,int maxRecursionDepth) {     
  double c = (a + b)/2, h = b - a;                                                                  
  double fa = f(a), fb = f(b), fc = f(c);                                                           
  double S = (h/6)*(fa + 4*fc + fb);                                                                
  return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fc, maxRecursionDepth);                   
}