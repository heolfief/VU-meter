/**
 * \file data_structure.h
 * \brief Audio data structure declaration.
 * \author Heol Fief
 */ 


#ifndef DATA_STRUCTURE_H_
#define DATA_STRUCTURE_H_

/**
 * \struct audio_object
 * \brief Object to handle RAW, average, peak and VU data for and audio sample.
 */
typedef struct
{
	int adc_RAW;		/*!< RAW ADC data. */
	float adc_avg;		/*!< Average ADC data. */
	uint8_t peak_value;	/*!< Audio peak value (range from 0 to NUMBER_OF_LED). */
	uint8_t vu_value;	/*!< Audio VU-value  (range from 0 to NUMBER_OF_LED). */
	
} audio_object;


#endif /* DATA_STRUCTURE_H_ */
