/*
 * UART.h
 *
 * Created: 08.03.2017 9:54:03
 *  Author: stepan
 */ 
#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define F_CPU 16000000UL// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/************************************************************************/
/* Define prototype UART functions                                      */
/************************************************************************/

void USART_Ini( uint16_t ubrr );
void USART_Transmit( uint8_t data );
uint8_t USART_Receive( void );
void USART_Flush( void );
void UART_RX_int_DISABLE(void);
void UART_RX_int_ENABLE(void);

#endif /* UART_H_ */