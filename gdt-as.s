	.global gdt_flush
	.type gdt_flush, @function
gdt_flush:
	movl (%esp+4), %eax
	lgdt %eax
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	jmp flush
flush:
	ret
idt_flush:
	movl (%esp+4), %eax
	lidt (%eax)
	ret
