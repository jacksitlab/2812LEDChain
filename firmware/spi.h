/*
 * spi.h
 *
 *  Created on: 08.08.2016
 *      Author: Jack
 */

#ifndef SPI_H_
#define SPI_H_

void spi_init(void);
void spi_dma_write(void);
void spi_calculate(unsigned char* src,unsigned int len);
void rgb_increment_factors(void);
void rgb_decrement_factors(void);
float rgb_getfactor(unsigned int);

#endif /* SPI_H_ */
