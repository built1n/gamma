#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "term.h"
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr)
{
  init_terminal();
  term_setcolor(COLOR_GREEN);
  term_puts("kernel booting...\n");
  term_puts("Answer to life: ");
  term_putn_dec(42);
  double d;
  term_putchar('\n');
  return 0xDEADBEEF;
}
