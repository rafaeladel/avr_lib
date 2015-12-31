/*
 * KEYPAD.c
 *
 * Created: 12/31/2015 9:35:40 PM
 *  Author: Rafael
 */ 
#include <avr/io.h>

#include "../MCAL/include/MCAL.h"
#include "include/KEYPAD.h"
#include <util/delay.h>

void init_keypad()
{
	struct conf c;
	c.port_pointer = PIND_ADDR;
	c.value = 0xf0;	
	set_direction_port(c);

	c.value = 0xff;
	write_port(c);
}

char getKey()
{
	volatile struct conf c;
	c.port_pointer = PIND_ADDR;
	
	char col = 0, row = 0;
	for(col = 0; col < 4; col++) {
		c.port_pointer->portx = c.port_pointer->portx | 0xf0;
		c.port_pointer->portx &= ~(1 << col) << 4;
		_delay_ms(1);
		row = c.port_pointer->pinx & 0x0f;
		if(row != 0x0f) {
			while((c.port_pointer->pinx & 0x0F) != 0x0F);
			break;
		}
	}
	
	if(col < 4) {
		row = getRowIndex(row);
		return keymap[row][col];
	}
	return '\0';
	
}

char getRowIndex(char row)
{
	row = (~row) & 0x0f;
	char index = 0;
	while(row >>= 1){
		index++;
	}
	return index;
}