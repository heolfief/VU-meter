/**
 * \file HC595.h
 * \brief Shift-registers header file.
 * \author Heol Fief
 *
 * Header file containing definitions for the shift-registers.
 *
 */ 


#include <avr/io.h>

#ifndef HC595_H_
#define HC595_H_

/**
 * \fn void HC595Write(uint8_t level, uint8_t peak)
 * \brief Function to light LED according to the VU-level and peak value, by sending data to the shift-registers.
 *
 * \param level The VU-level measured
 * \param peak The peak level measured 
 */
void HC595Write(uint8_t level, uint8_t peak);

#endif /* HC595_H_ */
	