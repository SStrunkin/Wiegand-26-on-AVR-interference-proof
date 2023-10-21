/*
 * LEDs.c
 *
 * Created: 04.03.2017 8:09:01
 *  Author: stepan
 */ 
#include "LEDs.h"

/* -----------------------------------------------------------------------------
*                        Define basic LEDs operations
* ------------------------------------------------------------------------------
*/

					 	


/* -----------------------------------------------------------------------------
*                        LEDs functions
* ------------------------------------------------------------------------------
*/


void LEDs_ini()
{	
	DEBUG_LED_DDR_REGISTER |= 1 << DEBUG_LED_PIN;										                       /// DEBUG_LED pin to output	   
}


void Blink_DEBUG_LED()
{														   	
	DEBUG_LED_ON;
	//_delay_ms(DEBUG_LED_BLINK_TIME);
	DEBUG_LED_OFF;
	//_delay_ms(DEBUG_LED_BLINK_TIME);	
}




