#include <avr/io.h>
#include <util/delay.h>

int count = 0;

int main()
{
  Serial.begin(9600);
  DDRB &= ~(1 << PB6);         // Clear PD2 (pin 2) bit in DDRD to set it as input

  DDRB |= (1 << PB7);         //setup PORTB (pin7) as an output

  //7Segment 
  DDRH |= (1 << PH4); //A
  DDRH |= (1 << PH3); //B
  DDRE |= (1 << PE3); //C
  DDRG |= (1 << PG5); //D
  DDRE |= (1 << PE5); //E
  DDRE |= (1 << PE4); //F
  DDRH |= (1 << PH5); //G

  //set PORTB to a known state
  //PORTB = 0xFF;
  
  seg(count);          //Updates 7 segment

  bool prevState = false; // Variable to store previous state

  while(true)                 //loop for continuous update checking 
  {
    Serial.println(count);
    bool currentState = PINB & (1 << PB6);

    if(currentState && !prevState)    // Check if pin 6 is HIGH
    {
      PORTB |= (1 << PB7);    // Sets 7 HIGH
      count++;                //Updates Count 
      Serial.println(count);
      if(count < 10 )         //Checks boundary 
      {
        Serial.println(count);
        seg(count);          //Updates 7 segment 
      }
      else 
      {
        Serial.println(count);
        count = 0;            //Resets count to 0
        seg(count);          //Updates 7 segment 
      }
    }
    else 
    {
      PORTB &= ~(1 << PB7);   //Sets 7 LOW
    }
    prevState = currentState;
  }
}

void seg(int count)
{
  //Clear Ports 
  PORTH &= ~(1 << PH4); //A
  PORTH &= ~(1 << PH3); //B
  PORTE &= ~(1 << PE3); //C
  PORTG &= ~(1 << PG5); //D
  PORTE &= ~(1 << PE5); //E
  PORTE &= ~(1 << PE4); //F
  PORTH &= ~(1 << PH5); //G
  Serial.println("Make it here");
  if(count == 0)
  {
    PORTH |= (1 << PH4); //A
    PORTH |= (1 << PH3); //B
    PORTE |= (1 << PE3); //C
    PORTG |= (1 << PG5); //D
    PORTE |= (1 << PE5); //E
    PORTE |= (1 << PE4); //F
    Serial.println("Make it here 1");
  }
  else if (count == 1)
  {
    PORTH |= (1 << PH3); //B
    PORTE |= (1 << PE3); //C
  }
  else if (count == 2)
  {
    PORTH |= (1 << PH4); //A
    PORTH |= (1 << PH3); //B
    PORTG |= (1 << PG5); //D
    PORTE |= (1 << PE5); //E
    PORTH |= (1 << PH5); //G
  }
  else if (count == 3)
  {
    PORTH |= (1 << PH4); //A
    PORTH |= (1 << PH3); //B
    PORTE |= (1 << PE3); //C
    PORTG |= (1 << PG5); //D
    PORTH |= (1 << PH5); //G
  }
  else if (count == 4)
  {
    PORTH |= (1 << PH3); //B
    PORTE |= (1 << PE3); //C
    PORTE |= (1 << PE4); //F
    PORTH |= (1 << PH5); //G
  }
  else if (count == 5)
  {
    PORTH |= (1 << PH4); //A
    PORTE |= (1 << PE3); //C
    PORTG |= (1 << PG5); //D
    PORTE |= (1 << PE4); //F
    PORTH |= (1 << PH5); //G
  }
  else if (count == 6)
  {
    PORTH |= (1 << PH4); //A
    PORTE |= (1 << PE3); //C
    PORTG |= (1 << PG5); //D
    PORTE |= (1 << PE5); //E
    PORTE |= (1 << PE4); //F
    PORTH |= (1 << PH5); //G
  }
  else if (count == 7)
  {
    PORTH |= (1 << PH4); //A
    PORTH |= (1 << PH3); //B
    PORTE |= (1 << PE3); //C
  }
  else if (count == 8)
  {
    PORTH |= (1 << PH4); //A
    PORTH |= (1 << PH3); //B
    PORTE |= (1 << PE3); //C
    PORTG |= (1 << PG5); //D
    PORTE |= (1 << PE5); //E
    PORTE |= (1 << PE4); //F
    PORTH |= (1 << PH5); //G
  }
  else 
  {

    PORTH |= (1 << PH4); //A
    PORTH |= (1 << PH3); //B
    PORTE |= (1 << PE3); //C
    PORTE |= (1 << PE4); //F
    PORTH |= (1 << PH5); //G
  }
}