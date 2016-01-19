/*
 * config.h
 *
 * Created: 1/3/2016 10:33:50 PM
 *  Author: Rafael
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#define CONFIG_LCD_DATA_PORT PINB_ADDR
#define CONFIG_LCD_CONF_PORT PINA_ADDR
#define CONFIG_LCD_CONF_E_PIN 0
#define CONFIG_LCD_CONF_RW_PIN 1
#define CONFIG_LCD_CONF_RS_PIN 2

#define CONFIG_LCD_MODE_4_BIT 1

#define CONFIG_KEYPAD_OUT_PORT PINC_ADDR

#endif /* CONFIG_H_ */