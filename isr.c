#include <stddef.h>
#include <stdint.h>
#include "term.h"
struct registers_t {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t interrupt_number, error_code;
  uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));
void isr_handler(struct registers_t regs)
{
  term_puts("interrupt recieved!\n");
  term_puts("decimal interrupt number: ");
  term_putn_dec(regs.interrupt_number);
  term_putchar('\n');
}
