
.section ".text.vector_table_setup"

.global _vector_table_setup

// vtable setup routine, call after bss_init_loop
// Create vtable for EL1, place right before kernel_main
_vector_table_setup:
		ldr		x1, =_vector_table_el1
		msr		vbar_el1, x1
