; Blink LED on PB7 (ATMEGA 2560 pin 13)
; http://forum.arduino.cc/index.php?topic=159572#msg1194604

#define __SFR_OFFSET 0
  
#include "avr/io.h"

; let the C compiler know these are called elsewhere via external definition
.global start
.global blink

;start:
  sbi   DDRB,7  ; Set PB7 as output (set bit immediate)
  ret

blink: 
  ldi   r20,250 ; Set the delay duration in ms. Maximum value is 255.
  call  delay_n_ms
  sbi   PORTB,7 ; Set PB7 HIGH
  ldi   r20,250
  call  delay_n_ms
  cbi   PORTB,7 ; Set PB7 LOW ; (clear bit immediate)
  ret

;delay_n_ms:
  ; Delay about r20*1ms. Destroys r20, r30, and r31.
  ; One millisecond is about 16000 cycles at 16MHz.
  ; The basic loop takes about 5 cycles, so we need about 3000 loops.
  ldi   r31, 3000>>8 ; high(3000)
  ldi   r30, 3000&255  ; low(3000)

;delaylp:
  sbiw    r30, 1 ; subtract 1 word
  brne    delaylp ; branch if noto equal 
  subi    r20, 1 ; sub imident 
  brne    delay_n_ms ; branch not equal 
  ret
