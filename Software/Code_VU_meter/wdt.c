/*
 * wdt.c
 *
 * Created: 31/10/2018 20:12:24
 *  Author: Heol Fief
 */ 

#include <avr/io.h>
#include "headers/wdt.h"


void wdt_init()
{
	WDTCSR |= (1<<WDE);									// ...
	WDTCSR &= ~(1<<WDIE);								// ... Watchdog on System Reset Mode
	WDTCSR |= (1<<WDP2) |(1<<WDP0);						// ...
	WDTCSR &= ~(1<<WDP1);								// ... Watchdog time-out at 0.5s
}