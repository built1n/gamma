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
  for(;;)
    term_puts("LLLLLLLLLLLL\nO\nLLLLLLLLLLLLL");
  return 0xDEADBEEF;
}
