#define F_CPU       16000000UL


#include "bluetooth_uart.h"
#include "uart.h"
#include "bluetooht.h"
#include "bldc.h"
#include "servo.h"


#define b_manual_mode         1
#define b_auto_mode           2
#define b_servo_start         3
#define b_servo_stop          4
#define b_low                 5
#define b_middle              6
#define b_high                7
#define b_stop                8
#define b_reset               9


volatile int bluetooth_rx_data;
int b_manual_mode_select=0;
int b_auto_mode_select=0;
float b_duty = 5.0;

ISR(USART3_RX_vect)
{
    bluetooth_rx_data = UDR3;
}

void bluetooth_mode(void)
{
  if(bluetooth_rx_data == b_manual_mode)
    {

     b_manual_mode_select =1;
     b_auto_mode_select =0;
     b_uart_string_trans("Manual Mode\n");

        if(bluetooth_rx_data == b_low)
        {
           bldc_low();
        }

        if(bluetooth_rx_data == b_middle)
        {
           bldc_middle();
        }

        if(bluetooth_rx_data==b_high)
        {
            bldc_high();
        }

        if(bluetooth_rx_data==b_stop)
        {
           bldc_stop();
        }
    }

    else if (bluetooth_rx_data == b_auto_mode)
    {
        b_auto_mode_select =1;
        b_manual_mode_select =0;
        b_uart_string_trans("Auto Mode\n");
        temperature_sensor();
        photocell_mode();
    }

       if(bluetooth_rx_data==b_servo_start)
         {
            b_duty +=0.1;
            servo_counter_clockwise(b_duty);

            if(b_duty>25.0)
            {
             for(b_duty=25.0; b_duty>5.0; b_duty-=0.1)
             {
                servo_clockwise(b_duty);
             }

            }
         }

         if(bluetooth_rx_data==b_servo_stop)
         {
          servo_stop();
         }


      if(bluetooth_rx_data==b_reset && (b_manual_mode_select==1 || b_auto_mode_select==1))
        {
            b_auto_mode_select=0;
            b_manual_mode_select=0;
            b_uart_string_trans("Select Mode\n");
        }

}

