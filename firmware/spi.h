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


#endif /* SPI_H_ */
