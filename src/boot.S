// AArch64 mode

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global.
.global _start
.global _delay

// Entry point for the kernel. Registers:
// x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores)
// x1 -> 0
// x2 -> 0
// x3 -> 0
// x4 -> 32 bit kernel entry point, _start location

// begin execution here after firmware boot
_start:
    // Hang other threads
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    cbz     x0, _entry
    b       _halt

_entry:
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

_kernel_entry:
    // What is current exception level
    // msr     x0, CurrentEL
    // lsr     x0, x0, 2

    // What EL level are we in?
    // bl      _vector_table_setup
    // bl      _reg_init
    bl      kmew_main

    // for failsafe, halt this core too
    b _halt

_halt:
    wfe // nop

_delay:
		subs	x0, x0, #1
		bne		_delay
		ret
    b _halt
