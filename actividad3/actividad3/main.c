#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "ssd1306.h"
#include "adc.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	
	init_i2c();
	InitializeDisplay();
	reset_display();
	//init_adc_withoutINT();
	init_adc_withINT();
	
	sendStrXY("ADC converter:", 0, 0);
	sei();

	while (1) {
		//char buffer[10]=" ";
		//float temp = read_adc();
//
		//dtostrf(temp, 4, 1, buffer);
		//
		//sendStrXY(buffer, 1, 0);
	}
}
