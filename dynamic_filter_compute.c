#include "Talkthrough.h"

void filter_coeffs(fract coef[], signed int fc)
{
	short i;
	short M;
	fract ft;
	
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
			coef[i]=fast_sin(double_PI*ft*(i-(M/2)))/(PI*(M/2));
		}
	}
	
	// Hamming window weights computation.
	for(i=0;i<=TAPS;i++)
	{
		coef[i]=coef[i]*(0.54r-0.46r*fast_cos((long accum)((double_PI*i)/M)));
	}
}
