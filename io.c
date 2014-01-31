#include "gamma.h"
static char* read_buf;
static int idx=0, maxchars;
int readdone=0;
void on_keypress(char c)
{
  if(c!='\n' && c!='\b' && c!=127)
    {
      if(idx<maxchars)
	{
	  read_buf[idx]=c;
	  ++idx;
	}
      term_puts("Buffer: ");
      term_puts(read_buf);
      term_puts("\n");
    }
  else
    {
      switch(c)
	{
	case '\n':
	  readdone=1; // this does not work!
	  term_puts("Value of readdone: ");
	  term_putn_dec(readdone);
	  term_putchar('\n');
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
  if(buf)
    {
      memset(buf, 0, n);
      term_puts("Entering read function.\n");
      void* old_handler=get_keyboard_handler();
      idx=0;
      readdone=0;
      read_buf=buf;
      maxchars=n;
      term_puts("Registering new keyboard handler.\n");
      register_keyboard_handler(&on_keypress);
      term_puts("Looping...\n");
      int *ptr=&readdone; // prevent any optimizations 
    loop:
      if(*ptr==0)
	goto loop;
      else
	goto done;
    done:
      term_puts("Done!\n");
      register_keyboard_handler(old_handler);
      return idx;
    }
  return -1;
}
