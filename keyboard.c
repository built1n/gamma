#include "gamma.h"
#include <stdbool.h>
// Data port: 0x60, command: 0x64
struct {
  int ctrldown : 1; // done
  int shiftdown: 1; // done
  int arrowstat: 3; // 0: none 1: up 2: down 3: left 4: right
  int metadown : 1; // done
  int escdown  : 1; // done
  int recievede0:1; // did we just get 0xE0?
} modkeystatus;
extern char* inputbuf;
extern int inputbuf_idx;
static void ps2_qwerty_autogen(byte scancode)
{
  char c=0;
  switch(scancode)
    {
    case 0x1E:
      if(modkeystatus.shiftdown)
	c='A';
      else
	c='a';
      break;
    case 0x30:
      if(modkeystatus.shiftdown)
	c='B';
      else
	c='b';
      break;
    case 0x2E:
      if(modkeystatus.shiftdown)
	c='C';
      else
	c='c';
      break;
    case 0x20:
      if(modkeystatus.shiftdown)
	c='D';
      else
	c='d';
      break;
    case 0x12:
      if(modkeystatus.shiftdown)
	c='E';
      else
	c='e';
      break;
    case 0x21:
      if(modkeystatus.shiftdown)
	c='F';
      else
	c='f';
      break;
    case 0x22:
      if(modkeystatus.shiftdown)
	c='G';
      else
	c='g';
      break;
    case 0x23:
      if(modkeystatus.shiftdown)
	c='H';
      else
	c='h';
      break;
    case 0x17:
      if(modkeystatus.shiftdown)
	c='I';
      else
	c='i';
      break;
    case 0x24:
      if(modkeystatus.shiftdown)
	c='J';
      else
	c='j';
      break;
    case 0x25:
      if(modkeystatus.shiftdown)
	c='K';
      else
	c='k';
      break;
    case 0x26:
      if(modkeystatus.shiftdown)
	c='L';
      else
	c='l';
      break;
    case 0x32:
      if(modkeystatus.shiftdown)
	c='M';
      else
	c='m';
      break;
    case 0x31:
      if(modkeystatus.shiftdown)
	c='N';
      else
	c='n';
      break;
    case 0x18:
      if(modkeystatus.shiftdown)
	c='O';
      else
	c='o';
      break;
    case 0x19:
      if(modkeystatus.shiftdown)
	c='P';
      else
	c='p';
      break;
    case 0x10:
      if(modkeystatus.shiftdown)
	c='Q';
      else
	c='q';
      break;
    case 0x13:
      if(modkeystatus.shiftdown)
	c='R';
      else
	c='r';
      break;
    case 0x1F:
      if(modkeystatus.shiftdown)
	c='S';
      else
	c='s';
      break;
    case 0x14:
      if(modkeystatus.shiftdown)
	c='T';
      else
	c='t';
      break;
    case 0x16:
      if(modkeystatus.shiftdown)
	c='U';
      else
	c='u';
      break;
    case 0x2F:
      if(modkeystatus.shiftdown)
	c='V';
      else
	c='v';
      break;
    case 0x11:
      if(modkeystatus.shiftdown)
	c='W';
      else
	c='w';
      break;
    case 0x2D:
      if(modkeystatus.shiftdown)
	c='X';
      else
	c='x';
      break;
    case 0x15:
      if(modkeystatus.shiftdown)
	c='Y';
      else
	c='y';
      break;
    case 0x2C:
      if(modkeystatus.shiftdown)
	c='Z';
      else
	c='z';
      break;
    default:
      c=0;
      break;
    }
  if(c!=0)
    {
      term_putchar(c);
      return;
    }
}
byte ledstatus=0;
const char number_shift_lookup[10] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')'};
static void ps2_process_key(byte scancode)
{
  switch(scancode) // handle modifier keys
    {
    case 0x01: // esc.
      modkeystatus.escdown=1;
      return;
    case 0x81: // esc. up
      modkeystatus.escdown=0;
      return;
    case 0x2A: case 0x36:
      modkeystatus.shiftdown=1;
      break;
    case 0xAA: case 0xB6:
      modkeystatus.shiftdown=0;
      return;
    case 0x1D: // left ctrl.
      if(modkeystatus.recievede0) // right ctrl.
	modkeystatus.recievede0=0;
      modkeystatus.ctrldown=1;
      return;
    case 0x9D: // ctrl up
      if(modkeystatus.recievede0)
	modkeystatus.recievede0=0;
      modkeystatus.ctrldown=0;
      return;
    case 0x38: // left alt
      if(modkeystatus.recievede0)
	modkeystatus.recievede0=0;
      modkeystatus.metadown=1;
      return;
    case 0xB8: // alt up
      if(modkeystatus.recievede0)
	modkeystatus.recievede0=0;
      modkeystatus.metadown=0;
      return;
    case 0xE0:
      modkeystatus.recievede0=1;
      return;
    }
  // not a modifier
  ps2_qwerty_autogen(scancode);
  switch(scancode)
    {
    case 0x1C:
      term_putchar('\n');
      return;
    case 0x0E:
      term_putchar('\b');
      return;
    case 0x39:
      term_putchar(' ');
      return;
    case 0x53:
      if(modkeystatus.metadown && modkeystatus.ctrldown)
	{
	  // reboot, or print message
	  term_puts("CTRL-ALT-DELETE recieved!\n");
	  panic("CTRL-ALT-DELETE recieved");
 	}
    case 0x1A:
      if(modkeystatus.shiftdown)
	term_putchar('{');
      else
	term_putchar('[');
      return;
    case 0x1B:
      if(modkeystatus.shiftdown)
	term_putchar('}');
      else
	term_putchar(']');
      return;
    case 0x27:
      if(modkeystatus.shiftdown)
	term_putchar(':');
      else
	term_putchar(';');
      return;
    case 0x28:
      if(modkeystatus.shiftdown)
	term_putchar('"');
      else
	term_putchar('\'');
      return;
    case 0x29:
      if(modkeystatus.shiftdown)
	term_putchar('~');
      else
	term_putchar('`');
      return;
    case 0x2B:
      if(modkeystatus.shiftdown)
	term_putchar('|');
      else
	term_putchar('\\');
      return;
    case 0x33:
      if(modkeystatus.shiftdown)
	term_putchar('<');
      else
	term_putchar(',');
      return;
    case 0x34:
      if(modkeystatus.shiftdown)
	term_putchar('>');
      else
	term_putchar('.');
      return;
    case 0x35:
      if(modkeystatus.shiftdown)
	term_putchar('?');
      else
	term_putchar('/');
      return;
    case 0x0C:
      if(modkeystatus.shiftdown)
	term_putchar('_');
      else
	term_putchar('-');
      return;
    case 0x0D:
      if(modkeystatus.shiftdown)
	term_putchar('+');
      else
	term_putchar('=');
      return;
    case 0x0F:
      // tab
      term_puts("        ");
      return;
    }
  if(scancode >=2 && scancode <=11) // number
    {
      if(modkeystatus.shiftdown)
	term_putchar(number_shift_lookup[scancode-2]);
      else
	term_putchar(scancode!=11?dtoc(scancode-1):'0');
      return;
    }
  term_puts("Unhandled scancode: ");
  term_putn_hex(scancode);
  term_putchar('\n');
}
void set_leds(int num, int caps, int scroll)
{
  ledstatus=scroll | (num << 1) | (caps << 2);
  outb(0x60, 0xED);
  outb(0x60, ledstatus);
}
void ps2_interrupt(registers_t regs)
{
  ps2_process_key(inb(0x60));
}
void init_ps2()
{
  memset(&modkeystatus, 0, sizeof(modkeystatus)); 
  register_handler(33, &ps2_interrupt);
  outb(0x60, 0xF0);
  outb(0x60, 1); // scan code set 1
  set_leds(1, 1, 1);
}
