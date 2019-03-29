/**
 * \file data_structure.h
 * \brief Audio data structure declaration.
 * \author Heol Fief
 */ 

#include <inttypes.h>

#ifndef DATA_STRUCTURE_H_
#define DATA_STRUCTURE_H_

/**
 * \struct audio_object
 * \brief Object to handle average, peak and VU data for an audio sample.
 */
typedef struct
{
	uint16_t adc_avg;	/*!< Average ADC data. */
	uint8_t peak_value;	/*!< Audio peak value (range from 0 to NUMBER_OF_LED). */
	uint8_t vu_value;	/*!< Audio VU-value  (range from 0 to NUMBER_OF_LED). */
	
} audio_object;



#endif /* DATA_STRUCTURE_H_ */
