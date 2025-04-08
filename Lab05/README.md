# Laboratory 5

## Serial Code and LCD Display

### Lab Objectives:
The objective of this lab is to explore setting up your serial communication system to transmit data to/from your development board to your LCD. In addition to simply data transmission, we’ll be developing an LCD device driver to display the message sent by your serial terminal (or Putty).

### Procedure:
#### LCD Driver and Display
You will be using the LCD 1602 series (16 x 2) in 4-bit data transmission mode. BE WARNED, THE LCD TIMING INITIALIZAITON SEQUENCE IS A BIT “FINICKY”. We’ll go through the details here to make your life a bit easier. First, the LCD is connected to PORTB (pins 0&1) for enable and reset. Second, we use the upper nibble of PORTA for our data lines (as illustrated in Figure 1). Once connected, you should get something that looks like Figure 2 (note this is just for the LCD, you’ll wire the serial communication later).

![Figure 1Pinout illustration on the ATMega2560 device.](/assets/images/Figure1.png)
Figure 1Pinout illustration on the ATMega2560 device.

![Figure 2 Wiring illustration with your LCD and your development board](/assets/images/Figure2.png)
Figure 2 Wiring illustration with your LCD and your development board


You will want to read the datasheet thoroughly to get an idea of how the on-board LCD controller (KS0066U device) works to display characters on the LCD. Pay specific attention to page 26 (4-bit initialization) and Table 7 (instruction table). These are the essential components needed to get up and running. To save you some trial and error, and make life a bit easier, the following code may be useful: LCD.c

Now we’re ready to test our functions to make sure we can actually write something to the LCD. A simple test might look like the snippet to the left. If successful, you should now see a C in the first position of the top line and a Q in the first position of the bottom line.

### Part1:
#### Timer:
Create a digital clock with second precision using Timer0 in Normal mode, starting from a hardcoded initial time.

### Part2:
#### Serial Setup
Next you will interface a serial port (USART0) for 8-bit, asynchronous, no parity, one stop bit communication (take caution here as this is the serial port that is connected to your computer via the USB cable). You will use this serial port, along with your favorite terminal (I recommend Putty) to send messages to your LCD. Your setup will look something like the figure below.

#### To Do: Writing Data
Once you have everything up and running (at least you think you do), you need to illustrate the following
tasks:

You will design a menu driven system that (upon reset) will be displayed to the user. The menu will have 4 options as detailed below): 1) single character (prompt the user for a character), 2) string of characters (constant string to be displayed – something like “Welcome to my LCD”), 3) string of characters the user enters (prompt the user for a string and display it to the LCD), and 4) scrolling text (prompt the user for a string and scroll the display)

1. Print a single character to each line (the code provided should do this by default so this should be an easy one).
2. Print an entire string of characters to the LCD screen (similar to the above, the string can be hard coded but you must illustrate what happens if the string is too big?).
3. Interface your LCD with the USART so you can transmit and display messages between your computer and the ATMega2560 board.
a. You do NOT need to have perfect error checking (i.e., if the user enters more characters than will fit on a single line you can either only print the full line OR use a word-wrap and wrap to the next line.
b. If the user presses the “return” key, you should wrap to the beginning of the second line (i.e., you need to have the ability to print multiple lines). If you are on the second line, and they press the “return” key again, go back to the beginning of the first line and begin overwriting their first message.
c. Provide some mechanism for the user to clear the message on the LCD (this can be a special character you’re looking for like ^C or something similar).
4. Enable a mechanism for the text to scroll across the LCD (moves to the right and comes in from the left).

