#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "term.h"
#ifdef __cplusplus
extern "C"
#endif
int kernel_main(struct multiboot *mboot_ptr)
{
  init_terminal();
  term_puts("kernel booting...\n");
  for(int i=0;i<22;++i)
    term_puts("Empty line\n");
  return 0xDEADBEEF;
}
