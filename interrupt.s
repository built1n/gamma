	.global isr_handler_stub
	.type isr_handler_stub, @function
isr_handler_stub:
	pusha
	mov %ds, %ax # get data segment reg.
	push %eax
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	call isr_handler
	pop %eax	
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	popa
	add $8, %esp
	sti
	iret
	.global isr0
	.type isr0, @function
	.global isr0
.type isr0, @function
isr0:
    cli
    push 0
    push 0
    jmp isr_handler_stub
.global isr1
.type isr1, @function
isr1:
    cli
    push 0
    push 1
    jmp isr_handler_stub
.global isr2
.type isr2, @function
isr2:
    cli
    push 0
    push 2
    jmp isr_handler_stub
.global isr3
.type isr3, @function
isr3:
    cli
    push 0
    push 3
    jmp isr_handler_stub
.global isr4
.type isr4, @function
isr4:
    cli
    push 0
    push 4
    jmp isr_handler_stub
.global isr5
.type isr5, @function
isr5:
    cli
    push 0
    push 5
    jmp isr_handler_stub
.global isr6
.type isr6, @function
isr6:
    cli
    push 0
    push 6
    jmp isr_handler_stub
.global isr7
.type isr7, @function
isr7:
    cli
    push 0
    push 7
    jmp isr_handler_stub
.global isr8
.type isr8, @function
isr8:
    cli
    push 0
    push 8
    jmp isr_handler_stub
.global isr9
.type isr9, @function
isr9:
    cli
    push 0
    push 9
    jmp isr_handler_stub
.global isr10
.type isr10, @function
isr10:
    cli
    push 0
    push 10
    jmp isr_handler_stub
.global isr11
.type isr11, @function
isr11:
    cli
    push 0
    push 11
    jmp isr_handler_stub
.global isr12
.type isr12, @function
isr12:
    cli
    push 0
    push 12
    jmp isr_handler_stub
.global isr13
.type isr13, @function
isr13:
    cli
    push 0
    push 13
    jmp isr_handler_stub
.global isr14
.type isr14, @function
isr14:
    cli
    push 0
    push 14
    jmp isr_handler_stub
.global isr15
.type isr15, @function
isr15:
    cli
    push 0
    push 15
    jmp isr_handler_stub
.global isr16
.type isr16, @function
isr16:
    cli
    push 0
    push 16
    jmp isr_handler_stub
.global isr17
.type isr17, @function
isr17:
    cli
    push 0
    push 17
    jmp isr_handler_stub
.global isr18
.type isr18, @function
isr18:
    cli
    push 0
    push 18
    jmp isr_handler_stub
.global isr19
.type isr19, @function
isr19:
    cli
    push 0
    push 19
    jmp isr_handler_stub
.global isr20
.type isr20, @function
isr20:
    cli
    push 0
    push 20
    jmp isr_handler_stub
.global isr21
.type isr21, @function
isr21:
    cli
    push 0
    push 21
    jmp isr_handler_stub
.global isr22
.type isr22, @function
isr22:
    cli
    push 0
    push 22
    jmp isr_handler_stub
.global isr23
.type isr23, @function
isr23:
    cli
    push 0
    push 23
    jmp isr_handler_stub
.global isr24
.type isr24, @function
isr24:
    cli
    push 0
    push 24
    jmp isr_handler_stub
.global isr25
.type isr25, @function
isr25:
    cli
    push 0
    push 25
    jmp isr_handler_stub
.global isr26
.type isr26, @function
isr26:
    cli
    push 0
    push 26
    jmp isr_handler_stub
.global isr27
.type isr27, @function
isr27:
    cli
    push 0
    push 27
    jmp isr_handler_stub
.global isr28
.type isr28, @function
isr28:
    cli
    push 0
    push 28
    jmp isr_handler_stub
.global isr29
.type isr29, @function
isr29:
    cli
    push 0
    push 29
    jmp isr_handler_stub
.global isr30
.type isr30, @function
isr30:
    cli
    push 0
    push 30
    jmp isr_handler_stub
.global isr31
.type isr31, @function
isr31:
    cli
    push 0
    push 31
    jmp isr_handler_stub
