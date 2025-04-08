# Laboratory 2

## GPIO, PIR & 7-SEG

### Introduction
In this lab we will investigate the GPIO ports in a little more detail. In addition, we’ll look at interfacing motion detection sensing along with our single 7-segment display to determine how many times someone has entered a specific region.

### Part1:
The initial segment of this project involves integrating a Passive Infrared (PIR) motion sensor to monitor activity near the entrance of a smart home. The motion sensor, positioned outside close to the door, detects movement. You’ll want to connect the 5v pin to the 5v buss and be sure to connect the common ground to both the breadboard and your development board. You can then connect the output pin to an input port of your choosing (say bit-5 on PORTH – pin 8 on your dev. Board).

When motion is detected, this pin will be driven HIGH (to +5v) and remain there x-seconds depending on the delay (this is controlled via the upper-left potentiometer in the figure). The output pin is LOW (0v) otherwise. You can also play around with the sensitivity of the PIR (detection range) through the upper-right potentiometer in the figure. To validate you have part 1 working, connect an LED to PORTB (I’d recommend PIN7 but it’s up to you) such that when motion is detected, the LED is illuminated. It will stay illuminated for x-seconds before shutting off as long as no motion is detected. Recall: When I want to read a PORT, is must use the PINn declaration as opposed to writing to a PORT where I use the PORTn declaration.

![Figure 1](/Lab02/assets/images/Figure1.png)


### Part2:
Now that you can successfully detect motion with the PIR sensor, the next step is to determine how many times the PIR sensor has been triggered (0-9). If the PIR sensor is triggered more than 9 times, it will reset back to 0. For this purpose, we will interface with the single 7-segment display included in your kit (shown right). Note that the 7-segment display can display values 0-9 using the LED segments embedded in the display. The “com” is connected to a common ground and the individual segments are connected to an output PORT of your choosing (note we generally don’t like to drive the LEDs from the ATMega, however we will accept this for the current lab – be sure to place a current limiting resistor in series with each LED segment).

![Figure 2](/Lab02/assets/images/Figure2.png)


### Part3:
Having successfully connected and tested the 7-segment display (I would verify this by writing the digits 0-9 to the display and ensure they are doing what you expect), the final step is to integrate both parts into a complete motion counter for a smart home. Note: you may consider creating an array with the appropriate output to generate the digits 0-9 so you can simply index into the array and output that value to PORTn. You will now integrate part 1 and part 2 into a fully functional motion counter. Each time motion is detected, you will increment the 7-segment display which is installed in the main room of the house to count the number of times it is activated. Once the count reaches 9, you will simply reset the count back to zero and start again.