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
static void idle(){return;}
void kpanic(const char* str, const char* file, int line)
{
  printf("*KERNEL PANIC* - %s\nAt %s:%d\nSystem halted.\n", str, file, line);
  asm volatile("cli"); // stop interrupts
  asm volatile("hlt"); // put CPU in a non-executing state
  for(;;)idle(); // loop
}
