#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "spi.h"

#include <stdio.h>

SlaveSelect spi_slave;
volatile unsigned char spi_transmiting;
volatile unsigned char *spi_tx, *spi_rx;
volatile unsigned int spi_nbBytes, spi_count;

void spi_init()
{
    //SCK, MOSI, SS as outputs
    DDRB |= (1 << 2) | (1 << 3) | (1 << 5);
    //SS_ = 1
    PORTB |= (1 << 2);
    //7:interrupt enable, 6:spi enable, 5:lsb first, 4:master mode, 3:clk polarity, 2:clk phase, 1,0:clk frequency
    SPCR = ( 1 << 7 ) | ( 1 << 6 ) | ( 0 << 5 ) | ( 1 << 4 ) | ( 0 << 3 ) | ( 0 << 2 ) | ( 0 << 1 ) | ( 0 << 0 );
    //no double speed
    SPSR = 0;

    spi_transmiting = 0;
    spi_tx = NULL;
    spi_rx = NULL;
    spi_nbBytes = 0;
    spi_count = 0;
}

inline void spi_ssLow()
{
    switch(spi_slave)
    {
        case SS:
            PORTB &= ~(1 << 2);
            break;
        case SS2:
            break;
        default:
            break;
    }
}

inline void spi_ssHigh()
{
    switch(spi_slave)
    {
        case SS:
            PORTB |= (1 << 2);
            break;
        case SS2:
            break;
        default:
            break;
    }
}

void spi_transmit(unsigned char tx[], unsigned char rx[], unsigned int nbBytes, SlaveSelect slave)
{
    if(nbBytes)
    {
        while(spi_transmiting);
        spi_tx = tx;
        spi_rx = rx;
        spi_count = 0;
        spi_nbBytes = nbBytes;
        spi_transmiting = 1;
        spi_slave = slave;
        spi_ssLow();
        if(tx == NULL)
            SPDR = 0x0;
        else
            SPDR = *(tx ++);
    }

}

unsigned char spi_transmission_done()
{
    if((spi_nbBytes == spi_count) && (spi_transmiting == 0))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

ISR(SPI_STC_vect)   //SPI serial transfer complete
{
    volatile unsigned char trash;

    if(spi_transmiting)
    {
        if(spi_rx == NULL)
            trash = SPDR;
        else
            *(spi_rx ++) = SPDR;
        spi_count ++;
        if(spi_count < spi_nbBytes)
        {
            if(spi_tx == NULL)
                SPDR = 0x0;
            else
                SPDR = *(spi_tx ++);
        }
        else
        {
            spi_transmiting = 0;
            spi_ssHigh();
        }
    }
}
