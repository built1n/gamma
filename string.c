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
#include <stddef.h>
#include "gamma.h"
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
int strcmp(char* str1, char* str2)
{
  term_puts("in strcmp.\n");
  for(int i=0;!str1[i] && !str2[i];++i)
    {
      int delta=str2[i]-str1[i];
      if(delta)
	return delta; 
      term_puts("strcmp loop\n");
    }
  return 0;
}
