#include "gamma.h"
#include <stdint.h>
page_dir_t* current_directory;

void switch_page_directory(page_dir_t* page_dir)
{
  current_directory=page_dir;
  asm volatile("mov %0, %%cr3": : "r"(&page_dir->page_tables_phys)); // move address of page_dir to register cr3
  uint32_t cr0=0; // shut up GCC
  asm volatile("mov %%cr0, %0": "=r"(cr0)); // move reg. cr0 to variable cr0
  cr0 |=0x80000000;
  asm volatile("mov %0, %%cr0": :"r"(cr0)); // move var cr0 to reg. cr0
}
page_t *get_page(uint32_t addr, int make, page_dir_t* dir)
{
  addr/=0x1000;
  uint32_t tab_idx=addr/1024;
  if(dir->page_tables[tab_idx])
    {
      return &dir->page_tables[tab_idx]->pages[addr%1024];
    }
  else if(make)
    {
      uint32_t tmp;
      dir->page_tables[tab_idx]=(page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
      memset(dir->page_tables[tab_idx], 0, 0x1000);
      dir->page_tables_phys[tab_idx]=tmp | 0x7;
      return &dir->page_tables[tab_idx]->pages[addr%1024];
    }
  else
    return 0;
}
void page_fault(registers_t regs)
{
  uint32_t faulting_addr;
  asm volatile("mov %%cr2, %0" : "=r" (faulting_addr)); // get the faulting address from register cr2
  int present= !(regs.error_code & 1);
  int rw=(regs.error_code & 2);
  int us=(regs.error_code & 4);
  int res=(regs.error_code & 8);
  int id=(regs.error_code & 0x10);
  term_puts("page fault at address ");
  term_putn_hex(faulting_addr);
  term_puts("\n");
  panic("page fault");
}
void init_paging(void)
{
  uint32_t mem_end_page=0x1000000; // 16MB for now
  nFrames=mem_end_page/0x1000;
  frames=(uint32_t*)kmalloc(INDEX_FROM_BIT(nFrames));
  memset(frames, 0, INDEX_FROM_BIT(nFrames));
  page_dir_t* kernel_dir=(page_dir_t*)kmalloc_a(sizeof(page_dir_t));
  memset(kernel_dir, 0, sizeof(page_dir_t));
  current_directory=kernel_dir;
  int i=0;
  while(i<next_addr)
    {
      alloc_frame( get_page(i, 1, kernel_dir),0,0);
      i+=0x1000;
    }
  register_handler(14, &page_fault);
  switch_page_directory(kernel_dir);
}


