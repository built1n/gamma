#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
#ifdef __cplusplus
extern "C"
#endif
void gpf(registers_t regs)
{
  term_puts("Recieved general protection failure!\n");
}
int kernel_main(struct multiboot *mboot_ptr)
{
  init_desc_tables();
  init_terminal();
  init_clock(100); // do this AFTER terminal initialization
  term_puts("terminal initialized.\n");
  term_puts("kernel booting...\n");
  // register interrupt handlers
  register_handler(0xD, &null_handler);
  set_unhandled_panic(true); // we've already registered all the handlers
  term_puts("testing number printing:\n");
  term_putn_dec(42);
  term_putchar('\n');
  term_putn_hex(0xDEADBEEF);
  term_putchar('\n');
 sys_idle:
  goto sys_idle; // let the system run

  return 0xDEADBEEF; // we should never get here
}
