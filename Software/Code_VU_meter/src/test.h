/**
 * \file test.h
 * \brief Test header file.
 * \author Heol Fief
 *
 * Header file containing definitions for the tests.
 *
 */ 


#ifndef TEST_H_
#define TEST_H_

/**
 * \fn void test_audio(void)
 * \brief Function to test level and peak audio calculation.
 * Data is sent by a serial connection and formated to be displayed with https://github.com/CieNTi/serial_port_plotter software.
 */
void test_audio(void);

#endif /* TEST_H_ */