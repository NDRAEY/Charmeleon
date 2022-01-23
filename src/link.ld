ENTRY(_start)

SECTIONS
{
	. = 1M;
	.text ALIGN(4K) : AT (ADDR(.text))
	{
		*(.multiboot)
		*(.text)
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
		*(.initial_stack)

	}
	end = .;
}
