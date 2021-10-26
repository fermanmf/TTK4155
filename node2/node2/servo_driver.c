// INIT SERVO

#include "servo_driver.h"

#include "pwm_driver.h"


#include "sam.h"

void setup_servo(int system_clock) {
    float period = 0.02;
    setup_pwm(period, system_clock);
    set_pulse(0.015);
}

void set_servo(float value) {
    float min = 0.009;
    float max = 0.021;

    float setValue = value;

    if (value < min) {
        setValue = min;
    }
    else if (value > max) {
        setValue = max;
	}

    set_pulse(setValue);
}