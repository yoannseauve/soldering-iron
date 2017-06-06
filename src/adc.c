#include <avr/io.h>

void ADC_init()
{
    ADMUX = ( 0 << 7 ) | ( 1 << 6 ) | ( 0 << 5 ) | ( 0 << 4 ) | ( 0 << 2 ) | ( 0 << 1 ) | ( 0 << 0 ); //AVcc as Vref, right align, ADC0
    ADCSRA = ( 1 << 7 ) | ( 0 << 6 ) | ( 0 << 5 ) | ( 0 << 4 ) | ( 1 << 2 ) | ( 1 << 1 ) | ( 1 << 0 ); //ADC enabled, no autotriger, prescaler 128
    DIDR0 = ( 0 << 7 ) | ( 0 << 6 ) | ( 0 << 5 ) | ( 0 << 4 ) | ( 0 << 2 ) | ( 0 << 1 ) | ( 1 << 0 ); //ADC0 digital input buffer disables
}

unsigned int ADC_read()
{
    ADCSRA |= ( 1 << 6 );
    while (ADCSRA & ( 1 << 6 ));

    unsigned char low = ADCL; //16 bit register reading

    return ((unsigned int)(low) | (ADCH << 8));
}
