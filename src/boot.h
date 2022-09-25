#ifndef _BOOT_H_
#define _BOOT_H_

#include <stdint.h>

uint64_t get_el();
uint64_t get_daif();
uint64_t get_nzcv();

void set_sp(uint64_t);

void enable_irq();
void disable_irq();


#endif // _BOOT_H_
