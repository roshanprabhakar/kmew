
ENTRY(_start)

SECTIONS {
    . = 0x80000;
    .text :
    {
        KEEP(*(.text.boot))	
				KEEP(*(.text.vector_table_setup))

        *(.text) /* Contains kernel */

				. = ALIGN(0x800); /* Align req for vector table */
				KEEP(*(.text.vector_tables))
    }
    . = ALIGN(4096); /* PI page size */

    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096);

    .data : 
    {
        *(.data)
    }
    . = ALIGN(4096);

    __bss_start = .;
    .bss : 
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096);
    __bss_end = .;

    __bss_size = __bss_end - __bss_start;
    __end = .;
}

