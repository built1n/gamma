#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "gamma.h"
bool panic_on_unhandled;
struct registers_t {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t interrupt_number, error_code;
  uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));
void(*handlers[256])(int);
void register_handler(unsigned int number, void(*fnPtr)(int))
{
  handlers[number]=fnPtr;
}
void unregister_handler(unsigned int number)
{
  handlers[number]=0;
}
void init_isr()
{
  for(unsigned int i=0;i<256;++i)
    {
      unregister_handler(i);
    }
}
void set_unhandled_panic(bool b)
{
  panic_on_unhandled=b;
}
void isr_handler(struct registers_t regs) // high-level handler for interrupts
{
  if(handlers[regs.interrupt_number]==0 && panic_on_unhandled==true)
    { 
      term_puts("received unhandled interrupt\n");
      term_puts("interrupt number in decimal: ");
      term_putn_dec(regs.interrupt_number);
      term_putchar('\n');
      term_puts("error code in decimal: ");
      term_putn_dec(regs.error_code);
      term_putchar('\n');
      panic("unhandled interrupt");
    }
  else
    handlers[regs.interrupt_number](regs.error_code);
}
