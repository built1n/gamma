#include "gamma.h"
static char* read_buf;
static int idx=0, maxchars;
static int* readdone;
void on_keypress(char c)
{
  if(c!='\n' && c!='\b' && c!=127)
    {
      if(idx<maxchars)
	{
	  read_buf[idx]=c;
	  ++idx;
	}
      printf("Buffer: ");
      printf(read_buf);
      printf("\n");
    }
  else
    {
      switch(c)
	{
	case '\n':
	  readdone=1; // this does not work!
	  break;
	case '\b': case 127:
	  if(idx>0)
	    {
	      read_buf[idx]=0;
	      --idx;
	    }
	  break;
	}
    }
}
int read(int n, char* buf)
{
  readdone=kmalloc(4);
  *readdone=0;
  if(buf)
    {
      memset(buf, 0, n);
      printf("Entering read function.\n");
      void* old_handler=get_keyboard_handler();
      idx=0;
      readdone=0;

      read_buf=buf;
      maxchars=n;
      printf("Registering new keyboard handler.\n");
      register_keyboard_handler(&on_keypress);
      printf("Looping...\n");
      int *ptr=readdone; // prevent any optimizations 
    loop:
      if(*ptr==0)
	goto loop;
      else
	goto done;
    done:
      printf("Done!\n");
      register_keyboard_handler(old_handler);
      return idx;
    }
  return -1;
}
