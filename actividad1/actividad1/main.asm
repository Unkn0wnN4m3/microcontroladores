8;
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
.def counter = r17
.def repeat = r18
.def counter1 = r19
.def repeat1 = r20
.def counter2 = r21
.def repeat2 = r22
.def counter3 = r23
.def repeat3 = r24
.def temp = r16

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

        ldi temp, 0x05
        out TCCR0B, temp
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
        breq Start3
        rjmp selection

; 1hz
; (15625 * 1) / 250
Start:
        sbi PORTB, PB5
        call Delay
        cbi PORTB, PB5
        call Delay
        rjmp selection

Delay:
        ldi counter,0
        out TCNT0,counter
        ldi repeat,0;
loop:
        in counter,TCNT0
        cpi counter,250
        brne loop
        ldi counter,0
        out TCNT0,counter
        inc repeat
        cpi repeat,62
        brne loop
        ret

; 2.5hz
; (15625 * 0.4) / 250
Start1:
        sbi PORTB, PB5
        call Delay1
        cbi PORTB, PB5
        call Delay1
        rjmp selection

Delay1:
        ldi counter1,0
        out TCNT0,counter1
        ldi repeat1,0;
loop1:
        in counter1,TCNT0
        cpi counter1,250
        brne loop1
        ldi counter1,0
        out TCNT0,counter1
        inc 
        cpi repeat1,25
        brne loop1
        ret

; 50hz
; (15625 * 0.02) / 250
Start2:
        sbi PORTB, PB5
        call Delay2
        cbi PORTB, PB5
        call Delay2
        rjmp selection

Delay2:
        ldi counter2,0
        out TCNT0,counter2
        ldi repeat2,0;
loop2:
        in counter2,TCNT0
        cpi counter2,250
        brne loop2
        ldi counter2,0
        out TCNT0,counter2
        inc repeat2
        cpi repeat2,2
        brne loop2
        ret

; 10khz
; (15625* 0.0001) / 250
Start3:
        sbi PORTB, PB
        call Delay3
        cbi PORTB, PB5
        call Delay3
        rjmp selection

Delay3:
        ldi counter3,0
        out TCNT0,counter3
        ldi repeat3,0;
loop3:
        in counter3,TCNT0
        cpi counter3,250
        brne loop3
        ldi counter3,0
        out TCNT0,counter3
        inc repeat3
        cpi repeat3,1
        brne loop3
        ret
