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
void detect_floppy(void)
{
  const char* lookup_table[16]={"No floppy drive", 
				"360 KB 5.25\" floppy drive", 
				"1.2 MB 5.25\" floppy drive", 
				"720 KB 3.5\" floppy drive", 
				"1.44 MB 3.5\" floppy drive", 
				"2.88 MB 3.5\" floppy drive",0,0,0,0,0,0,0,0,0,0};
  printf("Detecting floppy drives...\n");
  byte floppy_info=read_cmos(0x10, 0);
  printf("%s on master.\n", lookup_table[(floppy_info & 0xF0) >> 4]);
  printf("%s on slave.\n", lookup_table[floppy_info & 0x0F]);
}
static inline void early_init(void) // do low-level init
{
  init_terminal();
  printf("Terminal initialized.\n");
  init_desc_tables(); // GDT, IDT
  printf("Descriptor tables initialized.\n");
  register_handler(0xD, &null_handler); // for some reason, int 0xD gets sent constantly
  register_handler(32, &clock_tick);
  printf("Interrupt handlers registered.\n");
  init_ps2(); // the name is misleading: it supports USB, too!
  printf("Keyboard initialized.\n");
  //  init_clock(100); // 100 times per second, seems to crash sometimes
  printf("Early init complete.\n");
  // init_paging(); // BUGGY!
}
static inline void init(void)
{
  detect_floppy();
  // register interrupt handlers
  register_handler(0, &dividebyzero);
  /*
  printf("Getting real time...\n");
  rtc_t rtc;
  load_real_time_clock(&rtc);
  printf("RTC Loaded.\n");
  printf("Time: &%d:%d\n", rtc.hours, rtc.minutes);
  printf("Date: %d/%d/%d\n", rtc.month, rtc.day, rtc.year+2000);
  */
  set_unhandled_panic(true); // we've already registered all the interrupt handlers we need
}
void ctrlaltdel(void)
{
  printf("Current tick: %d\n", time());
  return;
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

  printf("Type: ");
  char *str=kmalloc(256);
  read(256, str);
  printf("You typed \"%s\"\n",str); 
 sys_run:
  goto sys_run; // let the system run
  return 0xDEADBEEF; // we should never get here
}
