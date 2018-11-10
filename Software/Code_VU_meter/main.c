/*
 * Code_VU_meter.c
 *
 * Created: 24/10/2018 18:37:47
 * Author : Heol Fief
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "headers/Peripherals.h"
#include "headers/usart.h"
#include "headers/HC595.h"
#include "headers/Config.h"
#include "headers/wdt.h"

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
		test();
    }
}