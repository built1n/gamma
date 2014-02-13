	.set ALIGN,	 1<<0 	# Multiboot stuff
	.set MEMINFO,	 1<<1
	.set FLAGS,	 ALIGN | MEMINFO
	.set MAGIC,	 0x1BADB002 # 1 Bad Boot
	.set CHECKSUM,	 -(MAGIC + FLAGS)
	
.section .multiboot
	.align 4
multiboot_header:	
	.long MAGIC
	.long FLAGS
	.long CHECKSUM		# Prove that we are multiboot
	
.section .stack
stack_bottom:			# Stack grows up in addresses, so bottom is
				# lower than the top
	.skip 32768		# 32KB stack
stack_top:
	
.section .text 			# The executable section
	.global _start		# Declare _start as a global function
	.type _start, @function
_start:                         # This is where execution begins
	cli			# Stop interrupts, this is a critical section
	movl $stack_bottom, %esp	# Initialize the stack
	push %ebp		# Add register ebp to the arguments
	call kernel_main	# Start the kernel, SHOULD not return
	cli			# Stop interrupts
	hlt			# Halt the CPU
.LKernel_hang:			# Idle forever
	jmp .LKernel_hang
	.size _start, . - _start
