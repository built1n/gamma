#include <gamma.h>
void power_off(void)
{
  clear_idt(); 
  asm volatile("int $0x3"); // generate a triple-fault
  kprintf("Shutdown failed!\n");
 l:
  goto l; // for good measure
}
