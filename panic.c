#include "gamma.h"
static void idle(){return;}
void kpanic(const char* str, const char* file, int line)
{
  term_puts("*PANIC*: ");
  term_puts(str);
  term_putchar('\n');
  term_puts("occurred at ");
  term_puts(file);
  term_putchar(':');
  term_putn_dec(line);
  term_puts("\n");
  asm volatile("cli");
  asm volatile("hlt");
  for(;;)idle();
}
