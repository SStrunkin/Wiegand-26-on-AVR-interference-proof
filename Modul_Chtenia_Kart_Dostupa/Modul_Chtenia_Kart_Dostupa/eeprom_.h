/*
 * eeprom_.h
 *
 * Created: 14.08.2023 6:42:47
 *  Author: stepan
 */ 


#ifndef EEPROM__H_
#define EEPROM__H_

#include <avr/io.h>
#include "main.h"

void EEPROM_write_byte(uint16_t uiAddress, uint8_t ucData);
uint8_t EEPROM_read_byte(uint16_t uiAddress);



#endif /* EEPROM__H_ */