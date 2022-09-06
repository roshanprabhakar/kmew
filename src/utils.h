/**
 * Alternate implementations of libc functions included here.
 */

#ifndef _SA_LIBC_
#define _SA_LIBC_

#include <stdint.h>

void* memset(void* data, int c, uint32_t len);

#endif // _SA_LIBC_
