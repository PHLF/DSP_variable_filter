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
/*
#define TAPS1	137
#define TAPS2	214
#define TAPS3	237
#define TAPS4	228
#define TAPS5	228
#define TAPS6	185
#define TAPS7	137
#define TAPS8	137
#define TAPS9	228
#define TAPS10	274
#define TAPS11	228
#define TAPS12	228
*/
#define TAPS13	228
//#define TAPS	341

//--------------------------------------------------------------------------//
// Global variables															//
//--------------------------------------------------------------------------//
// DSP sampling frequency (Hz) -This doesn't change the hardware setup!!! It is only used for the filter_coef() function: it must be set according to the actual sampling frequency.
#define sampling_freq	96000

// For computation purpose
#define PI	3.141592654lk
#define double_PI	6.283185307lk

static short compteur = 0;
static short increm = 0;
static short sens = 0;

static int index_echo = 0;
static int echo = 1;

extern short Echo0LeftOut[];
extern short Echo0RightOut[];


extern short sChannel0LeftIn[];
extern short sChannel0RightIn[];
extern short sChannel0LeftOut[];
extern short sChannel0RightOut[];

/*
extern short fir_OutLeft_1[];
extern short fir_OutRight_1[];
extern short fir_OutLeft_2[];
extern short fir_OutRight_2[];
extern short fir_OutLeft_3[];
extern short fir_OutRight_3[];
extern short fir_OutLeft_4[];
extern short fir_OutRight_4[];
extern short fir_OutLeft_5[];
extern short fir_OutRight_5[];
extern short fir_OutLeft_6[];
extern short fir_OutRight_6[];
extern short fir_OutLeft_7[];
extern short fir_OutRight_7[];
extern short fir_OutLeft_8[];
extern short fir_OutRight_8[];
extern short fir_OutLeft_9[];
extern short fir_OutRight_9[];
extern short fir_OutLeft_10[];
extern short fir_OutRight_10[];
extern short fir_OutLeft_11[];
extern short fir_OutRight_11[];
extern short fir_OutLeft_12[];
extern short fir_OutRight_12[];
*/
extern short fir_OutLeft_13[];
extern short fir_OutRight_13[];

// the FIR filter related variables and structures
extern fract16 delayL[];
extern fract16 delayR[];
extern fract16 coef[];
extern fir_state_fr16 stateL;
extern fir_state_fr16 stateR;
/*
extern fract16 delayL1[];
extern fract16 delayR1[];

extern fract16 delayL2[];
extern fract16 delayR2[];

extern fract16 delayL3[];
extern fract16 delayR3[];

extern fract16 delayL4[];
extern fract16 delayR4[];

extern fract16 delayL5[];
extern fract16 delayR5[];

extern fract16 delayL6[];
extern fract16 delayR6[];

extern fract16 delayL7[];
extern fract16 delayR7[];

extern fract16 delayL8[];
extern fract16 delayR8[];

extern fract16 delayL9[];
extern fract16 delayR9[];

extern fract16 delayL10[];
extern fract16 delayR10[];

extern fract16 delayL11[];
extern fract16 delayR11[];

extern fract16 delayL12[];
extern fract16 delayR12[];
*/
extern fract16 delayL13[];
extern fract16 delayR13[];
/*
extern fract16 coef1[];

extern fract16 coef2[];

extern fract16 coef3[];

extern fract16 coef4[];

extern fract16 coef5[];

extern fract16 coef6[];

extern fract16 coef7[];

extern fract16 coef8[];

extern fract16 coef9[];

extern fract16 coef10[];

extern fract16 coef11[];

extern fract16 coef12[];
*/
extern fract16 coef13[];
/*
extern fir_state_fr16 stateL1;
extern fir_state_fr16 stateR1;

extern fir_state_fr16 stateL2;
extern fir_state_fr16 stateR2;

extern fir_state_fr16 stateL3;
extern fir_state_fr16 stateR3;

extern fir_state_fr16 stateL4;
extern fir_state_fr16 stateR4;

extern fir_state_fr16 stateL5;
extern fir_state_fr16 stateR5;

extern fir_state_fr16 stateL6;
extern fir_state_fr16 stateR6;

extern fir_state_fr16 stateL7;
extern fir_state_fr16 stateR7;

extern fir_state_fr16 stateL8;
extern fir_state_fr16 stateR8;

extern fir_state_fr16 stateL9;
extern fir_state_fr16 stateR9;

extern fir_state_fr16 stateL10;
extern fir_state_fr16 stateR10;

extern fir_state_fr16 stateL11;
extern fir_state_fr16 stateR11;

extern fir_state_fr16 stateL12;
extern fir_state_fr16 stateR12;
*/
extern fir_state_fr16 stateL13;
extern fir_state_fr16 stateR13;

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

/*
void Init_FIR1(void);
void Init_FIR2(void);
void Init_FIR3(void);
void Init_FIR4(void);
void Init_FIR5(void);
void Init_FIR6(void);
void Init_FIR7(void);
void Init_FIR8(void);
void Init_FIR9(void);
void Init_FIR10(void);
void Init_FIR11(void);
void Init_FIR12(void);*/
void Init_FIR13(void);

// in file Process_data.c
void Process_Data(void);

// in file ISRs.c
EX_INTERRUPT_HANDLER(Sport0_RX_ISR);

// in file fast_math.c
fract32 fast_sin(long accum x);
fract32 fast_cos(long accum x);
unsigned int fast_factorial(unsigned short i);

// in file dynamic_filter_compute.c
void filter_coeffs(fract16* coef, signed int fc);

#endif //__Talkthrough_DEFINED
