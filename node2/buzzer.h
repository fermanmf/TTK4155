/**
 * @file
 * @brief Buzzer driver and accompanying fourth octave tone macros
 */
#pragma once

#include <stdint.h>

#define buzzerC			261.63
#define buzzerCSharp	277.18
#define buzzerD			293.66
#define buzzerDSharp	311.13
#define buzzerE			329.63
#define buzzerF			349.23
#define buzzerFSharp	369.99
#define buzzerG			392.00
#define buzzerGSharp	415.30
#define buzzerA			440.00
#define buzzerASharp	466.16
#define buzzerB			493.88

/**
 * @brief Initializes driver
 * 
 */
void buzzer_init();

/**
 * @brief Plays note
 * 
 * @param tone[in] Frequency of tone. Recomended to be used with macros defined in this module
 * @param invdur[in] Inverse duration of note. I.e. 1 is whole note, 8 is eigth note and so on
 */
void buzzer_play_note(float tone, uint8_t invdur);
