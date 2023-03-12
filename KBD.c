
#include "KBD.h"
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include <libpic30.h>
#include "AUX_FUNCTIONS.h"

//An easy way to map the XY location is a lookup table.
//You'll need to fill this in - you might need to figure out
//if mirrored etc or something funky.
char buttons[4][3] = 
{{'1', '2', '3'},
 {'4', '5', '6'},
 {'7', '8', '9'},
 {'*', '0', '#'}};

void kb_init(void)
{
	
	// Configuring Rows as outputs
    KB_DIR &= (~ROW0 | ~ROW1 | ~ROW2 | ~ROW3);
    
	// Configuring Columns as inputs with Pullups
    KB_DIR  |= (COL0 | COL1 | COL2);
    KB_PU |= (COL0 | COL1 | COL2); // Pullups (Interrup-On-Change Pull-Ups)
	
}

/******************************************************************************
This function writes to the appropriate pin, depending on the row called.
Note that the row indices are 0, ..., 3.
TO BE COMPLETED BY THE STUDENTS.
******************************************************************************/
void set_row_low(unsigned int row)
{
	//This code should set a single pin LOW associated with
	//the passed row. Ensure only a single pin goes low.
	
	switch(row){
		case 0:
		KB_OUT_PORT |= ROW1 | ROW2 | ROW3;
		KB_OUT_PORT &= ~ROW0;
		break;
		
		case 1:
		KB_OUT_PORT |= ROW0 | ROW2 | ROW3;
		KB_OUT_PORT &= ~ROW1;
		break;
		
		case 2:
		KB_OUT_PORT |= ROW0 | ROW1 | ROW3;
		KB_OUT_PORT &= ~ROW2;
		break;
		
		case 3:
		KB_OUT_PORT |= ROW0 | ROW1 | ROW2;
		KB_OUT_PORT &= ~ROW3;
		break;
	}
	
}

/******************************************************************************
This function reads the status of each keypad matrix column.
The return value is the value of the first column that is in a low state.
Note that by definition, the column indices are 1, 2, 3
******************************************************************************/
int col_pushed(void)
{
	//This code should return what column was detected.
	//Remember the following:
	// 1) We need to mask off such we only get the bit we care about.
	// 2) We need to detect the LOW state (as we are setting the row to be LOW)

	if ((KB_IN_PORT & COL0) == 0)	return 1;	// C1 -> KB5
	if ((KB_IN_PORT & COL1) == 0)	return 2;	// C2 -> KB6
	if ((KB_IN_PORT & COL2) == 0)	return 3;	// C3 -> KB7

	//If not column detected, return nothing
	return 0;
}

/******************************************************************************
This function activates each row one by one, and reads the column.
If a button is pressed, returns the character pressed.  Otherwise, returns a zero.
Use main_test_1() to test this function.
******************************************************************************/
char get_button(void)
{
	char button = 0;
	//Use the scanning example from main_test_1()
	//to build a simple code that scans and waits for
	//a button press. Return the character pressed.

	for(int row = 0; row < 4; row++){
		set_row_low(row);
//		_delay_ms(20);
        delay_ms(20);
		
		int col = col_pushed();
		
		if(col)
            button = buttons[row][col-1];
	}

	return button;
}

/******************************************************************************
This function calls get_button() and makes sure that it is only registered once.
This function is complete.
******************************************************************************/
char get_new_button(void)
{
	static char last_button;
	char b = get_button();
	
	//Check if we held button down
	if(b == last_button) return 0;
	
	last_button = b;
	
	return b;
}