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
#include "data_structure.h"

void test_audio(audio_object * smpl)
{
	uart_puts("$");
	uart_putint((int)smpl->vu_value);
	uart_puts(" ");
	uart_putint((int)smpl->peak_value);
	uart_puts(";\n");
}