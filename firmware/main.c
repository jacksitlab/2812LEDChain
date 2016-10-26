
/**
 * |==================================|
 * |                                  |
 * |           Memory 1               |
 * |          for RGB Values          |
 * |        Size: NUMLEDSMAX          |
 * |                                  |
 * |==================================|
 *
 *
 * |==================================|
 * |                                  |
 * |           Memory 2               |
 * |        for DMA output            |
 * |  Size: 3* RGBMem + ResetOffset   |
 * |                                  |
 * |==================================|
 *
 *
 * |==================================|
 * |                                  |
 * |           Memory 3               |
 * |          for Config              |
 * |                                  |
 * |==================================|
 *
 */



#include <msp430.h> 

#include "i2c.h"
#include "spi.h"
#include "constants.h"

#ifdef COMPILE_MINIMAL
#else
#include "demos.h"
#define PROGRAM_IDLE 0
#define PROGRAM_RECALCRGB 1
#define PROGRAM_OFFSET 2
#define PROGRAM_KITT 3
#define PROGRAM_RINGBUFFER 4



unsigned int programMode=PROGRAM_IDLE;
static unsigned int timercounter=0;
#endif

void clock_init(void)
{
	 CSCTL0_H = 0xA5;
	  CSCTL1 |= DCORSEL + DCOFSEL0 + DCOFSEL1;   // Set max. DCO setting
	  CSCTL2 = SELA_3 + SELS_3 + SELM_3;        // set ACLK = MCLK = DCO
	  CSCTL3 = DIVA__32 + DIVS_0 + DIVM_0;        // set all dividers to 0

	  __delay_cycles(76563);
}
void i2c_onwritecomplete(unsigned char* ptr,unsigned int len)
{
	//spi_calculate(rgbmem,rgb_getnumleds());
	//spi_dma_write();
#ifdef COMPILE_MINIMAL
	spi_calculate(rgbmem,rgb_getlength());
    spi_dma_write();
#else
	programMode=PROGRAM_RECALCRGB;
#endif
}
void i2c_oncommand(unsigned int command,unsigned char* params)
{
#ifndef COMPILE_MINIMAL
	switch(command)
	{
		case COMMAND_OFFSET:
		{
			programMode=PROGRAM_OFFSET;
			parammem[0]=*params++;
			break;
		}
		case COMMAND_DEMO_KITT:
		{
			programMode=PROGRAM_KITT;
			timercounter=demo_getKITTCounterInit(rgb_getlength(),10);
			break;
		}
		case COMMAND_RINGBUFFER:
		{
			programMode=PROGRAM_RINGBUFFER;
			parammem[0]=*params++;
			parammem[1]=*params++;
			break;
		}
		case COMMAND_SETLENGTH:
		{
			unsigned int len=*params++;
			len<<=8;
			len+=*params;
			if(len>0 && len<NUMLEDSMAX)
				rgb_setlength(len);
			break;
		}
		case COMMAND_SETADDRESS:
		{
			break;
		}
		case COMMAND_SETFACTORS:
		{

			break;
		}
		default:
			break;
	}
#endif
}
/*
 * main.c
 */
unsigned int ringbufferreset=1000;

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    clock_init();
    i2c_init();
    spi_init();
    rgb_initdemo();

    spi_calculate(rgbmem,6);

    spi_dma_write();


    //=====TimerB Init for (24MHz)  / 24000 = 1000Hz = 1ms

    TB0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
    TB0CCR0 = 24000;
    TB0CTL = TBSSEL__SMCLK + MC__UP + ID__1;                 // SMCLK, UP mode

    __bis_SR_register(GIE);        // Enter LPM0 w/ interrupts
    programMode=PROGRAM_IDLE;
    while(1)
    {

#ifndef COMPILE_MINIMAL
    	switch(programMode)
    	{
    		case PROGRAM_RECALCRGB:
    		{
    			 spi_calculate(rgbmem,rgb_getnumleds());
    			 spi_dma_write();
    			 programMode=PROGRAM_IDLE;
    			 break;
    		}
    		case PROGRAM_OFFSET:
    		{	signed char x=(parammem[0]);
    			rgb_addoffset(x);
    			programMode=PROGRAM_RECALCRGB;
    			break;
    		}
    		case PROGRAM_RINGBUFFER:
    		{
    			ringbufferreset=parammem[0];
    			ringbufferreset<<=8;
    			ringbufferreset|=parammem[1];
    			timercounter=ringbufferreset;
    			while(timercounter>0)_nop();
    			rgb_shift(parammem[2]);
    			spi_calculate(rgbmem,rgb_getnumleds());
    			spi_dma_write();
    			break;
    		}
    		case PROGRAM_KITT:
    		{


    			programMode=PROGRAM_IDLE;
    			break;
    		}
    		default:
    		{
    			//programMode=PROGRAM_IDLE;
    			_nop();
    			break;
    		}
    	}
#endif
    }
}
#ifndef COMPILE_MINIMAL
// Timer B0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_B0_VECTOR))) Timer_B (void)
#else
#error Compiler not supported!
#endif
{
//	spi_dma_write();

	if(timercounter>0)
		timercounter--;
	//spi_calculate(rgbmem,rgb_getnumleds());
	//spi_dma_write();
}

#endif
