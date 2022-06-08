#include <avr/io.h>
#include <avr/interrupt.h>


volatile int sw1;
volatile int sw2;
volatile int manual_flag;
volatile int auto_flag;

int sw_init (void)
{


    EICRA |= (1 << ISC01);
    EICRA |= (1 << ISC11);

    EIMSK |= (1 << INT0);
    EIMSK |= (1 << INT1);

    sei();
}

int manual_mode (void)
{
  manual_BLDC(sw1, manual_flag);
  manual_servo(sw2, manual_flag);
}

void auto_mode (void)
{
    temp_mode(auto_flag);
    photocell_mode(auto_flag);
}

void switch_mode (void
{
   sw_init();

   if (sw1 % 2 == 1 && sw2 == 1)
    {
        lcd_mode(sw1, manual_flag);
        sw1 = 0;
        sw2 = 0;
        manual_flag = 1;
        auto_flag = 0;
        manual_mode();
    }
    else if(sw1 % 2== 0 && sw2 ==1)
    {
        lcd_mode(sw1, manual_flag);
        sw1 = 0;
        sw2 = 0;
        auto_flag = 1;
        manual_flag = 0;
        auto_mode();
    }

}

ISR (INT0_vect)
{
    sw1++;

}

ISR (INT1_vect)
{
    sw2++;

}

