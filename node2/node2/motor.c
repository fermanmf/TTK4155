#include "motor.h"
#include "dac.h"

void motor_run_open_loop(){
    while (1){
        dac_write(joystick_read());
    }
}
void motor_run_closed_loop(){
    while (1){
        unsigned int pos = motor_read_encoder();

        dac_write(joystick_read());
    }
}

void motor_reed_encoder(){
    //D0-D7 er p33-p40
    //32-DIR, 30-EN, 25-!OE, 26-!RST, 27-SEL
    


/*• Set !OE low to enable output of encoder 
• Set SEL low to get high byte
• Wait about 20 microseconds
• Read MSB
• Set SEL high to get low byte
• Wait about 20 microseconds
• Read LSB
• Toggle !RST to reset encoder
• Set !OE high to disable output of encoder • Process received data....
*/
}