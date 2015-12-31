/*
 * KEYPAD.h
 *
 * Created: 12/31/2015 9:34:51 PM
 *  Author: Rafael
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

char keymap[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'c', '0', '=', '+'}
};

void init_keypad();
char getKey();
char getRowIndex(char);




#endif /* KEYPAD_H_ */