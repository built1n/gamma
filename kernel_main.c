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
static inline void early_init(void) // do low-level init
{
  init_terminal();
  printf("Terminal initialized.\n");
  init_desc_tables(); // GDT, IDT
  
  register_handler(0xD, &null_handler); // for some reason, int 0xD gets sent constantly
  
  init_ps2();
  printf("Keyboard initialized.\n");
  
  init_clock(100); // 100 times per second

  printf("Early init complete.\n");
  // init_paging(); // BUGGY!
}
static inline void init(void)
{
  // register interrupt handlers
  register_handler(0, &dividebyzero);
  set_unhandled_panic(true); // we've already registered all the interrupt handlers we need
}
static int ctrlaltdel_count=0;
void ctrlaltdel(void)
{
  printf("Current tick: %d\n", time());
  ++ctrlaltdel_count;
}
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(void *mboot_ptr) // kernel entry point
{
  early_init();
  printf("Booting...\n");
  init();
  asm volatile("sti"); // enable interrupts
#ifndef NDEBUG
  printf("Build date: %s, %s\n", build_time, build_date);
#endif
  printf("System initialized at tick %d.\n", time());
 sys_run:
  goto sys_run; // let the system run
  return 0xDEADBEEF; // we should never get here
}
