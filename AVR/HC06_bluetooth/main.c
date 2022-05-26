#define F_CPU       16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
volatile unsigned char value;

ISR(USART_RX_vect)
{
    value = UDR0;
}
int main(void)
{
    DDRB=0xff;
    PORTB=0x00;

    unsigned char data;

    uart_init();
    sei();

    while(1)
    {
        if(value=='1')
        {
            PORTB |=0x01;
            PORTB &= ~0x02;

        }
        else if(value=='2')
        {
            PORTB |= 0x02;
            PORTB &= ~0x01;
        }
        /*data = uart_recv();
        if(data=='1')
        {
            PORTB |=0x01;
            PORTB &= ~0x02;

        }
        else if(data=='2')
        {
            PORTB |= 0x02;
            PORTB &= ~0x01;
        }
        uart_trans(data);*/
    }

    return 0;
}
