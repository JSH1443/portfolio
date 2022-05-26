#define F_CPU          16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"

void adc_init (unsigned char channel)
{

    ADMUX |= 0x40;
    ADCSRA |= 0x07;
    ADCSRA |= 0x80;
    ADCSRA |= 0x20;
    ADMUX |= ((ADMUX & 0xE0) | channel);
    ADCSRA |= 0x40;
}

int read_adc (void)
{
    while (!(ADCSRA & 0x10))
    {
        ;
    }

    return ADC;
}

void int_to_string (int n, char *buf)
{
    sprintf(buf, "%04d", n);
    buf[4] = '\0';
}

int main(void)
{
    int read;
    char buf[5];

    DDRB = 0x20;

    uart_init();
    adc_init(0);

    while(1)
    {
        read = read_adc();
        int_to_string(read, buf);
        uart_string_trans(buf);
        uart_string_trans("\n");

        if (read < darkness_mean)
        {
            PORTB = 0x20;
        }
        else if (read > brightness_mean)
        {
            PORTB = 0x00;
        }
    }

    return 0;
}
