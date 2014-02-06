#include "../gamma.h"
#define LINGO_STACK_SIZE 8192
struct lingo_regs_t {
  uint32_t ra, rb, rc, rd, rsp, pc;
  byte rf;
};
typedef struct lingo_regs_t lingo_regs_t;
struct lingo_ctx {
  lingo_regs_t regs;
  byte* program; // the executable, with LINGO_STACK_SIZE bytes appended for stack
};
typedef struct lingo_ctx lingo_ctx;
lingo_ctx* lingo_new_ctx(byte*, uint32_t, uint32_t stack_size=0);
void lingo_exec(lingo_ctx*);
