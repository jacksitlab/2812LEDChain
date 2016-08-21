/*
 * spi.c
 *
 *  Created on: 08.08.2016
 *      Author: Jack
 */
#include <msp430.h>
#include "constants.h"

#define RESET_OFFSET 40
#pragma SET_DATA_SECTION(".fram_data_noinit")
unsigned char ledoutputmem[3*3*NUMLEDSMAX+RESET_OFFSET];
#pragma SET_DATA_SECTION()

const unsigned long convert_table_3bit [256] = {		// 1 Byte => 3 Byte
 0x924924,0x924926,0x924934,0x924936,0x9249A4,0x9249A6,0x9249B4,0x9249B6, // 0 ... 7
 0x924D24,0x924D26,0x924D34,0x924D36,0x924DA4,0x924DA6,0x924DB4,0x924DB6, // 8 ... 15
 0x926924,0x926926,0x926934,0x926936,0x9269A4,0x9269A6,0x9269B4,0x9269B6,
 0x926D24,0x926D26,0x926D34,0x926D36,0x926DA4,0x926DA6,0x926DB4,0x926DB6,
 0x934924,0x934926,0x934934,0x934936,0x9349A4,0x9349A6,0x9349B4,0x9349B6,
 0x934D24,0x934D26,0x934D34,0x934D36,0x934DA4,0x934DA6,0x934DB4,0x934DB6,
 0x936924,0x936926,0x936934,0x936936,0x9369A4,0x9369A6,0x9369B4,0x9369B6,
 0x936D24,0x936D26,0x936D34,0x936D36,0x936DA4,0x936DA6,0x936DB4,0x936DB6,
 0x9A4924,0x9A4926,0x9A4934,0x9A4936,0x9A49A4,0x9A49A6,0x9A49B4,0x9A49B6,
 0x9A4D24,0x9A4D26,0x9A4D34,0x9A4D36,0x9A4DA4,0x9A4DA6,0x9A4DB4,0x9A4DB6,
 0x9A6924,0x9A6926,0x9A6934,0x9A6936,0x9A69A4,0x9A69A6,0x9A69B4,0x9A69B6,
 0x9A6D24,0x9A6D26,0x9A6D34,0x9A6D36,0x9A6DA4,0x9A6DA6,0x9A6DB4,0x9A6DB6,
 0x9B4924,0x9B4926,0x9B4934,0x9B4936,0x9B49A4,0x9B49A6,0x9B49B4,0x9B49B6,
 0x9B4D24,0x9B4D26,0x9B4D34,0x9B4D36,0x9B4DA4,0x9B4DA6,0x9B4DB4,0x9B4DB6,
 0x9B6924,0x9B6926,0x9B6934,0x9B6936,0x9B69A4,0x9B69A6,0x9B69B4,0x9B69B6,
 0x9B6D24,0x9B6D26,0x9B6D34,0x9B6D36,0x9B6DA4,0x9B6DA6,0x9B6DB4,0x9B6DB6,
 0xD24924,0xD24926,0xD24934,0xD24936,0xD249A4,0xD249A6,0xD249B4,0xD249B6,
 0xD24D24,0xD24D26,0xD24D34,0xD24D36,0xD24DA4,0xD24DA6,0xD24DB4,0xD24DB6,
 0xD26924,0xD26926,0xD26934,0xD26936,0xD269A4,0xD269A6,0xD269B4,0xD269B6,
 0xD26D24,0xD26D26,0xD26D34,0xD26D36,0xD26DA4,0xD26DA6,0xD26DB4,0xD26DB6,
 0xD34924,0xD34926,0xD34934,0xD34936,0xD349A4,0xD349A6,0xD349B4,0xD349B6,
 0xD34D24,0xD34D26,0xD34D34,0xD34D36,0xD34DA4,0xD34DA6,0xD34DB4,0xD34DB6,
 0xD36924,0xD36926,0xD36934,0xD36936,0xD369A4,0xD369A6,0xD369B4,0xD369B6,
 0xD36D24,0xD36D26,0xD36D34,0xD36D36,0xD36DA4,0xD36DA6,0xD36DB4,0xD36DB6,
 0xDA4924,0xDA4926,0xDA4934,0xDA4936,0xDA49A4,0xDA49A6,0xDA49B4,0xDA49B6,
 0xDA4D24,0xDA4D26,0xDA4D34,0xDA4D36,0xDA4DA4,0xDA4DA6,0xDA4DB4,0xDA4DB6,
 0xDA6924,0xDA6926,0xDA6934,0xDA6936,0xDA69A4,0xDA69A6,0xDA69B4,0xDA69B6,
 0xDA6D24,0xDA6D26,0xDA6D34,0xDA6D36,0xDA6DA4,0xDA6DA6,0xDA6DB4,0xDA6DB6,
 0xDB4924,0xDB4926,0xDB4934,0xDB4936,0xDB49A4,0xDB49A6,0xDB49B4,0xDB49B6,
 0xDB4D24,0xDB4D26,0xDB4D34,0xDB4D36,0xDB4DA4,0xDB4DA6,0xDB4DB4,0xDB4DB6,
 0xDB6924,0xDB6926,0xDB6934,0xDB6936,0xDB69A4,0xDB69A6,0xDB69B4,0xDB69B6,
 0xDB6D24,0xDB6D26,0xDB6D34,0xDB6D36,0xDB6DA4,0xDB6DA6,0xDB6DB4,0xDB6DB6   // ... 255
};

void calc_RGB_3bit (unsigned char R, unsigned char G, unsigned char B,unsigned char n)
{
	unsigned char *ptr=&ledoutputmem[RESET_OFFSET+(9*n)];
	// Gruen
	*ptr++= (unsigned char)(convert_table_3bit[G]>>16);
	*ptr++= (unsigned char)(convert_table_3bit[G]>>8);
	*ptr++= (unsigned char)(convert_table_3bit[G]);
	// Rot
	*ptr++= (unsigned char)(convert_table_3bit[R]>>16);
	*ptr++=(unsigned char)(convert_table_3bit[R]>>8);
	*ptr++= (unsigned char)(convert_table_3bit[R]);
	// Blau
	*ptr++= (unsigned char)(convert_table_3bit[B]>>16);
	*ptr++= (unsigned char)(convert_table_3bit[B]>>8);
	*ptr++= (unsigned char)(convert_table_3bit[B]);
}

void spi_init(void)
{
	  P2SEL1 |= BIT5;
	  UCA1CTLW0 |= UCSWRST;                     // **Put state machine in reset**
	  UCA1CTLW0 |= UCMST+UCSYNC+UCCKPL+UCMSB;   // 3-pin, 8-bit SPI master
	                                            // Clock polarity high, MSB
	  UCA1CTLW0 |= UCSSEL__SMCLK;                    // SMCLK
	  UCA1BR0 = 0x09;                          //  fsystem/10 = 2.400MHz
	  UCA1BR1 = 0;                              //
	  UCA1MCTLW = 0;                            // No modulation
	  UCA1CTLW0 &= ~UCSWRST;                    // **Initialize USCI state machine**

	  __data16_write_addr((unsigned short) &DMA0SA,(unsigned long)&ledoutputmem[1]);
	                                            // Source block address
	  __data16_write_addr((unsigned short) &DMA0DA,(unsigned long)&UCA1TXBUF);
	   // channel 17 = UCATXIFG as trigger for DMA
	    DMACTL0 = DMA0TSEL__UCA1TXIFG;
	    DMACTL1 = 0;
	    DMACTL2 = 0;
	    DMACTL3 = 0;                                // Destination single address
	  DMA0SZ = (sizeof ledoutputmem)-1 ;                            // Block size
	  DMA0CTL = DMASRCINCR_3 + DMASBDB + DMALEVEL+ DMADT_0;		// inc src_adr, byte=>byte, level sensitive, Repeated single
	  DMA0CTL |= DMAEN;                         // Enable DMA0
	  unsigned char i=RESET_OFFSET;
	  unsigned char* ptr=ledoutputmem;
	  while(i--)
		  *ptr++=0;
}
/*
 * Calculate rgbValues to dma-RAW-bytes for DMA sending
 *
 * inputs: *src = Pointer of rgb-values
 * 			len = number of rgb-values (for 6LEDS = 6, not 18)
 *
 */
void spi_calculate(unsigned char* src,unsigned int len)
{
	unsigned char i=0;
	while(len--)
	{
		calc_RGB_3bit(*(src+0),*(src+1),*(src+2),i++);
		src+=3;
	}


}
void spi_dma_write(void)
{
	//spi_loadtest();
	DMA0CTL |= DMAEN;
	//DMA0CTL |= DMAREQ;                      // Trigger block transfer
	UCA1TXBUF = ledoutputmem[0];
}

#pragma vector= DMA_VECTOR
__interrupt void dma_irq(void) {
  // DMA0CTL&=~DMAREQ;
}



