#include "gamma.h"
static void idle(){return;}
void kpanic(const char* str, const char* file, int line)
{
  term_puts("kernel panic: ");
  term_puts(str);
  term_putchar('\n');
  term_puts("occurred in file ");
  term_puts(file);
  term_puts(" at line ");
  term_putn_dec(line);
  term_puts("\nhalted.");
  asm volatile("cli");
  asm volatile("hlt");
  for(;;)idle();
}
