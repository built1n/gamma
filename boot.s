	.set ALIGN,	 1<<0 	# Multiboot stuff
	.set MEMINFO,	 1<<1
	.set FLAGS,	 ALIGN | MEMINFO
	.set MAGIC,	 0x1BADB002 # 1 Bad Boot
	.set CHECKSUM,	 -(MAGIC + FLAGS)
	
.section .multiboot
	.align 4
	.long MAGIC
	.long FLAGS
	.long CHECKSUM		# Prove that we are multiboot
	
.section .initialize_stack
stack_bottom:			# Grows downwards in memory
	.skip 32768		# 32KB stack
stack_top:
	
.section .text
	.global _start
	.type _start, @function
_start:				# This is where execution begins
	cli			# Stop interrupts, this is a critical section
	movl %esp, stack_top	# Initialize the stack
	push %ebp		# Add register ebp to the arguments
	call kernel_main	# Start the kernel, SHOULD not return
	cli			# Stop interrupts
	hlt			# Halt the CPU
.LKernel_hang:			# Idle forever
	jmp .LKernel_hang
	.size _start, . - _start
