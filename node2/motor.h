void motor_control_pos(int interrupt_period);
void motor_init();
int motor_read_encoder();
struct controlVariables{
    int pos;
    int ref;
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
struct controlVariables pid;