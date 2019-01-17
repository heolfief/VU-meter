/**
 * \file interrupts.c
 * \brief File for ISR.
 * \author Heol Fief
 *
 * File containing the Interrupt Service Routine (a.k.a. code to be run on interrupt).
 *
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <inttypes.h>
#include "Config.h"
#include "HC595.h"


float adc_avg = 0;
int peak_hd_cnt = 0;
float gain=1;
uint16_t threshold=0;
uint8_t peak_value;
uint8_t vu_value;

/**
 * \fn ISR(ADC_vect)
 * \brief Interrupt Service Routine on ADC conversion complete. NOT A FUNCTION, automatically called by hardware.
 * 
 * Performs audio data acquisition and all the calculation for the audio level and peak measurement.
 */
ISR(ADC_vect)											// Interrupt on ADC conversion complete
{
	int adc_output = ADC;
	
	TIFR0=(1<<OCF0A);									// Disable tmr0 comp match a interrupt
	
	if ((ADMUX & 0b111)==AUDIO_ADC_CHANNEL)				// If ADC read audio signal
	{
		if (adc_output < threshold) adc_output = 0;		// Ignore signal under threshold
		
		adc_output = adc_output * gain;					// Multiply signal by gain
		if(adc_output>1023)adc_output=1023;				// Stay on 10bits representation
		
		adc_avg += (((float)adc_output - adc_avg) / AVERAGEWIDTH);	// Pseudo running average
		
		vu_value = 20*log10(adc_avg+1)*NUMBER_OF_LED/60.2; // 60.2=20*Log10(1024)
		
		if ((peak_hd_cnt*9.948) > PEAK_HOLD_TIME)		// If peak hold time is reached
		{
			if (peak_value < PEAK_FALL_RATE) peak_value = 0;// decrease peak value only if it will stay higher than 0
			else peak_value -= PEAK_FALL_RATE;
		}
		if (vu_value > peak_value)						// If a peak higher than the previous is detected
		{
			peak_value = vu_value;						// Store the peak
			peak_hd_cnt = 0;							// start the peak hold counter
		}
		peak_hd_cnt ++;									// Increase the peak hold counter
	}
	
	if ((ADMUX & 0b111)==GAIN_ADC_CHANNEL)				// If ADC reads gain level
	{
		gain = (float)adc_output * (GAIN_MAX - GAIN_MIN) / (1023.0) + GAIN_MIN;	// Map gain between GAIN_MIN and GAIN_MAX
		ADMUX = AUDIO_ADC_CHANNEL & 0b111;				// Select back ADC channel
	}
	
	if ((ADMUX & 0b111)==THRESHOLD_ADC_CHANNEL)			// If ADC reads threshold level
	{
		threshold = adc_output;
		ADMUX = AUDIO_ADC_CHANNEL & 0b111;				// Select back ADC channel
	}
}

/**
 * \fn ISR(TIMER2_COMPA_vect)
 * \brief Interrupt Service Routine on timer2 compare match. NOT A FUNCTION, automatically called by hardware.
 * 
 * Update LED display periodically (based on timer2 settings). Also change ADC channel to periodically measure potentiometers value.
 */
ISR(TIMER2_COMPA_vect)									// Interrupt on timer2 compare match
{
	static int cnt;										// Counter to alternate between ADC channel selection
	
	HC595Write(vu_value, peak_value);					// Light up LEDs
	
	if(cnt & 1) ADMUX = GAIN_ADC_CHANNEL & 0b111;		// ...
	else ADMUX = THRESHOLD_ADC_CHANNEL & 0b111;			// ... Alternate between ADC channel selection
	++cnt;												// Increase counter
}