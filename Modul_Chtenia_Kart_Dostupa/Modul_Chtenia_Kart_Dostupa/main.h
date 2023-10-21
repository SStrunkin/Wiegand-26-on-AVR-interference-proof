/*
 * IncFile1.h
 *
 * Created: 28.06.2023 8:18:14
 *  Author: stepan
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define F_CPU 16000000UL// Clock Speed

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include "LEDs.h"
#include "UART.h"
#include "wiegand_26.h"
#include "WIEGAND26.H"
#include "watchdog.h"
#include "sleep_mode.h"
#include "EEPROM.h"

/************************************************************************/
/* Program Status byte. Bits manipulation                                                                     */
/************************************************************************/

#define W26_MESSAGE_READY_BIT	    0                                                              ///< Index bit in programm_status_byte
#define SET_W26_MESSAGE_READY_BIT   programm_status_byte |= (1 << W26_MESSAGE_READY_BIT)           ///< Bit == 1 if Wiegand 26 message from low abstract level ready
#define CLEAR_W26_MESSAGE_READY_BIT programm_status_byte &= ~(1 << W26_MESSAGE_READY_BIT)          ///< clear this bit after reading Wiegand 26 message


#endif /* INCFILE1_H_ */