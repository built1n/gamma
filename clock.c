#include "gamma.h"
long double sysuptime=0;
void clock_tick(int err)
{
  term_puts("Clock tick...\n");
}
unsigned long sys_uptime(void)
{
  return (unsigned long)0;
}
