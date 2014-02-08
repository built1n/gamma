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
uint32_t tick=0; // hundredths of a second, will overflow in 1.3 years
void clock_tick(registers_t regs)
{
  ++tick;
}
void init_clock(uint32_t frequency)
{
  tick=0;
  uint32_t divisor=CLOCK_FREQ/frequency;
  byte low=(byte)(divisor & 0xFF), high=(byte)( (divisor >> 8) & 0xFF);
  register_handler(32, &clock_tick); // IRQ0
  outb(0x43, 0x36);
  outb(0x40, low);
  outb(0x40, high);
}
uint32_t time(void)
{
  return tick; 
}
void sleep(uint32_t n)
{
  uint32_t stop=tick+n;
  while(tick<=stop)
    ;
}
