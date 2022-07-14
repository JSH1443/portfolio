
#define F_CPU                           16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "bluetooth_uart.h"
#include "lcd.h"
#include "switch.h"
#include "bldc.h"
#include "servo.h"
#include "temp.h"
#include "phtocell.h"
#include "bluetooht.h"
#include "wifi.h"


int main(void)
{
    uart_init();
    b_uart_init();
    lcd_init();
    sw_init();
    BLDC_init();
    servo_init();
    temp_init();
    photocell_init();


    uart_string_trans("Select Mode\n");
    lcd_write_string("Select Mode\n");

    while(1)
   {
     switch_mode();
     wifi_mode();
     bluetooth_mode();
    _delay_ms(70);
   }



}



