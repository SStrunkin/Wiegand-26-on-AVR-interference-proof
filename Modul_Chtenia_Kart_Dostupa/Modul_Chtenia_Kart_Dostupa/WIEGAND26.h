/*
 * WIEGAND26.h
 *
 * Created: 02.07.2023 19:45:54
 *  Author: stepan
 */ 


#ifndef WIEGAND26_H_
#define WIEGAND26_H_

#include <avr/io.h>
#include "UART.h"

void w26_get_data_from_messege();
void send_w26_data_to_uart();
void clear_w26_recieve_data();

#endif /* WIEGAND26_H_ */