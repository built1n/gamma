	.global gdt_flush
	.type gdt_flush, @function
gdt_flush: // this function is BUGGY
	pop %eax
	push %eax # will restore stack w/ eax=top
	lgdt (%eax)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ss, %ax
	jmp flush
flush:
	ret
	.global idt_flush
	.type idt_flush, @function
idt_flush:
	movl 4(%esp), %eax
	lidt (%eax)
	ret
