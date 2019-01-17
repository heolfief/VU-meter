/**
 * \file peripherals.h
 * \brief Peripherals header file.
 * \author Heol Fief
 *
 * Header file containing definitions for the peripherals.
 *
 */ 


#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

/**
 * \fn void adc_init(void)
 * \brief Function to initialize ADC.
 */
void adc_init(void);

/**
 * \fn void tmr0_init(void)
 * \brief Function to initialize timer0.
 */
void tmr0_init(void);

/**
 * \fn void tmr2_init(void)
 * \brief Function to initialize timer2.
 */
void tmr2_init(void);

/**
 * \fn void io_init(void)
 * \brief Function to initialize inputs and outputs.
 */
void io_init(void);

#endif /* PERIPHERALS_H_ */
