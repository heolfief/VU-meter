/*
 * Peripherals.c
 *
 * Created: 24/10/2018 18:49:22
 *  Author: Heol
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include <inttypes.h>
#include "headers/Peripherals.h"
#include "headers/usart.h"
#include "headers/HC595.h"
#include "headers/Config.h"

uint8_t led_array[NUMBER_OF_LED];
int adc_raw;
float adc_avg = 0;
int peak_ht_cnt = 0;
float peak_value = 0;


void adc_init()
{
	ADMUX = ADC_CHANNEL & 0b111;						// Select ADC channel
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
	//DDRD = 0xFF;										// PortD set on output mode
	//PORTD = 0xFF;
}

void test()
{
	uart_puts("$");
	uart_putint(20*log10(adc_avg+1)*NUMBER_OF_LED/60.2);
	uart_puts(" ");
	uart_putint(peak_value);
	uart_puts(";");
}

ISR(ADC_vect)											// Interrupt on ADC conversion complete
{	
	TIFR0=(1<<OCF0A);									// Disable tmr0 comp match a interrupt
		
	adc_avg += (((float)ADC - adc_avg) / AVERAGEWIDTH);	// Pseudo running average
	
	float vu_value = 20*log10(adc_avg+1)*NUMBER_OF_LED/60.2; // 60.2=20*Log10(1024)
	
	if ((peak_ht_cnt*9.948) > PEAK_HOLD_TIME)			// If peak hold time is reached
	{
		if (peak_value < PEAK_FALL_RATE) peak_value = 0;// decrease peak value only if it will stay higher than 0
		else peak_value -= PEAK_FALL_RATE;
	}
	if (vu_value > peak_value)							// If a peak higher than the previous is detected
	{
		peak_value = vu_value;							// Store the peak
		peak_ht_cnt = 0;								// start the peak hold counter
	}
	peak_ht_cnt ++;										// Increase the peak hold counter
	
	for (uint8_t i=0; i<vu_value; ++i) led_array[i]=1;	// Fill bottom part of led_array with 1
	for (uint8_t i=adc_avg; i<sizeof(led_array); ++i) led_array[i]=0;	// Fill top part of led_array with 0
	
	led_array[(int)peak_value]=1;						// Light up peak led
}

ISR(TIMER2_COMP_vect)									// Interrupt on timer2 compare match
{
	HC595Write(led_array);								// Light up LEDs
}