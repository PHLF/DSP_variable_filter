#ifndef  __Talkthrough_DEFINED
	#define __Talkthrough_DEFINED

//--------------------------------------------------------------------------//
// Header files																//
//--------------------------------------------------------------------------//
#include <sys\exception.h>
#include <cdefBF533.h>
#include <ccblkfn.h>
#include <sysreg.h>
#include <fract.h>
#include <filter.h>
#include <math.h>
#include <stdfix.h>


//--------------------------------------------------------------------------//
// Symbolic constants														//
//--------------------------------------------------------------------------//
// addresses for Port B in Flash A
#define pFlashA_PortA_Dir	(volatile unsigned char *)0x20270006
#define pFlashA_PortA_Data	(volatile unsigned char *)0x20270004

// names for codec registers, used for sCodec1836TxRegs[]
#define DAC_CONTROL_1		0x0000
#define DAC_CONTROL_2		0x1000
#define DAC_VOLUME_0		0x2000
#define DAC_VOLUME_1		0x3000
#define DAC_VOLUME_2		0x4000
#define DAC_VOLUME_3		0x5000
#define DAC_VOLUME_4		0x6000
#define DAC_VOLUME_5		0x7000
#define ADC_0_PEAK_LEVEL	0x8000
#define ADC_1_PEAK_LEVEL	0x9000
#define ADC_2_PEAK_LEVEL	0xA000
#define ADC_3_PEAK_LEVEL	0xB000
#define ADC_CONTROL_1		0xC000
#define ADC_CONTROL_2		0xD000
#define ADC_CONTROL_3		0xE000

// names for slots in ad1836 audio frame
#define INTERNAL_ADC_L0			0
#define INTERNAL_ADC_R0			1
#define INTERNAL_DAC_L0			0
#define INTERNAL_DAC_R0			1

// size of array sCodec1836TxRegs
#define CODEC_1836_REGS_LENGTH	11

// SPI transfer mode
#define TIMOD_DMA_TX 0x0003

// SPORT0 word length
#define SLEN_24	0x0017
#define SLEN_32	0x001f
#define SLEN_16	0x000f

// DMA flow mode
#define FLOW_1	0x1000

// Audio Buffer Size
#define BUFFER_SIZE 128

// FIR number of TAPS - define it here
#define TAPS	32
//#define TAPS	341

// DSP sampling frequency (Hz)
#define sampling_freq	96000

// For computation purpose
#define PI	3.141592654lk
#define double_PI	6.283185307lk

//--------------------------------------------------------------------------//
// Global variables															//
//--------------------------------------------------------------------------//
extern short sChannel0LeftIn[];
extern short sChannel0RightIn[];
extern short sChannel0LeftOut[];
extern short sChannel0RightOut[];


// the FIR filter related variables and structures
extern fract16 delayL[];
extern fract16 delayR[];
extern fract16 coef[];
extern fir_state_fr16 stateL;
extern fir_state_fr16 stateR;



extern volatile short sCodec1836TxRegs[];
extern volatile short sRxBuffer[];
extern volatile short sTxBuffer[];

//--------------------------------------------------------------------------//
// Prototypes																//
//--------------------------------------------------------------------------//
// in file Initialize.c
void Init_EBIU(void);
void Init_Flash(void);
void Init1836(void);
void Init_Sport0(void);
void Init_DMA(void);
void Init_Interrupts(void);
void Enable_DMA_Sport(void);
void Enable_DMA_Sport0(void);
void Init_FIR(void);

// in file Process_data.c
void Process_Data(void);

// in file ISRs.c
EX_INTERRUPT_HANDLER(Sport0_RX_ISR);

// in file fast_math.c
long fract fast_sin(long accum x);
long fract fast_cos(long accum x);
unsigned int fast_factorial(unsigned short i);

// in file dynamic_filter_compute.c
void filter_coeffs(fract* coef, signed int fc);

#endif //__Talkthrough_DEFINED
