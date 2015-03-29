#include "Talkthrough.h"

//--------------------------------------------------------------------------//
// Function:	Process_Data()												//
//																			//
// Description: This function is called from inside the SPORT0 ISR every 	//
//				time a complete audio frame has been received. The new 		//
//				input samples can be found in the variables iChannel0LeftIn,//
//				iChannel0RightIn, iChannel1LeftIn and iChannel1RightIn 		//
//				respectively. The processed	data should be stored in 		//
//				iChannel0LeftOut, iChannel0RightOut, iChannel1LeftOut,		//
//				iChannel1RightOut, iChannel2LeftOut and	iChannel2RightOut	//
//				respectively.												//
//--------------------------------------------------------------------------//
void Process_Data(void)
{
	int i;

	// Comment lines below as required (talkthrough or filterin)

	
	// Process loopback
	
	for (i=0; i<BUFFER_SIZE; i++)
	{
		sChannel0RightOut[i] = sChannel0RightIn[i];
		sChannel0LeftOut[i] = sChannel0LeftIn[i];
	}
	
	
	// Or process FIR filter
	//fir_fr16(sChannel0RightIn, sChannel0RightOut, BUFFER_SIZE, &stateR);
	
	
	//fir_fr16(sChannel0LeftIn, sChannel0LeftOut, BUFFER_SIZE, &stateL);
}
