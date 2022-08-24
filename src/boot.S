/* 	Machine entry point. 
		boot starts at _start.
 */

#include "regs.h"

// AArch64 mode

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make _start global.
.global _start
.global _delay
.global _get_exception_level
.global _switch_to_el1

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
    cbz     x0, _switch_to_el1
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

_get_exception_level:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret

_switch_to_el1:
    // Configure processor when running in EL1
    ldr x0, =SCTLR_MMU_DISABLED
    msr sctlr_el1, x0

    mrs x0, CurrentEL
    lsr x0, x0, #2

    // Check that we are in EL2, if yes, only initialize EL2
    cmp x0, 3
    bne init_el2

    // Configure EL3 (but we start on EL2 so how does this work??)
    ldr x0, =SCR_VALUE
    msr scr_el3, x0

    ldr x0, =SPSR_VALUE
    msr spsr_el3, x0

    adr x0, _entry
    msr elr_el3, x0

init_el2:
    // Configure EL2
    ldr x0, =HCR_VALUE
    msr hcr_el2, x0

    ldr x0, =SPSR_VALUE
    msr spsr_el2, x0

    adr x0, _entry
    msr elr_el2, x0

    eret
