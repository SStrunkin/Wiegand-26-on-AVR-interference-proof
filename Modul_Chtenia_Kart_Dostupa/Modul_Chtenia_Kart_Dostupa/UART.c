/*
 * UART.c
 *
 * Created: 08.03.2017 9:53:44
 *  Author: stepan
 */ 
#include "UART.h"

void USART_Ini(uint16_t ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);									       /// Set baud rate
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);							                   /// Enable: receiver, transmitter
	UCSR0C = (3<<UCSZ00);													   /// Set frame format: 8data, 1stop bit
}

void USART_Transmit(uint8_t data)
{	
	while ( !( UCSR0A & (1<<UDRE0)) )											/// Wait for empty transmit buffer
	;
	UDR0 = data;																/// Put data into buffer, sends the data
}

uint8_t USART_Receive(void)
{	
	while ( !(UCSR0A & (1<<RXC0)) )												/// Wait for data to be received
	;	
	return UDR0;																/// Get and return received data from buffer
}

void USART_Flush(void)
{
	uint8_t dummy = 0;	
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
	if (dummy == 0)																/// No warning about not being used dummy
	{
		dummy++;
	}
	 
}

void UART_RX_int_DISABLE(void)
{
	UCSR0B &= ~(1 << RXCIE0);	                                               /// Clear RX Complete Interrupt bit
}

void UART_RX_int_ENABLE(void)
{
	USART_Flush();
	UCSR0B |= (1 << RXCIE0);                                                   /// Set RX Complete Interrupt bit
}

