#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
#ifdef __cplusplus
extern "C"
#endif
void gpf(registers_t regs)
{
}
int kernel_main(struct multiboot *mboot_ptr)
{
  init_desc_tables();
  init_clock(10); // do this ASAP, argument is time in milliseconds
  register_handler(0x0D, &gpf);
  init_terminal();
  term_puts("terminal initialized.\n");
  term_puts("kernel booting...\n");
  set_unhandled_panic(false); // we've already registered all handlers
 sys_idle:
  goto sys_idle; // let the system run
  return 0xDEADBEEF; // we should never get here
}
