/*
 * sleep_mode.c
 *
 * Created: 30.07.2023 17:35:06
 *  Author: stepan
 */ 

#include "sleep_mode.h"

void sleep()
{
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sleep_cpu();
    sleep_disable();
}