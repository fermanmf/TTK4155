#pragma once

volatile unsigned int *IR;

void adc_init();
void (*ir_beam_broken_cb)();