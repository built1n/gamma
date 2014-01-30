/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
#include "gamma/gamma.h"
static void idle(){return;}
void kpanic(const char* str, const char* file, int line)
{
  term_putchar('[');
  term_putn_dec(time());
  term_puts("] ");
  term_puts("*KERNEL PANIC* - ");
  term_puts(str);
  term_putchar('\n');
  term_puts("At ");
  term_puts(file);
  term_putchar(':');
  term_putn_dec(line);
  term_putchar('\n');
  term_puts("System halted.\n");
  asm volatile("cli"); // stop interrupts
  asm volatile("hlt"); // put CPU in a non-executing state
  for(;;)idle(); // loop
}
