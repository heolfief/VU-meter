/**
 * \file dsp.h
 * \brief DSP header file.
 * \author Heol Fief
 *
 * Header file containing definitions for the DSP functions.
 *
 */ 

#include "data_structure.h"

#ifndef INCFILE1_H_
#define INCFILE1_H_

/**
 * \fn void dsp_VU_peak_compute()
 * \brief Function to process the VU-level and peak level.
 *
 * \param smpl the audio_object structure to save processed data to. 
 */
void dsp_VU_peak_compute(audio_object * smpl);


#endif /* INCFILE1_H_ */