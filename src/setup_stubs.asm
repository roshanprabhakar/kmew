
.section ".text.system_init_proxys"

.global _vector_table_setup
.global _reg_init

// vtable setup routine, call after bss_init_loop
// Create vtable for EL1, place right before kernel_main
_vector_table_setup:
		ldr		x1,	=_vector_table_el1
		msr		vbar_el1,	x1
		ret

_reg_init:
		bl		_general_reg_init
		bl		_fp_reg_init
		bl		_sp_init
		bl		_sys_ctrl_reg_init
		ret
