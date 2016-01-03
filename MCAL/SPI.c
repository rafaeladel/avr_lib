/*
 * SPI.c
 *
 * Created: 1/3/2016 4:07:38 PM
 *  Author: Rafael
 */ 
#include <avr/io.h>

#include "include/MCAL.h"
#include "include/SPI.h"


void spi_init(void)
{
	#if defined(SPI_SLAVE)
		_spi_init_slave();
	#else
		_spi_init_master();
	#endif
	
	//Freq (16)
	SPCR |= (1 << SPR0);
	SPCR &= ~(1 << SPR1);
	
	//Polarity (0)
	SPCR &= ~(1 << CPOL);
	
	//Phase (0)
	SPCR &= ~(1 << CPHA);
		
	//Enable SPI
	SPCR |= 1 << SPE;
}

void _spi_init_master(void)
{
	//Set master
	SPCR = 1 << MSTR;
	
	//Set data direction
	//SS
	set_direction_pin(DDR_ADDR(PINB_ADDR), 4, 1);

	//MOSI
	set_direction_pin(DDR_ADDR(PINB_ADDR), 5, 1);

	//SCK
	set_direction_pin(DDR_ADDR(PINB_ADDR), 7, 1);
}

void _spi_init_slave(void) 
{
	//Set Slave
	SPCR &= ~(1 << MSTR);

	//Set data direction
	//MISO
	set_direction_pin(DDR_ADDR(PINB_ADDR), 6, 1);
}

void spi_transfer(char data)
{
	SPDR = data;
	while(!(SPSR & (1 << SPIF))){}
}

char spi_recieve()
{
	while(!(SPSR & (1 << SPIF))){}
	return SPDR;
}