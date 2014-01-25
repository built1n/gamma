	.global gdt_flush  # function prototype: void gdt_flush(uint32_t addr)
	.type gdt_flush, @function
gdt_flush:
	cli # this is a critical section of code!
	movl 4(%esp), %eax # load the address off the stack
	lgdt (%eax) # load the GDT
	mov $0x10, %ax # set all section registers to 16
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ss, %ax
	sti # enable interrupts
	ret
	
	.global idt_flush # function prototype: void idt_flush(uint32_t addr)
	.type idt_flush, @function
idt_flush:
	cli # this is a critical section of code!
	movl 4(%esp), %eax # load the address off the stack
	lidt (%eax) # load the IDT
	sti # resume interrupts
	ret


