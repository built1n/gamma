#include "term.h"
#include "string.h"
#include <stdint.h>
#include <stddef.h>
uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
  return fg | bg <<4;
}
uint16_t make_vgaentry(char c, uint8_t col)
{
  uint16_t c16=c;
  uint16_t color16=col;
  return c16 | color16 << 8;
}

void init_terminal()
{
  term_row=0;
  term_column=0;
  term_color=make_color(COLOR_WHITE, COLOR_BLACK);
  term_buffer=(uint16_t*)0xB8000;
  for(size_t y=0;y<VGA_HEIGHT;++y)
    {
      for(size_t x=0;x<VGA_WIDTH;++x)
	{
	  const size_t idx=y*VGA_WIDTH+x;
	  term_buffer[idx]=make_vgaentry(' ', term_color);
	}
    }
}
void term_scroll() // scroll the terminal 1 line
{
  const size_t max=VGA_HEIGHT-1;
  for(size_t y=1;y<max;++y)
    {
      for(size_t x=0;x<VGA_WIDTH;++x) // scroll all lines except last one
	{
	  const size_t idx1=y*VGA_WIDTH+x, idx2=y-1*VGA_WIDTH+x;
	  term_buffer[idx2]=term_buffer[idx1];
	}
    }
  const size_t n=max*VGA_WIDTH;
  for(size_t x=0;x<VGA_WIDTH;++x) // fill last line with spaces
    {
      const size_t idx=n+x;
      term_buffer[idx]=make_vgaentry(' ', term_color);
    }
  term_row=max-1;
}
void term_setcolor(uint8_t color)
{
  term_color=color;
}
void term_putentry(char c, uint8_t color, size_t x, size_t y)
{
  const size_t idx=y*VGA_WIDTH+x;
  term_buffer[idx]=make_vgaentry(c, color);
}
void term_putchar(char c)
{
  if(c=='\n')
    {
      term_column=0;
      if(++term_row==VGA_HEIGHT)
	{
	  term_scroll();
	}
    }
  else
    term_putentry(c, term_color, term_column, term_row);
  if(++term_column==VGA_WIDTH)
    {
      term_column=0;
      if(++term_row==VGA_HEIGHT)
	{
	  term_scroll();
	}
    }
}
void term_puts(const char* str)
{
  const size_t length=strlen(str);
  for(size_t i=0;i<length;++i)
    {
      term_putchar(str[i]);
    }
}
void term_putn(int number)
{
  int firstDigit=10; // size_t for 64-bit numbers
  while(number%firstDigit==0 && firstDigit>0)
    {
      --firstDigit;
    }
  for(;firstDigit>0;--firstDigit)
    {
      term_putchar((char)dtoc((char)(number%firstDigit)));
    }
}
