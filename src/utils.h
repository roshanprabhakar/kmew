/**
 * Alternate implementations of libc functions included here.
 */

#ifndef __STANDALONE_LIBC_UTILS
#define __STANDALONE_LIBC_UTILS

#include <stdint.h>

void* memset(void*, int, uint32_t) __attribute__((section(".text.kmew_libc")));
inline void* memset(void* data, int c, uint32_t len) {
	for (char* i = (char*) data; i < (char*) data + len; i++) 
		*i = (unsigned char) c;
	return data;
}

#endif /* __STANDALONE_LIBC_UTILS */
