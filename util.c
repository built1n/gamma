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
#include <stddef.h>
#include <stdint.h>
void outb(uint16_t port, uint8_t val)
{
  asm volatile ("outb %1, %0": :"dN" (port), "a" (val));
}
uint8_t inb(uint16_t port)
{
  uint8_t ret;
  asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}
uint16_t inw(uint16_t port)
{
  uint16_t ret;
  asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}
void call_trace(uint32_t max_frames)
{
  term_puts("Call trace:\n");
  uint32_t *ebp=&max_frames - 2;
  for(int i=0;i<max_frames;++i)
    {
      uint32_t eip=ebp[1];
      if(eip==0)
	return;
      ebp=ebp[0];
      uint32_t *args=&ebp[2];
      term_puts(" ");
      term_putn_hex(eip);
      term_puts("\n");
    }
}
