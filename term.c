#include "gamma.h"
#include <stdint.h>
#include <stddef.h>
static const size_t VGA_WIDTH=80, VGA_HEIGHT=24;
size_t term_row, term_column;
uint8_t term_color;
uint16_t* term_buffer;
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
void term_clear(void)
{
  for(size_t y=0;y<VGA_HEIGHT;++y)
    {
      for(size_t x=0;x<VGA_WIDTH;++x)
	{
	  const size_t idx=y*VGA_WIDTH+x;
	  term_buffer[idx]=make_vgaentry(' ', term_color);
	}
    }
}
void term_move_cursor(uint16_t cursor_idx)
{
  outb(0x3D4, 14);
  outb(0x3D5, cursor_idx >> 8); // high byte
  outb(0x3D4, 15);
  outb(0x3D5, cursor_idx); // low byte
}
void update_bios_cursor(void)
{
  uint16_t cursor_x=term_column, cursor_y=term_row;
  if(cursor_x==VGA_WIDTH)
    {
      cursor_x=0;
      ++cursor_y;
    }
  uint16_t cursor_idx=cursor_y * VGA_WIDTH + cursor_x;
  term_move_cursor(cursor_idx);
}
void init_terminal(void)
{
  term_row=0;
  term_column=0;
  term_color=make_color(COLOR_WHITE, COLOR_BLACK);
  term_buffer=(uint16_t*)0xB8000;
  term_clear();
  term_move_cursor(0);
}
void term_reset(void)
{
  init_terminal();
}
void term_scroll(void) // scroll the terminal 1 line, seems buggy!
{
  const size_t max=VGA_HEIGHT-1; // this is correct
  for(size_t y=0;y<max;++y)
    {
      for(size_t x=0;x<VGA_WIDTH;++x) // scroll all lines except last one
	{
	  const size_t idx1=y*VGA_WIDTH+x, idx2=(y+1)*VGA_WIDTH+x;
	  term_buffer[idx1]=term_buffer[idx2];
	}
    }
  for(size_t x=0;x<VGA_WIDTH;++x) // fill last line with spaces
    {
      const size_t idx=(VGA_HEIGHT-1)*VGA_WIDTH+x;
      term_buffer[idx]=make_vgaentry(' ', term_color);
    }
  term_row=max;
  update_bios_cursor();
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
  else if(c=='\b')
    {
      if(--term_column>=0) // this will not go past newlines
	{
	  term_buffer[term_row * VGA_WIDTH+term_column]=make_vgaentry(' ', term_color);
	  update_bios_cursor();
	} 
    }
  else // do not increase the column in case of a newline
    {
      term_putentry(c, term_color, term_column, term_row);
      if(++term_column==VGA_WIDTH)
	{
	  term_column=0;
	  if(++term_row==VGA_HEIGHT)
	    {
	      term_scroll();
	    }
	}
      update_bios_cursor();
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
void term_putn_dec(int number)
{
  int firstDigit=1000000000;
  if(number<0)
    term_putchar('-');
  while(number/firstDigit==0 && firstDigit>0)firstDigit/=10;
  if(firstDigit!=0)
    {
      while(firstDigit>0)
	{
	  term_putchar(dtoc((uint8_t)number/firstDigit));
	  number%=firstDigit;
	  firstDigit/=10;
	}
    }
  else
    term_putchar('0');
}
void term_putn_bin(unsigned int number)
{
  int mask=0x80000000;
  while(mask!=0)
    {
      if((number & mask)==0)
	{
	  term_putchar('0');
	}
      else
	{
	  term_putchar('1');
	}
      mask>>=1;
    }
}
void put_hex_char(unsigned char n)
{
  if(n<=9)
    term_putchar(dtoc(n));
  else
    {
      char c;
      switch(n)
	{
	case 10:
	  c='A';
	  break;
	case 11:
	  c='B';
	  break;
	case 12:
	  c='C';
	  break;
	case 13:
	  c='D';
	  break;
	case 14:
	  c='E';
	  break;
	case 15:
	  c='F';
	  break;
	default:
	  c='?';
	}
      term_putchar(c);
    }
}
void term_putn_hex(unsigned int number)
{
  term_puts("0x");
  int mask=0xF0000000;
  for(int i=0;i<8;++i)
    {
      put_hex_char(number & mask);
      mask >>=4;
    }
}
