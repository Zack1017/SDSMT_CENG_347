/*#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.c"

// Hardcoded initial time
volatile uint8_t hours = 12;
volatile uint8_t minutes = 34;
volatile uint8_t seconds = 45;

volatile uint16_t overflow_count = 0;  // Count Timer0 overflows

// Function to initialize Timer0 in Normal Mode
void timer0_init(void) {
    // Set Timer0 to Normal Mode
    TCCR0A = 0;  // Normal Mode
    TCCR0B = (1 << CS02) | (1 << CS00);  // Prescaler 1024
    TIMSK0 = (1 << TOIE0);  // Enable overflow interrupt
    sei();  // Enable global interrupts
}

// Function to update the clock time
void update_time() {
    seconds++;
    
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        
        if (minutes >= 60) {
            minutes = 0;
            hours++;
            
            if (hours >= 24) {
                hours = 0;  // Reset to midnight
            }
        }
    }
}

// Function to display the time on Serial Monitor
void display_time() 
{
    char time_str[9];  // Buffer to store formatted time HH:MM:SS
    
    // Format the time string as HH:MM:SS
    snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", hours, minutes, seconds);
    
    // Clear the LCD and move cursor to the beginning
    LCD_write_instruction(LCD_4bit_displayCLEAR);
    _delay_ms(80); // Allow time for the clear operation
    
    // Set cursor position to the first line
    LCD_write_instruction(LCD_4bit_cursorSET | LineOneStart);
    
    // Display the formatted time on the LCD
    for (int i = 0; time_str[i] != '\0'; i++) {
        LCD_write_char(time_str[i]);
    }
}

ISR(TIMER0_OVF_vect) 
{
    overflow_count++;
    
    if (overflow_count >= 61) {  // Roughly 1 second
        overflow_count = 0;
        update_time();
        display_time();
    }
}


int main(void)
{
    DDRB = 0x23;
    DDRA = 0xF0;

    timer0_init();           // Initialize Timer0

    //char MyChar = 'C';

    // Initialize the LCD for 4-bit mode, two lines, and 5 x 8 dots
    // Inits found on Page 26 of datasheet and Table 7 for function set instructions
    LCD_init();

    // Write a single character
    //LCD_write_char(MyChar);

    // line two
    //LCD_write_instruction(LCD_4bit_cursorSET | LineTwoStart);
    //_delay_us(80); // delay must be > 37us - datasheet forgets to mention this
    //MyChar = 'Q';
    //LCD_write_char(MyChar);

    while (1)
    {
        PORTB ^= 0x20;
        _delay_ms(500);
    }
    return 1;
}*/