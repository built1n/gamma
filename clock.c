#include "gamma.h"
#include <stdint.h>
uint64_t tick; // hundredths of a second
void clock_tick(registers_t regs)
{
  term_puts("Clock tick...");
  // there could be a problem with number printing in interrupt handlers
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
uint64_t ms_time(void)
{
  return tick * 100; 
}
