#include <stdio.h>
#include "uartConfig.h"

#ifdef _UART_USED_
extern FILE UART;

void uart_init(unsigned int baudRate);
void uart_transmit_char(char data);
void uart_transmit(char data[], unsigned char size);
unsigned char uart_receiv_buffer_avalable();
unsigned char uart_read(char data[], unsigned char size);
char uart_read_char();

#endif
