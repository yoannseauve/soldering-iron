volatile extern unsigned char tic; //set on each tic
extern unsigned char pwm_duty; //pwd duty cycle

void init_tic(); //timer1
void init_pwm(); //timer0
void set_pwm(unsigned char duty_cycle);
