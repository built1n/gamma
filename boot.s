	.set ALIGN,	 1<<0 	# Multiboot stuff
	.set MEMINFO,	 1<<1
	.set FLAGS,	 ALIGN | MEMINFO
	.set MAGIC,	 0x1BADB002
	.set CHECKSUM,	 -(MAGIC + FLAGS)
	.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long CHECKSUM		# Prove that we are multiboot
	.section .initialize_stack
stack_bottom:			# Grows downwards
	.skip 16384		# 16K
stack_top:
	.section .text
	.global _start
	.type _start, @function
_start:
	movl stack_top, %esp	# Initialize the stack
	push %ebp		# Add %ebp to the arguments of kernel_main
	call kernel_main	# Start the kernel
	cli			# Clear interrupts
	hlt			# Halt the CPU
.LKernel_hang:			# Idle forever
	jmp .LKernel_hang
	.size _start, . - _start
