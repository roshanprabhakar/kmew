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
struct process* ptable;
uint8_t cur_proc = 0;

uint64_t low_memory_start;

uint64_t t1_entry(uint64_t argc, uint64_t argv) {
	char msg[] = "hello world!\n";
	for (int i = 0; i < sizeof(msg); i++) {
		printf("%c", msg[i]);
		delay(100000000);
	}
	return 0;
}


void kmew_main() {

	// execution starts at el1
  printf("current exception level: %ld\n", get_el() >> 2);
  asm volatile("hvc #10");
  printf("current exception level: %ld\n", get_el() >> 2);

	// enable async interrupts
	enable_irq();

	// tracks length of all maintained kernel structures
	uint64_t kds = 0; // kernel data size
	
	// initialize memory page allocator
	mmap = readable_boundary + kds;
	uint32_t mmap_size = NUM_PAGES / 8;
	memset((void*) readable_boundary + kds, 0, mmap_size);
	kds += mmap_size;
	
	// initialize process table
	ptable = (struct process*) (readable_boundary + kds);	
	cur_proc = 0;
	uint32_t ptable_size = sizeof(struct process) * PROCESS_CAP;
	for (int i = 0; i < PROCESS_CAP; i++) {
		ptable[i].in_use = 0;
	}
	kds += ptable_size;

	low_memory_start = ROUND_UP(mmap + kds, PAGE_SIZE);
	
	t_init(&t1_entry, 0, 0);
	t_init(&t1_entry, 0, 0);

	printf("num in use proc block: ");

	int c = 0;
	for (int i = 0; i < PROCESS_CAP; i++) {
		if (ptable[i].in_use) c++;
	}

	printf_("%d\n", c);
	
#if 0
	// trigger timer interrupts
	inc_timer_cmp(200000);
	enable_timer_IRQ();
#endif

#if 0
  struct cli command_line; // first instance cannibalizes serial io
  cli_start(&command_line, (char *)&__kernel_boundary_end); 	// initialize session
#endif

  return;
}
