#include <avr/io.h>
#include <avr/interrupt.h>
#include "uartConfig.h"
#include "uart.h"

#ifdef _UART_USED_

char uartTxBuffer[UART_BUFFER_SIZE]; 
char* volatile uartTxBufferWrite;
char* volatile uartTxBufferRead;

char uartRxBuffer[UART_BUFFER_SIZE]; 
char* volatile uartRxBufferWrite;
char* volatile uartRxBufferRead;

unsigned char uartTransmiting;

void uart_init(unsigned int baudRate)
{
    uartTxBufferWrite = uartTxBuffer;
    uartTxBufferRead = uartTxBuffer;
    uartRxBufferWrite = uartRxBuffer;
    uartRxBufferRead = uartRxBuffer;

    uartTransmiting = 0;

    if(baudRate > 0 && baudRate <= 1000000) //valide baudrate
    {
        /* Set baud rate */
        unsigned int ubrr = (1000000/baudRate) -1;
        UBRR0H = (unsigned char)(ubrr>>8);
        UBRR0L = (unsigned char)(ubrr);
        /* Enable receiver and transmitter , and anable receiv and send interrupt*/
        UCSR0B = (1 << 7) | (0 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (0 << 2) | (1 << 1) | (1 << 0); 
        /* Set frame format: 8data, 1stop bit */
        UCSR0C = (0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (0 << 0); 
        sei();// enable global interrupts:
    }
}

void uart_transmit(char data[], unsigned char size)
{
    if(size == 0)
        return;
    unsigned char i;
    for(i=0; i < size; i++)
    {
        uart_transmit_char(data[i]);
    }
}

void uart_transmit_char(char data)
{    
    if( uartTransmiting == 0 )
    {
        /* Wait for empty transmit buffer */
        while ( !( UCSR0A & (1 << 5)) ) 
            PINB = 1<<7;
        /* Put data into buffer, sends the data *  */
        UDR0 = data;
        uartTransmiting = 1;
        UCSR0B |= (1 << 5); //enable UDRE interrupt
    }
    else
    {
        while( (uartTxBufferWrite == uartTxBufferRead -1) || ((uartTxBufferRead == uartTxBuffer) && (uartTxBufferWrite == uartTxBuffer + UART_BUFFER_SIZE - 1)) ); //wait for free space in Tx buffer
        *uartTxBufferWrite = data;  // put character in buffer

        uartTxBufferWrite++;           //increment buffer pointer
        if(uartTxBufferWrite == uartTxBuffer + UART_BUFFER_SIZE)
        {
            uartTxBufferWrite = uartTxBuffer;
        }
    }
}

unsigned char uart_receiv_buffer_avalable()
{
    if (uartRxBufferWrite < uartRxBufferRead)
        return (UART_BUFFER_SIZE - (uartRxBufferRead - uartRxBufferWrite));
    else
        return (uartRxBufferWrite - uartRxBufferRead);
}

unsigned char uart_read(char data[], unsigned char size)
{
    unsigned char i;
    unsigned char nbReads;

    nbReads = uart_receiv_buffer_avalable();
    if( size < nbReads )
        nbReads = size;

    for(i=0; i < nbReads; i++)
    {
        data[i] = uart_read_char();
    }
    return nbReads;
}

char uart_read_char()
{    
    char data;

    if(uartRxBufferRead == uartRxBufferWrite) //buffer enpty
        return 0;
    else
        data = *uartRxBufferRead;    //read data

    uartRxBufferRead++;        //increment buffer pointer
    if(uartRxBufferRead == uartRxBuffer + UART_BUFFER_SIZE)
    {
        uartRxBufferRead = uartRxBuffer;
    }
    return data;
}

ISR(USART_RX_vect)    //uart RX interrupt
{
    char data=UDR0;

    if(!( (uartRxBufferWrite == uartRxBufferRead -1) || ((uartRxBufferRead == uartRxBuffer) && (uartRxBufferWrite == (uartRxBuffer + UART_BUFFER_SIZE - 1)))) )  //if ther is free space in Rx buffer
    {
        (*uartRxBufferWrite) = data; //read data

        uartRxBufferWrite++;           //increment buffer pointer
        if(uartRxBufferWrite >= (uartRxBuffer + UART_BUFFER_SIZE))
        {
            uartRxBufferWrite = uartRxBuffer;
        }
    }
}

ISR(USART_UDRE_vect)    //uart  UDRE interrupt
{
    if(uartTxBufferWrite == uartTxBufferRead) //TX buffer empty
    {
        uartTransmiting = 0;
        UCSR0B &= ~(1 << 5); //disable UDRE interrupt
    }
    else
    {
        UDR0 = *uartTxBufferRead;    //transmit character
        uartTxBufferRead++;                        //increament buffer pointer
        if(uartTxBufferRead == uartTxBuffer + UART_BUFFER_SIZE)
        {
            uartTxBufferRead = uartTxBuffer;
        }
    }
}

int uartWrapper(char c, FILE *stream)
{
    uart_transmit_char(c);
    return 0;
}
FILE UART = FDEV_SETUP_STREAM(uartWrapper, NULL, _FDEV_SETUP_WRITE);

#endif
