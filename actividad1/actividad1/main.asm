.include "./m328Pdef.inc"
.equ Value = 0xc2f7

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

        ; builtin LED
        sbi DDRB, PB5 ; 1

        ; Activate pull-ups
        sbi PORTB, PB0
        sbi PORTB, PB1

Start:
        sbi PORTB, PB5
        call Delay
        cbi PORTB, PB5
        call Delay
        rjmp Start

Delay:
        ; set up timer counter to Value
        ldi r30, high(Value)
        sts TCNT1H, r30
        ldi r30, low(Value)
        sts TCNT1L, r30

        ; set normal mode
        ldi r31, 0x00 
        sts TCCR1A, r31
        ldi r31, 0x05  ; 1024 prescaler
        sts TCCR1B, r31

Loop:
        sbis TIFR1, TOV1  ; skip if TOV1 = 1
        rjmp Loop
        sbi TIFR1, TOV1  ; Clear TOV1 writing 1
        ; stop timer1
        ldi r30, 0xFF
        sts TCCR1B, r30
        ret
