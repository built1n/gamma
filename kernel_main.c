#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "term.h"
#include "gdt.h"
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr)
{
  init_terminal();
  term_puts("terminal initialized.\n");
  term_puts("will initialize gdt, idt...");
  for(int i=0;i<10000000;++i);
  init_desc_tables();
  term_puts("kernel booting...\n");
  return 0xDEADBEEF;
}
