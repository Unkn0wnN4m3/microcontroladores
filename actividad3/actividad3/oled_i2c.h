#ifndef OLED_H
#define OLED_H

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

// Define SSD1306 Commands
#define SSD1306_DISPLAY_OFF 0xAE
#define SSD1306_SET_DISPLAY_CLOCK_DIV 0xD5
#define SSD1306_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_SET_START_LINE 0x40
#define SSD1306_CHARGE_PUMP 0x8D
#define SSD1306_MEMORY_MODE 0x20
#define SSD1306_SEG_REMAP 0xA1
#define SSD1306_COM_SCAN_DIR_DEC 0xC8
#define SSD1306_SET_COM_PINS 0xDA
#define SSD1306_SET_CONTRAST_CONTROL 0x81
#define SSD1306_SET_PRECHARGE_PERIOD 0xD9
#define SSD1306_SET_VCOM_DESELECT 0xDB
#define SSD1306_DISPLAY_ON 0xAF

// Define OLED Constants
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

void init_oled(void);
void clear_oled(void);
void write_text(char* text, uint8_t x, uint8_t y);

#endif /* OLED_H */
