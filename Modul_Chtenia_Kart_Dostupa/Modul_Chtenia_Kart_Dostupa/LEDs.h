/*
 * LEDs.h
 *
 * Created: 04.03.2017 8:40:32
 *  Author: stepan
 */ 
#ifndef LEDS_H_
#define LEDS_H_
#define F_CPU 16000000UL// Clock Speed


#define DEBUG_LED_DDR_REGISTER                   DDRC
#define DEBUG_LED_PIN_REGISTER                   PINC
#define DEBUG_LED_PORT_REGISTER				     PORTC
#define DEBUG_LED_PIN							 0
#define DEBUG_LED_BLINK_TIME					 500				         
#define DEBUG_LED_ON							 DEBUG_LED_PORT_REGISTER |= (1 << DEBUG_LED_PIN)
#define DEBUG_LED_OFF							 DEBUG_LED_PORT_REGISTER &= ~(1 << DEBUG_LED_PIN)						 
						 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include "main.h"


/************************************************************************/
/* Define prototype LEDs functions                                      */
/************************************************************************/

void LEDs_ini();																		 
void Blink_DEBUG_LED();																     

#endif /* LEDS_H_ */
