#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
#ifdef __cplusplus
extern "C"
#endif
extern void clock_tick(int);
int kernel_main(struct multiboot *mboot_ptr)
{
  init_terminal();
  term_puts("terminal initialized.\n");
  init_desc_tables();
  register_handler(8, &clock_tick);
  term_puts("kernel booting...\n");
  // boot
  int uptime=sys_uptime();
  while(sys_uptime()!=uptime+1)
    {
      uptime=sys_uptime();
      term_puts("1 second...\n");
    }
  // do stuff
  return 0xDEADBEEF;
}
