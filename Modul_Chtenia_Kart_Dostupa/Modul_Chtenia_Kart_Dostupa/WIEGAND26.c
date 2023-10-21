/*
 * WIEGAND26.c
 *
 * Created: 02.07.2023 19:45:35
 *  Author: stepan
 */ 
#include "WIEGAND26.h"

uint32_t w26_recieve_data;													   ///< Wiegand 26 data, all bits from low abstract level
uint8_t w26_facility;														   ///< Divide w26_recieve_data, first byte	
uint8_t w26_middle_byte;													   ///< Divide w26_recieve_data, middle byte	
uint8_t w26_last_byte;                                                         ///< Divide w26_recieve_data, last byte

/**
@brief Divide w26_recieve_data to bytes. \n
Parity processing (not implement now)
*/
void w26_get_data_from_messege()
{
    cli();
	w26_recieve_data >>= 1;													   /// Delete last parity check bit
	
	w26_last_byte = w26_recieve_data;
	w26_recieve_data >>= 8;
	w26_middle_byte = w26_recieve_data;
	w26_recieve_data >>= 8;
	w26_facility = w26_recieve_data;
	
	w26_recieve_data = 0;	
    sei();
}

/**
@brief Send w26_facility, w26_middle_byte and w26_last_byte to UART.
*/
void send_w26_data_to_uart()
{
	USART_Transmit(w26_facility);
	USART_Transmit(w26_middle_byte);
	USART_Transmit(w26_last_byte);
}

