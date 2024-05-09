#include <avr/io.h>
#include <stdlib.h>	//conversion to ASCII
#include <avr/interrupt.h>
#include "i2c.h"
#include "ssd1306.h"

void init_adc_withoutINT(void)
{
	ADMUX=(1<<REFS0);	//selects Vref
	//(AVCC with external capacitor at AREF pin)
	//Entrada AVcc= 5v y Aref= con un capacitor a GND
	//Internamente: Vref=0-5v
	ADCSRA = (1<<ADEN);//enable ADC
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	//Prescaler div factor =128
	//fo=1,000,000/128 ~ 7Khz
}

uint16_t read_adc(void)
{
	ADMUX &=0b11111000;				//Selects ADC channel (0-5)
	ADCSRA|=(1<<ADSC);				//start conversion
	while(!(ADCSRA & (1<<ADIF)));	//wait for conversion complete
	ADCSRA|=(1<<ADIF);				//clear flag for next conversion
	return(ADC);					//return sample value
}

ISR (ADC_vect)
{
	uint8_t LowPart = ADCL;	//10-bit resolution
	uint16_t TenBitResult = ADCH << 2 | LowPart >> 6;
	
	char ascii_temp [10];

	dtostrf(TenBitResult, 4, 1, ascii_temp);  //4 integers, 1 decimals
	
	if (PINC0) {
		sendStrXY("A0 active:", 2, 0);
	}
	else if (PINC1) {
		sendStrXY("A1 active:", 2, 0);
	}
	else if (PINC2) {
		sendStrXY("A2 active:", 2, 0);
	}
	else if (PINC3) {
		sendStrXY("A3 active:", 2, 0);
	}
	else if (PINC4) {
		sendStrXY("A4 active:", 2, 0);
	}
	
	setXY(3,0);
	sendStr(ascii_temp);
	
	//start another conversion
	ADCSRA |= 1<<ADSC;
}

void init_adc_withINT(void)
{
	ADCSRA |=(1 << ADEN);	//enable adc
	ADCSRA |=(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); // activate prescaler fo=16,000,000Hz/128~125KHz
	ADMUX |=(1 << ADLAR);	//left justified (ADCH bit9-2, ADCL bit1-0)
	//ADMUX |=(1 << MUX0);	//Selects ADC channel (0-5)
	ADMUX |=(1 << REFS0);	//Selects Vref(pag 257)//AVcc= 5v & Aref= with capacitor to GND
	ADCSRA |= 1 << ADIE;	//enable ADC interrupts
	ADCSRA |= 1 << ADSC;	//start conversion
}