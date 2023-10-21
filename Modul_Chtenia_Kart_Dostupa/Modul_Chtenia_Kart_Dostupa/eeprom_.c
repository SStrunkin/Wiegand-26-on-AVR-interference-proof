/*
 * eeprom_.c
 *
 * Created: 14.08.2023 6:42:32
 *  Author: stepan
 */ 


#include "eeprom_.h"

void EEPROM_write_byte(uint16_t uiAddress, uint8_t ucData)
{
    cli();																					 /// Wait for completion of previous write */
    while(EECR & (1<<EEPE))
    ;
                                                                                             /// Set up address and data registers */
    EEAR = uiAddress;
    EEDR = ucData;
                                                                                             /// Write logical one to EEMWE */
    EECR |= (1<<EEMPE);
                                                                                             /// Start eeprom write by setting EEWE */
    EECR |= (1<<EEPE);
    sei();
    }

    uint8_t EEPROM_read_byte(uint16_t uiAddress)
    {
    cli();																					 /// Wait for completion of previous write */
    while(EECR & (1<<EEPE))
    ;
                                                                                             /// Set up address register */
    EEAR = uiAddress;
                                                                                             /// Start eeprom read by writing EERE */
    EECR |= (1<<EERE);
    sei();																					 /// Return data from data register */
    return EEDR;
    }