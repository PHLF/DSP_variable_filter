#include "Talkthrough.h"

fract32 fast_sin(long accum x){
	fract32 y;
	int x_pow_5;
	int x_pow_7;
	
	//Is x between -PI and +PI?
	if(x>PI)
	{
		x=x-double_PI;
	}
	else if(x<-PI)
	{
		x=x+double_PI;
	}
	
	//This is necessary because accumulator min and max values are -256 and 256.
	if(x<2.20817lk||x>-2.20817lk)
	{
		y=bitslk(x-((x*x*x)/fast_factorial(3))+((x*x*x*x*x)/fast_factorial(5))-(x*x*x*x*x*x*x/fast_factorial(7)));
	}
	else if(x>2.20817lk||x<-2.20817lk)
	{
		x_pow_7=(int)(x*x*x*x*x*x*x);
		y=bitslk(x-((x*x*x)/fast_factorial(3))+((x*x*x*x*x)/fast_factorial(5))-(x_pow_7/fast_factorial(7)));
	}
	else if(x>3.03143lk||x<-3.03143lk)
	{
		x_pow_5=(int)(x*x*x*x*x*x*x);
		x_pow_7=(int)(x*x*x*x*x*x*x);
		y=bitslk(x-((x*x*x)/fast_factorial(3))+(x_pow_5/fast_factorial(5))-(x_pow_7/fast_factorial(7)));
	}
	
	return y;
}

fract32 fast_cos(long accum x){
	fract32 y;
	int x_pow_6;
	
	//Is x between -PI and +PI?
	if(x>PI)
	{
		x=x-double_PI;
	}
	else if(x<-PI)
	{
		x=x+double_PI;
	}
	
	//This is necessary because accumulator min and max values are -256 and 256.
	if(x<2.51984lk||x>-2.51984lk)
	{
		y=bitslk(1-((x*x)/fast_factorial(2))+((x*x*x*x)/fast_factorial(4))-(x*x*x*x*x*x/fast_factorial(6)));
	}
	else if(x>2.51984lk||x<-2.51984lk)
	{
		x_pow_6=(int)(x*x*x*x*x*x);
		y=bitslk(1-((x*x)/fast_factorial(2))+((x*x*x*x)/fast_factorial(4))-(x_pow_6/fast_factorial(6)));
	}
	
	return y;
}

//Max unsigned int value for ASDP-BF533 is 4294967295.
unsigned int fast_factorial(unsigned short i){
	unsigned int array_factorial[13]={
		1,
		1,
		2,
		6,
		24,
		120,
		720,
		5040,
		40320,
		362880,
		3628800,
		39916800,
		479001600};

		return array_factorial[i];
}
