;
;
; ████████╗██╗███╗   ███╗███████╗██████╗ 
; ╚══██╔══╝██║████╗ ████║██╔════╝██╔══██╗
;    ██║   ██║██╔████╔██║█████╗  ██████╔╝
;    ██║   ██║██║╚██╔╝██║██╔══╝  ██╔══██╗
;    ██║   ██║██║ ╚═╝ ██║███████╗██║  ██║
;    ╚═╝   ╚═╝╚═╝     ╚═╝╚══════╝╚═╝  ╚═╝
;
;

.include "./m328Pdef.inc"
.def temp = r16
.equ Value = 0xE17B
.equ Value1 = 0xF3CB
.equ Value2 = 0xFF64
.equ Value3 = 0xFFFD

.cseg
.org 0x00

        ;init stack
        ldi temp,high(RAMEND)
        out SPH,temp
        ldi temp,low(RAMEND)
        out SPL,temp

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
;
selection:
        in r16, PINB
        cpi r16, 0x00
        breq Start

        in r16, PINB
        cpi r16, 0x01
        breq Start1

        in r16, PINB
        cpi r16, 0x02
        breq Start2

        in r16, PINB
        cpi r16, 0x03
        rjmp Start3

        rjmp selection

; The equation to obtain the desired frequency is:
; TOP = Fosc / (2 * N * f)
; f = desired output frequency
; Fosc = micro frequency
; N = prescaler
; TOP = max value

; 1hz
; 16*10^6 / (2 * 1024 * 1) = 7812.5
; 65536 - 7812 = 57724
; Value = 57724 = 0xE17B
Start:
        sbi PORTB, PB5
        call Delay
        cbi PORTB, PB5
        call Delay
        rjmp selection

Delay:
        ldi r30, High(Value)
        sts TCNT1H, r30
        ldi r30, Low(Value)
        sts TCNT1L, r30         ;Setup Timer Counter TCNT1 = Value
        ldi r31, 0x00           ;0b00000000 - normal mode
        sts TCCR1A, r31
        ldi r31, 0x05           ;0b00000101, prescaler = 1024
        sts TCCR1B, r31         ;Timer will start counting after this
                                                        ;instruction is executed.
Loop:   Sbis TIFR1, TOV1        ;If TOV1=1, skip next instruction
        Rjmp Loop                       ;else, loop back and check TOV1 flag
        sbi TIFR1, TOV1         ;Clear TOV1 bit by writing a 1 to it
        ldi r30, 0xFF           ;0b11111111
        sts TCCR1B, r30         ;Stop timer1
        Ret

; 2.6hz
Start1:
        sbi PORTB, PB5
        call Delay1
        cbi PORTB, PB5
        call Delay1
        rjmp selection

Delay1:
        ldi r30, High(Value1)
        sts TCNT1H, r30
        ldi r30, Low(Value1)
        sts TCNT1L, r30         ;Setup Timer Counter TCNT1 = Value
        ldi r31, 0x00           ;0b00000000 - normal mode
        sts TCCR1A, r31
        ldi r31, 0x04           ;0b00000101, prescaler = 1024
        sts TCCR1B, r31         ;Timer will start counting after this
                                                        ;instruction is executed.
Loop1:   Sbis TIFR1, TOV1        ;If TOV1=1, skip next instruction
        Rjmp Loop1                       ;else, loop back and check TOV1 flag
        sbi TIFR1, TOV1         ;Clear TOV1 bit by writing a 1 to it
        ldi r30, 0xFF           ;0b11111111
        sts TCCR1B, r30         ;Stop timer1
        Ret

; 50hz
Start2:
        sbi PORTB, PB5
        call Delay2
        cbi PORTB, PB5
        call Delay2
        rjmp selection

Delay2:
        ldi r30, High(Value2)
        sts TCNT1H, r30
        ldi r30, Low(Value2)
        sts TCNT1L, r30         ;Setup Timer Counter TCNT1 = Value
        ldi r31, 0x00           ;0b00000000 - normal mode
        sts TCCR1A, r31
        ldi r31, 0x05           ;0b00000101, prescaler = 1024
        sts TCCR1B, r31         ;Timer will start counting after this
                                                        ;instruction is executed.
Loop2:   Sbis TIFR1, TOV1        ;If TOV1=1, skip next instruction
        Rjmp Loop2                       ;else, loop back and check TOV1 flag
        sbi TIFR1, TOV1         ;Clear TOV1 bit by writing a 1 to it
        ldi r30, 0xFF           ;0b11111111
        sts TCCR1B, r30         ;Stop timer1
        Ret

; 10khz
Start3:
        sbi PORTB, PB5
        call Delay3
        cbi PORTB, PB5
        call Delay3
        rjmp selection

Delay3:
        ldi r30, High(Value3)
        sts TCNT1H, r30
        ldi r30, Low(Value3)
        sts TCNT1L, r30         ;Setup Timer Counter TCNT1 = Value
        ldi r31, 0x00           ;0b00000000 - normal mode
        sts TCCR1A, r31
        ldi r31, 0x04           ;0b00000101, prescaler = 256
        sts TCCR1B, r31         ;Timer will start counting after this
                                                        ;instruction is executed.
Loop3:   Sbis TIFR1, TOV1        ;If TOV1=1, skip next instruction
        Rjmp Loop3                       ;else, loop back and check TOV1 flag
        sbi TIFR1, TOV1         ;Clear TOV1 bit by writing a 1 to it
        ldi r30, 0xFF           ;0b11111111
        sts TCCR1B, r30         ;Stop timer1
        Ret
