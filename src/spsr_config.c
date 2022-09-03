#include <stdint.h>

#include "spsr_config.h"

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
