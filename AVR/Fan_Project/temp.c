#define F_CPU          16000000UL

#define low_min      32
#define low_max      34
#define middle_min   34
#define middle_max   36
#define high_min     36
#define stop_min     32


#include "lcd.h"
#include "uart.h"
#include "temp.h"
#include "bldc.h"



void temp_init (void)
{
    ADMUX |= (1 << REFS0);
    ADMUX |= (1 << MUX0);
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

void temperature_sensor (void)
{

    int read;
    char buf[5];


       read = (5.0 * read_temp() * 100.0) / 1024;
        temp_tring(read, buf);
        uart_string_trans(buf);
        uart_string_trans("\n");

         if (read<stop_min)
         {
           bldc_stop();
         }

         else if (read >low_min && read < low_max )
         {
            bldc_low();
         }
        else if (read>middle_min && read<middle_max)
         {
            bldc_middle();
         }
        else if (read>high_min)
         {
            bldc_high();
         }

}








