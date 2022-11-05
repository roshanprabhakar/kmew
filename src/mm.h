#ifndef _MM_H_
#define _MM_H_

#include <stdint.h>
#include "serial_io.h"
#include "system.h"
#include "printf.h"

#define PAGE_SIZE (4L * KiB)
#define NUM_PAGES 64 // must be multiple of 8

extern uint64_t start_assignable; 	// beginning of first assignable page
extern uint64_t mmap; 							// free page table

#define PTR_TO_IND(p) ((p - start_assignable) / PAGE_SIZE)
#define IND_TO_PTR(i) (uint64_t) (start_assignable + i * PAGE_SIZE)

#define IS_FREE(i) (!((((char*)mmap)[i / 8]) & (1 << (i % 8))))
#define SET_FREE(i) (((char*)mmap)[i / 8] &= (~0) ^ (1 << (i % 8)))
#define SET_USE(i) (((char*)mmap)[i / 8] |= 1 << (i % 8))

// NULL if no free page available
uint64_t malloc_page();
void free(uint64_t);

#endif // _MM_H_
