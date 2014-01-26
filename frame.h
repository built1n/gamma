#include <stdint.h>
#include "gamma.h"
uint32_t *frames;
uint32_t nFrames;
extern uint32_t next_addr;
#define INDEX_FROM_BIT(a) (a/(8*4))
void alloc_frame(page_t* page, int kernel, int writeable);
void free_frame(page_t* page);




