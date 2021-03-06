#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU               16000000L
#include <util/delay.h>

#define IN1                 PD0

#include <math.h>

void init_dc_motor(void)
{
    DDRB = 0xFF;
    DDRD = 0xFF;

    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1);
    TCCR2B |= (1 << WGM22);
    TCCR2B |= (1 << CS22);
}
int main(void)
{
    int count = 0;
    double speed, t;
    unsigned char velocity;

    init_dc_motor();

    DDRB &= ~(1 << DDB5);
    PORTB |= (1 << PORTB4);

    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT5);

    sei();

    while(1)
    {
        t = (double)count / 180.0 * 3.14192;
        speed = 255 * sin(t);
        velocity = (unsigned int)fabs(speed);

        if(speed >= 0)
        {
            PORTD |= 0x08;
            PORTB &= ~0x08;
            OCR2A = 255 - velocity;
        }
        else
        {
            PORTD &= ~0x08;
            PORTB |= 0x08;
            OCR2A = velocity;
        }

        count++;
        _delay_ms(20);
    }
}

ISR (PCINT0_vect)
{
    PORTB ^= 0x10;
}
