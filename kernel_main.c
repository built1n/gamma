#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "term.h"
#include "gdt.h"
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr)
{
  init_terminal();
  term_puts("terminal initialized.\n");
  init_desc_tables(); // buggy!
  term_puts("kernel booting...\n");
  return 0xDEADBEEF;
}
