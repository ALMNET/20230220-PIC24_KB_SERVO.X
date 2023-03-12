#ifndef XC_KBD_H
#define	XC_KBD_H

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include <libpic30.h>
#include "AUX_FUNCTIONS.h"
//#include <p24FJ256GA702.h>

#define ROW0 (1 << 8)
#define ROW1 (1 << 9)
#define ROW2 (1 << 10)
#define ROW3 (1 << 11)

#define COL0 (1 << 12)
#define COL1 (1 << 13)
#define COL2 (1 << 14)

#define KB_PORT PORTB
#define KB_DIR  TRISB

//An easy way to map the XY location is a lookup table.
//You'll need to fill this in - you might need to figure out
//if mirrored etc or something funky.
// TODO: map the appropriate characters.
extern char buttons[4][3];

void init_hardware(void);

/******************************************************************************
This function writes to the appropriate pin, depending on the row called.
Note that the row indices are 0, ..., 3.
TO BE COMPLETED BY THE STUDENTS.
******************************************************************************/
void set_row_low(unsigned int row);

/******************************************************************************
This function reads the status of each keypad matrix column.
The return value is the value of the first column that is in a low state.
Note that by definition, the column indices are 1, 2, 3
******************************************************************************/
int col_pushed(void);

/******************************************************************************
This function activates each row one by one, and reads the column.
If a button is pressed, returns the character pressed.  Otherwise, returns a zero.
Use main_test_1() to test this function.
This function must be completed by the students.
******************************************************************************/
char get_button(void);
/******************************************************************************
This function calls get_button() and makes sure that it is only registered once.
This function is complete.
******************************************************************************/
char get_new_button(void);

#endif