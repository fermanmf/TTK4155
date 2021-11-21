#include "buzzer.h"

#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#include "sam.h"
#include "consts.h"
#include "printf-stdarg.h"

void buzzer_init() {
	PIOC->PIO_PDR |= PIO_PC9; // pwm 41
	PIOC->PIO_ABSR |= PIO_PC9;
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	PWM->PWM_CH_NUM[3].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024;
	
	//TC7
	PMC ->PMC_PCER1 |= PMC_PCER1_PID34;
	TC2->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;	
	TC2->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_CPCSTOP;
	TC2->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN;
	
	NVIC_EnableIRQ(TC7_IRQn);
}
	
void buzzer_play_note(float tone, float duration) {
	PWM->PWM_CH_NUM[3].PWM_CPRD = round(MCK_NODE2/(1024 * tone));
	PWM->PWM_CH_NUM[3].PWM_CDTY = PWM->PWM_CH_NUM[3].PWM_CPRD / 2; // 50 % duty cycle
	PWM->PWM_ENA = PWM_DIS_CHID3; // enable pwm
	
	TC2->TC_CHANNEL[1].TC_RC = round(2 * duration * MCK_NODE2 / 128);
	TC2->TC_CHANNEL[1].TC_CCR = TC_CCR_SWTRG; // start tc
}

typedef struct {
	float tone;
	float duration;
} Note;

Note NOTES[] = {
	{buzzerE, 3.0/8},
	{buzzerE, 1.0/8},
	{buzzerG, 3.0/8},
	{buzzerE, 3.0/8},
	{buzzerD, 1.0/4},
	{buzzerC, 1.0/2},
	{buzzerB, 1.0/2},
	{buzzerE, 3.0/8},
	{buzzerE, 1.0/8},
	{buzzerG, 3.0/8},
	{buzzerE, 3.0/8},
	{buzzerD, 1.0/4},
	{buzzerC, 1.0/2},
	{buzzerD, 1.0/4},
	{buzzerC, 1.0/2},
	{buzzerB, 1.0/2},
};

#define NOTES_LEN 16

static bool playing = false;
static int i = -1;

static void play_next_note() {
	if (i == (NOTES_LEN - 1)) {
		i = -1;
		playing = false;
	} else {
		const Note note = NOTES[++i];
		buzzer_play_note(note.tone, note.duration);
		playing = true;
	}
}

void buzzer_play_seven_nation_army() {
	if (!playing) {
		play_next_note();
	}
}

void TC7_Handler(){
	PWM->PWM_DIS = PWM_DIS_CHID3; // disable pwm
	TC2->TC_CHANNEL[1].TC_SR; // clear tc interrupt
	
	if (playing) {
		play_next_note();
	}
}