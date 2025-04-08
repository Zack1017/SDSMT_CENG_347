/*#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.c"

#define F_CPU 16000000UL    // 16 MHz clock
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

// Function prototypes
void USART0_init(unsigned int ubrr);
void USART0_transmit(char data);
char USART0_receive(void);
void USART0_sendString(const char* str);

int main(void)
{
    DDRB = 0x23;
    DDRA = 0xF0;

    // Initialize the LCD for 4-bit mode, two lines, and 5 x 8 dots
    // Inits found on Page 26 of datasheet and Table 7 for function set instructions
    LCD_init();
        
    // Initialize the USART0
    USART0_init(MYUBRR);
        
    char receivedChar;
    
    while (1)
    {
        // Receive a character from the terminal
        receivedChar = USART0_receive();
            
        // Display the received character on the LCD
        LCD_write_char(receivedChar);
    }
        
    return 0;
}

// Initialize the USART0 for serial communication
void USART0_init(unsigned int ubrr)
{
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Transmit a single character over USART0
void USART0_transmit(char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Put data into the buffer, sends the data
    UDR0 = data;
}

// Receive a single character from USART0
char USART0_receive(void)
{
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)));
    
    // Get and return received data from the buffer
    return UDR0;
}

// Send a string over USART0
void USART0_sendString(const char* str)
{
    while (*str)
    {
        USART0_transmit(*str++);
    }
}*/