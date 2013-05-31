#ifndef _GADSP
#define _GADSP


#include "ofMain.h"
// constants
#include "gamuzaConstants.h"


class gaDsp{
	
	public:
		
		gaDsp();
		~gaDsp();
		
		void		setupDSP(int _nChannels);
		void		clearBuffer(float* _buffer, int _bufferSize);
		void		removeDC(float* _buffer, int _bufferSize);
	
		void		addOsc();
		void		addOsc(int _ch);
		void		resetOsc();
	
		int			*numOscInCh;
		int			numChannels;
	
		float		*dc;
		float		*dc1;
		float		*dc2;
		int			count1;
		int			count2;
	
};

#endif	