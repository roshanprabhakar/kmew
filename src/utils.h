/**
 * Alternate implementations of libc functions included here.
 */

#ifndef _SA_LIBC_
#define _SA_LIBC_

#include <stdint.h>

#define SHALLOW_SIZE(X) (sizeof(X) / sizeof(X[0]))

void* memset(void*, int, uint32_t);
int32_t strcmp(char const*, char const*);

// only works for b a power of 2
uint64_t round_down(uint64_t, uint64_t);
uint64_t round_up(uint64_t, uint64_t);

#endif // _SA_LIBC_
