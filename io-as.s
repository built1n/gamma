	.global	loop_while_ptr_zero
	# function prototype: void loop...(uint32_t* ptr)
	.type loop_while_ptr_zero, @function
	
loop_while_ptr_zero:
	pushl %ebp
	movl %esp, %ebp
	movl 4(%esp), %ebx # load the address
	movl $1, %ecx
loop:	
	movl (%ebx), %eax # dereference the pointer
	cmpl %eax, %ecx # compare eax and one
	jne loop # the pointer is still zero
	leave
	ret
