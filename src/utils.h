/**
 * Alternate implementations of libc functions included here.
 */

#ifndef __STANDALONE_LIBC_UTILS
#define __STANDALONE_LIBC_UTILS

#include <stdint.h>

void* memset(void* data, int c, uint32_t len);

#endif /* __STANDALONE_LIBC_UTILS */
