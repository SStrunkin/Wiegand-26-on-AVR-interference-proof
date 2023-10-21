/*
 * watchdog.c
 *
 * Created: 29.07.2023 6:08:22
 *  Author: stepan
 */ 
#include "watchdog.h"
#include "UART.h"

/**
@brief Set timeout and enable watchdog.
*/
void watchdog_ini()
{        
    wdt_enable(WDTO_4S);    
    WDTCSR |= (1 << WDIE);
}

void watchdog_disable()
{
     wdt_reset();
     wdt_disable();
}

