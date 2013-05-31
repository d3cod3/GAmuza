#include "gaussian.h"

//--------------------------------------------------                                                                                                
float gaussianFn(float x, float amplitude, float center, float width){
	float base = (x - center) / width; // divide top by bottom  
	base *= base * -.5; // square top and bottom, multiply by -1/2  
	base = exp(base); // take pow(e, base)  
	return amplitude * base;
}