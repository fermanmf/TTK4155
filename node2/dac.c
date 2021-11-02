#include "dac.h"

#include <math.h>

#include "sam.h"
#include "printf-stdarg.h"

void dac_init(){
    // disable write_protect
    //DACC->DACC_WPMR = DACC_WPMR_WPEN | DACC_WPMR_WPKEY("DAC");

    //set peripheral clock for DAC
    PMC->PMC_PCER1 |= PMC_PCER1_PID38;

    // set mode register 

    DACC->DACC_MR = DACC_MR_STARTUP_8 | DACC_MR_TAG_DIS | DACC_MR_WORD_HALF | DACC_MR_REFRESH(3) | DACC_MR_USER_SEL_CHANNEL1;
    DACC->DACC_CHER = DACC_CHER_CH1;
    // TODO: Verify startup register

    // enable write_protect
    //DACC->DACC_WPMR = DACC_WPMR_WPKEY("DAC");

}


void dac_write(float value){
    
    if (DACC->DACC_ISR & DACC_ISR_TXRDY){
        DACC->DACC_CDR = (unsigned int)round(value * 0xfff);
    }
    else{
        printf("ERROR: DAC NOT READY!");
    }
}

void dac_test(float value){
    dac_init();
    dac_write(value);
	
}