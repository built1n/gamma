	.global	loop_while_ptr_zero
	# function prototype: void loop...(uint32_t* ptr)
	.type loop_while_ptr_zero, @function
loop_while_ptr_zero:
	movl 4(%esp), %ebx # load the address
loop:	
	movl (%ebx), %eax
	subl $1, %eax
	jnz loop
	ret
