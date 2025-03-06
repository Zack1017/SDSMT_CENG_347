#include <avr/io.h>
#include <util/delay.h>

int main()
{

  DDRB &= ~(1 << PB2);// Clear PD2 (pin 2) bit in DDRD to set it as input

  DDRB |= (1 << PB7);//setup PORTB (pin7) as an output

  //set PORTB to a known state
  //PORTB = 0xFF;

  //loop for continuous blinking
  while(true)
  {
    if(PINB & (1 << PB2))// Check if pin 2 is HIGH
    {
      PORTB |= (1 << PB7);
    }
    else 
    {
      PORTB &= ~(1 << PB7);
    }
  }
}