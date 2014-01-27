/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
// this is a PS/2 driver, not a USB driver!
#define TAB_WIDTH 4
#include "gamma.h"
#include <stdbool.h>
static void(*kbdhandler)(char)=0;
// PS/2 Data port: 0x60, command port: 0x64
struct {
  int ctrldown : 1; // done
  int shiftdown: 1; // done
  int arrowstat: 3; // 0: none 1: up 2: down 3: left 4: right, not implemented
  int metadown : 1; // done
  int escdown  : 1; // done
  int recievede0:1; // did we just get 0xE0?
  int numlock  : 1; // num lock on?
  int capslock : 1; // caps lock on?
  int scrlock  : 1; // scroll lock?
} modkeystatus; // keep track of modifier keys (ctrl, shift, etc)
byte ledstatus=0; // keep track of LEDs
void register_keyboard_handler(void(*fnPtr)(char))
{
  kbdhandler=fnPtr;
}
void *get_keyboard_handler()
{
  return kbdhandler;
}
void set_leds(int num, int caps, int scroll)
{
  ledstatus=scroll | (num << 1) | (caps << 2);
  outb(0x60, 0xED);
  outb(0x60, ledstatus);
}
static char ps2_qwerty_autogen(byte scancode) // process the scancode if it is A-Z
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
    case 0x1C: // enter down
      c='\n';
      break;
    case 0x39: // space down
      c=' ';
      break;
    case 0x0E: // bksp down
      c='\b';
      break;;
    default:
      c=0;
      break;
    }
    switch(scancode)
    {
    case 0x53: // delete down
      if(modkeystatus.metadown && modkeystatus.ctrldown) // is it CTRL-ALT-DEL?
	{
	  // meant to be a debug aid
	  term_clear();
	  return 127;
	}
      return 127;
    case 0x1A: // left bracket
      if(modkeystatus.shiftdown)
	c='{';
      else
	c='[';
      break;
    case 0x1B: // right bracket
      if(modkeystatus.shiftdown)
	c='}';
      else
	c=']';
      break;
    case 0x27: // semicolon
      if(modkeystatus.shiftdown)
	c=':';
      else
	c=';';
      break;
    case 0x28: // single quote
      if(modkeystatus.shiftdown)
	c='"';
      else
	c='\'';
      break;
    case 0x29: // tilde, backtick
      if(modkeystatus.shiftdown)
	c='~';
      else
	c='`';
      break;
    case 0x2B: // backslash
      if(modkeystatus.shiftdown)
	c='|';
      else
	c='\\';
      break;
    case 0x33: // comma
      if(modkeystatus.shiftdown)
	c='<';
      else
	c=',';
      break;
    case 0x34: // period
      if(modkeystatus.shiftdown)
	c='>';
      else
	c='.';
      break;
    case 0x35: // forward slash
      if(modkeystatus.shiftdown)
	c='?';
      else
	c='/';
      break;
    case 0x0C: // hyphen
      if(modkeystatus.shiftdown)
	c='_';
      else
	c='-';
      break;
    case 0x0D: // equal sign
      if(modkeystatus.shiftdown)
	c='+';
      else
	c='=';
      break;
    case 0x0F:
      // tab
      for(int i=0;i<TAB_WIDTH;++i)
	term_put_keyboard_char(' ');
      c='\t';
      break;
    }
  if(c!=0)
    {
      // we can do other stuff here, too
      // for instance: append to a keyboard buffer
      term_put_keyboard_char(c);
      if(kbdhandler)
	{
	  kbdhandler(c);
	}
      return c;
    }
  return 0;
}
const char number_shift_lookup[10] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')'}; // array of number keys + shift
static void ps2_process_key(byte scancode) // top level QWERTY PS/2 decoder
{
  // up code for any down code is down code + 0x80
  switch(scancode) // handle modifier keys
    {
    case 0x01: // esc
      modkeystatus.escdown=1;
      return;
    case 0x81: // esc up
      modkeystatus.escdown=0;
      return;
    case 0x2A: case 0x36:
      if(!modkeystatus.capslock) // shift down
	modkeystatus.shiftdown=1;
      else
	modkeystatus.shiftdown=modkeystatus.shiftdown+1;
      break;
    case 0xAA: case 0xB6: // shift up
      if(!modkeystatus.capslock)
	modkeystatus.shiftdown=0;
      else
	modkeystatus.shiftdown=modkeystatus.shiftdown+1;
      break;
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
  if(ps2_qwerty_autogen(scancode))
    return;
  if(scancode >=2 && scancode <=11) // number
    {
      if(modkeystatus.shiftdown)
	term_put_keyboard_char(number_shift_lookup[scancode-2]);
      else
	term_put_keyboard_char(scancode!=11? dtoc(scancode-1) : '0');
      return;
    }
}
void ps2_interrupt(registers_t regs)
{
  byte scancode=inb(0x60); // read the scancode
  ps2_process_key(scancode); // process the scancode
}
void init_ps2()
{
  memset(&modkeystatus, 0, sizeof(modkeystatus));
  register_handler(33, &ps2_interrupt);
  outb(0x60, 0xF0); 
  outb(0x60, 1); // set to scan code set 1
  set_leds(1, 1, 1); // flash the leds
  set_leds(0, 0, 0);
  term_puts("PS/2 keyboard initialized.\n");
}
