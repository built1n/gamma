#include "gamma.h"
#include <stdbool.h>
byte ps2_current_scancode_set;
enum PS2_State { READY, SENDING, WAITING } ps2_state;
// Data port: 0x60, command: 0x64
struct {
  int ctrldown : 1; // done
  int shiftdown: 1; // done
  int arrowstat: 3; // 0: none 1: up 2: down 3: left 4: right
  int metadown : 1; // done
  int escdown  : 1; // done
  int recievede0:1; // did we just get 0xE0?
} modkeystatus;
static void ps2_qwerty_autogen(byte scancode)
{
  switch(scancode)
    {
    case 0x1E:
      if(modkeystatus.shiftdown)
	term_putchar('A');
      else
	term_putchar('a');
      break;
    case 0x30:
      if(modkeystatus.shiftdown)
	term_putchar('B');
      else
	term_putchar('b');
      break;
    case 0x2E:
      if(modkeystatus.shiftdown)
	term_putchar('C');
      else
	term_putchar('c');
      break;
    case 0x20:
      if(modkeystatus.shiftdown)
	term_putchar('D');
      else
	term_putchar('d');
      break;
    case 0x12:
      if(modkeystatus.shiftdown)
	term_putchar('E');
      else
	term_putchar('e');
      break;
    case 0x21:
      if(modkeystatus.shiftdown)
	term_putchar('F');
      else
	term_putchar('f');
      break;
    case 0x22:
      if(modkeystatus.shiftdown)
	term_putchar('G');
      else
	term_putchar('g');
      break;
    case 0x23:
      if(modkeystatus.shiftdown)
	term_putchar('H');
      else
	term_putchar('h');
      break;
    case 0x17:
      if(modkeystatus.shiftdown)
	term_putchar('I');
      else
	term_putchar('i');
      break;
    case 0x24:
      if(modkeystatus.shiftdown)
	term_putchar('J');
      else
	term_putchar('j');
      break;
    case 0x25:
      if(modkeystatus.shiftdown)
	term_putchar('K');
      else
	term_putchar('k');
      break;
    case 0x26:
      if(modkeystatus.shiftdown)
	term_putchar('L');
      else
	term_putchar('l');
      break;
    case 0x32:
      if(modkeystatus.shiftdown)
	term_putchar('M');
      else
	term_putchar('m');
      break;
    case 0x31:
      if(modkeystatus.shiftdown)
	term_putchar('N');
      else
	term_putchar('n');
      break;
    case 0x18:
      if(modkeystatus.shiftdown)
	term_putchar('O');
      else
	term_putchar('o');
      break;
    case 0x19:
      if(modkeystatus.shiftdown)
	term_putchar('P');
      else
	term_putchar('p');
      break;
    case 0x10:
      if(modkeystatus.shiftdown)
	term_putchar('Q');
      else
	term_putchar('q');
      break;
    case 0x13:
      if(modkeystatus.shiftdown)
	term_putchar('R');
      else
	term_putchar('r');
      break;
    case 0x1F:
      if(modkeystatus.shiftdown)
	term_putchar('S');
      else
	term_putchar('s');
      break;
    case 0x14:
      if(modkeystatus.shiftdown)
	term_putchar('T');
      else
	term_putchar('t');
      break;
    case 0x16:
      if(modkeystatus.shiftdown)
	term_putchar('U');
      else
	term_putchar('u');
      break;
    case 0x2f:
      if(modkeystatus.shiftdown)
	term_putchar('V');
      else
	term_putchar('v');
      break;
    case 0x11:
      if(modkeystatus.shiftdown)
	term_putchar('W');
      else
	term_putchar('w');
      break;
    case 0x2D:
      if(modkeystatus.shiftdown)
	term_putchar('X');
      else
	term_putchar('x');
      break;
    case 0x15:
      if(modkeystatus.shiftdown)
	term_putchar('Y');
      else
	term_putchar('y');
      break;
    case 0x2C:
      if(modkeystatus.shiftdown)
	term_putchar('Z');
      else
	term_putchar('z');
      break;
    default:
      break;
    }
}
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
  if(scancode >=2 && scancode <=10) // number
    {
      if(modkeystatus.shiftdown)
	term_putchar(number_shift_lookup[scancode-1]);
      else
	term_putchar(dtoc(scancode-1));
      return;
    }
  switch(scancode)
    {
    case 0x1C:
      term_putchar('\n');
      return;
    case 0x0E:
      term_putchar('\b');
      return;
    }
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
  outb(0x60, 0xED);
  outb(0x60, 0x7); // all leds
}
