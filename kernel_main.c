#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "term.h"

#ifdef __cplusplus
extern "C"
#endif
void kernel_main()
{
  init_terminal();
  term_puts("kernel booting...");
}
