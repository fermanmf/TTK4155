#include "solenoid.h"

#include "sam.h"

void solenoid_init() {
    //TODO: Enable timer counter, set values for R_B and R_C

    // PMC TC6
    PMC->PMC_PCER1 |= PMC_PCER1_PID33;
    // PIO
    PIOC->PIO_PDR |= PIO_PC25;
    PIOC->PIO_ABSR |= PIO_PC25;
    // Enable clock
    TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN;
    TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_WAVE | TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVSEL_UP_RC; //| TC_CMR_CPCSTOP;
    // ======== idk ========
    TC2->TC_CHANNEL[0].TC_CMR |= TC_CMR_ACPA_SET | TC_CMR_ACPC_CLEAR;
    // =====================
    TC2->TC_CHANNEL[0].TC_RC = 1000;
    TC2->TC_CHANNEL[0].TC_RA = 0;

}

void solenoid_on() {
    
}