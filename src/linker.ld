ENTRY(_start)

__kernel_start = 0x80000;

SECTIONS {
  . = __kernel_start;
  .text :
  {
    KEEP(*(.text.boot))
    /* KEEP(*(.text.kernel_main)) */
    /* KEEP(*(.text.printf)) */
    /* KEEP(*(.text.serial_cli)) */
    /* KEEP(*(.text.kmew_libc)) */

    /* KEEP(*(.text.system_init_proxys)) */
    /* KEEP(*(.text.reg_init)) */

    /* . = ALIGN(0x800); */ /* Align req for vector table */
    /* KEEP(*(.text.vector_tables)) */

    KEEP(*(.text))
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

  __kernel_boundary_end = .;
  __end = .;

  __cpu_stack_top = __kernel_start;
  __cpu_stack_size = __kernel_start;
}

