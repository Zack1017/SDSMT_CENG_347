// LCD.c

// Data definitions and member functions for working LCD driver
// LCD KS0066U device

// Last Modified by: Randy C. Hoover

// Date: rev1 - 03/02/2020

// Hardware configuration: Assumes ATMega2560 operating at 16MHz
// Pin details below.

/**************************************************************************

The four data lines as well as the two control lines may be
implemented on any available I/O pin of any port.  These are
the connections used for this program:

| ATMega2560

 1  | | LCD |
|------------|-----------------|-----|
|         PA7|---------------->| D7  |
|         PA6|---------------->| D6  |
|         PA5|---------------->| D5  |
|         PA4|---------------->| D4  |
|            |                 | D3  |
|            |                 | D2  |
|            |                 | D1  |
|            |                 | D0  |
|         PB1|---------------->| E   |
|         GND|---------------->| RW  |
|         PB0|---------------->| RS  |
**************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

// Helpful LCD control defines
#define LCD_Reset             0b00110000        // reset the LCD to put in 4-bit mode
#define LCD_4bit_enable       0b00100000        // 4-bit data - can't set the line display or fonts until this is set
#define LCD_4bit_mode         0b00101000        // 2-line display, 5x8 font
#define LCD_4bit_displayOFF   0b00001000        // set display off
#define LCD_4bit_displayON    0b00001100        // set display on - no blink
#define LCD_4bit_displayON_B1 0b00001101        // set display on - with blink
#define LCD_4bit_displayCLEAR 0b00000001        // replace all chars with "space"
#define LCD_4bit_entryMODE    0b00000110        // set cursor to write/read from left -> right
#define LCD_4bit_cursorSET    0b10000000        // set cursor position

// For two line mode
#define LineOneStart 0x00
#define LineTwoStart 0x40                       // must set DDRAM address in LCD controller for line two

// Pin definitions for PORTB control lines
#define LCD_EnablePin 1
#define LCD_RegisterSelectPin 0

// Prototypes
void LCD_init(void);
void LCD_E_RS_init(void);
void LCD_write_4bits(uint8_t);
void LCD_EnablePulse(void);
void LCD_write_instruction(uint8_t);
void LCD_write_char(char);

// Important notes in sequence from page 26 in the KS0066U datasheet - initialize the LCD in 4-bit two line mode
// LCD is initially set to 8-bit mode - we need to reset the LCD controller to 4-bit mode before we can set anything else
void LCD_init(void)
{
    // Wait for power up - more than 30ms for vdd to rise to 4.5V
    _delay_ms(100);

    // Note that we need to reset the controller to enable 4-bit mode
    LCD_E_RS_init(); // Set the E and RS pins active low for each LCD reset

    // Reset and wait for activation
    LCD_write_4bits(LCD_Reset);
    _delay_ms(10);

    // Now we can set the LCD to 4-bit mode
    LCD_write_4bits(LCD_4bit_enable);
    _delay_us(80); // delay must be > 39us

    //////////////// system reset is complete - set up LCD modes ////////////////////
    // At this point we are operating in 4-bit mode
    // (which means we have to send the high-nibble and low-nibble separate)
    // and can now set the line numbers and font size
    // Notice: we use the "LCD_write_4bits()" when in 8-bit mode and the LCD_instruction() (this just
    // makes use of two calls to the LCD_write_4bits() function)
    // once we're in 4-bit mode. The set of instructions are found in Table 7 of the datasheet.
    LCD_write_instruction(LCD_4bit_mode);
    _delay_us(80); // delay must be > 39us

    // From page 26 (and Table 7) in the datasheet we need to:
    // display - off, display - clear, and entry mode - set
    LCD_write_instruction(LCD_4bit_displayOFF);
    _delay_us(80); // delay must be > 39us

    LCD_write_instruction(LCD_4bit_displayCLEAR);
    _delay_ms(80); // delay must be > 1.53ms

    LCD_write_instruction(LCD_4bit_entryMODE);
    _delay_us(80); // delay must be > 39us

    // The LCD should now be initialized to operate in 4-bit mode, 2 lines, 5 x 8 dot fontsize
    // Need to turn the display back on for use
    LCD_write_instruction(LCD_4bit_displayON);
    _delay_us(80); // delay must be > 39us
}

void LCD_E_RS_init(void)
{
    // Set up the E and RS lines to active low for the reset function
    PORTB &= ~(1 << LCD_EnablePin);
    PORTB &= ~(1 << LCD_RegisterSelectPin);
}

// Send a byte of Data to the LCD module
void LCD_write_4bits(uint8_t Data)
{
    // We are only interested in sending the data to the upper 4 bits of PORTA
    PORTA &= 0b00001111; // Ensure the upper nybble of PORTA is cleared
    PORTA |= Data;       // Write the data to the data lines on PORTA

    // The data is now sitting on the upper nybble of PORTA - need to pulse enable to send it
    LCD_EnablePulse();   // Pulse the enable to write/read the data
}

// Write an instruction in 4-bit mode - need to send the upper nybble first and then the lower nybbles
void LCD_write_instruction(uint8_t Instruction)
{
    // ensure RS is low
    // PORTB &= ~(1 << LCD_RegisterSelectPin);
    LCD_E_RS_init(); // Set the E and RS pins active low for each LCD reset

    LCD_write_4bits(Instruction);       // write the high nybble first
    LCD_write_4bits(Instruction << 4); // write the low nybble
}

// Pulse the Enable pin on the LCD controller to write/read the data lines - should be at least 230ns pulse width
void LCD_EnablePulse(void)
{
    // Set the enable bit low -> high -> low
    // PORTB &= ~(1 << LCD_EnablePin); // Set enable low
    // _delay_us(1);                  // wait to ensure the pin is low
    PORTB |= (1 << LCD_EnablePin);  // Set enable high
    _delay_us(1);                  // wait to ensure the pin is high
    PORTB &= ~(1 << LCD_EnablePin); // Set enable low
    _delay_us(1);                  // wait to ensure the pin is low
}

// write a character to the display
void LCD_write_char(char Data)
{
    // Set up the E and RS lines for data writing
    PORTB |= (1 << LCD_RegisterSelectPin); // Ensure RS pin is set high
    PORTB &= ~(1 << LCD_EnablePin);      // Ensure the enable pin is low
    LCD_write_4bits(Data);                // write the upper nybble
    LCD_write_4bits(Data << 4);          // write the lower nybble
    _delay_us(80);                       // need to wait > 43us
}

// write a string
void LCD_sendString(const char* str)
{
    while (*str)
    {
        LCD_write_char(*str++);
    }
}