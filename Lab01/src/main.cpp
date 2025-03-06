#include <avr/io.h>
#include <util/delay.h>
#include <avr/io.h>
#include <util/delay.h>

int count = 0; 

int main()
{
  DDRB |= 0xF0;     //setup PORTB (pin7-4) as an output
  PORTB &= ~0xFF;   //set PORTB to a known state

   while(true)
  {
    PORTB = (PORTB & 0x0F) | (count << 4);  //toggle PORTB
    _delay_ms(500); //wait 500 ms
    count = (count + 1) & 0x0F; //Update count
  }
}