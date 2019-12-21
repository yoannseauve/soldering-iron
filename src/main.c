#include <stdio.h>

#include "uart.h"
#include "spi.h"
#include "timer.h"
#include "screen.h"
#include "thermocouple.h"
#include "adc.h"

#include <avr/io.h>

#define MAX_TEMP 500
#define OPEN_CIRCUIT_MSG "ouvert"

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

    float in[3] = {0, 0, 0};
    float out[3] = {0, 0, 0};
    float output;

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
            //printf("%s\n", tx);
            lcd_write(tx);

            unsigned int potar = (unsigned int)(ADC_read()/(1024.0/MAX_TEMP));
            lcd_gotoXY(2, 3);
            sprintf(tx, "%d", potar);
            lcd_write(tx);


            //correcteur
            in[2] = in[1];
            in[1] = in[0];
            in[0] = potar - temp;

            out[2] = out[1];
            out[1] = out[0];
            out[0] = in[0]*0.94516595 - in[1]*1.84202271 + in[2]*0.89717046 + out[1]*1.98701299 - out[2]*0.98701299;

            if(in[0]>0.0 && in[1]<0.0 && in[2]<0.0)
            {
                in[0] = 0.0;
                in[1] = 0.0;
                in[2] = 0.0;
                out[0] = 0.0;
                out[1] = 0.0;
                out[2] = 0.0;
            }

            output = out[0];
            if(temp < 0)
                output = 0.0;

            if(output > 255)
                output = 255;

             if(output < 0)
                 output = 0;
            
            set_pwm((unsigned char)(output));

            lcd_gotoXY(0, 4);
            lcd_power((unsigned char)(output));

        }
    }
    return 0;
}
