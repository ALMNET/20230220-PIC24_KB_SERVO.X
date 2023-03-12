#ifndef XC_KBD_H
#define	XC_KBD_H

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

// To configure KB port, modify these lines according to the desided port.
// in this case the desired port is PORTB
#define KB_IN_PORT  PORTB       // Assign PORTB input value
#define KB_OUT_PORT LATB        // Assign LATB (Portb output latch)
#define KB_DIR      TRISB       // Assign direction for input/output init set
#define KB_PU       IOCPUB      // Set the pullup register according to selected
                                // port

// To configure kb port pins, modify next lines according to your needs
#define ROW0 (1 << 8)
#define ROW1 (1 << 9)
#define ROW2 (1 << 10)
#define ROW3 (1 << 11)

#define COL0 (1 << 12)
#define COL1 (1 << 13)
#define COL2 (1 << 14)



//An easy way to map the XY location is a lookup table.
//Definition of the array can be found in the KBD.c file
extern char buttons[4][3];

void kb_init(void);

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