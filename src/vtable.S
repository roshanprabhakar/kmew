.section ".text"

.global init_el1_vector_table
.global init_el2_vector_table

.global enable_irq
.global disable_irq
.global vectors

#define S_FRAME_SIZE 256
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

.macro ventry label
.balign 0x80
b \label
.endm

/****************************/
/******** EL1 VTABLE ********/
/****************************/
.balign 0x800
vtable_1:
	// from el1 shared sp
	ventry sync_t_from_el1
	ventry irq_t_from_el1
	ventry fiq_t_from_el1
	ventry serr_t_from_el1
	// from el1 distinct sp
	ventry sync_h_from_el1
	ventry irq_h_from_el1
	ventry fiq_h_from_el1
	ventry serr_h_from_el1
	// to el1 in aarch64
	ventry sync_from_aarch64_to_el1
	ventry irq_from_aarch64_to_el1
	ventry fiq_from_aarch64_to_el1
	ventry serr_from_aarch64_to_el1
	// to el1 in aarch32
	ventry sync_from_aarch32_to_el1
	ventry irq_from_aarch32_to_el1
	ventry fiq_from_aarch32_to_el1
	ventry serr_from_aarch32_to_el1

.macro exception_handler_el1 type
	kernel_entry
	mov x0, #\type
	mrs x1, esr_el1
	mrs x2, elr_el1
	mov x3, #1
	bl show_invalid_entry_message
	kernel_exit
.endm

//////////////////////////////
sync_t_from_el1:
	exception_handler_el1 0
irq_t_from_el1:
	exception_handler_el1 1
fiq_t_from_el1:
	exception_handler_el1 2
serr_t_from_el1:
	exception_handler_el1 3

//////////////////////////////
sync_h_from_el1:
	exception_handler_el1 4
irq_h_from_el1:
	exception_handler_el1 5
fiq_h_from_el1:
	exception_handler_el1 6
serr_h_from_el1:
	exception_handler_el1 7

//////////////////////////////
sync_from_aarch64_to_el1:
	exception_handler_el1 8
irq_from_aarch64_to_el1:
	exception_handler_el1 9
fiq_from_aarch64_to_el1:
	exception_handler_el1 10
serr_from_aarch64_to_el1:
	exception_handler_el1 11

//////////////////////////////
sync_from_aarch32_to_el1:
	exception_handler_el1 12
irq_from_aarch32_to_el1:
	exception_handler_el1 13
fiq_from_aarch32_to_el1:
	exception_handler_el1 14
serr_from_aarch32_to_el1:
	exception_handler_el1 15


/****************************/
/******** EL2 VTABLE ********/
/****************************/
.balign 0x800
vtable_2:
	// from el1 shared sp
	ventry sync_t_from_el2
	ventry irq_t_from_el2
	ventry fiq_t_from_el2
	ventry serr_t_from_el2
	// from el1 distinct sp
	ventry sync_h_from_el2
	ventry irq_h_from_el2
	ventry fiq_h_from_el2
	ventry serr_t_from_el2
	// to el1 in aarch64
	ventry sync_from_aarch64_to_el2
	ventry irq_from_aarch64_to_el2
	ventry fiq_from_aarch64_to_el2
	ventry serr_from_aarch64_to_el2
	// to el1 in aarch32
	ventry sync_from_aarch32_to_el2
	ventry irq_from_aarch32_to_el2
	ventry fiq_from_aarch32_to_el2
	ventry serr_from_aarch32_to_el2

.macro exception_handler_el2 type
	kernel_entry
	mov x0, #\type
	mrs x1, esr_el2
	mrs x2, elr_el2
	mov x3, #2
	bl show_invalid_entry_message
	kernel_exit
.endm

//////////////////////////////
sync_t_from_el2:
	exception_handler_el2 0
irq_t_from_el2:
	exception_handler_el2 1
fiq_t_from_el2:
	exception_handler_el2 2
serr_t_from_el2:
	exception_handler_el2 3

//////////////////////////////
sync_h_from_el2:
	exception_handler_el2 4
irq_h_from_el2:
	exception_handler_el2 5
fiq_h_from_el2:
	exception_handler_el2 6
serr_h_from_el2:
	exception_handler_el2 7

//////////////////////////////
sync_from_aarch64_to_el2:
	exception_handler_el2 8
irq_from_aarch64_to_el2:
	exception_handler_el2 9
fiq_from_aarch64_to_el2:
	exception_handler_el2 10
serr_from_aarch64_to_el2:
	exception_handler_el2 11

//////////////////////////////
sync_from_aarch32_to_el2:
	exception_handler_el2 12
irq_from_aarch32_to_el2:
	exception_handler_el2 13
fiq_from_aarch32_to_el2:
	exception_handler_el2 14
serr_from_aarch32_to_el2:
	exception_handler_el2 15

//////////////////////////////
init_el1_vector_table:
  adr x0, vtable_1
  msr vbar_el1, x0
  ret

init_el2_vector_table:
	adr x0, vtable_2
	msr vbar_el2, x0
	ret

enable_irq:
  msr daifclr, #2
  ret

disable_irq:
  msr daifset, #2
  ret

