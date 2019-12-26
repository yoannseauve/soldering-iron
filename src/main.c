#include <stdio.h>

#include "uart.h"
#include "spi.h"
#include "timer.h"
#include "screen.h"
#include "thermocouple.h"
#include "adc.h"
#include "linearisation.h"

#include <avr/io.h>

#define MAX_TEMP 500
#define OPEN_CIRCUIT_MSG "ouvert"

#define Te 0.5 //sampling frequency
#define Kp 2.0 //PID proportional parameter
#define Kd 0.8 //PID derivator parameter
#define tau 130.0 //PI integrator parameter

#define NUMBUFF_SIZE 80


int main(void)
{
    uart_init(9600);
    stdout = &UART;

    spi_init(SPI_MOD_1);
    //unsigned char rx[2];

    init_tic();

    init_pwm();

    screen_init();

    lcd_clear();
    ADC_init();

    double in[3] = {0, 0, 0};
    double ind[3] = {0, 0, 0};
    double out[2] = {0, 0};
    unsigned char PWM_consigne;


    char caracMode = 0;
    int caracNumIn = 0;
    int caracPWM = 0;

    for(;;)
    {
        if(tic)
        {
            tic = 0;

            lcd_clear();

            lcd_gotoXY(2, 2);
            char tx[10];
            float temp = read_thermocouple();
            if(temp < 0)
                sprintf(tx, OPEN_CIRCUIT_MSG);
            else
                sprintf(tx, "%d", (int)(temp));
            lcd_write(tx);

            /// uart commande
            char inChar=uart_read_char();
            while(inChar != 0)
            {
                if (inChar == '\r')
                    caracPWM = (caracNumIn <= 255)? caracNumIn : 255;
                if (inChar == 'c')
                    caracMode = 1;
                if (inChar == 'r')
                    caracMode = 0;
                if(inChar >= '0' && inChar <= '9')
                    caracNumIn = 10 * caracNumIn + (inChar - '0');
                else
                    caracNumIn=0;
                inChar=uart_read_char();
            }


            /// end uart commande


            lcd_gotoXY(2, 3);
            unsigned int potar = (unsigned int)(ADC_read()/(1024.0/MAX_TEMP));
            if (caracMode == 0)
                sprintf(tx, "%d", potar);
            else
                sprintf(tx, "carca: %d", caracPWM);
            lcd_write(tx);


            //correcteur

            //PI

            //PID
            in[0] = potar - temp;
            if (out[0] > 0 && out[0] < 43.6576) //if no saturation
                out[0] = out[1] + Kp*(1.0+(Te/tau)+(Kd/Te))*in[0] - Kp*(1.0+2.0*(Kd/Te))*in[1] + Kp*(Kd/Te)*in[2];
            else    //do not charg integrater when in saturation
                out[0] = out[1] + Kp*(1.0+(Kd/Te))*in[0] - Kp*(1.0+2.0*(Kd/Te))*in[1] + Kp*(Kd/Te)*in[2];

            in[2] = in[1];
            in[1] = in[0];
            out[1] = out[0];

            //linearisation of the iron response

            PWM_consigne = linearisation(out[0]);

            if (caracMode == 0)
            {
                set_pwm(PWM_consigne);
                printf("potar: %d\ttemp: %c%d%d%d\tPWM: %d\r", potar, (temp<0)?'-':' ', (int)(temp/100), ((int)(temp/10))%10, ((int)(temp))%10, PWM_consigne);
            }
            else
            {
                set_pwm(caracPWM);
                printf("carac PWM:%d, temp:%c%d%d%d\r", caracPWM, (temp<0)?'-':' ', (int)(temp/100), ((int)(temp/10))%10, ((int)(temp))%10);
            }

            lcd_gotoXY(0, 4);
            lcd_power(PWM_consigne);

        }
    }
    return 0;
}

