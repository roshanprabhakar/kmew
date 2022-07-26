// AArch64 mode

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global.
.global _start

// Entry point for the kernel. Registers:
// x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores)
// x1 -> 0
// x2 -> 0
// x3 -> 0
// x4 -> 32 bit kernel entry point, _start location

// begin execution here after firmware boot
_start:     
    ldr     x5, =_start
    mov     sp, x5 // set stack before kernel code

    // clear bss section (size is no. 64-bit words in bss)
    ldr     x5, =__bss_start
    ldr     w6, =__bss_size
_bss_init_loop:
    cbz     w6, _kernel_entry
    str     xzr, [x5], #8
    sub     w6, w6, #1
    cbnz    w6, _bss_init_loop

    // jump to C code, should not return
_kernel_entry:
		bl			_vector_table_setup
		bl			_reg_init
    bl      kmew_main

    // for failsafe, halt this core too
    b _halt

_halt:
    wfe // nop
    b _halt
