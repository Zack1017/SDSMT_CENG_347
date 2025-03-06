# Laboratory 3

## AVR Assembly

### Introduction
In this lab we will re-visit Lab 1 using AVR assembly to implement our 4-bit binary counter.

### Part 1:
Start with your Lab 1 wiring diagram for connecting four LEDs to the upper nybble of PORTB. Your goal is to get these to count from 0-15 similar to Lab 1, however we will use Assembly language as opposed to C. To enable the creation of assembly programs in the Platform.IO env., we need a couple items: 1) we need to create a new project called Lab3 (or your choice in naming) in your Lab3 directory tree and 2) we need to develop an external assembly listing where your code will be located.

Create a new Platform.IO project named Lab3 and save it to your working lab directory. In main.cpp (right figure), you’ll need to copy the contents of main.cpp in the .zip folder in D2L. Under the src directory in your project, you’ll need to create a new file called Blink.S (or whatever you like with the .S (capital) extension).

We will first create a simple program to make the LED blink on pin 13 (PORTB pin 7). As can be seen in the figure, we are going to define two new functions in assembly: start() and blink(). The start() function is simply initializing the port as output whereas the blink() function is responsible for blinking the LED at approximately 2Hz. Although we’ve told the Platform.IO (and really the avr-gcc compiler) that we will define two new functions externally, we can define as many as we want in the actual assembly listing (we just can’t call them from within our C project). This is important as you will need to define a delay_ms function to incorporate the delay within the assembly listing (this doesn’t need to be called from C unless you prefer). In the .S file, add the following code (below – in the Blink.S file from D2L). The #define on line 4 just tells the assembler how to offset PORTn address definitions (we want zero offset in this case). The #include will include the I/O port definitions, etc. The assembler directives .global tells the assembler these functions are global to the program so they can be called externally (i.e., the definition of extern start() and blink() above).

Functions in assembly are really just labels with assembly instructions to follow, however, they MUST end with some form of ret (we have used the default form in this case to return from subroutine). In the figure to the right, you’ll notice that we have defined both the start() and blink() functions. Start() does nothing more than initialize the data direction register to set PORTB bit 7 as an output (our LED) (sbi is the set bit immediate instruction). The blink() function simply turns on the LED on/off with a delay of approximately 250ms between. The delay comes from the function “delay_n_ms” that is invoked with the call instruction. Once implemented, you can go back to your Lab3 project and click the build/upload button to build and upload the code to your board. You should see the LED connected to Pin 13 blink at approximately 2Hz. 

Some things to note: The “delay_n_ms” function expects the number of ms to delay to be located in R20 (R20 is NOT preserved so it’s clobbered by the function). The “delay_n_ms” function also clobbers registers R30 and R31 (these are used by the function  “delaylp” to simply spin in place 3000 times (the internal workings of the loop requires just over 5 clock cycles so 3000*5 clock cycles is almost 1ms, this is multiplied by the value in R20 (we wrote 250) to get about a 250ms delay between the LED-on state and LED-off state. R20 is an 8-bit register!!!!! So you can NOT delay more than 255ms using this function unless you make multiple calls to it.

### Part 2:
Now that you can successfully control an LED on your board using assembly code, modify your code to:
1. Re-create the binary counter from Lab 1 (upper for bits of PORTB).
2. 2Extend the delay to something a bit more reasonable (it would be nice to delay 500ms to cycle through the count values at a rate of 1Hz – make this happen).

#### Hints:
1. Because you are only really using Assembly for your “code”, you can feel free to use whatever registers you’d like without too much worry of clobbering them (i.e., you’ll need a register to extend the delay).
2. You should ALWAYS be careful with setting/clearing bits in PORTs, we used the logical OR and logical AND to do this in C, you’ll want to investigate these instructions in assembly as well.
3. You use the out instruction to write to a port (this is true for all memory mapped ports such as PORTB as well as DDRB). For example, suppose you want to set the upper for bits of PORTB as output, you might consider:

    ; Set upper nybble of PORTB to output without affecting
    ; the rest of the PORT
    ldi R16, 0b11110000
    in R17, DDRB
    or R16, R17
    out DDRB, R16