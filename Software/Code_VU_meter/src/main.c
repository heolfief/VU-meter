/**
 * \file main.c
 * \brief main program
 * \author Heol Fief
 *
 * Main program for the VU-meter. Initialize everything needed for program to work, and loop forever.
 *
 */

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Peripherals.h"
#include "usart.h"
#include "HC595.h"
#include "Config.h"
#include "wdt.h"
#include "test.h"

/**
 * \fn int main(void)
 * \brief Main program.
 *
 * \return Nothing. Loops forever.
 */
int main(void)
{
	wdt_init();
	tmr0_init();
	tmr2_init();
	adc_init();
	io_init();
	
	uart_set_FrameFormat(USART_8BIT_DATA|USART_1STOP_BIT|USART_NO_PARITY|USART_ASYNC_MODE);
	uart_init(BAUD_CALC(115200));
	
	sei();		// Enable interrupts
    
	while(1)
    {
		watchdogReset();
		
		_delay_ms(10);
		test_audio();
    }
}