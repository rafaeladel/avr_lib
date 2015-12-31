/*
 * LCD.c
 *
 * Created: 12/29/2015 3:55:58 PM
 *  Author: Rafael
 */ 


#include "../MCAL/include/MCAL.h"
#include "include/LCD.h"

#include <util/delay.h>

#define LCD_4_BIT

void init_lcd()
{
	struct conf con;
	con.port_pointer = PINA_ADDR;
	con.value= 0xff;
	set_direction_port(con);
	
	con.port_pointer = PINC_ADDR;
	con.value= 0xff;
	set_direction_port(con);
	
	#ifdef LCD_4_BIT
	lcd_send_cmd(0x02);
	lcd_send_cmd(0x28);
	#else
	lcd_send_cmd(0x38);
	#endif
	lcd_send_cmd(0x0c);
		
}

void set_control_reg(char reg)
{
	struct conf con;
	con.pin_no = 2;
	con.dir = 1;
	con.port_pointer = PINA_ADDR;
	con.value=reg;
	
	set_direction_pin(con);
	write_pin(con);
}

void set_lcd_dir(char dir)
{
	struct conf con;
	con.pin_no = 1;
	con.dir = 1;
	con.port_pointer = PINA_ADDR;
	con.value=dir;
	
	set_direction_pin(con);
	write_pin(con);
}

void set_lcd_enable(char is_enabled)
{
	struct conf con;
	con.pin_no = 0;
	con.dir = 1;
	con.port_pointer = PINA_ADDR;
	con.value=is_enabled;

	set_direction_pin(con);
	write_pin(con);
}

void lcd_send_cmd(char cmd)
{
	set_lcd_dir(0);
	set_control_reg(0);
	
	#ifdef LCD_4_BIT
	lcd_send(cmd & 0xf0);
	lcd_save();
	
	lcd_send((cmd & 0x0f) << 4);
	lcd_save();
	#else 
	lcd_send(cmd);
	lcd_save();
	#endif
}

void lcd_send_char(char c)
{
	set_lcd_dir(0);
	set_control_reg(1);
	
	#ifdef LCD_4_BIT
	lcd_send(c & 0xf0);
	lcd_save();
	
	lcd_send((c & 0x0f) << 4);
	lcd_save();
	#else
	lcd_send(c);
	lcd_save();
	#endif
}

void lcd_send_string(char* str, char x, char y)
{
	lcd_set_pos_xy(x, y);
	char i = 0;
	while(str[i] != '\0') {
		lcd_send_char(str[i++]);
	}
}

void lcd_set_pos_xy(char x, char y)
{
	lcd_send_cmd(0x80 + (y * 0x40) + x);
}

void lcd_send(char c)
{
	struct conf con;
	con.port_pointer = PINC_ADDR;
	con.value= c;
	
	write_port(con);
}

void lcd_save()
{
	set_lcd_enable(0);
	_delay_ms(10);
	set_lcd_enable(1);	
	_delay_ms(10);
	set_lcd_enable(0);
}

//void lcd_is_busy()
//{
	//set_control_reg(0);
	//set_lcd_dir(1);
	//while(read_button(PINC_ADDR, 7)){}
//}