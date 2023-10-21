/*
 * Interrupts.h
 *
 * Created: 05.03.2017 9:06:48
 *  Author: stepan
 */ 
#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "main.h"
#include "LEDs.h"
#include "UART.h"
#include "EEPROM.h"


/************************************************************************/
/* Define prototype functions                                           */
/************************************************************************/

void Weigand_26_ini();
void Weigand_26_D0_D1_int_ini();								   
void Weigand_26_high_phase_ini();
void Weigand_26_TIMER0_ini();
void Buttons_ints_ENABLE();
void Buttons_ints_DISABLE();

#endif /* INTERRUPTS_H_ */