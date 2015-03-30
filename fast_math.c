#include "Talkthrough.h"

#define PI	3.141592654lk
#define double_PI	6.283185307lk

long fract fast_sin(long accum x){
	long fract y;
	int high_pow_x;
	
	//Is x between -PI and +PI?
	if(x>PI)
	{
		x=x-double_PI;
	}
	else if(x<-PI)
	{
		x=x+double_PI;
	}
	
	//This is necessary because accumulator only goes to 256.
	if(x>2.20815lk||x<-2.20815lk)
	{
		high_pow_x=(int)(x*x*x*x*x*x*x);
	}
	
	y=x-((x*x*x)/fast_factorial(3))+((x*x*x*x*x)/fast_factorial(5))-(high_pow_x/fast_factorial(7));
	return y;
}

long fract fast_cos(long accum x){
	long fract y;
	int high_pow_x;
	
	//Is x between -PI and +PI?
	if(x>PI)
	{
		x=x-double_PI;
	}
	else if(x<-PI)
	{
		x=x+double_PI;
	}
	
	//This is necessary because accumulator only goes to 256.
	if(x>2.51983lk||x<-2.51983lk)
	{
		high_pow_x=(int)(x*x*x*x*x*x);
	}
	
	y=1-((x*x)/fast_factorial(2))+((x*x*x*x)/fast_factorial(4))-(high_pow_x/fast_factorial(6));
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
