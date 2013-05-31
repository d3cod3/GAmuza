#include "gaDsp.h"


//--------------------------------------------------------------
gaDsp::gaDsp(){
	count1 = 0;
	count2 = 0;
	
}

//--------------------------------------------------------------
gaDsp::~gaDsp(){
	
}

//--------------------------------------------------------------
void gaDsp::setupDSP(int _nChannels){
	
	numChannels = _nChannels;
	
	dc1 = new float[numChannels];
	dc2 = new float[numChannels];
	
	memset(&dc, 0.0, numChannels*2 * sizeof(float));
	memset(&dc1, 0.0, numChannels * sizeof(float));
	memset(&dc2, 0.0, numChannels * sizeof(float));
	
	
	numOscInCh = new int[numChannels];
	resetOsc();
}

//--------------------------------------------------------------
void gaDsp::clearBuffer(float* _buffer, int _bufferSize){
	while(_bufferSize--)
	{
		*_buffer++	= DENORMAL_BUFFER;
		*_buffer++	= DENORMAL_BUFFER;		
	}
}

//--------------------------------------------------------------
void gaDsp::removeDC(float* _buffer, int _bufferSize){
	
	count1 = 0;
	count2 = 0;
	
	for(int c=0;c<numChannels;c++){
		if(c%2==0){
			dc1[count1] = dc[c];
			count1++;
		}else{
			dc2[count2] = dc[c];
			count2++;
		}
	}
	
	float	in;
	
	while(_bufferSize--)
	{
		in			= *_buffer;
		
		for(int c=0;c<numChannels;c++){
			dc1[c]		= 0.999999 * dc1[c] + in - dc2[c];
			dc2[c]		= in;
			*_buffer++	= dc1[c];
		}
		
	}
	
	count1 = 0;
	count2 = 0;
	
	for(int c=0;c<numChannels;c++){
		if(c%2==0){
			dc[c] = dc1[count1];
			count1++;
		}else{
			dc[c] = dc2[count2];
			count2++;
		}
	}
	
}

//--------------------------------------------------------------
void gaDsp::addOsc(){
	for(int c=0;c<numChannels;c++){
		numOscInCh[c] = numOscInCh[c]+1;
	}
}

//--------------------------------------------------------------
void gaDsp::addOsc(int _ch){
	numOscInCh[_ch] = numOscInCh[_ch]+1;
}

//--------------------------------------------------------------
void gaDsp::resetOsc(){
	for(int c=0;c<numChannels;c++){
		numOscInCh[c] = 0;
	}
}
