/* 	Machine entry point. 
	boot starts at start.
*/

// #include "boot.h"
#include "sysregs.h"

// AArch64 mode

// To keep this in the first portion of the binary.
.section ".text.boot"

// Make start global.
.global start
.global halt
.global delay

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
	// clear bss section (size is no. 64-bit words in bss)
	ldr     x5, =__bss_start
	ldr     w6, =__bss_size
bss_init_loop:
	cbz     w6, kernel_entry
	str     xzr, [x5], #8
	sub     w6, w6, #1
	cbnz    w6, bss_init_loop

kernel_entry:

	bl pconfig_pre_el1

	// set sp_el1
	ldr     x5, =start
	mov     sp, x5 // set stack before kernel code

	bl kmew_main
	// for failsafe, halt this core too
	b halt

halt:
	wfe // nop
	b halt

delay:
	subs	x0, x0, #1
	bne		delay
	ret
	b halt

pconfig_pre_el1:
	// set up sp_el2
	ldr x5, =start
	mov sp, x5

	// save ret address
	mov x1, lr

	// disable caches, mmu
	ldr x0, =SCTLR_VALUE_MMU_DISABLED	
	msr sctlr_el1, x0

	// init_el2 if in el2, else halt
	mrs x0, CurrentEl
	lsr x0, x0, #2
	cmp x0, 2
	bne halt

init_el2:
	// sets el1 execution state to aarch64
	ldr x0, =HCR_VALUE
	msr hcr_el2, x0

	// config vbar_eln
	bl init_el1_vector_table
	bl init_el2_vector_table
	
	//
	ldr x0, =SPSR_VALUE
	msr spsr_el2, x0

	//
	msr elr_el2, x1
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

/** debug **/
get_vbar_el1:
	mrs x0, vbar_el1
	ret

get_vbar_el2:
	mrs x0, vbar_el2
	ret

get_spsel:
	mrs x0, spsel
	ret
