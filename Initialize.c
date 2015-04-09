#include "Talkthrough.h"

//--------------------------------------------------------------------------//
// Function:	Init_EBIU													//
//																			//
// Description:	This function initializes and enables asynchronous memory 	//
//				banks in External Bus Interface Unit so that Flash A can be //
//				accessed.													//
//--------------------------------------------------------------------------//
void Init_EBIU(void)
{
	*pEBIU_AMBCTL0	= 0x7bb07bb0;
	*pEBIU_AMBCTL1	= 0x7bb07bb0;
	*pEBIU_AMGCTL	= 0x000f;
}


//--------------------------------------------------------------------------//
// Function:	Init_Flash													//
//																			//
// Description:	This function initializes pin direction of Port A in Flash A//
//				to output.  The AD1836_RESET on the ADSP-BF533 EZ-KIT board //
//				is connected to Port A.										//
//--------------------------------------------------------------------------//
void Init_Flash(void)
{
	*pFlashA_PortA_Dir = 0x1;
}

//--------------------------------------------------------------------------//
// Function:	Init_FIR													//
//																			//
// Description:	This function initializes FIR filter states for right & left//
//				channels													//
//--------------------------------------------------------------------------//
void Init_FIR(void)
{
	fir_init(stateR, coef, delayR, TAPS, 1);
	fir_init(stateL, coef, delayL, TAPS, 1);
}

/*
void Init_FIR1(void)
{
	fir_init(stateR1, coef1, delayR1, TAPS1, 1);
	fir_init(stateL1, coef1, delayL1, TAPS1, 1);
}

void Init_FIR2(void)
{
	fir_init(stateR2, coef2, delayR2, TAPS2, 1);
	fir_init(stateL2, coef2, delayL2, TAPS2, 1);
}

void Init_FIR3(void)
{
	fir_init(stateR3, coef3, delayR3, TAPS3, 1);
	fir_init(stateL3, coef3, delayL3, TAPS3, 1);
}
void Init_FIR4(void)
{
	fir_init(stateR4, coef4, delayR4, TAPS4, 1);
	fir_init(stateL4, coef4, delayL4, TAPS4, 1);
}

void Init_FIR5(void)
{
	fir_init(stateR5, coef5, delayR5, TAPS5, 1);
	fir_init(stateL5, coef5, delayL5, TAPS5, 1);
}
void Init_FIR6(void)
{
	fir_init(stateR6, coef6, delayR6, TAPS6, 1);
	fir_init(stateL6, coef6, delayL6, TAPS6, 1);
}

void Init_FIR7(void)
{
	fir_init(stateR7, coef7, delayR7, TAPS7, 1);
	fir_init(stateL7, coef7, delayL7, TAPS7, 1);
}

void Init_FIR8(void)
{
	fir_init(stateR8, coef8, delayR8, TAPS8, 1);
	fir_init(stateL8, coef8, delayL8, TAPS8, 1);
}
void Init_FIR9(void)
{
	fir_init(stateR9, coef9, delayR9, TAPS9, 1);
	fir_init(stateL9, coef9, delayL9, TAPS9, 1);
}

void Init_FIR10(void)
{
	fir_init(stateR10, coef10, delayR10, TAPS10, 1);
	fir_init(stateL10, coef10, delayL10, TAPS10, 1);
}

void Init_FIR11(void)
{
	fir_init(stateR11, coef11, delayR11, TAPS11, 1);
	fir_init(stateL11, coef11, delayL11, TAPS11, 1);
}
void Init_FIR12(void)
{
	fir_init(stateR12, coef12, delayR12, TAPS12, 1);
	fir_init(stateL12, coef12, delayL12, TAPS12, 1);
}
*/
void Init_FIR13(void)
{
	fir_init(stateR13, coef13, delayR13, TAPS13, 1);
	fir_init(stateL13, coef13, delayL13, TAPS13, 1);
}

//--------------------------------------------------------------------------//
// Function:	Init1836()													//
//																			//
// Description:	This function sets up the SPI port to configure the AD1836. //
//				The content of the array sCodec1836TxRegs is sent to the 	//
//				codec.														//
//--------------------------------------------------------------------------//
void Init1836(void)
{
	int i;
	int j;
	static unsigned char ucActive_LED = 0x01;
	
	// write to Port A to reset AD1836
	*pFlashA_PortA_Data = 0x00;
	
	// write to Port A to enable AD1836
	*pFlashA_PortA_Data = ucActive_LED;
	
	// wait to recover from reset
	for (i=0; i<0xf0000; i++) asm("nop;");

	// Enable PF4
	*pSPI_FLG = FLS4;
	// Set baud rate SCK = HCLK/(2*SPIBAUD) SCK = 2MHz	
	*pSPI_BAUD = 16;
	// configure spi port
	// SPI DMA write, 16-bit data, MSB first, SPI Master
	*pSPI_CTL = TIMOD_DMA_TX | SIZE | MSTR;
	
	// Set up DMA5 to transmit
	// Map DMA5 to SPI
	*pDMA5_PERIPHERAL_MAP	= 0x5000;
	
	// Configure DMA5
	// 16-bit transfers
	*pDMA5_CONFIG = WDSIZE_16;
	// Start address of data buffer
	*pDMA5_START_ADDR = (void *)sCodec1836TxRegs;
	// DMA inner loop count
	*pDMA5_X_COUNT = CODEC_1836_REGS_LENGTH;
	// Inner loop address increment
	*pDMA5_X_MODIFY = 2;
	
	// enable DMAs
	*pDMA5_CONFIG = (*pDMA5_CONFIG | DMAEN);
	// enable spi
	*pSPI_CTL = (*pSPI_CTL | SPE);
	
	// wait until dma transfers for spi are finished 
	for (j=0; j<0xaff0; j++) asm("nop;");
	
	// disable spi
	*pSPI_CTL = 0x0000;
}


//--------------------------------------------------------------------------//
// Function:	Init_Sport0													//
//																			//
// Description:	Configure Sport0 for I2S mode, to transmit/receive data 	//
//				to/from the AD1836. Configure Sport for external clocks and //
//				frame syncs.												//
//--------------------------------------------------------------------------//
void Init_Sport0(void)
{
	// Sport0 receive configuration
	// External CLK, External Frame sync, MSB first, Active Low
	// 16-bit data, Stereo frame sync enable
	*pSPORT0_RCR1 = RFSR | RCKFE | LRFS;
	*pSPORT0_RCR2 = RSFSE | SLEN_16;
	
	// Sport0 transmit configuration
	// External CLK, External Frame sync, MSB first, Active Low
	// 16-bit data, Secondary side enable, Stereo frame sync enable
	*pSPORT0_TCR1 = TCKFE | TFSR | LTFS;
	*pSPORT0_TCR2 = TSFSE | SLEN_16;
	
}


//--------------------------------------------------------------------------//
// Function:	Init_DMA													//
//																			//
// Description:	Initialize DMA1 in autobuffer mode to receive and DMA2 in	//
//				autobuffer mode to transmit									//
//--------------------------------------------------------------------------//
void Init_DMA(void)
{
	// Set up DMA1 to receive
	// Map DMA1 to Sport0 RX
	*pDMA1_PERIPHERAL_MAP = 0x1000;
	
	// Configure DMA1
	// 16-bit transfers, Interrupt on completion, Autobuffer mode
	*pDMA1_CONFIG = WNR | WDSIZE_16 | DI_EN | FLOW_1;
	// Start address of data buffer
	*pDMA1_START_ADDR = (void *)sRxBuffer;
	// DMA inner loop count
	*pDMA1_X_COUNT = 2;
	// Inner loop address increment
	*pDMA1_X_MODIFY = 2;
	
	
		
	// Set up DMA2 to transmit
	// Map DMA2 to Sport0 TX
	*pDMA2_PERIPHERAL_MAP = 0x2000;
	
	// Configure DMA2
	// 16-bit transfers, Autobuffer mode
	*pDMA2_CONFIG = WDSIZE_16 | FLOW_1;
	// Start address of data buffer
	*pDMA2_START_ADDR = (void *)sTxBuffer;
	// DMA inner loop count
	*pDMA2_X_COUNT = 2;
	// Inner loop address increment
	*pDMA2_X_MODIFY = 2;
}

//--------------------------------------------------------------------------//
// Function:	Enable_DMA_Sport											//
//																			//
// Description:	Enable DMA1, DMA2, Sport0 TX and Sport0 RX					//
//--------------------------------------------------------------------------//
void Enable_DMA_Sport0(void)
{
	// enable DMAs
	*pDMA2_CONFIG	= (*pDMA2_CONFIG | DMAEN);
	*pDMA1_CONFIG	= (*pDMA1_CONFIG | DMAEN);
	
	// enable Sport0 TX and RX
	*pSPORT0_TCR1 	= (*pSPORT0_TCR1 | TSPEN);
	*pSPORT0_RCR1 	= (*pSPORT0_RCR1 | RSPEN);
}

//--------------------------------------------------------------------------//
// Function:	Init_Interrupts												//
//																			//
// Description:	Initialize Interrupt for Sport0 RX							//
//--------------------------------------------------------------------------//
void Init_Interrupts(void)
{
	// Set Sport0 RX (DMA1) interrupt priority to 2 = IVG9 
	*pSIC_IAR0 = 0xffffffff;
	*pSIC_IAR1 = 0xffffff2f;
	*pSIC_IAR2 = 0xffffffff;

	// assign ISRs to interrupt vectors
	// Sport0 RX ISR -> IVG 9
	register_handler(ik_ivg9, Sport0_RX_ISR);

	// enable Sport0 RX interrupt
	*pSIC_IMASK = 0x00000200;
}

