 /*
 * MCAL.c
 *
 * Created: 11/28/2015 6:55:02 PM
 *  Author: Rafael
 */ 

#include "include/MCAL.h"

void set_direction_pin(struct conf c)
{
	if(c.dir == 1) {
		c.port_pointer->ddrx |= 1 << c.pin_no;
	} else if(c.dir == 0) {
		c.port_pointer->ddrx &= ~(1 << c.pin_no);
	} 
}

char read_pin(struct conf c)
{
	// Like: if((PINC & (1 << PC3)) != 0){}
	return (c.port_pointer->pinx & (1 << c.pin_no)) != 0;
}

void write_pin(struct conf c)
{
	if(c.value == 1) {
		c.port_pointer->portx |= 1 << c.pin_no;
	} else if(c.value == 0) {
		c.port_pointer->portx &= ~(1 << c.pin_no);
	}
}

void set_direction_port(struct conf c)
{
	c.port_pointer->ddrx = c.value;
}

void write_port(struct conf c)
{
	c.port_pointer->portx = c.value;
}