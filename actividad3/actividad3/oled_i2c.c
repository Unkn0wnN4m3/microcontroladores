#include "oled_i2c.h"

void send_command(uint8_t command) {
	start();
	write_i2c(0x78); // OLED address + write mode
	write_i2c(0x00); // Control byte: Co = 0, D/C# = 0 (Command)
	write_i2c(command); // Send command
	stop();
}

void send_data(uint8_t data) {
	start();
	write_i2c(0x78); // OLED address + write mode
	write_i2c(0x40); // Control byte: Co = 0, D/C# = 1 (Data)
	write_i2c(data); // Send data
	stop();
}

void init_oled(void) {
	init_i2c(); // Initialize I2C communication
	_delay_ms(100); // Delay for stability
	
	send_command(SSD1306_DISPLAY_OFF); // Turn off display
	
	// Initialization sequence
	send_command(SSD1306_SET_DISPLAY_CLOCK_DIV);
	send_command(0x80); // suggested ratio 0x80
	
	send_command(SSD1306_SET_MULTIPLEX_RATIO);
	send_command(0x3F); // 1/64 duty
	
	send_command(SSD1306_SET_DISPLAY_OFFSET);
	send_command(0x00); // no offset
	
	send_command(SSD1306_SET_START_LINE | 0x00); // line #0
	
	send_command(SSD1306_CHARGE_PUMP);
	send_command(0x14); // enable charge pump
	
	send_command(SSD1306_MEMORY_MODE);
	send_command(0x00); // horizontal addressing mode
	
	send_command(SSD1306_SEG_REMAP | 0x01); // column address 127 is mapped to SEG0
	
	send_command(SSD1306_COM_SCAN_DIR_DEC); // scan direction
	
	send_command(SSD1306_SET_COM_PINS);
	send_command(0x12); // set COM pins hardware configuration
	
	send_command(SSD1306_SET_CONTRAST_CONTROL);
	send_command(0xCF); // contrast value
	
	send_command(SSD1306_SET_PRECHARGE_PERIOD);
	send_command(0xF1); // phase 1 period of 15 DCLK, phase 2 period of 1 DCLK
	
	send_command(SSD1306_SET_VCOM_DESELECT);
	send_command(0x40); // Vcomh deselect level
	
	send_command(SSD1306_DISPLAY_ON); // turn on OLED display
}

void clear_oled(void) {
	int i, j;
	for (i = 0; i < OLED_HEIGHT / 8; i++) {
		send_command(0xB0 + i); // Set page address
		send_command(0x00); // Set lower column address
		send_command(0x10); // Set higher column address
		for (j = 0; j < OLED_WIDTH; j++) {
			send_data(0x00); // Clear entire page
		}
	}
}

void write_text(char* text, uint8_t x, uint8_t y) {
	int i = 0;
	while (text[i] != '\0') {
		if (text[i] == '\n') {
			// Move to the next line
			y += 8;
			x = 0;
			} else {
			send_command(0xB0 + (y / 8)); // Set page address
			send_command(0x00 + (x & 0x0F)); // Set lower column address
			send_command(0x10 + ((x >> 4) & 0x0F)); // Set higher column address
			send_data(text[i]);
			x += 6; // Width of each character
		}
		i++;
	}
}
