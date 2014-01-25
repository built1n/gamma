#include "gamma.h"
#include <stdint.h>
uint64_t tick; // hundredths of a second
void clock_tick(registers_t regs)
{
  ++tick;
}
void init_clock(uint32_t frequency)
{
  tick=0;
  uint32_t divisor=1193180/frequency;
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


