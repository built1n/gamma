#include "gamma.h"
void idle(){return;}
void panic(const char* str)
{
  term_puts("kernel panic: ");
  term_puts(str);
  asm volatile("cli");
  asm volatile("hlt");
  for(;;)idle();
}
