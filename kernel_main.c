#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
#ifdef __cplusplus
extern "C"
#endif
void general_protection_fault(int err)
{
  term_puts("General protection fault!\n");
}
int kernel_main(struct multiboot *mboot_ptr)
{
  init_terminal();
  term_puts("terminal initialized.\n");
  init_desc_tables();
  register_handler(0xD, &general_protection_fault);
  term_puts("kernel booting...\n");
  // boot
  
  // do stuff
  return 0xDEADBEEF;
}
