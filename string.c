#include <stdint.h>
#include <stddef.h>
size_t strlen(const char* str)
{
  size_t ret=0;
  while(str[ret]!=0)
    ++ret;
  return ret;
}
char dtoc(uint8_t digit) // this should go into ctype.h, but this is ok
{
  return '0'+digit;
}
void memset(void* ptr, unsigned char value, size_t n)
{
  unsigned char *p=ptr;
  while(--n)
    {
      *p++= value;
    }
}
