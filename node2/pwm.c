#include "pwm.h"

#include <math.h>

#include "sam.h"
#include "config.h"
#include "utils.h"
#include "printf-stdarg.h"

void pwm_init() {
	PIOC->PIO_PDR |= PIO_PC19;
	PIOC->PIO_ABSR |= PIO_PC19;
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	
	
	PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CPRE_MCK_DIV_32;
	PWM->PWM_CH_NUM[5].PWM_CPRD = MCK / (50 * 32);
	PWM->PWM_ENA |= PWM_DIS_CHID5;
}

	
void pwm_set(float duty_cycle) {
	if (duty_cycle < 0 || duty_cycle > 1) {
		printf("Invalid duty cycle %f", duty_cycle);
		panic();
	} else {
		PWM->PWM_CH_NUM[5].PWM_CDTY = round(PWM->PWM_CH_NUM[5].PWM_CPRD * (1 - duty_cycle));
	}
}
