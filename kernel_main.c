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
  init_clock(100); // do this ASAP, argument is time in milliseconds
  init_terminal();
  term_puts("terminal initialized.\n");
  term_puts("kernel booting...\n");
  // register interrupt handlers
  register_handler(0x0D, &gpf);
  set_unhandled_panic(true); // we've already registered all handlers

 sys_idle:
  goto sys_idle; // let the system run

  return 0xDEADBEEF; // we should never get here
}
