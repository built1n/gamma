	.global	loop_while_ptr_zero
	# function prototype: void loop...(uint32_t* ptr)
	.type loop_while_ptr_zero, @function
	
loop_while_ptr_zero:
	pushl %ebp
	movl %esp, %ebp
	movl 4(%esp), %eax
loop:
	movl (%eax), %edx
	testl %edx, %edx
	je loop
	ret
