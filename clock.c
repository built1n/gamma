#include "gamma.h"
long double uptime=0;
void clock_tick(int err)
{
  sysuptime+=0.0549405494;
}
unsigned long sys_uptime(void)
{
  return (unsigned long)uptime;
}
