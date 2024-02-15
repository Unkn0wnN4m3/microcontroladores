;
; actividad1.asm
;
; Created: 10/02/2024 20:28:09
; Author : unk0wnn4m3
;


; Replace with your application code
.def counter=r18
.def repeat=r19

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
        sbi DDRB, PB5 ; 1

        ; Activate pull-ups
        sbi PORTB, PB0
        sbi PORTB, PB1

        ;init stack
        ldi r16, high(RAMEND)
        out SPH, r16
        ldi r16, low(RAMEND)
        out SPH, r16

start:
        sbi PORTB, PB5
        rcall delay
        cbi PORTB, PB5
        rcall delay
        rjmp start

delay:
        ; starting counter with 0
        ldi counter, 0
        out TCNT1, counter

        ; starting repetitions with 0
        ldi repeat, 0

cycle:
        ; read from counter
        in counter, TCNT1

        ; 65535 max counter
        cpi counter, 
        brne cycle

        ; init counter with 0
        ldi counter, 0
        out TCNT1, counter

        ; repeat n times
        inc repeat
        cpi repeat, 12
        brne cycle



        ret

