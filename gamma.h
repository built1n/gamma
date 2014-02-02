#ifndef GAMMA_H
#define GAMMA_H
/* instead of including every header in every source file , this file includes them all in one place */
#include "gdt.h" // Global descriptor table
#include "idt.h" // Interrupt table
#include "isr.h" // Interrupt handlers
#include "string.h" // strcmp, strlen, etc.
#include "term.h" // terminal functions
#include "util.h" // port i/o, call trace
#include "panic.h" // the panic function
#include "clock.h" // extremely complex!
#include "keyboard.h" // PS/2 only
#include "page.h" //-+ 
#include "heap.h" // += Virtual memory
#include "frame.h"//-+
#include "io.h"
#include "power.h"
#include "sound.h"
const char* build_time;
const char* build_date;
typedef unsigned char byte;
#endif
