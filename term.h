#pragma once
#include <stdint.h>
#include <stddef.h>

enum vga_color
  {
    COLOR_BLACK=0,
    COLOR_BLUE=1,
    COLOR_GREEN=2,
    COLOR_CYAN=3,
    COLOR_RED=4,
    COLOR_MAGENTA=5,
    COLOR_BROWN=6,
    COLOR_LGRAY=7,
    COLOR_DGRAY=8,
    COLOR_LBLUE=9,
    COLOR_LGREEN=10,
    COLOR_LCYAN=11,
    COLOR_LRED=12,
    COLOR_LMAGENTA=13,
    COLOR_LBROWN=14,
    COLOR_WHITE=15,
  };
void init_terminal();
void term_setcolor(uint8_t color); // set color of text to be printed in the future
void term_putchar(char c);
void term_puts(const char* str);
void term_putn_dec(int number);
void term_clean();
