/*
 * Modul_Chtenia_Kart_Dostupa.c
 *
 * Created: 20.07.2023 8:21:40
 * Author : stepan
 */ 

#include "main.h"

uint8_t programm_status_byte;
/**
@brief programm_status_byte description

bit 0 - weigan26 message ready, 1 message ready, 0 message not ready


*/

int main(void)
{             
	LEDs_ini();
    Blink_DEBUG_LED();    
 	USART_Ini( MYUBRR );                  
 	Weigand_26_ini();                                                                  
                                 
 	sei();		
	
	while (1)
	{	
        watchdog_ini();		
        
        		
		if (bit_is_set(programm_status_byte, W26_MESSAGE_READY_BIT))
		{
			w26_get_data_from_messege();
			send_w26_data_to_uart();
			CLEAR_W26_MESSAGE_READY_BIT;
 		}	                 
         
        watchdog_disable();        
        sleep();
	}
}

