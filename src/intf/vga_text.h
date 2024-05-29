#pragma once
#include <stdint.h>

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};

void vga_set_global_color(uint8_t bg_color, uint8_t fg_color);
void vga_set_bg_color(uint8_t color);
void vga_set_fg_color(uint8_t color);
void vga_set_color(uint8_t bg_color, uint8_t fg_color);
void vga_set_cursor_pos(uint16_t x, uint16_t y);
void vga_write_char(char c);
void vga_write_str(const char* str);
void vga_clear_screen();