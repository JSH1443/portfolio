#define F_CPU          16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"



void temp_init (void)
{
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADIF);
    ADCSRA |= (1 << ADSC);

    DDRF = (1 << PORT0);
}

int read_temp (void)
{
    while (!(ADCSRA & 0x10))
    {
        ;
    }

    return ADC;
}

void temp_tring (int n, char *buf)
{
    sprintf(buf, "%04d", n);
    buf[4] = '\0';
}

void temp_mode (int auto_flag2)
{
    int read;
    char buf[5];
    int temp;

    uart_init();
    temp_init();
   while(1)
   {
     if(auto_flag2!=1)
            break;

     if(auto_flag2==1)
     {
        read = (5.0 * read_temp() * 100.0) / 1024;
        temp_tring(read, buf);
        uart_string_trans(buf);
        uart_string_trans("\n");
        lcd_write_string(read);

         if (read < 28 && read > 24)
         {
            temp = 1;
         }
        else if (read>28 && read<30)
         {
            temp = 2;
         }
        else if (read>30)
         {
            temp = 3;
         }
         else if(read<24)
         {
           temp = 4;
         }
         auto_BLDC(temp, auto_flag2);
         _delay_ms(500);
        }
     }
}








