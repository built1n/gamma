#include <stddef.h>
#include <stdint.h>
#include "gamma.h"
struct registers_t {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t interrupt_number, error_code;
  uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));
void(*handlers[256])(int);
void register_handler(unsigned char number, void(*fnPtr)(int))
{
  handlers[number]=fnPtr;
}
void unregister_handler(unsigned char number)
{
  handlers[number]=0;
}
void init_isr()
{
  for(unsigned char i=0;i<256;++i)
    {
      unregister_handler(i);
    }
}
void isr_handler(struct registers_t regs) // high-level handler for interrupts
{
  if(handlers[regs.interrupt_number]==0)
    { 
      term_puts("unhandled interrupt!\n");
      term_puts("interrupt number in hex: ");
      term_putn_hex(regs.interrupt_number);
      term_putchar('\n');
      term_puts("error code in hex: ");
      term_putn_hex(regs.error_code);
      term_putchar('\n');
    }
  else
    handlers[regs.interrupt_number](regs.error_code);
}
