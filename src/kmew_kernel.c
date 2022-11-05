/**
 * Kernel entrypoint.
 *
 * Launches command line in infinite loop.
 */

#include <stdint.h>

#include "interrupts.h"
#include "printf.h"
#include "cli.h"
#include "boot.h"
#include "mm.h"
#include "serial_io.h"
#include "utils.h"

extern uint64_t __kernel_boundary_end;
uint64_t readable_boundary = (uint64_t) &__kernel_boundary_end;

uint64_t mmap;
uint64_t start_assignable;

void kmew_main() {

	uint64_t kds = 0; // kernel data structures size

	mmap = readable_boundary + kds;
	uint32_t mmap_size = NUM_PAGES / 8;
	memset((void*) mmap, 0, mmap_size);

	kds += mmap_size;
	start_assignable = round_up(readable_boundary + kds, PAGE_SIZE);

	/*
	bprint((void*) mmap, 8, 1); // dump bytes asc
	_putchar('\n');

	for (int i = 0; i < NUM_PAGES; i++) {
		printf("%d", IS_FREE(i));
	}
	_putchar('\n');
	*/

	uint64_t p1 = malloc_page();
	uint64_t p2 = malloc_page();
	uint64_t p3 = malloc_page();

	printf("start assign: %x\n", start_assignable);
	printf("%x, %x, %x\n", p1, p2, p3);
	printf("%d, %d\n", p2 - p1, p3 - p2);
	printf("index 1 in use: %d\n", IS_FREE(1));
	free(p2);
	printf("index 1 in use: %d\n", IS_FREE(1));
	uint64_t p4 = malloc_page();
	printf("same loc: %d\n", p2 == p4);


	// bprint((void*) mmap, 8, 1);
	// _putchar('\n');

	asm volatile("bl halt"); // return address is corrupted, halt here
  return;
}
