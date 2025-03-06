; Count LED on PB7-4 (ATMEGA 2560 pin 13-10)
; http://forum.arduino.cc/index.php?topic=159572#msg1194604

#define __SFR_OFFSET 0
  
#include "avr/io.h"

; let the C compiler know these are called elsewhere via external definition
.global start
.global counter
.global delay_n_ms

start:
    ; Setup Pin 7-4 as output 
    sbi     DDRB,7
    sbi     DDRB,6
    sbi     DDRB,5
    sbi     DDRB,4

    ; Sets to known state 
    clr     r16
    out     PORTB, r16

    ; Sets count to zero
    clr     r17
    ret

counter:
    ldi     r20, 255            ; Set delay to 255ms
    call    delay_n_ms
    ldi     r20, 255            ; Set delay to 255ms
    call    delay_n_ms
    
    ; Preserve lower 4 bits of PORTB and update upper 4 bits with inverted count
    in      r18, PORTB          ; Load PORTB value
    ldi     r21, 0x0F           ; Load 0x0F  
    and     r18, r21            ; And R18 and 0x0F 
    mov     r19, r17            ; Copy count value
   
    ; Swap nibbles to shift left 4 bits
    mov     r22, r19            ;Creates copy
    and     r19, r21            ;Keep lower nibble
    lsl     r19                 ;Shift Left by 4 
    lsl     r19
    lsl     r19
    lsl     r19

    and     r22, r21            ; Keeps only upper nibble 
    lsl     r20                 ; shfits right by 4 
    lsl     r20
    lsl     r20
    lsl     r20

    or      r19, r20            ; combines the nibbles 

    ; Invers bits 
    ldi     r23, 0xFF           ; loads all ones 
    EOR     r19, r23            ; Xor to flip bits 

    and     r18, r21            ; Ensures only upper 4 are affected 
    or      r18, r19            ; Merge with PORTB lower 4 bits
    out     PORTB, r18          ; Output to PORTB

    ldi     r24, 1              ; Loads incerment value into regster 
    add     r17, r24            ; increments by value 

    and     r17, r21            ; Keep only lower 4 bits

    ret

delay_n_ms:
  ; Delay about r20*1ms. Destroys r20, r30, and r31.
  ; One millisecond is about 16000 cycles at 16MHz.
  ; The basic loop takes about 5 cycles, so we need about 3000 loops.
  ldi   r31, 3000>>8 ; high(3000)
  ldi   r30, 3000&255  ; low(3000)
  ldi   r25, 255
delaylp:
  sbiw    r30, 1
  brne    delaylp
  subi    r20, 1
  brne    delay_n_ms
  ret