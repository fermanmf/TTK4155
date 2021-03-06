#include "dac.h"

#include <math.h>

#include "sam.h"
#include "printf-stdarg.h"
//dacc uses 25us maximum at each conversion 
void dac_init(){
   
    //set peripheral clock for DAC
    PMC->PMC_PCER1 |= PMC_PCER1_PID38;

    // set mode register 

    DACC->DACC_MR = DACC_MR_STARTUP_8 | DACC_MR_TAG_DIS | DACC_MR_WORD_HALF | DACC_MR_REFRESH(3) | DACC_MR_USER_SEL_CHANNEL1;
    DACC->DACC_CHER = DACC_CHER_CH1;
}

void dac_write_uint(uint32_t value){
	
	if (DACC->DACC_ISR & DACC_ISR_TXRDY){
		DACC->DACC_CDR = value;
	}
	else{
		printf("ERROR: DAC NOT READY!");
	}
}