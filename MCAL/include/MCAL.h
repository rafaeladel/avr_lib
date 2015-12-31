/*
 * MCAL.h
 *
 * Created: 11/28/2015 6:54:53 PM
 *  Author: Rafael
 */ 

#include "../../HAL/include/DIO.h"

struct port {
	char pinx;
	char ddrx;
	char portx;	
};

struct conf {
	volatile struct port *port_pointer;
	char dir;
	char pin_no;
	char value;	
};

void set_direction_pin(struct conf);
char read_pin(struct conf);
void write_pin(struct conf);

void set_direction_port(struct conf);
void write_port(struct conf);