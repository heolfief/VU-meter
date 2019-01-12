/*
 * Peripherals.c
 *
 * Created: 24/10/2018 18:49:22
 *  Author: Heol Fief
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <inttypes.h>
#include "Peripherals.h"
#include "Config.h"
#include "usart.h"


void adc_init()
{
	ADMUX = AUDIO_ADC_CHANNEL & 0b111;					// Select audio input ADC channel
	ADMUX &= ~((1<<REFS1) | (1<<REFS0));				// VCC used as Voltage Reference
	ADCSRB &= ~(1<<ADTS2);								// ...
	ADCSRB |= (1<<ADTS1) | (1<<ADTS0);					// ... Trigger ADC on Timer0 compare match A
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);		// ... ADC clock prescaler = 128
	ADCSRA |= (1<<ADIE) | (1<<ADEN) | (1<<ADATE);		// Enable ADC and enable interrupt and enable auto-trigger
	ADCSRA |= (1<<ADSC);								// Start ADC conversion
}

void tmr0_init()
{
	TCNT0=0;											// Reset timer
	TCCR0A |= (1<<WGM01);								// CTC mode (clear timer on compare match)
	TCCR0A &= ~((1<<COM0A1) | (1<<COM0A0));				// Normal port operation, OC0A disconnected.
	TCCR0B &= ~(1<<CS02);								// ... 
	TCCR0B = (1<<CS01)|(1<<CS00);						// ... Timer0 clock prescaler = 64
	OCR0A = 250;										// compare match every 250 * 1 / (16 000 000 / 64) = 1 ms  -->  1kHz
}

void tmr2_init()
{
	TCNT2=0;											// Reset timer
	TCCR2A |= (1<<WGM21);								// CTC mode (clear timer on compare match)
	TCCR2A &= ~((1<<COM2A1) | (1<<COM2A0));				// Normal port operation, OC2A disconnected.
	TCCR2B = (1<<CS22)| (1<<CS21) | (1<<CS20);			// Timer2 clock prescaler = 1024
	OCR2A = 250;										// compare match every 260 * 1 / (16 000 000 / 1024) = 16.64 ms  -->  60Hz
}

void io_init()
{
	HC595_DDR = 0xFF;									// Port HC595_PORT set on output mode
	HC595_PORT = 0x00;									// Initialize HC595_PORT on GND	
}