// INIT SERVO
#include "pwm_driver.h"

void setup_servo(int system_clock) {
    float period = 0.02;
    setup_pwm(period, system_clock);
    set_pulse(0.015);
}
