#include "gamma.h"
#include <stdint.h>
uint64_t tick; // hundredths of a second
void clock_tick(registers_t regs)
{
  term_puts("Clock tick number: ");
  term_putn_dec(tick);
  ++tick;
}
void init_clock(uint32_t frequency)
{
  tick=0;
  register_handler(32, &clock_tick);
  uint32_t divisor=1193180/frequency;
  outb(0x43, 0x36);
  byte low=(byte)(divisor & 0xFF), high=(byte)( (divisor >> 8) & 0xFF);
  outb(0x40, low);
  outb(0x40, high);
}
uint64_t ms_time(void)
{
  return tick * 10; 
}
