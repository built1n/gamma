#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr)
{
  init_terminal();
  term_puts("terminal initialized.\n");
  init_desc_tables();
  term_puts("kernel booting...\n");
  // boot
  
  // do stuff
  term_puts("42 in hex is: ");
  term_putn_hex(42);
  term_puts("\nIn binary: ");
  term_putn_bin(42);
  term_puts("\nenabling interrupts...\n");
  return 0xDEADBEEF;
}
