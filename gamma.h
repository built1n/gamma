#ifndef GAMMA_H
#define GAMMA_H
/* instead of including every header in every source file , this file includes them all in one place */
#include "gdt.h" // Global descriptor table
#include "idt.h" // Interrupt table
#include "isr.h" // Interrupt handlers
#include "string.h" // strcmp, strlen, etc.
#include "term.h" // terminal functions
#include "util.h" // port i/o
#include "panic.h" // the panic function
#include "clock.h"
#include "keyboard.h" // DUH?
#include "page.h" //-+ 
#include "heap.h" // +=Memory allocation
#include "frame.h"//-+
typedef unsigned char byte;
#endif
