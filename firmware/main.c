
/**
 * |==================================|
 * |                                  |
 * |           Memory 1               |
 * |          for RGB Values          |
 * |        Size: NUMLEDSMAX          |
 * |             (FRAM)               |
 * |==================================|
 *
 *
 * |==================================|
 * |                                  |
 * |           Memory 2               |
 * |        for DMA output            |
 * |  Size: 3* RGBMem + ResetOffset   |
 * |           (FRAM)                 |
 * |==================================|
 *
 *
 * |==================================|
 * |                                  |
 * |           Memory 3               |
 * |          for Config              |
 * |            (InfoB)               |
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
#define PROGRAM_FADEOUT 5
#define PROGRAM_FADEIN 6
#define PROGRAM_FADEOUT_LTR 7
#define PROGRAM_FADEIN_LTR 8
#define PROGRAM_FADEOUT_RTL 9
#define PROGRAM_FADEIN_RTL 10


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
unsigned int ringbufferreset=1000;
unsigned int fadetimerreset=1000;
unsigned int fadedirection_index=0;
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
		case COMMAND_FADEOUT:
		case COMMAND_FADEIN:
		{
			parammem[0]=*params++;
			parammem[1]=*params++;
			programMode=command==COMMAND_FADEOUT?PROGRAM_FADEOUT:PROGRAM_FADEIN;
			break;
		}
		case COMMAND_FADEIN_LTR:
		case COMMAND_FADEOUT_LTR:
		{
			parammem[0]=*params++;
			parammem[1]=*params++;
			fadedirection_index=0;
			programMode=command==COMMAND_FADEOUT_LTR?PROGRAM_FADEOUT_LTR:PROGRAM_FADEIN_LTR;
			break;
		}
		case COMMAND_FADEIN_RTL:
		case COMMAND_FADEOUT_RTL:
		{
			parammem[0]=*params++;
			parammem[1]=*params++;
			fadedirection_index=rgb_getnumleds();
			programMode=command==COMMAND_FADEOUT_RTL?PROGRAM_FADEOUT_RTL:PROGRAM_FADEIN_RTL;
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

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    clock_init();
    i2c_init();
    spi_init();
    rgb_initdemo();

//    spi_calculate(rgbmem,rgb_getlength());

//    spi_dma_write();


    //=====TimerB Init for (24MHz)  / 24000 = 1000Hz = 1ms

    TB0CCTL0 = CCIE;                          // TACCR0 interrupt enabled
    TB0CCR0 = 24000;
    TB0CTL = TBSSEL__SMCLK + MC__UP + ID__1;                 // SMCLK, UP mode

    __bis_SR_register(GIE);        // Enter LPM0 w/ interrupts
    programMode=PROGRAM_RECALCRGB;
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
    		case PROGRAM_FADEOUT:
    		case PROGRAM_FADEIN:
    		{
    			fadetimerreset=parammem[0];
    			fadetimerreset<<=8;
    			fadetimerreset|=parammem[1];
    			timercounter=fadetimerreset;
    			if(programMode==PROGRAM_FADEOUT)
    				rgb_decrement_factors();
    			else
    				rgb_increment_factors();
    			while(timercounter>0)_nop();
    			spi_calculate(rgbmem,rgb_getnumleds());
    			spi_dma_write();
    			if(programMode==PROGRAM_FADEOUT)
    			{
    				if(rgb_getfactor(0)<=0)
    					programMode=PROGRAM_IDLE;
    			}
    			else
    			{
    				if(rgb_getfactor(0)>=1)
    				    programMode=PROGRAM_IDLE;
    			}
    			break;
    		}
    		case PROGRAM_FADEOUT_LTR:
    		case PROGRAM_FADEIN_LTR:
    		{
    			fadetimerreset=parammem[0];
    		    fadetimerreset<<=8;
    		    fadetimerreset|=parammem[1];
    		    timercounter=fadetimerreset;
    		    if(programMode==PROGRAM_FADEOUT_LTR)
    		        rgb_decrement_factors_left(fadedirection_index);
    		    else //PROGRAM_FADEIN_LTR
    		    	rgb_increment_factors_left(fadedirection_index);
    		    while(timercounter>0)_nop();
    		    spi_calculate(rgbmem,rgb_getnumleds());
    		    spi_dma_write();
    		    if(programMode==PROGRAM_FADEOUT_LTR)
    		    {
    		    	if(rgb_getfactor(fadedirection_index)<0.5)
    		  	    	if(fadedirection_index<rgb_getnumleds()-1)
    		  	    		fadedirection_index++;
					if(rgb_getfactor(rgb_getnumleds()-1)<=0)
						programMode=PROGRAM_IDLE;
    		    }
    		    else	//PROGRAM_FADEIN_LTR
    		    {
    		    	if(rgb_getfactor(fadedirection_index)>0.5)
    		  	    	if(fadedirection_index<rgb_getnumleds()-1)
    		  	    		fadedirection_index++;
					if(rgb_getfactor(rgb_getnumleds()-1)>=1)
						programMode=PROGRAM_IDLE;
    		    }
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
	{
		timercounter--;
	}
	else
	{
	//	timercounter=5000;
//		programMode=PROGRAM_RECALCRGB;

	}
	//spi_calculate(rgbmem,rgb_getnumleds());
	//spi_dma_write();
}

#endif
