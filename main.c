/**
  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.168.0
        Device            :  PIC24FJ256GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// PROJECT LIBRARIES //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define _XTAL_FREQ	8000000
#define FCY			XTAL_FREQ/2

#include <stdio.h>
#include <string.h>
#include <libpic30.h>

#include "mcc_generated_files/system.h"

#include "AUX_FUNCTIONS.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/oc1.h"
#include "mcc_generated_files/pin_manager.h"
#include "KBD.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////// I/O PINOUT AND DEFINITIONS //////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// CONSTANTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////// DEFINITIONS //////////////////////////////////

#define INPUT		1
#define OUTPUT		0

#define ON			1
#define OFF			0

#define HIGH		1
#define LOW			0

#define ENGAGED		1
#define DISENGAGED	0


#define SERVO_CLOCKWISE         500     // (1ms   * 9999) / 20mS = 499.95
#define SERVO_NEUTRAL           749     // (1.5ms * 9999) / 20mS = 749.925
#define SERVO_COUNTERCLOCKWISE  1000    // (2ms   * 9999) / 20mS = 999.9


#define SERVO_COUNTERCLOCKWISE  1000    // (2ms   * 9999) / 20mS = 999.9

#define SERVO_0     250     // (0.5ms   * 9999) / 20mS = 999.9
#define SERVO_45    500     // (1.0ms   * 9999) / 20mS = 999.9
#define SERVO_90    750     // (1.5ms   * 9999) / 20mS = 999.9
#define SERVO_135   1000    // (2.0ms   * 9999) / 20mS = 999.9
#define SERVO_180   1250    // (2.5ms   * 9999) / 20mS = 999.9


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// VARIABLES  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

unsigned char buffer[64];
uint16_t potValue = 0;

enum states{RESET, SENSOR_ALARM_MODE, SENSOR_ALARM_ACK_MODE} OPER_STATUS;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROTOTYPE FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

unsigned int servo_fast_test();
unsigned int servo_test();
unsigned int kb_test(unsigned short numberOfAttempts);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// MAIN FUNCTION /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    // initialize the device
    OPER_STATUS = RESET;
        
    SYSTEM_Initialize();
    
    kb_init();



    kb_test(100);
    
    
        
    return 1;
}


/**
 * @brief 		Function to test full range of a SG90 servo
 *
 * @param[in] 	None
 * 
 * @retval		0 if the servo test executed successfully 
 */
unsigned int servo_fast_test(){
    
    unsigned int result = 1;    
    
    OC1_SecondaryValueSet(SERVO_0);
    delay_ms(1000);
    OC1_SecondaryValueSet(SERVO_45);
    delay_ms(1000);
    OC1_SecondaryValueSet(SERVO_90);
    delay_ms(1000);
    OC1_SecondaryValueSet(SERVO_135);
    delay_ms(1000);
    OC1_SecondaryValueSet(SERVO_180);
    delay_ms(1000);
    OC1_SecondaryValueSet(SERVO_135);
    delay_ms(1000);
    OC1_SecondaryValueSet(SERVO_90);
    delay_ms(1000);
    OC1_SecondaryValueSet(SERVO_45);
    delay_ms(1000);
    
    result = 0;
    return result;
}

/**
 * @brief 		Function to test full range of a SG90 servo
 *
 * @param[in] 	None
 * 
 * @retval		0 if the servo test executed successfully 
 */
unsigned int servo_test(){
    
    static unsigned int result = 1;    
    static unsigned int counter = 250;
    static unsigned short i;
    static enum counterState {clock, clockwise} counterState;
    
    for(i = 0; i < 1000; i++)
    {
        counterState = clock;

        if(counterState == clock)
        {
            if(counter < 1250)
                counter += 10;
            else
               counterState = clockwise; 
        }
        else
        {
            if(counter > 250)
                    counter -= 10;
            else
               counterState = clock; 

        }
        OC1_SecondaryValueSet(counter);
    }
    
    result = 0;
    return result;
}



/**
 * @brief 		Function to test n number of attemps the 4x3 keypad
 *              result is shown in the uart
 *
 * @param[in] 	numberOfAttempts: Quantity of keys to test
 * 
 * @retval		0 if the test executed successfully 
 */
unsigned int kb_test(unsigned short numberOfAttempts)
{
    
    static unsigned int result = 1;
    static unsigned short i;
    static char kb_pressed;
    
    for(i = 1; i <= numberOfAttempts; i++)
    {
        do{
            kb_pressed = get_new_button();
            if(kb_pressed != '\0')
                    printf("\nPWM Value = %c, Attempt = %u", kb_pressed, i);
        }while(kb_pressed == '\0');
    }
    
    result = 0;
    return result;
        
}