#ifndef _BOOT_H_
#define _BOOT_H_

#include <stdint.h>

/* Gets current exception level from CurrentEL register */
extern uint64_t get_exception_level();

#endif
