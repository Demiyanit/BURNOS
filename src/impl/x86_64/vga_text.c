#include "vga_text.h"
#include "x64.h"
//TODO: Get width and height dinamically
#define WIDTH 80
#define HEIGHT 25

static int cursor_x = 0;
static int cursor_y = 0;
static uint8_t bg_color = VGA_COLOR_BLACK;
static uint8_t fg_color = VGA_COLOR_LIGHT_GREY;
static uint8_t color = VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4;
static uint8_t global_color = VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4;

typedef struct Char {
	uint8_t ascii;
	uint8_t color;
};

char* buffer = 0xB8000;
uint16_t buffer_size = WIDTH * HEIGHT;

void vga_set_global_color(uint8_t bg_color, uint8_t fg_color) {
	global_color = fg_color | bg_color << 4;
	color = global_color;
}

void vga_set_bg_color(uint8_t _color) {
	bg_color = _color;
	color = fg_color | bg_color << 4;
}

void vga_set_fg_color(uint8_t _color) {
	fg_color = _color;
	color = fg_color | bg_color << 4;
}

void vga_set_color(uint8_t bg_color, uint8_t fg_color) {
	bg_color = bg_color;
	fg_color = fg_color;
	color = fg_color | bg_color << 4;
}

void shift_buf() {
	int i, j;
	for (i = 0; i < WIDTH * (HEIGHT - 1); i++) {
		buffer[i] = buffer[i + WIDTH];
	}
	for (i = WIDTH * (HEIGHT - 1); i < buffer_size; i++) {
		buffer[i] = 0;
	}
	cursor_y--;
	if (cursor_y < 0) {
		cursor_y = HEIGHT - 1;
	}
}

void vga_set_cursor_pos(uint16_t x, uint16_t y) {
	cursor_x = x;
	cursor_y = y;
}

void vga_write_char(char c) {
	switch (c) {
		case '\n':
			cursor_x = 0;
			cursor_y++;
			if (cursor_y >= HEIGHT) { 
				shift_buf();
			}
			break;
		case '\b':
			if (cursor_x > 0) {
				cursor_x--;
				if (cursor_x < 0) { 
					cursor_y--;
					if (cursor_y < 0) {
						cursor_y = 0;
					}
					cursor_x = 0;
				}
			}
			break;
		case '\r':
			cursor_x = 0;
			break;
		case '\t':
			for(int i = 0; i < 4; i++) { 
				buffer[2 * (cursor_y * WIDTH + cursor_x)] = ' ';
				buffer[2 * (cursor_y * WIDTH + cursor_x) + 1] = color;
				cursor_x++;
				if (cursor_x >= WIDTH) {
					return;
				}		
			}
			break;
		default:
			buffer[2 * (cursor_y * WIDTH + cursor_x)] = c;
			buffer[2 * (cursor_y * WIDTH + cursor_x) + 1] = color;
			cursor_x++;
			if (cursor_x >= WIDTH) {
				cursor_x = 0;
				cursor_y++;
				if (cursor_y >= HEIGHT) {
					shift_buf();
				}
			}
		break;
	}
}

void vga_write_str(const char* str) {
	while (*str) {
		vga_write_char(*str);
		str++;
	}
}

void vga_clear_screen() {
	for (int i = 0; i < buffer_size*2; i+=2) {
		buffer[i] = 0;
		buffer[i+1] = global_color;
	}
	cursor_x = 0;
	cursor_y = 0;
}