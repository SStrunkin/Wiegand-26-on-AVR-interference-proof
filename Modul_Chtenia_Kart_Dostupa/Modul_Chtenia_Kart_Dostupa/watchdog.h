/*
 * watchdog.h
 *
 * Created: 29.07.2023 6:08:48
 *  Author: stepan
 */ 


#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include <avr/io.h>
#include <avr/wdt.h>

/************************************************************************/
/* Define prototype functions                                           */
/************************************************************************/

void watchdog_ini();
void watchdog_disable();


#endif /* WATCHDOG_H_ */