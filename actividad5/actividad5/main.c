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
	
	//usart_received_char=UDR0;
	
	// si usart_receive() contirne un char, entonces necesitamos obtener ese caracter
	// del return, guardarlo en una variable temporal, en este caso en la variable global.
	// Para formar una string debemos guardar cada caracter en un array
	
	
	//char oled_text[64];
	//char received_char = ' ';
	//int i = 0;
	
	while(1)
	{
		//if (received_char != '\0') {
			//received_char = usart_receive();
			//oled_text[i++] = received_char;
		//}
	}
}

