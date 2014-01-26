#include "gamma.h"
typedef struct page {
  uint32_t present;
  uint32_t rw;
  uint32_t user;
  uint32_t accessed;
  uint32_t dirty;
  uint32_t unused;
  uint32_t frame;
} page_t;
typedef struct page_table {
  page_t pages[1024];
} page_table_t;
typedef struct page_directory {
  page_table_t *page_tables[1024]; // pointers to page tables
  uint32_t page_tables_phys[1024];
  uint32_t physAddr;
} page_dir_t;
void init_paging(void);
void switch_page_directory(page_dir_t *dir);
page_t* get_page(uint32_t addr, int make, page_dir_t *dir);
void page_fault(registers_t);





