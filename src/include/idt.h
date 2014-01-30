/*
        ####       ##       ##    ##       ##    ##       ##
       ## ##      ###      ###   ###      ###   ###      ###
      ##  ##     ####     ####  ####     ####  ####     ####
     ##         ## ##    ## ## ## ##    ## ## ## ##    ## ##
    ##   ###   ######   ##  ####  ##   ##  ####  ##   ######
   ##     ##  ##   ##  ##   ###   ##  ##   ###   ##  ##   ##
  ########## ##    ## ##    ##    ## ##    ##    ## ##    ##
*/


//////////////Interrupt Descriptor Table///////////////////

#include <stddef.h>
#include <stdint.h>

struct idt_entry_type //8-byte
{
  uint16_t base_low; // Low 2 byte of Interrupt Handler offset.
  uint16_t sel; // Code segment selector in GDT
  uint8_t zero; // take up space
  uint8_t flags; // Type and Attribute of entry.W
  uint16_t base_high; // Hight 2 bytes of Interrupt Handler offset.
} __attribute__((packed));

typedef struct idt_entry_type idt_entry_type;


struct idt_ptr //Pointer to IDT in memory.
{
  uint16_t limit; //Size of IDT and ending address.
  uint32_t base; //Starting Address of IDT.
} __attribute__((packed));

typedef struct idt_ptr idt_ptr;

void clear_idt(void); // clear the IDT, usually to generate a triple-fault 

// our interrupt handlers, defined in interrupt.s
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// hardware IRQs ( Interrupt Request )
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
