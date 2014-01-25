#pragma once
#include <stdint.h>
#include <stddef.h>
enum vga_color
  {
    COLOR_BLACK=   0 ,
    COLOR_BLUE=    1 ,
    COLOR_GREEN=   2 ,
    COLOR_CYAN=    3 ,
    COLOR_RED=     4 ,
    COLOR_MAGENTA= 5 ,
    COLOR_BROWN=   6 ,
    COLOR_LGRAY=   7 ,
    COLOR_DGRAY=   8 ,
    COLOR_LBLUE=   9 ,
    COLOR_LGREEN=  10,
    COLOR_LCYAN=   11,
    COLOR_LRED=    12,
    COLOR_LMAGENTA=13,
    COLOR_LBROWN=  14,
    COLOR_WHITE=   15
  };
void init_terminal(void);
void term_setcolor(uint8_t color); // set color of text TO BE printed
uint8_t term_getcolor(void);
void term_putchar(char); // print a non-backspacable char
void term_puts(const char*); // print a non-backspacable string
void term_debug(const char*); // print a debug message
void term_putn_hex(uint32_t); // non-backspacable
void term_putn_dec(int32_t); // same
void term_putn_bin(uint32_t); // same
void term_clear(void);
void term_reset(void); // clear, reset cursor, color
void term_put_keyboard_char(char); // put a backspaceable char
// wish: PRINTF, PLZ, PLZ, PLZ!!!!!!!
int kprintf(const char* fmt, ...);


