;
; actividad1.asm
;
; Created: 10/02/2024 20:28:09
; Author : unk0wnn4m3
;


; Replace with your application code
.cseg
.org 0x00

        ; Define the ports
        ; Making b0 = in, b1 = in and b2 = out
        ; | * | * | * | * | * | * | * | * |
        ; | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | PB
        ;   0   0   0  0   0   1   0  0 DDRB
        ;   0   0   0  0   0   0   0  1 PORTB
        ;   0   0   0  0   0   0   1  0 PINB
        ; DDRB -> in or out
        ; PORB -> in = res on / res off; out = 1 / 0
        ; PINB -> in = watcher
        cbi DDRB, PB0 ; 0
        cbi DDRB, PB1 ; 0

        ; WARN: must be the builtin LED
        sbi DDRB, PB2 ; 1

        ; TCNT timer/counter
        ; 

start:
