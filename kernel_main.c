#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr)
{
  init_desc_tables();
  register_handler(8, &clock_tick);
  set_unhandled_panic(false); // we've already registered all handlers
  init_terminal();
  term_puts("terminal initialized.\n");
  term_puts("kernel booting...\n");
 idle:
  goto idle; // let the system run
  return 0xDEADBEEF; // we should never get here
}
