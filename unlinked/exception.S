
.section ".text.vector_tables"

/*** Exception Handlers for EL 1  ***/
.global _vector_table_el1
.global _get_el

// assumes proper alignment by linker
_vector_table_el1:
    /**/
    b cur_el_with_sp0_sync
    .balign 0x80
    b cur_el_with_sp0_IRQ
    .balign 0x80
    b cur_el_with_sp0_FIQ
    .balign 0x80
    b cur_el_with_sp0_SError
    .balign 0x80

    /**/
    b cur_el_with_spx_sync
    .balign 0x80
    b cur_el_with_spx_IRQ
    .balign 0x80
    b cur_el_with_spx_FIQ
    .balign 0x80
    b cur_el_with_spx_SError
    .balign 0x80

    /**/
    b low_el_aarch64_sync
    .balign 0x80
    b low_el_aarch64_IRQ
    .balign 0x80
    b low_el_aarch64_FIQ
    .balign 0x80
    b low_el_aarch64_SError
    .balign 0x80

    /**/
    b low_el_aarch32_sync
    .balign 0x80
    b low_el_aarch32_IRQ
    .balign 0x80
    b low_el_aarch32_FIQ
    .balign 0x80
    b low_el_aarch32_SError

_get_el:
		mrs x0, CurrentEL
		lsr x0, x0, #2
		ret
