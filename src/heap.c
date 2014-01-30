#include "gamma/heap.h"
#include <stdint.h>
uint32_t next_addr=0x1000000; // be SURE to change this!!!
uint32_t kmalloc_impl(uint32_t sz, int align, uint32_t *phys)
{
  if(align==1 && (next_addr & 0xFFFFF000)!=0)
    {
      next_addr &= 0xFFFFF000;
      next_addr += 0x1000;
    }
  if(phys!=0)
    {
      *phys=next_addr;
    }
  uint32_t ret=next_addr;
  next_addr+=sz;
  return ret;
}
uint32_t kmalloc_a(uint32_t sz)
{
  return kmalloc_impl(sz, 1, 0);
}
uint32_t kmalloc_p(uint32_t sz, uint32_t *phys)
{
  return kmalloc_impl(sz, 0, phys);
}
uint32_t kmalloc_ap(uint32_t sz, uint32_t *phys)
{
  return kmalloc_impl(sz, 1, phys);
}
uint32_t kmalloc(uint32_t sz)
{
  return kmalloc_impl(sz, 1, 0);
}
