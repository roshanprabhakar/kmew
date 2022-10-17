#include <stdint.h>

#include "mm.h"
#include "printf.h"

void dump_mmap() {
	for (int i = 0; i < NUM_PAGES / 8; i++) {
		bprintn(((char*) mmap)[i]);
	}
}

uint8_t is_free(int i) {
	return !(((char* const) mmap)[i / 8] & (1 << (i % 8)));
}

void mm_query(int i, uint8_t m) {
	char* cur = ((char* const) mmap) + i / 8;
	*cur = m ? 
		*cur | (1 << (i % 8)) 							: // set in use
		*cur & ((~(char)0) ^ (1 << (i % 8))); // set free
}

void* malloc_page() {
	for (int i = 0; i < NUM_PAGES; i++) {
		if (is_free(i)) {
			set_in_use(i);
			return (void*) (low_memory_start + PAGE_SIZE * i);
		}
	}
	return (void*) 0;
}
