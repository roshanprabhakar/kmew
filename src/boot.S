/* 	Machine entry point. 
		boot starts at start.
 */

// #include "boot.h"

// AArch64 mode

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make start global.
.global start
.global halt
.global delay

.global switch_to_el1
.global get_el
.global get_daif
.global get_nzcv

// Entry point for the kernel. Registers:
// x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores)
// x1 -> 0
// x2 -> 0
// x3 -> 0
// x4 -> 32 bit kernel entry point, _start location

// begin execution here after firmware boot
start:
    // Hang other threads
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    cbz     x0, entry
    b       halt

entry:
    ldr     x5, =start
    mov     sp, x5 // set stack before kernel code

		// bl switch_to_el1

    // clear bss section (size is no. 64-bit words in bss)
    ldr     x5, =__bss_start
    ldr     w6, =__bss_size
bss_init_loop:
    cbz     w6, kernel_entry
    str     xzr, [x5], #8
    sub     w6, w6, #1
    cbnz    w6, bss_init_loop

kernel_entry:
    bl      kmew_main
    // for failsafe, halt this core too
    b halt

halt:
    wfe // nop

delay:
    subs	x0, x0, #1
    bne		delay
    ret
    b halt


/*
// https://developer.arm.com/documentation/ddi0595/2021-06/AArch64-Registers/SPSR-EL1--Saved-Program-Status-Register--EL1-
uint32_t get_reset_spsr_el1() {
	uint32_t r = 0;

	uint64_t el = get_el() ^ 0b1100;
	r |= (uint32_t) (el & SPSR_EL); 					// 3-0 = CurrentEL
																						// 4 = 0
																						// 5 = ?
	r |= (uint32_t) (get_daif() & SPSR_DAIF);	// 9-6 = daif
																						// 19-10 ?
																						// 20 = 0
																						// 21 = 0
																						// 27-22 = 0
	r |= (uint32_t) (get_nzcv() & SPSR_NZCV); // 31-28 = nzcv
	return r;
}
*/
get_reset_spsr_el1:
		stp	x29, x30, [sp, #-32]!
		mov	x29, sp
		str	wzr, [sp, #28]
		bl	get_el
		eor	x0, x0, #0xc
		str	x0, [sp, #16]
		ldr	x0, [sp, #16]
		and	w0, w0, #0xf
		ldr	w1, [sp, #28]
		orr	w0, w1, w0
		str	w0, [sp, #28]
		bl	get_daif
		and	w0, w0, #0x3c0
		ldr	w1, [sp, #28]
		orr	w0, w1, w0
		str	w0, [sp, #28]
		bl	get_nzcv
		and	w0, w0, #0xf0000000
		ldr	w1, [sp, #28]
		orr	w0, w1, w0
		str	w0, [sp, #28]
		ldr	w0, [sp, #28]
		ldp	x29, x30, [sp], #32
		ret

switch_to_el1:
		// store x0, x1 on stack
		sub sp, sp, #16
		stp x0, x1, [sp]
		
		// move return address from lr into elr_(curEl)
		mrs x30, elr_el2
		
		// get fake spsr, move it into spsr_el2
		bl get_reset_spsr_el1
		msr spsr_el2, x0

		// restore x0, x1 from stack
		ldp x0, x1, [sp]
		add sp, sp, #16

		eret

/** get pstate **/
get_el:
		mrs x0, CurrentEL
		ret

get_daif:
		mrs x0, daif
		ret

get_nzcv:
		mrs x0, nzcv
		ret

