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
void outb(uint16_t port, byte val)
{
  asm volatile ("outb %1, %0": :"dN" (port), "a" (val));
}
byte inb(uint16_t port)
{
  byte ret;
  asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}
uint16_t inw(uint16_t port)
{
  uint16_t ret;
  asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}
byte read_cmos(byte addr, byte nmi_disable)
{
  outb(0x70, ((nmi_disable | 0x1)<<7)|addr);
  return inb(0x71);
}
void nmi_enable(void)
{
  outb(0x70, (inb(0x70)&0x7F));
}
void nmi_disable(void)
{
  outb(0x70, inb(0x70)|0x80);
}
void disable_interrupts(void)
{
  asm volatile ("cli");
  nmi_disable();
}
void enable_interrupts(void)
{
  asm volatile("sti");
  nmi_enable();
}
