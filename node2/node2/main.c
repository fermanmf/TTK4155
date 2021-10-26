/*
 * Node2.c
 *
 * Created: 05.10.2021 15:00:46
 * Author : vetlesr
 */ 


#include "sam.h"
#include "uart.h"
#include "printf-stdarg.h"
#include "can_controller.h"
#include "dac.h"
#include "adc.h"
#include "pwm.h"


int main(void)
{
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;
	configure_uart();
	printf("Start\n\r");
	can_init_def_tx_rx_mb(0x00143156);
	
	dac_test(1);
	adc_init();
	pwm_init(50);
	pwm_set(0.5);
	
	
	while(1) {
		//printf("%u\n", IR[0]);
	}
	

    printf("Terminated\n\r");
}
