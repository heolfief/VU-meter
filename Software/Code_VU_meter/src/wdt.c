/**
 * \file wdt.c
 * \brief Functions to initialize watchdog timer.
 * \author Heol Fief
 */

#include <avr/io.h>
#include "wdt.h"


void wdt_init()
{
	WDTCSR |= (1<<WDE);									// ...
	WDTCSR &= ~(1<<WDIE);								// ... Watchdog on System Reset Mode
	WDTCSR |= (1<<WDP2) |(1<<WDP0);						// ...
	WDTCSR &= ~(1<<WDP1);								// ... Watchdog time-out at 0.5s
}