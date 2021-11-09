#pragma once

volatile unsigned int *IR;

void ir_init();
void (*ir_beam_broken_cb)();