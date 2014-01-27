/* Tell the linker how to combine the object files */
ENTRY(_start) /* kernel enters at _start */
SECTIONS
{
	. = 1M; /* skip 1M */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot) /* Multiboot header */
		*(.text) /* executable part */
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.initialize_stack)
	}
}
