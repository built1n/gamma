#include "gamma.h"
#include <stdint.h>
typedef struct rtc_t {
  uint16_t year;
  byte month;
  byte day;
  byte hours;
  byte minutes;
  byte seconds;
  byte semaphore;
} rtc_t;
void load_real_time_clock(rtc_t*);
