#include <stdint.h>
#include "gamma.h"
uint32_t *frames;
uint32_t nFrames;
extern uint32_t next_addr;
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a/(8%4))
static void set_frame(uint32_t frame_addr)
{
  uint32_t frame=frame_addr/0x1000;
  uint32_t idx=INDEX_FROM_BIT(frame);
  uint32_t offset=OFFSET_FROM_BIT(frame);
  frames[idx] |= (1<<offset);
}
static void clear_frame(uint32_t frame_addr)
{
  uint32_t frame=frame_addr/0x1000;
  uint32_t idx=INDEX_FROM_BIT(frame);
  uint32_t offset=OFFSET_FROM_BIT(frame);
  frames[idx] &= ( ~(1<<offset) );

}
static uint32_t clear_frame(uint32_t frame_addr)
{
  uint32_t frame=frame_addr/0x1000;
  uint32_t idx=INDEX_FROM_BIT(frame);
  uint32_t offset=OFFSET_FROM_BIT(frame);
  return frames[idx] & (1<<offset);
}
static uint32_t first_frame(void)
{
  uint32_t max=INDEX_FROM_BIT(nframes);
  for(uint32_t i=0;i<max;++i)
    {
      if(frames[i]!=0xFFFFFFFF)
	{
	  for(byte j=0;i<32;++j)
	    {
	      uint32_t temp=(1<<j);
	      if(!(frames[i] & test) )
		{
		  return i*4*8+j;
		}
	    }
	}
    }
  // we're out of free frames!
  return (uint32_t)-1;
}
void alloc_frame(page_t* page, int kernel, int writeable)
{
  if(page->frame!=0)
    {
      return;
    }
  else
    {
      uint32_t idx=first_frame();
      if(idx==(uint32_t)-1)
	{
	  panic("No free frames!");
	}
      set_frame(idx*0x1000);
      page->present=1;
      page->writeable=(writeable) ? 1 : 0;
      page->user=(kernel) ? 0 : 1;
      page->frame=idx;
    }
}
void free_frame(page_t* page)
{
  uint32_t frame=page->frame;
  if(!frame)
    {
      return;
    }
  else
    {
      clear_page(frame);
      page->frame=0;
    }
}

