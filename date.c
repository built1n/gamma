#include "gamma.h"
static rtc_t* current=0;
void private_get_rtc(registers_t regs)
{
  current->seconds=read_cmos(0x00, 0);
  current->minutes=read_cmos(0x02, 0);
  current->hours=read_cmos(0x04, 0);
  current->day=read_cmos(0x07, 0);
  current->month=read_cmos(0x08, 0);
  current->year=read_cmos(0x09, 0);
  current->semaphore=1;
}
byte compare_rtc(rtc_t a, rtc_t b)
{
  if(a.seconds==b.seconds && a.minutes==b.minutes && a.hours==b.hours && a.day==b.day && a.month==b.month && a.year==b.year)
    return 1;
  return 0;
}
void load_real_time_clock(rtc_t* ret)
{
  rtc_t old;
  rtc_t test;
  test.seconds=1;
  old.seconds=0;
  do {
    while(read_cmos(0x0A, 0) & 0x80)
    ;
    old.seconds=read_cmos(0x00, 0);
    old.minutes=read_cmos(0x02, 0);
    old.hours=read_cmos(0x04, 0);
    old.day=read_cmos(0x07, 0);
    old.month=read_cmos(0x08, 0);
    old.year=read_cmos(0x09, 0);
    test.seconds=read_cmos(0x00, 0);
    test.minutes=read_cmos(0x02, 0);
    test.hours=read_cmos(0x04, 0);
    test.day=read_cmos(0x07, 0);
    test.month=read_cmos(0x08, 0);
    test.year=read_cmos(0x09, 0);
    if(compare_rtc(old, test))
      {
	current->seconds=old.seconds;
	current->minutes=old.minutes;
	current->hours=old.hours;
	current->day=old.day;
	current->month=old.month;
	current->year=old.year;
      }
  } while(!compare_rtc(old, test));
}
