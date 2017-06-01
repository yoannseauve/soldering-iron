#include <stdio.h>

#include "uart.h"
#include "spi.h"
#include "timer.h"
#include "screen.h"
#include "thermocouple.h"

#include <avr/io.h>

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

    for(;;)
    {
        if(tic)
        {
            
            tic = 0;
            /*
            spi_transmit( NULL, rx, 2, SS);
            while(! spi_transmission_done());

            if(rx[1] & 1<<2)
                printf("ouvert\n");
            else
            printf("%d\n",  (((rx[1]>>3)&0x1f) | ((rx[0]&0x07)<<5))/4 );
            */
            //    spi_transmit( tx, NULL, 16, SS2);

            lcd_clear();
            lcd_gotoXY(2, 2);
            char tx[10];
            float temp = read_thermocouple();
            if(temp < 0)
                sprintf(tx, "ouvert");
            else
                sprintf(tx, "%d", (int)(temp));
            printf("%s", tx);
            lcd_write(tx);
        }
    }
    return 0;
}
