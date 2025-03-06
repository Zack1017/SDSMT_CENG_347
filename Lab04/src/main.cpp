#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define F_CPU 16000000UL  // 16 MHz clock speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define MAX_STR_LEN 80

// put function declarations here:

const int CLK = PB4; //Pin 10
const int DIN = PB5; //Pin 11
const int CS  = PB6; //Pin 12

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

void USART0_transmit(unsigned char data) 
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
    UDR0 = data;
}

// Function to send a byte to MAX7219
void WriteByte(unsigned char DATA) 
{
  for (int i = 0; i < 8; i++) 
  {
      PORTB &= ~(1 << CLK);  // Clear clock bit
      if (DATA & 0x80)        // Check MSB
      {
        PORTB |= (1 << DIN);  // Set DIN high
        //PORTB |= (0x0 << DIN);
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
void WriteData(unsigned char addr, unsigned char data1, unsigned char data2) 
{
  PORTB &= ~(1 << CS);  // Clear CS (start communication)
  WriteByte(addr);      // Send address
  WriteByte(data1);      // Send data
  WriteByte(addr);      // Send address
  WriteByte(data2);      // Send data
  PORTB |= (1 << CS);   // Set CS (latch data)
}


// MAX7219 initialization
void InitMatrix() {
  WriteData(0x09, 0x00, 0x00);  // Decode mode: No decode
  WriteData(0x0A, 0x03, 0x03);  // Intensity: Medium
  WriteData(0x0B, 0x07, 0x07);  // Scan limit: Display all rows
  WriteData(0x0C, 0x01, 0x01);  // Shutdown: Normal operation
  WriteData(0x0F, 0x00, 0x00);  // Display test: Off
}

void USART0_init(unsigned int ubrr) 
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Enable receiver and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data, 1 stop bit, no parity
}

unsigned char USART0_receive(void) 
{
    while (!(UCSR0A & (1 << RXC0))); // Wait for data to be received
    return UDR0;
}

void Display_Character(unsigned char index1, unsigned char index2) 
{
  //USART0_transmit(index);
  for (int i = 0; i < 8; i++) 
  {
      WriteData(i + 1, charTable[index2][i],charTable[index1][i]);
      //USART0_transmit(charTable[index1][i]);
      //USART0_transmit(charTable[index][i]);
  }
}

int main(void) {
    DDRB |= (1 << DIN) | (1 << CS) | (1 << CLK);
    USART0_init(MYUBRR);
    InitMatrix();
    //USART0_sendString("USART Initialized. Enter text:\r\n");

    char receivedString[MAX_STR_LEN];
    int index = 0;

    while (1) {
        char receivedChar = USART0_receive();
        USART0_transmit(receivedChar);
         // Echo back

        if (receivedChar == '\n' || receivedChar == '\r' || index >= MAX_STR_LEN - 1) 
        {
            receivedString[index] = '\0'; // Null-terminate the string
            for (uint8_t i = 0; i < index; i++) 
            {
                //USART0_transmit(receivedString[i]);
                if(receivedString[i] != '\0' && receivedString[i+1] != '\0')
                {
                    Display_Character(receivedString[i], receivedString[i+1]);
                    _delay_ms(500); // Delay between characters
                }               
                
            }
            index = 0; // Reset for next input
        } 
        else 
        {
            if(receivedChar >= '0' && receivedChar <= '9')
            {
                receivedString[index++] = receivedChar - '0';
            }
            else if (receivedChar >= 'A' && receivedChar <= 'Z')
            {
                receivedString[index++] = receivedChar - 55;
            }
            else if (receivedChar >= 'a' && receivedChar <= 'z')
            {
                receivedString[index++] = receivedChar - 87;
            }
            //receivedString[index++] = receivedChar;
        }
    }
}
