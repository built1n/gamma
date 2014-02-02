/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
#include <stdint.h>
#include "gamma.h"
#define CLOCK_FREQ 1193180 // this is the same for all Intel CPUs
void clock_tick(registers_t);
void init_clock(uint32_t);
uint64_t time(void); // in hundredths of a second
void sleep(uint32_t n); // sleep n hundredths of a second, accurate to 1 hundredth of a second
