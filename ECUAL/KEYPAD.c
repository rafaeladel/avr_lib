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
	set_direction_port(DDR_ADDR(PIND_ADDR), 0xf0);
	write_port(PORT_ADDR(PIND_ADDR), 0xff);
}

char getKey()
{
	char* port_ptr = make_pointer(PORT_ADDR(PIND_ADDR));
	volatile char* pin_ptr = make_pointer(PIND_ADDR);
	
	char col = 0, row = 0;
	for(col = 0; col < 4; col++) {
		add_to_port(PORT_ADDR(PIND_ADDR), 0xf0);
		subtract_from_port(PORT_ADDR(PIND_ADDR), (1 << col) << 4);
		_delay_ms(1);
		row = *(pin_ptr) & 0x0f;
		if(row != 0x0f) {
			while((*(pin_ptr) & 0x0f) != 0x0F);
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