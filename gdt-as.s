	.global gdt_flush
	.type gdt_flush, @function
gdt_flush:
	cli
	movl 4(%esp), %eax
	lgdt (%eax)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ss, %ax
	jmp flush
flush:
	sti
	ret
	
	.global idt_flush
	.type idt_flush, @function
idt_flush:
	cli
	movl 4(%esp), %eax
	lidt (%eax)
	sti
	ret
