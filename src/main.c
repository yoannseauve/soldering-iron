#include <stdio.h>

#include "uart.h"
#include "spi.h"
#include "timer.h"

int main(void)
{
    uart_init(9600);
    stdout = &UART;

    spi_init();
    unsigned char rx[2];

    init_tic();

    init_pwm();
    set_pwm(10);

    for(;;)
    {
        if(tic)
        {
            tic = 0;
            spi_transmit( NULL, rx, 2, SS);
            while(! spi_transmission_done());

            if(rx[1] & 1<<2)
                printf("ouvert\n");
            else
                printf("%d\n",  (((rx[1]>>3)&0x1f) | ((rx[0]&0x07)<<5))/4 );
        }
    }
    return 0;
}
