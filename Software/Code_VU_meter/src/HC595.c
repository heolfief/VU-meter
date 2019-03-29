/**
 * \file HC595.c
 * \brief Shift-registers program.
 * \author Heol Fief
 *
 * Program for the shift-registers.
 *
 */ 

#include <util/delay.h>
#include "hc595.h"
#include "Config.h"

void HC595Write(uint8_t level, uint8_t peak)
{
	HC595_PORT &= ~(1<<HC595_OE);
	HC595_PORT |= (1<<HC595_SCL);
	
   for(int8_t i = NUMBER_OF_LED - 1; i >= 0; --i)			// For each LED
   {
	   if(i>level && i!=peak) HC595_PORT &= ~(1<<HC595_SER);// Send Low level signal to DS pin
	   else					  HC595_PORT |=  (1<<HC595_SER);// Send High level signal to DS pin
	   
	   HC595_PORT |= (1<<HC595_SCK);						// ...
	   HC595_PORT &= ~(1<<HC595_SCK);						// ... Pulse shift clock
   }
   HC595_PORT |= (1<<HC595_RCK);							// Unfreeze output
   _delay_ms(1);
   HC595_PORT &= ~(1<<HC595_RCK);
}
