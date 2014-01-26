#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
void dividebyzero(registers_t regs)
{
  panic("Attempted division by zero!");
}
static void early_init(void) // do low-level init
{
  init_desc_tables(); // GDT, IDT
  init_terminal();
  term_puts("Terminal initialized.\n");
  init_clock(100);
  term_puts("System clock initialized.\n");
}
static void init(void)
{
  init_ps2();
  term_puts("PS/2 keyboard initialized.\n");
  // register interrupt handlers
  register_handler(0xD, &null_handler); /// FIXME: int 13 gets sent constantly!
  register_handler(0, &dividebyzero);
  set_unhandled_panic(true); // we've already registered all the handlers
}
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr) // kernel entry point
{
  early_init();
  term_puts("Booting...\n");
  init();
  asm volatile("sti"); // enable interrupts
  term_puts("System initialized.\n");
  term_puts("");
 sys_run:
  goto sys_run; // let the system run
  return 0xDEADBEEF; // we should never get here
}
