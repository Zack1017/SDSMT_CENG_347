# Laboratory 4

## Serial Communication

### Introduction
In this lab our goals are three-fold: 1) interfacing the 8x8 LED matrix to display a default string of text and 2) interfacing our serial port to allow a user to modify the default string, and 3) connect both LED matrices together to have a continuous scrolling (two-digit of course).

### Part1:
The first part of the lab will begin by interfacing the 8x8 LED matrix display (illustrated left). You’ll note that the LED matrix has 5 connections through its header:
    • VCC: connected to power (+5V)
    • GND: connected to ground
    • DIN: Data in
    • CS: Chip select (data loaded when low, latched on rising)
    • CLK: Clock address/data
To drive the LED matrix, we use an integrated MAX 7219 device (functional block diagram illustrated below). The 7219 uses a 16-bit serial shift register where the first 8-bits define the command, and the second 8-bits define the data. You’ll want to write two “helper” functions to make your life easier. The first (call it WriteByte(unsigned char DATA)) is simply to fill the 16-bit data register with the address and data (8-bits at a time, piped similar to serial, the second simply sets the CS bit low, makes a call to the first function once for the address and a second time for the data, the sets the CS bit high to latch the data. For simplicity, we call this function WriteData(unsigned char addr, unsigned char data). The addr is simply the value 1-8 which corresponds to the row of the LED matrix (address: top to bottom) while the data is an 8-bit value where 0-clears the LED in that row and 1-sets the LED in that row.

Pseudo-code for WriteByte(unsigned char DATA): 
for each bit in DATA, do:
    Clear the CLK bit
    Isolate the msb in DATA and write to DIN
    Left shift DATA to load the next bit to the msb
    Set CLK to load the data into the data register

Note: For simplicity I defined each of the pins on PORTH as follows (this is not a requirement but makes life easy for wiring and bit isolation):

Pseudo-code for WriteData(unsigned char addr, unsigned char data):
Clear the CS bit
WriteByte(addr);
WriteByte(data);
Set the CS bit

You will also want to initialize the LED display (more info can be found on page 7 of the datasheet) which can be done with the following function:

I HIGHLY recommend you test your LED matrix display by writing a few characters to the display. Ultimately, you’ll want to encode all letters of the alphabet in a table that you can easily access for displaying your text message (you may use the look up table (LUT) attached as a .txt – simply copy this matrix into your program). Your deliverable for part 1 is to illustrate your LED matrix displaying the entire 0-9 and A-Z digits with a short delay between each character (you do NOT need to worry about lower case digits too).

### Part 2:
Now that you can successfully control the LED matrix on your board and cycle through the entire LUT, you are now in a position to get things rolling with the serial interface. The goal here is simple, allow the user to input a string in the terminal (the Arduino IDE has a built-in terminal so feel free to use that, otherwise Putty is also a good choice). You’ll want to set the serial monitor exactly as your setup your serial device on the ATMega2560. Because we don’t have an FTDI device, you will be using USART0 for read from the serial monitor and display the string on the LED matrix (each character individually with a similar slight delay between digits). You can set a max string length of 80 characters and DO NOT need to worry about punctuation or case (all upper case is okay for this lab). Recall, you will set USART0 with the following parameters: 9600 BAUD, 8-bit frame size, 1-stop bit, no parity. You can find the serial monitor under the tools menu. You will need to set the BAUD (it might be at 9600 by default) but all other settings are in order by default. You can then type a character (or string of characters) and hit send to send them down the serial line (you will know it’s sending data because the Rx LED on your development board will blink when each character is sent). Your deliverables for part 2 are to illustrate that you can a) send serial data to your board and your board echos that data back to the serial monitor and b) you can integrate your serial string with your LED matrix to display the string (character by character) on the LED matrix.

### Part 3:
Once you get parts 1 & 2 working correctly, it is time to connect the output of the matrix to the input on your lab partners matrix. You should then be able to display two characters at a time (alternating between the two). Your deliverables for part 3 are to illustrate that you have completed parts 1 & 2, as well as demonstrating you can display two characters on the LED matrices (one character on each LED matrix).