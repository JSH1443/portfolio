#define F_CPU                           16000000UL

#include <avr/io.h>
#include <util/delay.h>


#define PORT_DATA                       PORTD

#define PORT_CONTROL                    PORTB

#define DDR_DATA                        DDRD

#define DDR_CONTROL                     DDRB

#define RS_PIN                          0

#define E_PIN                           1

#define COMMAND_CLEAR_DISPLAY           0x01

#define COMMAND_8_BIT_MODE              0x38

#define COMMAND_4_BIT_MODE              0x28

#define COMMAND_DISPLAY_ON_OFF_BIT     2
#define COMMAND_CURSOR_ON_OFF_BIT       1
#define COMMAND_BLINK_ON_OFF_BIT        0


void lcd_pulse_enable (void)
{
    PORT_CONTROL |= (1 << E_PIN);
    _delay_ms(1);
    PORT_CONTROL &= ~(1 << E_PIN);
    _delay_ms(1);
}

void lcd_write_data (uint8_t data)
{
    PORT_CONTROL |= (1 << RS_PIN);
    PORT_DATA = data;
    lcd_pulse_enable();
}

void lcd_write_command (uint8_t command)
{
    PORT_CONTROL &= ~(1 << RS_PIN);
    PORT_DATA = command;
    lcd_pulse_enable();
}

void lcd_clear (void)
{
    lcd_write_command(COMMAND_CLEAR_DISPLAY);
    _delay_ms(2);
}

void lcd_init (void)
{
    _delay_ms(50);

    DDR_DATA = 0xFF;
    DDR_CONTROL |= (1 << RS_PIN) | (1 << E_PIN);

    lcd_write_command(COMMAND_8_BIT_MODE);

    uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
    lcd_write_command(command);

    lcd_clear();

    lcd_write_command(0x06);
}

void lcd_write_string (char *string)
{
    uint8_t i;

    for (i = 0; string[i]; i++)
    {

        lcd_write_data(string[i]);
    }
}

void lcd_goto_xy (uint8_t row, uint8_t col)
{

    col %= 16;

    row %= 2;

    uint8_t address = (0x40 * row) + col;
    uint8_t command = 0x80 + address;

    lcd_write_command(command);
}

int lcd_mode (int sw1, int manual_flag)
{
    lcd_init();

     lcd_write_string("Select Mode");

    if(sw1 %2==1)
    {
     lcd_clear();
     lcd_write_string("Manual Mode");
    }
    else
    {
     lcd_clear();
     lcd_write_string("auto Mode");
    }
    if(manual_flag == 1)
    {
      switch(sw1)
      {
       case 1:
            lcd_clear();
            lcd_write_string("LOW");
            break;
       case 2:
            lcd_clear();
            lcd_write_string("MIDDLE");
            break;
       case 3:
            lcd_clear();
            lcd_write_string("HIGH");
            break;
       case 4:
            lcd_clear();
            lcd_write_string("STOP");
            sw1=0;
            break;
      }

    }
}




