#include "../gamma.h"
#include <stdint.h>
#define LINGO_STACK_SIZE 8192
struct lingo_regs_t {
  uint32_t RA, RB, RC, RD, RSP, PC;
  byte RF;
};
typedef struct lingo_regs_t lingo_regs_t;
struct lingo_ctx {
  lingo_regs_t regs;
  byte* program; // the executable, with LINGO_STACK_SIZE bytes appended for stack
};
typedef struct lingo_ctx lingo_ctx;
lingo_ctx* lingo_new_ctx(byte*, uint32_t, uint32_t);
void lingo_exec(lingo_ctx*);
