#pragma once

void setup_pwm(float period, int system_clock);

void set_period(float sec, int system_clock, int prescaler);

void set_pulse(float sec, int system_clock, int precaler);