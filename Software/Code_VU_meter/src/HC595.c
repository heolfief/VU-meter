/*
 * HC595.c
 *
 * Created: 27/10/2018 17:13:38
 *  Author: Heol Fief
 */ 

#include "HC595.h"
#include "Config.h"

void HC595Write(uint8_t *led_array)
{
	HC595_PORT &= ~(1<<HC595_RCK);							// Freeze output during shifting
	
   for(uint8_t i=sizeof(led_array)-1; i>0; --i)				// For each LED
   {
	   if(led_array[i]==0)	HC595_PORT &= ~(1<<HC595_SER);	// Send Low level signal to DS pin
	   else					HC595_PORT |=  (1<<HC595_SER);	// Send High level signal to DS pin
	   
	   HC595_PORT |= (1<<HC595_SCK);						// ...
	   HC595_PORT &= ~(1<<HC595_SCK);						// ... Pulse shift clock
   }
   HC595_PORT |= (1<<HC595_RCK);							// Unfreeze output
}
