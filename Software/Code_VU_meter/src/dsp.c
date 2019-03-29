/**
 * \file dsp.c
 * \brief DSP functions.
 * \author Heol Fief
 *
 * Functions for digital data processing: audio computation.
 *
 */ 

#include <math.h>
#include "config.h"
#include "data_structure.h"

int peak_hd_cnt = 0;

void dsp_VU_peak_compute(audio_object * smpl)
{
	smpl->vu_value = 20*log10(smpl->adc_avg+1)*NUMBER_OF_LED/60.2; // 60.2=20*Log10(1024)
	
	if ((peak_hd_cnt*9.948) > PEAK_HOLD_TIME)		// If peak hold time is reached
	{
		if (smpl->peak_value < PEAK_FALL_RATE) smpl->peak_value = 0;// decrease peak value only if it will stay higher than 0
		else smpl->peak_value -= PEAK_FALL_RATE;
	}
	if (smpl->vu_value > smpl->peak_value)// If a peak higher than the previous is detected
	{
		smpl->peak_value = smpl->vu_value;// Store the peak
		peak_hd_cnt = 0;							// start the peak hold counter
	}
	peak_hd_cnt ++;									// Increase the peak hold counter
}