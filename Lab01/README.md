# Laboratory 1

## Getting Started, GPIO, and Debugging

### Introduction
The purpose of this laboratory is twofold: 1) get up and running with VS Code/Platform.IO and 2) interfacing and debugging your code for future labs. We will perform each in two parts as outlined below.

### Part 1:
Download and follow the instruction for getting VS Code/Platfom.IO up and running on your board.

Import the AVR I/O library and delay library using the following #include files at the top of your project:

    #include <avr/io.h>
    #include <util/delay.h>

You will need to use the function “_delay_ms(x)” to delay a specific number of milliseconds. For the remainder of the lab, download the Blink.cpp and copy the code into your Platform. IO main.cpp code file (do not worry about what all the commands are doing at this stage, we’re simply  trying to ensure we can compile code and upload to your board). Once you have the code downloaded, compiled, and uploaded to your board (as per the tutorial under the resources tab on D2L), you should see the LED connected to Pin 7 on PORTB blinking at 1Hz intervals (500ms on and 500ms off).

### To Do:
1. Play with the input parameter for the delay function to change the rate at which the LED
blinks
    i) Change it to 1000 for a 2Hz blink rate.
    ii) Change it to 100 for a 10HZ blink rate.
    iii) No remove it altogether (comment it out) and document what you notice. What’s happening here?

### Note:
The LED on board is wired to PORTB Pin7 (PB7) as seen from the pinout below. Note that all pins on the AVR devices are multipurpose. You’ll notice a LOT of things going on in the figure with respect to PB7. It’s also listed as: 26, PB7, PCINT7, 0C1C, -13-, OC0A, and the orange symbol indicates the LED connection. We will configure this pin as a standard output to drive the LED, but we’ll get to what the other functions are in the duration of the course. For now, all CENG 347L Arduino IDE and GPIO we care about is the -13- means PWM pin 13 that is actually printed on the board, and PB7 implies PORTB Bit 7.

### Part 2:
Now that you can successfully write code and get it onto your microcontroller board, you will extend the above code to create a 4-bit binary counter (i.e., count from 0-15 in binary) using PORTB. To illustrate you can count in binary, you will connect 4 of your LEDs to the high nybble (i.e., PB4, PB5, PB6, PB7). Because microcontrollers aren’t meant to drive LEDs directly (even though they source enough current, it’s common practice to simply use them as logic gates not drivers), we will connect the anodes to a common source +5V and connect the cathodes to each of the PORTB pins as indicated above. Be sure to current limit by connecting a resistor in series with the LED and the supply. Note: by driving the LEDs in this manner you will be creating inverse logic, i.e., a 0 written to PB4 will turn the LED on whereas a 1 written to B4 will turn the LED off (you can address this in your source code to get a proper counter). An example schematic for a single LED connected to PB4 is illustrated below:

### Part 3
Now that we can successfully run code on our boards and understand some basic I/O functionality, let’s do some debugging. As before, download and follow the debugging tutorial provided under the resources tab on D2L. Go ahead and start the debugger by setting some break points before you write to PORTB (assuming you are using Part 2 of this lab for your source code). Now single step through the code and answer the following questions.

1. What are the contents of PORTB after assignment?
2. If you keep stepping, does PORTB change? Why or why not?
3. What if instead of single step, you continue? Does this change things?
4. What’s going on here?

### Part B
Debugging with Atmel ICE and PlatformIO
Step 1: Connecting Atmel ICE to JTAG on ATMega2560 To begin, take the 10-pin squid cable and connect the 100 mm connector into the AVR port of the Atmel ICE. With some wires from your kit, connect the cable to the JTAG of the Atmega2560 located in the high nybble of PORTF. The pins are as follows: Board ➔ Squid Cable [TCK] PF4 (A4) ➔ Pin 1 , [TMS] PF5 (A5) ➔ Pin 5, [TDO] PF6 (A6) ➔ Pin 3 ,[TDI] PF7 (A7) ➔ Pin 9, [VTG] Vcc (5v) ➔ Pin 4, [GND] Ground ➔ Pin 2 & 10 Tips: Pins 6, 7, 8 are not connected. Labels for pins 6 and 9 are not disambiguated; be sure to count the wires to ensure you have the correct one!

Plug the Atmel ICE into your lab computer. A red light should appear indicating it has power. Then connect your ATMega2560 board to the computer while it is still connected to JTAG, and a green light should appear on the Atmel ICE. If both lights are lit then the debugger is both powered and can see connections to the board.

To validate your connections in the previous step, log into the computer and open a terminal. Type in “avarice -4 -r” and you should see an output similar to what is shown below: