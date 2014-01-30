/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/
//////////////Interrrupt Service Routine////////////////////

#ifndef ISR_H
#define ISR_H

#include <stdbool.h>
#include <stdint.h>

#include "gamma.h"

struct registers_t {
  uint32_t ds; //Data Segment 
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // 8 General Registers.
  uint32_t interrupt_number, error_code;
  uint32_t eip, cs, eflags; //Instruction Pointer , code segment , efalges reg
  uint32_t useresp, ss; //user stack pointer , stack segment.
} __attribute__((packed));

typedef struct registers_t registers_t;

void init_isr(); //sets all handlers to 0

void register_handler(unsigned char number, void(*fnPtr)(registers_t));

void unregister_handler(unsigned char number); //sets handlers[number] to 0;

void set_unhandled_panic(bool); //sets panic_on_unhandled to b;

void null_handler(registers_t);

#endif
