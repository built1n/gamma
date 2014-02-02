/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
#include "gamma.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
static const size_t VGA_WIDTH=80, VGA_HEIGHT=24;
static size_t term_row, term_column;
static uint8_t term_color;
static uint16_t* term_buffer=(uint16_t*)0xB8000; // VGA screen buffer address
static int last_prompt_char[24]; // index of 1st character from right that cannot be backspaced over, one for each line
uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
  return fg | bg << 4;
}
static uint16_t make_vgaentry(char c, uint8_t col)
{
  uint16_t c16=c;
  uint16_t color16=col;      
  return c16 | color16 << 8;
}
static void move_cursor(uint16_t cursor_idx) // do the actual moving of the cursor
{
  outb(0x3D4, 14);
  outb(0x3D5, cursor_idx >> 8); // high byte
  outb(0x3D4, 15);
  outb(0x3D5, cursor_idx); // low byte
}
static void update_bios_cursor(void) // calculate the index of the cursor, then move it 
{
  uint16_t cursor_x=term_column, cursor_y=term_row;
  uint16_t cursor_idx=cursor_y * VGA_WIDTH + cursor_x;
  move_cursor(cursor_idx);
}
void term_clear(void)
{
  for(size_t y=0;y<=VGA_HEIGHT;++y)
    {
      for(size_t x=0;x<VGA_WIDTH;++x)
	{
	  const size_t idx=y*VGA_WIDTH+x;
	  term_buffer[idx]=make_vgaentry(' ', term_color);
	}
    }
  memset(&last_prompt_char, 0, sizeof(last_prompt_char));
  term_row=0;
  term_column=0;
  update_bios_cursor();
}
void init_terminal(void)
{
  term_row=0;
  term_column=0;
  term_color=make_color(COLOR_WHITE, COLOR_BLACK);
  term_buffer=(uint16_t*)0xB8000; // frame buffer location, provided by BIOS
  term_clear();
  move_cursor(0); // best to use update_bios_cursor, but this is faster
}
void term_reset(void)
{
  init_terminal();
}
static void scroll_if_needed(void) // scroll the terminal 1 line, seems buggy!
{
  if(term_row>VGA_HEIGHT)
    {
      for(uint16_t y=0;y<VGA_HEIGHT;++y)
	{
	  for(uint16_t x=0;x<VGA_WIDTH;++x) // scroll all lines except last one
	    {
	      const uint16_t idx1=y*VGA_WIDTH+x, idx2=(y+1)*VGA_WIDTH+x;
	      term_buffer[idx1]=term_buffer[idx2];
	    }
	  last_prompt_char[y]=last_prompt_char[y+1];
	}
      last_prompt_char[VGA_HEIGHT]=0;
      for(uint16_t x=0;x<VGA_WIDTH;++x) // fill last line with spaces
	{
	  const uint16_t idx=(VGA_HEIGHT)*VGA_WIDTH+x;
	  term_buffer[idx]=make_vgaentry(' ', term_color);
	}
      term_row=VGA_HEIGHT;
      update_bios_cursor();
    }
}
void term_setcolor(uint8_t color)
{
  term_color=color;
}
uint8_t term_getcolor(void)
{
  return term_color;
}
static void term_putentry(char c, uint8_t color, size_t x, size_t y)
{
  const size_t idx=y*VGA_WIDTH+x;
  term_buffer[idx]=make_vgaentry(c, color);
}
// print character c, and increment the last_prompt_char if no_bksp is nonzero
static void term_putchar_internal(char c, int no_backspace)
{ 
  if(c=='\n')
    {
      term_column=0;
      ++term_row;
    }
  else if(c=='\b')
    {
      int32_t term_column_32=term_column;
      if(term_column_32-1>=0) // this will not go past newlines
	{
	  --term_column;
	  term_putentry(' ', term_color, term_column, term_row);
	}
      else
	{
	  if((int32_t)term_row-1>=0) // this will go past newlines, but not off the screen
	    {
	      --term_row;
	      term_column=last_prompt_char[term_row]; // should make a new array of last_char, so we know what to set this to, instead of the last PROMPT char
	    }
	}
    }
  else if(c=='\a')
    {
      beep();
      return;
    }
  else if(c!=0) // not a newline or backspace, or null
    {
      term_putentry(c, term_color, term_column, term_row);
      if(++term_column==VGA_WIDTH)
	{
	  term_column=0;
	  ++term_row;
	}
      if(no_backspace)
	++last_prompt_char[term_row];
    }
  scroll_if_needed();
  update_bios_cursor();
}
void term_putchar(char c) // non-backspacable
{
  term_putchar_internal(c, 1);
}
void term_puts(const char* str)
{
  for(size_t i=0;str[i]!=0;++i)
    {
      term_putchar(str[i]);
    }
}
void term_putn_dec(int32_t number)
{
  if(number<0)
    term_putchar('-');
  if(number==0) // exit early
    {
      term_putchar('0');
      return;
    }
  char buf[10];
  for(int i=0;i<10;++i)
    {
      buf[9-i]=dtoc(number%10);
      number/=10;
    }
  uint8_t encountered_nonzero=0;
  for(int i=0;i<10;++i)
    {
      if(buf[i]!='0')
	{
	  encountered_nonzero=1;
	}
      if(encountered_nonzero)
	{
	  term_putchar(buf[i]);
	}
    }
}
void term_putn_bin(uint32_t number)
{
  for(int i=0;i<32;++i)
    {
      char c=((number & 0x80000000 )>> 31 == 1)?'1':'0';
      term_putchar(c);
      number<<=1;
    }
}
static char hex_chars[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '8', 'A', 'B', 'C', 'D', 'E', 'F'};
void term_putn_hex(uint32_t number)
{
  term_puts("0x");
  for(int i=0;i<8;++i)
    {
      term_putchar(hex_chars[((number & 0xF0000000 ) >> 28)]);
      number<<=4;
    }
}
void term_debug(const char* str)
{
  term_putchar('[');
  term_putn_dec(time());
  term_puts("] ");
  term_puts(str);
  term_putchar('\n');
}
void term_put_keyboard_char(char c) // put a backspacable character
{
  if(c!='\b') // c is not backspace
    term_putchar_internal(c, 0);
  else // backspace!
    {
      if(term_column>last_prompt_char[term_row])
	term_putchar_internal('\b', 0);
    }
}
int printf(const char* fmt, ...)
{
  va_list va;
  va_start(va, fmt);
  for(int i=0;fmt[i];++i)
    {
      char c=fmt[i];
      if(c=='%')
	{
	  ++i; // skip the % sign
	  switch(fmt[i])
	    {
	    case 'd': // signed integer
	      term_putn_dec(va_arg(va, int));
	      break;
	    case 's': // string
	      term_puts(va_arg(va, const char*));
	    }
	}
      else
	term_putchar(c);
    }
  va_end(va);
  return 0;
}
