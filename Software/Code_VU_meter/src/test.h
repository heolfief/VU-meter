/**
 * \file test.h
 * \brief Test header file.
 * \author Heol Fief
 *
 * Header file containing definitions for the tests.
 *
 */ 

#include "data_structure.h"

#ifndef TEST_H_
#define TEST_H_

/**
 * \fn void test_audio(void)
 * \brief Function to test level and peak audio calculation.
 * Data is sent by a serial connection and formated to be displayed with https://github.com/CieNTi/serial_port_plotter software.
 *
 * \param smpl the audio_object structure to get data from.
 */
void test_audio(audio_object * smpl);

#endif /* TEST_H_ */