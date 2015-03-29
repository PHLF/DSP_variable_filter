#include "Talkthrough.h"

//--------------------------------------------------------------------------//
// Function:	Sport0_RX_ISR												//
//																			//
// Description: This ISR is executed after a complete frame of input data 	//
//				has been received. The new samples are stored in 			//
//				iChannel0LeftIn, iChannel0RightIn, iChannel1LeftIn and 		//
//				iChannel1RightIn respectively.  Then the function 			//
//				Process_Data() is called in which user code can be executed.//
//				After that the processed values are copied from the 		//
//				variables iChannel0LeftOut, iChannel0RightOut, 				//
//				iChannel1LeftOut and iChannel1RightOut into the dma 		//
//				transmit buffer.											//
//--------------------------------------------------------------------------//
EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{

	static int index = 0;
	
	// confirm interrupt handling
	*pDMA1_IRQ_STATUS = 0x0001;

	
	// call function that contains user code
	if (index == 0)
	{
		Process_Data();
	}				

	sChannel0RightIn[index] = sRxBuffer[INTERNAL_ADC_R0];
	sChannel0LeftIn[index] = sRxBuffer[INTERNAL_ADC_L0];
	

	// copy processed data from variables into dma output buffer
	sTxBuffer[INTERNAL_DAC_L0] = sChannel0LeftOut[index];
	sTxBuffer[INTERNAL_DAC_R0] = sChannel0RightOut[index];

	
	//increment the array index and wait for the next sample to arrive
	index = circindex(index, 1, BUFFER_SIZE);
}


