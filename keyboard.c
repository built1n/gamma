#include "gamma.h"
#include <stdbool.h>
byte ps2_current_scancode_set;
enum PS2_State { READY, SENDING, WAITING } ps2_state;
// Data port: 0x60, command: 0x64
bool ps2_attempt_command(byte command, byte data, bool sendByte)
{
  ps2_state=SENDING;
  byte good=0xFE; // set to 0xFE for resend
  for(int i=0;i<3 || good!=0xFA;++i)
    { 
      outb(0x64, command);
      if(sendByte)
	outb(0x60, data);
      good=inb(0x60);
    }
  if(good==0xFE)
    {
      return false;
    }
  return true;
}
void ps2_interrupt(registers_t regs)
{
  byte key=inb(0x60);
  term_debug("Keypress detected");
  term_puts("Scancode is ");
  term_putn_hex((int)key);
  term_putchar('\n');
}
void init_ps2()
{
  register_handler(33, &ps2_interrupt);
}
