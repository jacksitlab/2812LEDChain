/*
 * i2c.c
 *
 *  Created on: 08.08.2016
 *      Author: Jack
 */

#include <msp430.h>
#include "i2c.h"

#define STATE_IDLE 0
#define STATE_MOREADR 1
#define STATE_WRITEMEM 2

//#pragma SET_DATA_SECTION(".fram_data_noinit")
unsigned char rgbmem[3*NUMLEDSMAX];//for RGB-Values
//#pragma SET_DATA_SECTION()

#pragma SET_DATA_SECTION(".infoB")
unsigned int rgb_numleds=NUMLEDSMAX;
static unsigned char i2c_address;
#pragma SET_DATA_SECTION()

unsigned char parammem[16];

static unsigned char state;


unsigned char TXData;
unsigned int writeOffset=0;
unsigned int lenWritten=0;
unsigned char *rxPtr,*txPtr;
void rgb_addoffset(signed char x)
{
	unsigned char* ptr=rgbmem;
	signed int xnew;
	unsigned int len=sizeof rgbmem;
	while(len--)
	{
		xnew=((unsigned char)*ptr)+x;
		if(xnew<0)
			xnew=0;
		else if(xnew>255)
			xnew=255;
		*ptr=(unsigned char)xnew;
		ptr++;
	}
}
void rgb_initdemo(void)
{
	unsigned char* ptr=rgbmem;
	unsigned long colors[]={0xff0000,0xFFff00,0x0000ff,0xffff00,0xff00ff,0x00ffff};
	unsigned int i;
	unsigned long color;
	for(i=0;i<rgb_numleds;i++)
	{
		color=colors[i%6];
		*ptr++=(unsigned char)(0xff&(color>>16));
		*ptr++=(unsigned char)(0xff&(color>>8));
		*ptr++=(unsigned char)(0xff&(color));

	}
}
unsigned char tmp;
//inline void xorSwap(unsigned char *x,unsigned char *y){ *x^=*y^(*y^=*x);}
inline void xorSwap(unsigned char *x,unsigned char *y){if(*x!=*y){*x ^= *y;*y ^= *x;*x ^= *y;}}
//inline void xorSwap(unsigned char *x,unsigned char *y){tmp=*x;*x=*y;*y=tmp;}

void rgb_shift(unsigned char dir)
{
	unsigned char* ptrSrc,*ptrDst;
	unsigned int len=rgb_getlength()-3;
	if(dir==SHIFTDIR_BACKWARD)
	{
		ptrSrc=rgbmem;
		ptrDst=ptrSrc+3;
		while(len--)
		{
			xorSwap(ptrSrc++,ptrDst++);
			_nop();
		}
	}
	else
	{
		ptrSrc=rgbmem+rgb_getlength()-1;
		ptrDst=ptrSrc-3;
		while(len--)
		{
			xorSwap(ptrSrc--,ptrDst--);
			_nop();
		}
	}
}
void i2c_init(void)
{
	//if(i2c_address==0 || i2c_address>0x7f)
		i2c_address=I2C_ADDRESS_DEFAULT;
	// Configure Pins for I2C
	    P1SEL1 |= BIT6 + BIT7;                  // Pin init
	    // eUSCI configuration
	    UCB0CTLW0 |= UCSWRST ;	            //Software reset enabled
	    UCB0CTLW0 |= UCMODE_3  + UCSYNC;	    //I2C mode, sync mode
	    UCB0I2COA0 = i2c_address + UCOAEN;   	    //own address is 0x48 + enable
	    UCB0CTLW0 &=~UCSWRST;	            //clear reset register
	    UCB0IE |=  UCTXIE0 + UCRXIE0 + UCSTPIE + UCSTTIE; 	    //transmit,receive,stop,start interrupt enable

}
unsigned char empty;

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_B0_VECTOR
__interrupt void USCIB0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_B0_VECTOR))) USCIB0_ISR (void)
#else
#error Compiler not supported!
#endif

{

switch(__even_in_range(UCB0IV,0x1E))
    {
        case 0x00: break; // Vector 0: No interrupts break;
        case 0x02: break; // Vector 2: ALIFG
        case 0x04: break; // Vector 4: NACKIFG
        case 0x06:  // Vector 6: STTIFG
        	lenWritten=0;writeOffset=0;txPtr=rgbmem;
        	state = STATE_IDLE;
           	break;
        case 0x08:       // Vector 8: STPIFG

          UCB0IFG &= ~UCSTPIFG;// Clear stop condition int flag
          if(writeOffset<=0xff00)
        	  i2c_onwritecomplete(&rgbmem[0],NUMLEDSMAX);
          else
        	  i2c_oncommand(0x00ff&writeOffset,parammem);
          state = STATE_IDLE;
          break;
        case 0x0a: break; // Vector 10: RXIFG3 break;
        case 0x0c: break; // Vector 14: TXIFG3 break;
        case 0x0e: break; // Vector 16: RXIFG2 break;
        case 0x10: break; // Vector 18: TXIFG2 break;
        case 0x12: break; // Vector 20: RXIFG1 break;
        case 0x16:  // Vector 24: RXIFG0 break;
        	switch(state)
        	{
        	case STATE_IDLE:	//first 8bit of adr(HI)
        		writeOffset=(0xff&UCB0RXBUF);
        		writeOffset<<=8;
        		state = STATE_MOREADR;
        		break;
        	case STATE_MOREADR:	//second 8bit of adr(LO)
        		writeOffset|=(0xff&UCB0RXBUF);
        		//address rx-pointer
        		//writeOffset=[0..0xff00] => rgbvalues => rgbmem+writeoffset
        		//writeOffset=[0xff00..0xffff] => command => parammem
        		rxPtr=writeOffset<=0xff00?(rgbmem+writeOffset):parammem;
        		state=STATE_WRITEMEM;
        		break;
        	case STATE_WRITEMEM:	//write rgbmem
        		if(writeOffset<=0xff00)
        		{
        			if(rxPtr<rgbmem+sizeof(rgbmem))
						*rxPtr++=(0xff&UCB0RXBUF);
        			else
						empty=(0xff&UCB0RXBUF);
        		}
        		else	//commands for adr>=0xff00
        		{
        			if(rxPtr<parammem+sizeof(parammem))
        				*rxPtr++=(0xff&UCB0RXBUF);
        			else
        				empty=(0xff&UCB0RXBUF);
        		}
        		break;
        	default:
        		empty=(0xff&UCB0RXBUF);
        		break;
        	}
        	break;
       	case 0x14:  break;// Vector 22: TXIFG1 break;
        case 0x18:
        	if(txPtr<(rgbmem+sizeof(rgbmem)))
        		UCB0TXBUF = *txPtr++;
        	else
        		UCB0TXBUF=0;
           break; // Vector 26: TXIFG0 break;
        case 0x1a: break; // Vector 28: BCNTIFG break;
        case 0x1c: break; // Vector 30: clock low timeout break;
        case 0x1e: break; // Vector 32: 9th bit break;
        default: break;

    }
}
