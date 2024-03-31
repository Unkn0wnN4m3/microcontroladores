#include "adc_graph.h"
#include <stdio.h>

// Función para mostrar la gráfica y el texto del canal ADC en la pantalla OLED
void show_adc_graph(uint16_t adc_value, uint8_t adc_channel) {
	// Initialize OLED
	init_oled();
	
	// Clear OLED
	clear_oled();

	// Convert ADC value to voltage (assuming Vref is 5V)
	float voltage = (adc_value * 5.0) / 1023.0;

	// Convert voltage to temperature (example conversion, adjust as needed)
	float temperature = voltage * 100.0; // Example conversion

	// Display ADC channel and temperature on OLED
	char text[20];
	sprintf(text, "Channel: ADC%d", adc_channel);
	write_text(text, 10, 10); // Display channel info

	// Display temperature graph (adjust position and scale as needed)
	int graph_height = temperature * 2; // Scale factor for graph
	for (int i = 0; i < graph_height; i++) {
		send_command(0xB0 + (i / 8)); // Set page address
		send_command(0x00 + (i & 0x0F)); // Set lower column address
		send_command(0x10 + ((i >> 4) & 0x0F)); // Set higher column address
		send_data(0xFF); // Draw graph line
	}
}
