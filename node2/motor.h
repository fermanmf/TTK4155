/**
 * @file motor.h
 * @brief controls the motor
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * @brief This function contains the pid regulator. It regulates the position of
 * the motor based on the reference.
 * 
 * @param interrupt_period This variable represents the interrupt_period of
 *  the timer and is neccessary to implent a controller with derivative and integral effect.
 */
void motor_control_pos(int interrupt_period);
/**
 * @brief This function initializes the motor including 
 * setting pins and resetting encoder registers.
 * 
 */
void motor_init();
/**
 * @brief This function reads the encoder and returns a signed integer of
 *  value in the range 0 - 8820 in the case of initial position being 
 * all the way to the left.
 * 
 * @return int This is the position of the encoder in range 0-8820 when start procedure is correct.
 */
int motor_read_encoder();
/**
 * @brief This is the variables of a pid-controller.
 * 
 */
struct controlVariables{
    float pos;
    float ref;
    int deviation;
    int prev_deviation;
    int period;
    int deviation_sum;
    int k_p;
    int k_i;
    int k_d;
    int p_actuation;
    int i_actuation;
    int d_actuation;
    int actuation;
};
/**
 * @brief This is the case of a pid controller that the motor is using.
 * 
 */
struct controlVariables pid;
