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


////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// VARIABLES  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

unsigned char buffer[64];
uint16_t potValue = 0;

enum states{RESET, SENSOR_ALARM_MODE, SENSOR_ALARM_ACK_MODE} OPER_STATUS;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROTOTYPE FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

uint16_t adc_value_get();

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// MAIN FUNCTION /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    // initialize the device
    OPER_STATUS = RESET;
        
    SYSTEM_Initialize();
    
    init_hardware();
    
    OC1_SecondaryValueSet(SERVO_CLOCKWISE);
//    OC2_SecondaryValueSet(SERVO_CLOCKWISE);
//    OC3_SecondaryValueSet(SERVO_NEUTRAL);
//    OC4_SecondaryValueSet(SERVO_COUNTERCLOCKWISE);
//    OC5_SecondaryValueSet(SERVO_COUNTERCLOCKWISE);
    
    // Inputs initializing
    PB1_SetDigitalInput();
    PB2_SetDigitalInput();
    
    // Outputs initializing
    LED1_SetDigitalOutput();
    LED2_SetDigitalOutput();
    
    unsigned int counter = 500;
    enum counterState {clock, clockwise} counterState;
    
    counterState = clock;
    
    char kb_pressed;
    do{
//        if(counterState == clock)
//        {
//            if(counter < 1000)
//                counter += 10;
//            else
//               counterState = clockwise; 
//        }
//        else
//        {
//            if(counter > 500)
//                    counter -= 10;
//            else
//               counterState = clock; 
//
//        }
//        OC1_SecondaryValueSet(counter);
        
        kb_pressed = get_new_button();
        
        if(kb_pressed != '\0')
            printf("\nPWM Value = %c", kb_pressed);
//        delay_ms(50);
    }while(1);
    
    
        
    return 1;
}

/**
 * @brief 		Function to handle the ADC module
 *
 * @param[in] 	None
 * 
 * @retval		0 to 100 adc result value 
 */
//uint16_t adc_value_get(){
//
//  
//    
//}