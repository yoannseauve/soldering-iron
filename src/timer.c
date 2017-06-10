#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"

volatile unsigned char tic; //set on each tic

void init_tic() //timer1
{

    ICR1H = 0x7A;   //31250 for 1/2 sec
    ICR1L = 0x12;   //31250 for 1/2 sec

    TIMSK1 = (1<<5); //tic interrupt

    TCNT1H = 0;     //reset counter
    TCNT1L = 0;

    TCCR1A = 0;
    TCCR1B = (1<<4) | (1<<3) | (1<<2) | (0<<1) | (0<<0);  //CTC mod and clk/256 (start timer)
}

void init_pwm() //timer0
{

    DDRD |= (1<<6);

    TCNT0 = 0;      //reset counter
    OCR0A = 0;      // PWM 0%

    TIMSK0 = 0;

    TCCR0A = (1<<7) | (0<<6) | (0<<1) | (1<<0); //PWM, Phase Correct
    TCCR0B = (0<<3) | (1<<2) | (0<<1) | (1<<0); // 1/1024 prescaling
}

void set_pwm(unsigned char duty_cycle)
{
   OCR0A = duty_cycle;
}

ISR(TIMER1_CAPT_vect)    //timer1 interrupt
{
    tic = 1;
}
