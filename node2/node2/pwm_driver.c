// INIT_PWM


// Prescaler settings
uint16_t prescaler = 256;

// f_desired = system_clock / (prescaler*(1+Top))

// Period = 20ms

void setup_pwm(float period, int system_clock) {

    // Set duty cycle
    int prescaler = 256;

    // Top / Period
    set_periode(period, system_clock, prescaler);

    // Pulse
    OCR1A = 0;

    // Fast mode PWM with timer1 -> Mode 14
    TCCR1A = (1<<WGM11);

    TCCR1B = (1<<WGM13) + (1<<WGM12);

    // Set prescaler to 256
    TCCR1B = (1<<CS12);

    // Compare output mode bits
    TCCR1A = (1<<COM1A1);

    // Set putput
    DDRB |= (1<<PB1);
}

// Set TOP / Periode
void set_period(float sec, int system_clock, int prescaler) {
    // Top = system_clock / (prescaler * f_desired) - 1
    int timer_frequency = system_clock/prescaler;
    ICR1 = timer_frequency*sec;
}

void set_pulse(float sec, int system_clock, int precaler) {
    int timer_frequency = system_clock/prescaler;
    ICR1A = timer_frequency*sec;
}