
/*
 * ECUAL.c
 *
 * Created: 11/28/2015 6:55:21 PM
 *  Author: Rafael
 */
 

#include "../MCAL/include/MCAL.h"
#include "include/ECUAL.h"


char read_button(char port_addr, char pin_no)
{
	struct conf con;
	con.pin_no = pin_no;
	con.dir = 0;
	con.port_pointer = port_addr;
	con.value=1;
	
	set_direction_pin(con);
	return read_pin(con);
}
