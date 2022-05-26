#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{

    DDRB = 0x08;


    PORTB |= (1 << PORT3);


    PCICR |= (1 << PCIE0);


    PCMSK0 |= (1 << PCINT5);


    sei();

    while(1)
    ;

    return 0;
}

ISR (PCINT0_vect)
{
    PORTB ^= 0x08;
}
