#include <avr/io.h>
#include <avr/interrupt.h>
#include "ssd1306.h"
#include "usart.h"
#include "I2C.h"


int main(void)
{
	sei();
	init_i2c();
	InitializeDisplay();
	reset_display();
	init_usart(207);
	
	setXY(0,0);
	sendStr("LED status:");
	
	while(1) {
		int i = 0;

		while (i < 64) {
			char received_char = usart_receive();
			if (received_char == '\0') break;
			
			setXY(1, i);
			SendChar(received_char[i]);
			i++;
		}
	}
}

