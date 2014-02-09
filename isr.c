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
static bool panic_on_unhandled;
static void(*handlers[256])(registers_t);
void register_handler(byte number, void(*fnPtr)(registers_t))
{
  handlers[number]=fnPtr;
}
void unregister_handler(byte number)
{
  handlers[number]=0;
}
void init_isr()
{
  memset(&handlers, 0, sizeof(void*)*256);
}
void set_unhandled_panic(bool b)
{
  panic_on_unhandled=b;
}
void isr_handler(struct registers_t regs) // high-level handler for interrupts
{
  if(handlers[regs.interrupt_number]==0)
    { 
#ifndef NDEBUG
      printf("received unhandled interrupt\n");
      printf("interrupt number in decimal: %d\n", regs.interrupt_number);
#endif
      if(panic_on_unhandled==true)
	panic("unhandled interrupt");
    }
  else
    {
      handlers[regs.interrupt_number](regs);
    }
}
void irq_handler(struct registers_t regs)
{
  if(regs.interrupt_number >= 40) // sent by slave PIC
    {
      outb(0xA0, 0x20); // slave EOI
    }
  outb(0x20, 0x20); // master EOI
  if(handlers[regs.interrupt_number]!=0)
    {
      handlers[regs.interrupt_number](regs);
    }
  else
    { 
#ifndef NDEBUG
      printf("received unhandled IRQ interrupt\n");
      printf("IRQ interrupt number in decimal: %d\n", regs.interrupt_number);
#endif
      if(panic_on_unhandled==true)
	panic("unhandled IRQ!");
    }
}
void null_handler(registers_t regs)
{
  return;
}
