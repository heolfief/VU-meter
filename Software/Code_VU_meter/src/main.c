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
#include "hc595.h"
#include "Config.h"
#include "wdt.h"
#include "test.h"
#include "dsp.h"


audio_object audio_sample;

int data_smpl_counter = 0;
float audio_avg;
float gain = 1;
uint16_t threshold = 30;
uint8_t sample_ready = 0;
uint8_t adc_channel;
uint16_t adc_raw=0;

/**
 * \fn int main(void)
 * \brief Main program.
 *
 * \return Nothing. Loops forever.
 */
int main(void)
{
	//wdt_init();
	tmr0_init();
	adc_init();
	io_init();
	
	#ifdef UART_DEBUG
	uart_set_FrameFormat(USART_8BIT_DATA|USART_1STOP_BIT|USART_NO_PARITY|USART_ASYNC_MODE);
	uart_init(BAUD_CALC(115200));
	#endif
	
	sei();		// Enable interrupts
	
	
	audio_sample.vu_value = 56;
	audio_sample.peak_value = 72;
	
	while(1)
    {
		//watchdogReset();										// Feed the watchdog
		if(sample_ready)
		{
			sample_ready = 0;									// reset flag
			dsp_VU_peak_compute(&audio_sample);					// Compute acquired data
			
			#ifdef UART_DEBUG
			test_audio(&audio_sample);							// Send data via serial (debug only)
			#endif
			
			HC595Write(audio_sample.vu_value, audio_sample.peak_value);// Light up LEDs
			
			if(adc_channel & 1) ADMUX = GAIN_ADC_CHANNEL & 0b111;// ...
			else ADMUX = THRESHOLD_ADC_CHANNEL & 0b111;			// ... Alternate between ADC channel selection
			ADMUX &= ~(1<<REFS1);								// ...
			ADMUX |= (1<<REFS0);								// ... VCC used as Voltage Reference
			++adc_channel;										// Increase counter
		}
		_delay_ms(1);
    }
}


/**
 * \fn ISR(ADC_vect)
 * \brief Interrupt Service Routine on ADC conversion complete. NOT A FUNCTION, automatically called by hardware.
 * 
 * Performs analog data acquisition and filtering calculation.
 */
ISR(ADC_vect)											// Interrupt on ADC conversion complete
{
	adc_raw = ADC;										// Get ADC RAW data

	TIFR0=(1<<OCF0A);									// Disable tmr0 comp match a interrupt
	
	if ((ADMUX & 0b111) == AUDIO_ADC_CHANNEL)			// If ADC read audio signal
	{		
		adc_raw = (float)adc_raw * gain;				// Multiply signal by gain
		if(adc_raw>1023)adc_raw=1023;					// Stay on 10bits representation
		
		if (adc_raw < threshold) adc_raw = threshold;	// Ignore signal under threshold
		
		audio_avg += adc_raw;							// Average data (1/2)
		
		++data_smpl_counter;							// Increment number of data sampled
		
		if(data_smpl_counter == AVERAGEWIDTH)			// Down-sampling from 10kHz to 100Hz (divide by 100)
		{
			audio_avg /= AVERAGEWIDTH;					// Average data (2/2)
			audio_avg = (audio_avg-threshold)*(1023)/(1023-threshold); // Map audio_avg between 1023 and threshold
			
			audio_sample.adc_avg = (uint16_t)audio_avg; // Save average value
			sample_ready = 1;							// Enable sample ready flag
			data_smpl_counter = 0;						// Reset samples counter 
		}
		return;
	}
	
	if ((ADMUX & 0b111) == GAIN_ADC_CHANNEL)			// If ADC reads gain level
	{
		gain = (float)adc_raw * (GAIN_MAX - GAIN_MIN) / (1023.0) + GAIN_MIN; // Map gain between GAIN_MIN and GAIN_MAX
		ADMUX = AUDIO_ADC_CHANNEL & 0b111;				// Select back ADC channel
		ADMUX |= (1<<REFS1) | (1<<REFS0);				// Internal 1.1V used as Voltage Reference
		return;
	}
	
	if ((ADMUX & 0b111) == THRESHOLD_ADC_CHANNEL)		// If ADC reads threshold level
	{
		threshold = adc_raw >> 5;
		ADMUX = AUDIO_ADC_CHANNEL & 0b111;				// Select back ADC channel
		ADMUX |= (1<<REFS1) | (1<<REFS0);				// Internal 1.1V used as Voltage Reference
		return;
	}
}