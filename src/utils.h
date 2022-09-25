/**
 * Alternate implementations of libc functions included here.
 */

#ifndef _SA_LIBC_
#define _SA_LIBC_

#include <stdint.h>

#define SHALLOW_SIZE(X) (sizeof(X) / sizeof(X[0]))

void* memset(void* data, int c, uint32_t len);
int32_t strcmp(char const* str1, char const* str2);

#endif // _SA_LIBC_
