/*
 * wdt.h
 *
 * Created: 31/10/2018 20:11:42
 *  Author: Heol
 */ 


#ifndef WDT_H_
#define WDT_H_

#define watchdogReset() asm volatile ("wdr")

void wdt_init();

#endif /* WDT_H_ */