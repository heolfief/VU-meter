/**
 * \file test.c
 * \brief Test program via serial output.
 * \author Heol Fief
 *
 * File containing the functions required to test program behavior via serial.
 *
 */

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include "usart.h"

extern uint8_t peak_value;
extern uint8_t vu_value;

void test_audio()
{
	uart_puts("$");
	uart_putint(vu_value);
	uart_puts(" ");
	uart_putint(peak_value);
	uart_puts(";");
}