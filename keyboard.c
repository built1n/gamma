#include "gamma.h"
#include <stdbool.h>
struct PS2_Command {
  uint16_t port;
  byte command;
};
struct PS2_QueueNode {
  struct PS2_Command value;
  struct PS2_QueueNode *next;
};
struct PS2_Queue {
  struct PS2_QueueNode *firstNode;
};
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
void init_ps2()
{
  if(ps2_state==READY) // this is useless, keep it in case of future changes
    {
      // attempt_command sets ps2_state to sending, so just set it back
      ps2_attempt_command(0xED, 7, true); // flash LED's
      ps2_attempt_command(0xED, 2, true);
      //ps2_attempt_command(0xF4, 0, false); // enable scanning
      ps2_state=READY;
    }
}
