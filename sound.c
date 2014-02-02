/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
// This is for the PC speaker, not the "real" speakers
#include "gamma.h"
static void beep_internal(uint32_t freq)
{
  uint32_t div=CLOCK_FREQ/freq; // CLOCK_FREQ defined in clock.h, it is the same across all x86s
  outb(0x43, 0xB6);
  outb(0x42, (byte)div);
  outb(0x42, (byte) (div >> 8));
  byte temp=inb(0x61);
  if(temp!=(temp|3))
    {
      outb(0x61, temp | 3);
    }
}
static void shut_up()
{
  byte out=(inb(0x61) & 0xFC);
  outb(0x61, out);
}

void beep()
{
  beep_internal(CLOCK_FREQ);
  sleep(10); // 10/100 second
  shut_up();
}
