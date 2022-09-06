/**
 * Kernel entry function.
 *
 * Launches command line in infinite loop.
 */

#include <stdint.h>
#include "printf.h"
#include "serial_io.h"
#include "cli.h"
#include "boot.h"
#include "interrupts.h"

extern uint64_t __kernel_boundary_end;

void kmew_main() {
	printf("1 current exception level: %ld\n", get_el() >> 2);
	asm volatile ("svc #10");

#if 1
  struct cli command_line; // first instance cannibalizes serial io
  cli_start(&command_line, (char *)&__kernel_boundary_end); 	// initialize session
#endif

  return;
}

