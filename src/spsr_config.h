#ifndef _SPSR_CONFIG_
#define _SPSR_CONFIG_

#include <stdint.h>

#define SPSR_EL 15 // lower 4 bits
#define SPSR_DAIF 15 << 6 // 9-6
#define SPSR_NZCV 15 << 28 // 31-28

uint32_t get_reset_spsr_el1(void);

#endif // _SPSR_CONFIG_
