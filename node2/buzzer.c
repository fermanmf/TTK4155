#include "buzzer.h"

#include <stdint.h>
#include <math.h>

#include "consts.h"

void buzzer_init() {
	PIOC->PIO_PDR |= PIO_PC9; // pwm 41
	PIOC->PIO_ABSR |= PIO_PC9;
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	PWM->PWM_CH_NUM[3].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024;
	PWM->PWM_CH_NUM[3].PWM_CPRD = 0xFFFFFFFF;
	PWM->PWM_CH_NUM[3].PWM_CDTY = 0;
	PWM->PWM_ENA |= PWM_DIS_CHID3;
}
	
void buzzer_play_note(float tone, invdur uint8_t) {
	const uint32_t CPRD = round(MCK_NODE2/(1024 * tone));
	PWM->PWM_CH_NUM[3].PWM_CPRD = CPRD;
	PWM->PWM_CH_NUM[3].PWM_CDTY = CPRD / 2;
}
