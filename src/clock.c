/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
#define CLOCK_FREQ 1193180 // this is the same for all Intel CPUs
#include "gamma/gamma.h"
#include <stdint.h>
unsigned long long tick; // hundredths of a second
void clock_tick(registers_t regs)
{
  ++tick;
}
void init_clock(uint32_t frequency)
{
  tick=0;
  uint32_t divisor=CLOCK_FREQ/frequency;
  byte low=(byte)(divisor & 0xFF), high=(byte)( (divisor >> 8) & 0xFF);
  register_handler(32, &clock_tick);
  outb(0x43, 0x36);
  outb(0x40, low);
  outb(0x40, high);
}
uint64_t time(void)
{
  return tick; 
}
