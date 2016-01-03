/*
 * SPI.c
 *
 * Created: 1/3/2016 4:07:38 PM
 *  Author: Rafael
 */ 
#include <avr/io.h>

#include "include/MCAL.h"
#include "include/SPI.h"

#define SPI_SLAVE

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
	struct conf c;
	c.port_pointer = PINB_ADDR;
	c.dir = 1;

	//SS
	c.pin_no = 4;
	set_direction_pin(c);

	//MOSI
	c.pin_no = 5;
	set_direction_pin(c);

	//SCK
	c.pin_no = 7;
	set_direction_pin(c);
}

void _spi_init_slave(void) 
{
	//Set Slave
	SPCR &= ~(1 << MSTR);

	//Set data direction
	struct conf c;
	c.port_pointer = PINB_ADDR;
	c.dir = 1;

	//MISO
	c.pin_no = 6;
	set_direction_pin(c);
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