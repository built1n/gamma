#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
void gpf(registers_t regs)
{
  term_puts("Recieved general protection failure!\n");
}
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr)
{
  init_desc_tables();
  init_terminal();
  init_clock(100); // do this AFTER terminal initialization
  term_puts("terminal initialized.\n");
  term_puts("kernel booting...\n");
  init_ps2();
  term_puts("keyboard initialized.\n");
  // register interrupt handlers
  register_handler(0xD, &null_handler);
  set_unhandled_panic(true); // we've already registered all the handlers
 sys_idle:
  goto sys_idle; // let the system run

  return 0xDEADBEEF; // we should never get here
}
