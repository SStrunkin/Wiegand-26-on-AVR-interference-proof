/*
 * EEPROM.h
 *
 * Created: 11.03.2017 7:19:28
 *  Author: stepan
 */ 
#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#include "main.h"
#include "eeprom_.h"


/* -----------------------------------------------------------------------------
*                        Define basic EEPROM constants and operations
* ------------------------------------------------------------------------------
*/



/* -----------------------------------------------------------------------------
*                        Define EEPROM functions
* ------------------------------------------------------------------------------
*/
uint8_t get_modbus_parity();
void set_modbus_parity(uint8_t data);

uint8_t get_modbus_stop_bits();
void set_modbus_stop_bits(uint8_t data);

uint32_t get_modbus_speed();
void set_modbus_speed(uint32_t data);

uint8_t get_modbus_address();
void set_modbus_address(uint8_t data);

uint8_t get_w26_LOW_phase();
uint8_t get_w26_HIGH_phase();

															





#endif /* EEPROM_H_ */