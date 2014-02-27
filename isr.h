/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
#ifndef ISR_H
#define ISR_H
#include <stdbool.h>
#include <stdint.h>
#include "gamma.h"
struct registers_t {
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t interrupt_number, error_code;
  uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));
typedef struct registers_t registers_t;
void init_isr();
void register_handler(unsigned char number, void(*fnPtr)(registers_t));
void unregister_handler(unsigned char number);
void set_unhandled_panic(bool);
void null_handler(registers_t);
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#endif
