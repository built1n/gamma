#include <stddef.h>
#include <stdint.h>
typedef struct gdt_entry_type { // do not alter the order of these!
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} gdt_entry_type __attribute__((packed)); // tell GCC to keep the contents in the order given
typedef struct gdt_ptr {
  uint16_t limit;
  uint32_t base;
} gdt_ptr __attribute__((packed)); // same purpose as above
void init_desc_tables(void);
