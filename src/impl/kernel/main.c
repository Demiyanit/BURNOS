#include "vga_text.h"

void kernel_main() {
    //                   Background  col  Foreground col
    vga_set_global_color(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_LIGHT_GREY);
    vga_clear_screen();
    vga_write_str("Well...\nHi!\n");
    vga_write_str("I'm a kernel!\nNice to meet you! This is a test text to fill up the screen and test it's limits so lololololololololololollolololololololololololololololololololololololololololololol");
    vga_set_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
    vga_write_str("\nAnd this is a text color test >:]");
}
