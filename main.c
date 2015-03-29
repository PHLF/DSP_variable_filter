//--------------------------------------------------------------------------//
//																			//
//	 Name: 	Talkthrough for the ADSP-BF533 EZ-KIT Lite						//
//																			//
//--------------------------------------------------------------------------//
//																			//
//	(C) Copyright 2006 - Analog Devices, Inc.  All rights reserved.			//
//																			//
//	Project Name:	BF533 C Talkthrough I2S									//
//																			//
//	Date Modified:	04/03/03		Rev 1.0							//
//																			//
//	Software:		VisualDSP++4.5											//
//																			//
//	Hardware:		ADSP-BF533 EZ-KIT Board									//
//																			//
//	Connections:	Connect RSCLK0 to TSCLK0 together (Turn SW9 pin 6 on)	//
//					Connect RFS0 to TFS0 together (Turn SW9 pin 5 ON)		//					Connect an input source (such as a radio) to the Audio	//
//					input jack and an output source (such as headphones) to //
//					the Audio output jack									//
//																			//
//	Purpose:		This program sets up the SPI port on the ADSP-BF533 to  //
//					configure the AD1836 codec.  The SPI port is disabled 	//
//					after initialization.  The data to/from the codec are 	//
//					transfered over SPORT0 in I2S mode						//
//																			//
//--------------------------------------------------------------------------//

#include "Talkthrough.h"
#include "sysreg.h"
#include "ccblkfn.h"


//--------------------------------------------------------------------------//
// Variables																//
//																			//
// Description:	The variables sChannelxLeftIn and sChannelxRightIn contain 	//
//				the data coming from the codec AD1836.  The (processed)		//
//				playback data are written into the variables 				//
//				sChannelxLeftOut and sChannelxRightOut respectively, which 	//
//				are then sent back to the codec in the SPORT0 ISR.  		//
//				The values in the array iCodec1836TxRegs can be modified to //
//				set up the codec in different configurations according to   //
//				the AD1836 data sheet.										//
//--------------------------------------------------------------------------//
// left input data from ad1836
short sChannel0LeftIn[BUFFER_SIZE];
// right input data from ad1836
short sChannel0RightIn[BUFFER_SIZE];

// left output data for ad1836	
short sChannel0LeftOut[BUFFER_SIZE];
// right output data for ad1836
short sChannel0RightOut[BUFFER_SIZE];



// array for registers to configure the ad1836
// names are defined in "Talkthrough.h"
volatile short sCodec1836TxRegs[CODEC_1836_REGS_LENGTH] =
{									
					DAC_CONTROL_1	| 0x010, // 16bit data width DAC 
					DAC_CONTROL_2	| 0x000,
					DAC_VOLUME_0	| 0x3ff,
					DAC_VOLUME_1	| 0x3ff,
					DAC_VOLUME_2	| 0x3ff,
					DAC_VOLUME_3	| 0x3ff,
					DAC_VOLUME_4	| 0x000,
					DAC_VOLUME_5	| 0x000,
					ADC_CONTROL_1	| 0x000,
					ADC_CONTROL_2	| 0x020, // 16bit data width ADC
					ADC_CONTROL_3	| 0x000
					
};
// SPORT0 DMA transmit buffer
volatile short sTxBuffer[2];
// SPORT0 DMA receive buffer
volatile short sRxBuffer[2];



fract16 delayL[TAPS]={0};
fract16 delayR[TAPS]={0};

fract16 coef[TAPS] = {
	// low-pass
	// #include "coef32_low2_158taps.dat"
	#include "coef32.dat"
	// high-pass filter with Fstop=3000 and Fpass=3500
	// #include "fdacoefs_high4_032taps.dat"
	// band pas-pass filters
	// #include "fdacoefs_pass4_341taps.dat"
	// #include "fdacoefs_pass4_032taps.dat"
	// band-stop
	// #include "fdacoefs_stop4_162taps.dat"
	
	
};


fir_state_fr16 stateL;
fir_state_fr16 stateR;




//--------------------------------------------------------------------------//
// Function:	main														//
//																			//
// Description:	After calling a few initalization routines, main() just 	//
//				waits in a loop forever.  The code to process the incoming  //
//				data can be placed in the function Process_Data() in the 	//
//				file "Process_Data.c".										//
//--------------------------------------------------------------------------//
void main(void)
{
	
	sysreg_write(reg_SYSCFG, 0x32);		//Initialize System Configuration Register
	Init_EBIU();
	Init_Flash();
	Init1836();
	Init_Sport0();

	Init_FIR();
	
	Init_DMA();
	Init_Interrupts();
	Enable_DMA_Sport0();
	

	while(1);
	
}
