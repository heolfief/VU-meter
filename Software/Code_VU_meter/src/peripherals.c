/**
 * \file peripherals.c
 * \brief Program for peripherals initialization and settings.
 * \author Heol Fief
 *
 * File containing the functions required to initialize and set peripherals.
 *
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
	ADMUX |= (1<<REFS1) | (1<<REFS0);					// Internal 1.1V used as Voltage Reference
	ADCSRB &= ~(1<<ADTS2);								// ...
	ADCSRB |= (1<<ADTS1) | (1<<ADTS0);					// ... Trigger ADC on Timer0 compare match A
	ADCSRA |= (1<<ADPS1);								// ... 
	ADCSRA &= ~((1<<ADPS2) | (1<<ADPS0));				// ... ADC clock prescaler = 32
	ADCSRA |= (1<<ADIE) | (1<<ADEN) | (1<<ADATE);		// Enable ADC and enable interrupt and enable auto-trigger
	ADCSRA |= (1<<ADSC);								// Start ADC conversion
}

void tmr0_init()
{
	TCNT0=0;											// Reset timer
	TCCR0A |= (1<<WGM01);								// CTC mode (clear timer on compare match)
	TCCR0A &= ~((1<<COM0A1) | (1<<COM0A0));				// Normal port operation, OC0A disconnected.
	TCCR0B &= ~((1<<CS02) | (1<<CS00));					// ... 
	TCCR0B |= (1<<CS01);								// ... Timer0 clock prescaler = 8
	OCR0A = 200;										// compare match every 200 * 1 / (16 000 000 / 8) = 100µs  -->  10kHz
}

void io_init()
{
	HC595_DDR |= (1<<HC595_SER) | (1<<HC595_SCK) | (1<<HC595_RCK) | (1<<HC595_SCL) | (1<<HC595_OE); // Port HC595_PORT set on output mode
	HC595_PORT &= ~((1<<HC595_SER) | (1<<HC595_SCK) | (1<<HC595_RCK) | (1<<HC595_SCL) | (1<<HC595_OE)); // Initialize HC595_PORT on GND	
}