#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "LCD.c"

#define F_CPU 16000000UL    // 16 MHz clock
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

// Function prototypes
void USART0_init(unsigned int ubrr);
void USART0_transmit(char data);
char USART0_receive(void);
void USART0_sendString(const char* str);
void display_menu();
void scroll_text(const char* str);
void display_menu_final();
void display_menu_term();
void handle_option(char option);
void setLineOne();


int main(void)
{
    DDRB = 0x23;
    DDRA = 0xF0;

    // Initialize the LCD for 4-bit mode, two lines, and 5 x 8 dots
    // Inits found on Page 26 of datasheet and Table 7 for function set instructions
    LCD_init();
        
    // Initialize the USART0
    USART0_init(MYUBRR);
        
        
   // Redisplay the menu after processing
   _delay_ms(1000);
   display_menu();
   display_menu_term();
    
   while (1)
   {
       char buffer[16];          // Buffer to store the user's input
       uint8_t index = 0;        // Index to track the buffer position
       char receivedChar;
   
       // Clear the buffer
       memset(buffer, 0, sizeof(buffer));
   
       // Read characters until the user presses Enter
       while (1)
       {
           receivedChar = USART0_receive();
           
           // Break the loop if Enter is pressed
           if (receivedChar == '\n' || receivedChar == '\r')
           {
            USART0_transmit('\n');
               buffer[index] = '\0';  // Null-terminate the string
               break;
           }
   
           // Store the character in the buffer
           if (index < sizeof(buffer) - 1)
           {
               buffer[index++] = receivedChar;
               USART0_transmit(receivedChar);  // Echo back the character
           }
       }
   
       // Handle the option stored in the buffer
       if (index > 0)
       {
           handle_option(buffer[0]);  // Send the first character to handle_option
       }
   
       // Display the menu again
       USART0_transmit('\n');
       USART0_sendString("==========End of Option=========" );
       USART0_transmit('\n');
       USART0_transmit('\n');
       display_menu_term();
       display_menu_final();
       USART0_receive();
       
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
}

void display_menu_term()
{
    USART0_sendString("Weclome Options Are:");
    USART0_transmit('\n');
    USART0_sendString("1) single character");
    USART0_transmit('\n');
    USART0_sendString("2) string of characters");
    USART0_transmit('\n');
    USART0_sendString("3) string of characters the user enters");
    USART0_transmit('\n');
    USART0_sendString("4) scrolling text");
    USART0_transmit('\n');
    USART0_sendString("Enter Option: ");
}

// Display the menu on the LCD

void setLineOne()
{
    LCD_write_instruction(LCD_4bit_displayCLEAR);
    _delay_ms(80);
    LCD_write_instruction(LCD_4bit_cursorSET | LineOneStart);
    _delay_ms(80);
}


void display_menu()
{
    setLineOne();

    // Welcome Message 
    LCD_sendString("Welcome to Lab05"); 

    LCD_write_instruction(LCD_4bit_cursorSET | LineTwoStart);
    _delay_ms(80);

    LCD_sendString("Options:"); 
    _delay_ms(3000);

    //Option 1 message 
    setLineOne();

    scroll_text("1) single character");

    _delay_ms(1000);

    //setLineOne();
    
    //LCD_sendString("(prompt the user");
    //LCD_write_instruction(LCD_4bit_cursorSET | LineTwoStart);
    //_delay_ms(80);
    //LCD_sendString("for a character)"); 
    //_delay_ms(3000);

    //Option 2 message 
    setLineOne();

    scroll_text("2) string of characters");

    _delay_ms(1000);

    //setLineOne();

    //scroll_text("(constant string to be displayed - something like 'Welcome to my LCD') "); 
    //_delay_ms(3000);

    //Option 3 message 
    setLineOne();

    scroll_text("3) string of characters the user enters");

    _delay_ms(1000);

    //setLineOne();

    //scroll_text("(prompt the user for a string and display it to the LCD) "); 
    //_delay_ms(3000);

     //Option 4 message 
     setLineOne();
 
     scroll_text("4) scrolling text");
 
     _delay_ms(1000);
 
     //setLineOne();
 
     //scroll_text("(prompt the user for a string and scroll the display)"); 
     //1_delay_ms(3000);

     display_menu_final();
}

void display_menu_final()
{
    //Option Final 
    setLineOne();

    LCD_sendString("Enter Option: ");

    _delay_ms(1000);

    LCD_write_instruction(LCD_4bit_cursorSET | LineTwoStart);
    _delay_ms(80);

    LCD_sendString("1,2,3,4 - Enter"); 
    _delay_ms(3000);
}

// Handle user's menu option

void handle_option(char option)
{
    setLineOne();

    if(option == '1')
    {
        USART0_receive();
        USART0_sendString("Enter Character:" );
        char inputchar = USART0_receive();
        USART0_transmit(inputchar);
        
        LCD_write_char(inputchar);
        LCD_write_instruction(LCD_4bit_cursorSET | LineTwoStart);
        _delay_ms(80);
        LCD_write_char(inputchar);
        _delay_ms(80);
        USART0_transmit('\n');
    }
    else if(option == '2')
    {
        LCD_sendString("Hello!");
    }
    else if(option == '3')
    {
        USART0_receive();
        USART0_sendString("Enter String:" );
        char userStr[16];  // Buffer for user string
        int i = 0;
            
        // Receive and store string until newline or max length
        while (i < 15)
        {
            char ch = USART0_receive();
            USART0_transmit(ch);
            if (ch == '\n' || ch == '\r') break;  // Stop on newline
            userStr[i++] = ch;
        }
        userStr[i] = '\0';  // Null-terminate the string
            
        // Display the user-entered string
        LCD_sendString(userStr);
    }
    else if (option == '4')
    {
        scroll_text("Hellow World, I am Computer!");
    }
    else 
    {
        LCD_sendString("Invalid Option");
    }
    _delay_ms(2000);  // Delay before returning to menu
}

// Scrolls the text across the LCD
void scroll_text(const char* str)
{

    int len = strlen(str);
    
    // If the string is shorter than 16 chars, no need to scroll
    if (len <= 16)
    {
        LCD_write_instruction(0x01);        // Clear the display
        _delay_ms(30);
        LCD_sendString(str);
        _delay_ms(2000);
        return;
    }

    for (int i = 0; i < len - 15; i++)
    {
        LCD_write_instruction(0x01);        // Clear the display
        _delay_ms(20);

        // Print the next 16 characters
        for (int j = 0; j < 16; j++)
        {
            LCD_write_char(str[i + j]);
        }

        _delay_ms(500);  // Scrolling speed
    }
}