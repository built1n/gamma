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
  term_puts("kernel booting...\n");
  asm volatile ("int 0x3");
  asm volatile ("int 0x4");
  return 0xDEADBEEF;
}
