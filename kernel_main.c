/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
const char* build_time=__TIME__;
const char* build_date=__DATE__;
void dividebyzero(registers_t regs)
{
  panic("Attempted division by zero!");
}
static void early_init(void) // do low-level init
{
  init_desc_tables(); // GDT, IDT
  register_handler(0xD, &null_handler); /// FIXME: int 0xD gets sent constantly
  init_terminal();
  term_puts("Terminal initialized.\n");
  init_clock(100);
  term_puts("System clock initialized.\n");
  // init_paging(); // BUGGY!
}
static void init(void)
{
  init_ps2();
  term_puts("PS/2 keyboard initialized.\n");
  // register interrupt handlers
  register_handler(0, &dividebyzero);
  set_unhandled_panic(true); // we've already registered all the handlers
}
static void start_kernel(void)
{
  early_init();
  term_puts("Booting...\n");
  init();
  asm volatile("sti"); // enable interrupts
#ifndef NDEBUG
  term_puts("Build date: ");
  term_puts(build_time);
  term_puts(", ");
  term_puts(build_date);
  term_putchar('\n');
#endif
  term_puts("System initialized.\n");
}
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(void *mboot_ptr) // kernel entry point
{
  start_kernel();
 sys_run:
  goto sys_run; // let the system run
  return 0xDEADBEEF; // we should never get here
}
