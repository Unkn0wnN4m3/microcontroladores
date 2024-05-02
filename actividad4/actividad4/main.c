/*
 * actividad4.c
 *
 * Created: 30/04/2024 13:13:01
 * Author : huawe
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2C.h"
#include "ssd1306.h"
#include "adc.h"
#include "usart.h"


int main(void)
{
	
	init_i2c();
	InitializeDisplay();
	reset_display();
	init_adc_withINT();
	init_usart(207);
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
}

