/**
 * \file wdt.h
 * \brief Header file for watchdog timer.
 * \author Heol Fief
 */


#ifndef WDT_H_
#define WDT_H_

/**
 * \def watchdogReset() asm volatile ("wdr")
 * \brief ASM instruction to reset watchdog.
 */
#define watchdogReset() asm volatile ("wdr")

/**
 * \fn void wdt_init(void)
 * \brief Function to initialize watchdog timer.
 */
void wdt_init(void);

#endif /* WDT_H_ */