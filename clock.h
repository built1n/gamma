#include <stdint.h>
#include "gamma.h"
void clock_tick(registers_t);
void init_clock(uint32_t);
uint64_t ms_time(void); // inaccurate, only to 10 millisecond resolution
