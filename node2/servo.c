#include "servo.h"

#include <math.h>

#include "sam.h"
#include "printf-stdarg.h"
#include "consts.h"

#define T 20 // 20 ms

void servo_init() {
	PIOC->PIO_PDR |= PIO_PC19;
	PIOC->PIO_ABSR |= PIO_PC19;
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;
	
	PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CPRE_MCK_DIV_32;
	PWM->PWM_CH_NUM[5].PWM_CPRD = round(T*MCK_NODE2/32000); // Channel PeRioD register
	PWM->PWM_ENA |= PWM_DIS_CHID5;
	
	servo_set(0);
}

	
void servo_set(float value) {
	if (value < -1 || value > 1) {
		printf("servo error: invalid value\n\r");
	} else {
		const float t_on = 1.5 - 0.6*value;
		PWM->PWM_CH_NUM[5].PWM_CDTY = round(PWM->PWM_CH_NUM[5].PWM_CPRD * (1 - (t_on / T)));
	}
}
