/*#include <avr/io.h>
#include <util/delay.h>
//#include <Arduino.h>

#define USART_BAUDRATE 57600
#define BAUD_PRESCALE F_CPU / (USART_BAUDRATE * 16UL) -1

// put function declarations here:

const int CLK = PB4; //Pin 10
const int DIN = PB5; //Pin 11
const int CS  = PB6; //Pin 12


#define F_CPU 16000000UL  // 16 MHz clock speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define MAX_STR_LEN 80
void USART0_transmit(unsigned char data) 
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
    UDR0 = data;
}

void USART0_init(unsigned int ubrr) 
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data, 1 stop bit, no parity
}

// Character lookup table (example for 0-9 and A-Z)
const unsigned char charTable[36][8] = {
  {0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x00, 0x00}, // 0
  {0x00, 0x42, 0x7F, 0x40, 0x00, 0x00, 0x00, 0x00}, // 1
  {0x62, 0x51, 0x49, 0x49, 0x46, 0x00, 0x00, 0x00}, // 2
  {0x22, 0x41, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00}, // 3
  {0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, 0x00, 0x00}, // 4
  {0x27, 0x45, 0x45, 0x45, 0x39, 0x00, 0x00, 0x00}, // 5
  {0x3C, 0x4A, 0x49, 0x49, 0x31, 0x00, 0x00, 0x00}, // 6
  {0x01, 0x71, 0x09, 0x05, 0x03, 0x00, 0x00, 0x00}, // 7
  {0x36, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00}, // 8
  {0x46, 0x49, 0x49, 0x29, 0x1E, 0x00, 0x00, 0x00}, // 9
  {0x7E, 0x09, 0x09, 0x09, 0x7E, 0x00, 0x00, 0x00}, // A
  {0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00}, // B
  {0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00, 0x00}, // C
  {0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00, 0x00, 0x00}, // D
  {0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, 0x00, 0x00}, // E
  {0x7F, 0x09, 0x09, 0x09, 0x01, 0x00, 0x00, 0x00}, // F
  {0x3E, 0x41, 0x49, 0x49, 0x7A, 0x00, 0x00, 0x00}, // G
  {0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x00, 0x00}, // H
  {0x00, 0x41, 0x7F, 0x41, 0x00, 0x00, 0x00, 0x00}, // I
  {0x20, 0x40, 0x41, 0x3F, 0x01, 0x00, 0x00, 0x00}, // J
  {0x7F, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00}, // K
  {0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00}, // L
  {0x7F, 0x02, 0x04, 0x02, 0x7F, 0x00, 0x00, 0x00}, // M
  {0x7F, 0x02, 0x04, 0x08, 0x7F, 0x00, 0x00, 0x00}, // N
  {0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00, 0x00, 0x00}, // O
  {0x7F, 0x09, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00}, // P
  {0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00, 0x00, 0x00}, // Q
  {0x7F, 0x09, 0x19, 0x29, 0x46, 0x00, 0x00, 0x00}, // R
  {0x46, 0x49, 0x49, 0x49, 0x31, 0x00, 0x00, 0x00}, // S
  {0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, 0x00, 0x00}, // T
  {0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, 0x00, 0x00}, // U
  {0x0F, 0x30, 0x40, 0x30, 0x0F, 0x00, 0x00, 0x00}, // V
  {0x7F, 0x20, 0x18, 0x20, 0x7F, 0x00, 0x00, 0x00}, // W
  {0x63, 0x14, 0x08, 0x14, 0x63, 0x00, 0x00, 0x00}, // X
  {0x07, 0x08, 0x70, 0x08, 0x07, 0x00, 0x00, 0x00}, // Y
  {0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x00, 0x00}  // Z
};



// Function to send a byte to MAX7219
void WriteByte(unsigned char DATA) 
{
  for (int i = 0; i < 8; i++) 
  {
      PORTB &= ~(1 << CLK);  // Clear clock bit
      if (DATA & 0x80)        // Check MSB
      {
        PORTB |= (1 << DIN);  // Set DIN high
      }   
      else
      {
        PORTB &= ~(1 << DIN); // Set DIN low
      }
      DATA <<= 1;             // Shift left
      PORTB |= (1 << CLK);    // Set clock to load bit
  }
}


// Function to send address + data to MAX7219
void WriteData(unsigned char addr, unsigned char data) 
{
  USART0_transmit(data);
  //Serial.println(addr);
  //USART0_Transmit(data - '0');
  PORTB &= ~(1 << CS);  // Clear CS (start communication)
  WriteByte(addr);      // Send address
  WriteByte(data);      // Send data
  PORTB |= (1 << CS);   // Set CS (latch data)
}


// MAX7219 initialization
void InitMatrix() {
  WriteData(0x09, 0x00);  // Decode mode: No decode
  WriteData(0x0A, 0x03);  // Intensity: Medium
  WriteData(0x0B, 0x07);  // Scan limit: Display all rows
  WriteData(0x0C, 0x01);  // Shutdown: Normal operation
  WriteData(0x0F, 0x00);  // Display test: Off
}

// Function to display a character on LED matrix
void Display_Character(unsigned char index) 
{
  //USART0_Transmit(index);
  for (int i = 0; i < 8; i++) {
      WriteData(i + 1, charTable[index][i]);
      //USART0_Transmit(char(charTable[index][i]));
  }
}


int main() 
{
    DDRB |= (1 << DIN) | (1 << CS) | (1 << CLK);
        InitMatrix();  // Initialize MAX7219 LED matrix

    while (1) 
    {
        for(int i =0; i < 32; i++)
        {
          Display_Character(i);
          _delay_ms(500);
        }
    }

    return 0;
}*/