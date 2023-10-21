/*
 * EEPROM.c
 *
 * Created: 11.03.2017 7:19:11
 *  Author: stepan
 */ 
#include "EEPROM.h"

#define w26_LOW_phase_eep_addr              0x0000
#define w26_HIGH_phase_eep_addr             0x0001

#define modbus_address_eep_addr             0x0002
#define modbus_speed_begin_sector_eep_addr  0x0003
#define modbus_speed_end_sector_eep_addr    0x0006
#define modbus_stop_bits_eep_addr           0x0007
#define modbus_parity_eep_addr              0x0008


uint8_t get_modbus_parity()
{
    return EEPROM_read_byte(modbus_parity_eep_addr);
}

void set_modbus_parity(uint8_t data)
{
    EEPROM_write_byte(modbus_parity_eep_addr, data);
}


uint8_t get_modbus_stop_bits()
{
    return EEPROM_read_byte(modbus_stop_bits_eep_addr);
}

void set_modbus_stop_bits(uint8_t data)
{
    EEPROM_write_byte(modbus_stop_bits_eep_addr, data);
}


uint32_t get_modbus_speed()
{
    uint32_t data;
    uint16_t address = modbus_speed_begin_sector_eep_addr;
    
    data = EEPROM_read_byte(address);
    
    data <<= 8;
    address++;
    data += EEPROM_read_byte(address);
    
    data <<= 8;
    address++;
    data += EEPROM_read_byte(address);
    
    data <<= 8;
    address++;
    data += EEPROM_read_byte(address);
    
    return data;
}

void set_modbus_speed(uint32_t data)
{
    uint16_t address = modbus_speed_end_sector_eep_addr;
    
    EEPROM_write_byte(address, data);
    
    data >>= 8;
    address--;    
    EEPROM_write_byte(address, data);
    
    data >>= 8;
    address--;    
    EEPROM_write_byte(address, data);
    
    data >>= 8;
    address--;    
    EEPROM_write_byte(address, data);
}


uint8_t get_modbus_address()
{
    return EEPROM_read_byte(modbus_address_eep_addr);
}

void set_modbus_address(uint8_t data)
{
    EEPROM_write_byte(modbus_address_eep_addr, data);
}


uint8_t get_w26_LOW_phase()
{
    return EEPROM_read_byte(w26_LOW_phase_eep_addr);
}

void set_w26_LOW_phase(uint8_t data)
{
    EEPROM_write_byte(w26_LOW_phase_eep_addr, data);
}


uint8_t get_w26_HIGH_phase()
{
    return EEPROM_read_byte(w26_HIGH_phase_eep_addr);
}

void set_w26_HIGH_phase(uint8_t data)
{
    EEPROM_write_byte(w26_HIGH_phase_eep_addr, data);
}
















	
