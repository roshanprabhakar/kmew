/**
 * Kernel entry function.
 *
 * Launches command line in infinite loop.
 */

#include <stdint.h>
#include "irq.h"
#include "printf.h"
#include "serial_io.h"
#include "cli.h"
#include "boot.h"
#include "vtable.h"

extern uint64_t __kernel_boundary_end;

/* This function runs in exception level 1 */
void kmew_main() {

	init_irq_vector();
	enable_interrupt_controller();

  printf("Current exception level is: %d\n", get_exception_level());

#if 1
  struct cli command_line; 													// first instance cannibalizes serial io
  cli_start(&command_line, (char *)&__kernel_boundary_end); 	// initialize session
#endif

  return;
}
