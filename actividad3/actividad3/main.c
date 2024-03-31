#include <avr/io.h>
#include <util/delay.h>
//#include "adc_graph.h"

int main(void) {
	// Simulando valores de ADC y canal ADC
	uint16_t adc_value = 512; // Valor del ADC
	uint8_t adc_channel = 3; // Canal del ADC

	// Mostrar gráfica y texto en la pantalla OLED
	// WARN:NECESITA CORRECCÓN LA LIBRERIA
	//show_adc_graph(adc_value, adc_channel);

	while (1) {
		// Tu código principal aquí
	}

	return 0;
}
