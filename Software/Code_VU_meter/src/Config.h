/**
 * \file config.h
 * \brief User-configuration file.
 * \author Heol Fief
 *
 * User configuration file. Change it to adapt code to your hardware.
 *
 */ 

// FUSES : avrdude command : -U lfuse:w:0xf7:m -U hfuse:w:0xde:m -U efuse:w:0xfd:m 


#ifndef CONFIG_H_
#define CONFIG_H_

/* SOFTWARE CONFIG */
#define AVERAGEWIDTH			100			// Number of samples for the digital filter (don't change, dependent on sampling frequency)
#define PEAK_HOLD_TIME			300			// Hold time for the peak before falling
#define PEAK_FALL_RATE			0.2			// Speed for the peak to fall

#define GAIN_MIN				0.5			// Minimal input signal gain
#define GAIN_MAX				6.0			// Maximal input signal gain

/* HARDWARE CONFIG */
#define NUMBER_OF_LED			80			// Number of LED for the VU meter display

#define AUDIO_ADC_CHANNEL		0			// ADC channel to read audio signal from
#define GAIN_ADC_CHANNEL		1			// ADC channel to read gain from
#define THRESHOLD_ADC_CHANNEL	2			// ADC channel to read threshold from

#define HC595_PORT				PORTD		// IO port where HC595 is connected
#define HC595_DDR				DDRD		// DATA DIRECTION REGISTER of the port chosen above

#define HC595_SER				PD7		    // Data pin (DS) pin location
#define HC595_SCK				PD5			// Shift Clock (SH_CP) pin location
#define HC595_RCK				PD4			// Register Clock (SH_CP) pin location
#define HC595_SCL				PD6			// Serial clear (active LOW) pin location
#define HC595_OE				PD3			// Output Enable (active LOW) pin location

#endif /* CONFIG_H_ */