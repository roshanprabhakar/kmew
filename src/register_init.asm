
.section ".text.reg_init"

.global _general_reg_init
.global _fp_reg_init
.global _sp_init
.global _sys_ctrl_reg_init

// init general register bank
_general_reg_init:
    mov     x0,			xzr		
		mov			x1,			xzr
		mov			x2,			xzr
		mov			x3,			xzr
		mov			x4,			xzr
		mov			x5,			xzr
		mov			x6,			xzr
		mov			x7,			xzr
		mov			x8,			xzr
    mov     x9, 		xzr
    mov     x10, 		xzr
    mov     x11,		xzr
    mov     x12,		xzr
    mov     x13,		xzr
    mov     x14,		xzr
    mov     x15,		xzr
    mov     x16,		xzr
    mov     x17,		xzr
    mov     x18,		xzr
    mov     x19,		xzr
    mov     x20,		xzr
    mov     x21,		xzr
    mov     x22,		xzr
    mov     x23,		xzr
    mov     x24,		xzr
    mov     x25,		xzr
    mov     x26,		xzr
    mov     x27,		xzr
    mov     x28,		xzr
    mov     x29,		xzr
    mov     x30,		xzr
		ret

// init floating point register bank
_fp_reg_init:
		msr			cptr_el3, 	xzr
		msr			cptr_el2,		xzr

		fmov		d1,			xzr
		fmov		d2,			xzr
		fmov		d3,			xzr
		fmov		d4,			xzr
		fmov		d5,			xzr
		fmov		d6,			xzr
		fmov		d7,			xzr
		fmov		d8,			xzr
		fmov		d9,			xzr
		fmov		d10,		xzr
		fmov		d11,		xzr
		fmov		d13,		xzr
		fmov		d14,		xzr
		fmov		d15,		xzr
		fmov		d16,		xzr
		fmov		d17,		xzr
		fmov		d18,		xzr
		fmov		d19,		xzr
		fmov		d20,		xzr
		fmov		d21,		xzr
		fmov		d22,		xzr
		fmov		d23,		xzr
		fmov		d24,		xzr
		fmov		d25,		xzr
		fmov		d26,		xzr
		fmov		d27,		xzr
		fmov		d28,		xzr
		fmov		d29,		xzr
		fmov		d30,		xzr
		fmov		d31,		xzr
		ret

// init stack pointer registers
// NOTE split stack when enabling more cores
_sp_init:
		ldr			x1,		=__cpu_stack_top			// load stack start into x1
		mrs			x2, 	mpidr_el1					// mpidr_el1 stores core identifier, load this into x2
		and 		x2,		x2,		#0xFF				// get cpu identifier from first byte, in case first 32bit 
		ldr			x3,		=__cpu_stack_size
		mov			sp, 	x1								// init sp
		ret

// init system control registers
_sys_ctrl_reg_init:
		nop
		ret
