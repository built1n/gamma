	.global	loop_while_ptr_zero
	# function prototype: void loop...(uint32_t* ptr)
	.type loop_while_ptr_zero, @function
	
loop_while_ptr_zero:
	push %ebp
	mov %esp, %ebp
	xor %edx, %edx
loop:
	movl 4(%esp), %eax
	movl (%eax), %eax
	cmp %eax, %edx
	je loop
	ret
