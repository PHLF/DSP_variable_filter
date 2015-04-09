#include "Talkthrough.h"

void filter_coeffs(fract16 coef[], signed int fc)
{
	short i;
	short M;
	
	long accum phase;
	fract16 ft;
	
	M=TAPS-1;
	ft=fc/sampling_freq;
	
	// Sinc weights computation
	for(i=0;i<=TAPS;i++)
	{
		if(i==(M/2))
		{
			coef[i]=2*ft;
		}
		else if(i!=(M/2))
		{
			phase=double_PI*lkbits(ft*(i-(M/2))/(PI*(M/2)));
			coef[i]=fast_sin(phase);
		}
	}
	
	// Hamming window weights computation.
	for(i=0;i<=TAPS;i++)
	{
		phase=(double_PI*i)/M;
		coef[i]=coef[i]*0.54-0.46*fast_cos(phase);
	}
}
