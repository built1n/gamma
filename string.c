#include <stdint.h>
#include <stddef.h>
size_t strlen(const char* str)
{
  size_t ret=0;
  while(str[ret]!=0)
    ++ret;
  return ret;
}
char dtoc(uint8_t digit) // this should go into ctype.h, but this is fine
{
  return digit+'0';
}
