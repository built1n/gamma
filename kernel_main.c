#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
void gpf(registers_t regs)
{
  term_puts("General protection fault\n");
}
void dividebyzero(registers_t regs)
{
  panic("Divide by zero");
}
static void early_init(void)
{
  init_desc_tables();
  init_terminal();
  term_puts("terminal initialized.\n");
  init_clock(100); // do this AFTER terminal initialization 
  term_puts("clock initialized.\n");
}
static void init(void)
{
  init_ps2();
  term_puts("keyboard initialized.\n");
  // register interrupt handlers
  register_handler(0xD, &null_handler);
  register_handler(0, &dividebyzero);
  set_unhandled_panic(true); // we've already registered all the handlers
}
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr) // kernel entry point
{
  early_init();
  term_puts("booting...\n");
  init();
  asm volatile("sti"); // enable interrupts
  term_puts("system initialized.\n");
 sys_run:
  goto sys_run; // let the system run
  return 0xBADC0DE; // we should never get here
}
