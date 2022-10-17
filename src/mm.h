#ifndef _MM_H_
#define _MM_H_

#include <stdint.h>

#define KiB 1024
#define PAGE_SIZE 4 * KiB
#define NUM_PAGES 80 // must be multiple of 8

#define set_free(i) mm_query(i, 0)
#define set_in_use(i) mm_query(i, 1)

extern uint64_t low_memory_start; // after kernel data
extern uint64_t mmap; // each byte marks a page in use or free

void* malloc_page();
uint8_t is_free(int i);

#endif // _MM_H_
