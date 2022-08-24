#ifndef _BOOT_H_
#define _BOOT_H_

#include <stdint.h>

/* Gets current exception level from CurrentEL register */
extern uint64_t _get_exception_level();
extern void _switch_to_el1();

#endif
