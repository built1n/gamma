#include "gamma.h"
void power_off(void)
{
  clear_idt();
  asm volatile("int $0x3");
 l:
  goto l;
}
