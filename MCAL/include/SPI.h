/*
 * SPI.h
 *
 * Created: 1/3/2016 3:56:18 PM
 *  Author: Rafael
 */ 


#ifndef SPI_H_
#define SPI_H_

void _spi_init_master(void);
void _spi_init_slave(void);
void spi_init(void);
void spi_transfer(char);
char spi_recieve();

#endif /* SPI_H_ */