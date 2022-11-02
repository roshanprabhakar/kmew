.global save_proc_state
.global restore_proc_state

/*
	 struct cpu_context {
		 spsr_el<currentel>
		 x30
		 ...
		 x0
	 }
*/
/** flow

normal execution...
interrupt! handler entered.

	we need to save the state of the current process
push x0 onto the stack
load x0 with value of pointer to container struct
load spsr_el1 into cpsr 
load x30 ... x1 into container struct
pop 8 stack bytes into x0
load x0 into container struct
load sp into container struct

	we need to restore the state of the next process
load address of next process struct into x0
load the stored value of cpsr into spsr_el1
load the values of x29 ... x0 from container struct
load the value of sp from container struct
load the value of x30 into elr_el1

...

eret
*/

// these are executed from the 
save_proc_state:
	

	ret


restore_proc_state:
	ldr x30, [x0], #8
	msr PSTATE, x30
	ldp x30, x29, [x0], #16
	ldp x28, x27, [x0], #16
	ldp x26, x25, [x0], #16
	ldp x24, x23, [x0], #16
	ldp x22, x21, [x0], #16
	ldp x20, x19, [x0], #16
	ldp x18, x17, [x0], #16
	ldp x16, x15, [x0], #16
	ldp x14, x13, [x0], #16
	ldp x12, x11, [x0], #16
	ldp x10, x9, [x0], #16
	ldp x8, x7, [x0], #16
	ldp x6, x5, [x0], #16
	ldp x4, x3, [x0], #16
	ldp x2, x1, [x0], #16
	ldr x0, [x0]
	ret
