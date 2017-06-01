#include "spi.h"

float read_thermocouple()
{
    unsigned char rx[2];

    spi_switchMod(SPI_MOD_1);

    spi_transmit( NULL, rx, 2, SS);
    while(! spi_transmission_done());


    if(rx[1] & 1<<2)
        return -1.0;

    int four_temp = (((rx[1]>>3)&0x1f) | ((rx[0]&0x07)<<5));

    return four_temp/4.0 ;
}
