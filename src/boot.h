#ifndef _BOOT_H_
#define _BOOT_H_

#include <stdint.h>

#define SPSR_EL 15 // lower 4 bits
#define SPSR_DAIF 15 << 6 // 9-6
#define SPSR_NZCV 15 << 28 // 31-28

uint32_t get_reset_spsr_el1(void);
void switch_to_el1(void);

uint64_t get_el(void);
uint64_t get_daif(void);
uint64_t get_nzcv(void);

#endif // _BOOT_H_
