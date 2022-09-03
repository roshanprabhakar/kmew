#include "vtable.h"

.section ".text"

.global init_el1_vector_table
.global init_el2_vector_table

.global enable_irq
.global disable_irq
.global vectors

/* 
 * We need to pass 7 to the align directive because that is the amount
 * of zeroes placed before 1 appears in the binary representation of
 * the alignment.
 * 1 << 7 = 128 = 0x80
 * alignment has to be 0x80
 */
.macro ventry label
.align 7
b \label
.endm

.macro kernel_entry
sub	sp, sp, #S_FRAME_SIZE
stp	x0, x1, [sp, #16 * 0]
stp	x2, x3, [sp, #16 * 1]
stp	x4, x5, [sp, #16 * 2]
stp	x6, x7, [sp, #16 * 3]
stp	x8, x9, [sp, #16 * 4]
stp	x10, x11, [sp, #16 * 5]
stp	x12, x13, [sp, #16 * 6]
stp	x14, x15, [sp, #16 * 7]
stp	x16, x17, [sp, #16 * 8]
stp	x18, x19, [sp, #16 * 9]
stp	x20, x21, [sp, #16 * 10]
stp	x22, x23, [sp, #16 * 11]
stp	x24, x25, [sp, #16 * 12]
stp	x26, x27, [sp, #16 * 13]
stp	x28, x29, [sp, #16 * 14]
str	x30, [sp, #16 * 15] 
.endm

.macro	kernel_exit
ldp	x0, x1, [sp, #16 * 0]
ldp	x2, x3, [sp, #16 * 1]
ldp	x4, x5, [sp, #16 * 2]
ldp	x6, x7, [sp, #16 * 3]
ldp	x8, x9, [sp, #16 * 4]
ldp	x10, x11, [sp, #16 * 5]
ldp	x12, x13, [sp, #16 * 6]
ldp	x14, x15, [sp, #16 * 7]
ldp	x16, x17, [sp, #16 * 8]
ldp	x18, x19, [sp, #16 * 9]
ldp	x20, x21, [sp, #16 * 10]
ldp	x22, x23, [sp, #16 * 11]
ldp	x24, x25, [sp, #16 * 12]
ldp	x26, x27, [sp, #16 * 13]
ldp	x28, x29, [sp, #16 * 14]
ldr	x30, [sp, #16 * 15] 
add	sp, sp, #S_FRAME_SIZE		
eret
.endm

/***************************************************/
/************** EL1 EXCEPTION VECTORS **************/
/***************************************************/

.macro debug_handler_el1 type
kernel_entry
mov x0, #\type                      // Exception type
mrs x1, esr_el1                     // Exception description (what caused it?)
mrs x2, elr_el1                     // Address of the instruction that caused the exception
bl show_invalid_entry_message
b halt
.endm

/*
 * There are 4 exception types: Synchronous, IRQ, FIQ, SError
 * For each, we need to define 4 handlers:
 * - When in EL1 but using the shared spel0 stack pointer register (SPSel == 0)
 * - When in EL1 but not using the shared spel0 stack pointer register (SPSel == 1)
 * - When in EL0 64 bit
 * - When in EL0 32 bit
 */
.balign 0x800 /* use .balign for aligning by num bytes. */
el1_vectors:
ventry sync_invalid_el1t        // Synchronous EL1t
ventry irq_invalid_el1t         // IRQ EL1t
ventry fiq_invalid_el1t         // FIQ EL1t
ventry error_invalid_el1t       // Error EL1t

ventry sync_invalid_el1h        // Synchronous EL1h
ventry irq_invalid_el1h					        // IRQ EL1h
ventry fiq_invalid_el1h         // FIQ EL1h
ventry error_invalid_el1h       // Error EL1h

ventry sync_invalid_el0_64      // Synchronous 64-bit EL0
ventry irq_invalid_el0_64       // IRQ 64-bit EL0
ventry fiq_invalid_el0_64       // FIQ 64-bit EL0
ventry error_invalid_el0_64     // Error 64-bit EL0

ventry sync_invalid_el0_32      // Synchronous 32-bit EL0
ventry irq_invalid_el0_32       // IRQ 32-bit EL0
ventry fiq_invalid_el0_32       // FIQ 32-bit EL0
ventry error_invalid_el0_32     // Error 32-bit EL0

/////////////////////////////////////////

// If stack pointer is shared (EL0 and EL1 - just using spel0)
sync_invalid_el1t:
debug_handler_el1  SYNC_INVALID_ELnt

irq_invalid_el1t:
debug_handler_el1  IRQ_INVALID_ELnt

fiq_invalid_el1t:
debug_handler_el1  FIQ_INVALID_ELnt

error_invalid_el1t:
debug_handler_el1  ERROR_INVALID_ELnt

/////////////////////////////////////////

// If stack pointer is not shared (using spel1 or spel0 depending on EL)
sync_invalid_el1h:
debug_handler_el1  SYNC_INVALID_ELnh

irq_invalid_el1h:
debug_handler_el1  IRQ_INVALID_ELnh

fiq_invalid_el1h:
debug_handler_el1  FIQ_INVALID_ELnh

error_invalid_el1h:
debug_handler_el1  ERROR_INVALID_ELnh

/////////////////////////////////////////

sync_invalid_el0_64:
debug_handler_el1  SYNC_INVALID_ELm_64

irq_invalid_el0_64:
debug_handler_el1  IRQ_INVALID_ELm_64

fiq_invalid_el0_64:
debug_handler_el1  FIQ_INVALID_ELm_64

error_invalid_el0_64:
debug_handler_el1  ERROR_INVALID_ELm_64

/////////////////////////////////////////

sync_invalid_el0_32:
debug_handler_el1  SYNC_INVALID_ELm_32

irq_invalid_el0_32:
debug_handler_el1  IRQ_INVALID_ELm_32

fiq_invalid_el0_32:
debug_handler_el1  FIQ_INVALID_ELm_32

error_invalid_el0_32:
debug_handler_el1  ERROR_INVALID_ELm_32


/***************************************************/
/************** EL2 EXCEPTION VECTORS **************/
/***************************************************/

.macro debug_handler_el2 type
kernel_entry
mov x0, #\type
mrs x1, esr_el2
mrs x2, elr_el2
bl show_invalid_entry_message
b halt
.endm

.balign 0x800
el2_vectors:	// n < 2
ventry sync_invalid_el2t
ventry irq_invalid_el2t
ventry fiq_invalid_el2t
ventry error_invalid_el2t

ventry sync_invalid_el2h
ventry irq_invalid_el2h
ventry fiq_invalid_el2h
ventry error_invalid_el2h

ventry sync_invalid_eln_64
ventry irq_invalid_eln_64
ventry fiq_invalid_eln_64
ventry error_invalid_eln_64

ventry sync_invalid_eln_32
ventry irq_invalid_eln_32
ventry fiq_invalid_eln_32
ventry error_invalid_eln_32

/////////////////////////////////////////

// If stack pointer is shared (EL0 and EL1 - just using spel0)
sync_invalid_el2t:
debug_handler_el2  SYNC_INVALID_ELnt

irq_invalid_el2t:
debug_handler_el2  IRQ_INVALID_ELnt

fiq_invalid_el2t:
debug_handler_el2  FIQ_INVALID_ELnt

error_invalid_el2t:
debug_handler_el2  ERROR_INVALID_ELnt

/////////////////////////////////////////

// If stack pointer is not shared (using spel1 or spel0 depending on EL)
sync_invalid_el2h:
debug_handler_el2  SYNC_INVALID_ELnh

irq_invalid_el2h:
debug_handler_el2  IRQ_INVALID_ELnh

fiq_invalid_el2h:
debug_handler_el2  FIQ_INVALID_ELnh

error_invalid_el2h:
debug_handler_el2  ERROR_INVALID_ELnh

/////////////////////////////////////////

sync_invalid_eln_64:
debug_handler_el2  SYNC_INVALID_ELm_64

irq_invalid_eln_64:
debug_handler_el2  IRQ_INVALID_ELm_64

fiq_invalid_eln_64:
debug_handler_el2  FIQ_INVALID_ELm_64

error_invalid_eln_64:
debug_handler_el2  ERROR_INVALID_ELm_64

/////////////////////////////////////////

sync_invalid_eln_32:
debug_handler_el2  SYNC_INVALID_ELm_32

irq_invalid_eln_32:
debug_handler_el2  IRQ_INVALID_ELm_32

fiq_invalid_eln_32:
debug_handler_el2  FIQ_INVALID_ELm_32

error_invalid_eln_32:
debug_handler_el2  ERROR_INVALID_ELm_32

/////////////////////////////////////////

init_el1_vector_table:
  adr x0, el1_vectors
  msr vbar_el1, x0
  ret

init_el2_vector_table:
	adr x0, el2_vectors
	msr vbar_el1, x0
	ret

enable_irq:
  msr daifclr, #2
  ret

disable_irq:
  msr daifset, #2
  ret

