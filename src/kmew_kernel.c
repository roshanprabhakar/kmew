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

extern uint64_t __kernel_boundary_end;

void kmew_main() {

  printf("current exception level: %ld\n", get_el() >> 2);
  asm volatile("hvc #10");
  printf("current exception level: %ld\n", get_el() >> 2);

	enable_irq();
	inc_timer_cmp(200000);
	enable_timer_IRQ();

#if 0
  struct cli command_line; // first instance cannibalizes serial io
  cli_start(&command_line, (char *)&__kernel_boundary_end); 	// initialize session
#endif

  return;
}
