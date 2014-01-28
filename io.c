#include "gamma.h"
static char* read_buf;
static int idx=0, maxchars;
static volatile int readdone=0;
void on_keypress(char c)
{
  if(c!='\n' && c!='\b' && c!=127)
    {
      if(idx<maxchars)
	{
	  read_buf[idx]=c;
	  ++idx;
	}
    }
  else
    {
      switch(c)
	{
	case '\n':
	  readdone=1;
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
static void idle()
{
  return;
}
int read(int n, char* buf)
{
  term_puts("Entering read function.\n");
  void* old_handler=get_keyboard_handler();
  idx=0;
  readdone=0;
  read_buf=buf;
  maxchars=n;
  term_puts("Registering new keyboard handler.\n");
  register_keyboard_handler(&on_keypress);
  term_puts("Looping...\n");
  while(readdone==0)
    idle();
  term_puts("Done!\n");
  register_keyboard_handler(old_handler);
  return idx;
}
