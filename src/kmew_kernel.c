/**
 * Kernel entry function.
 *
 * Launches command line in infinite loop.
 */

#include <stdint.h>
#include "interrupt_handlers.h"
#include "printf.h"
#include "serial_io.h"
#include "cli.h"
#include "vtable.h"
#include "timer.h"

extern uint64_t __kernel_boundary_end;

/* This function runs in exception level 1 */
void kmew_main() {
  printf("Current exception level is: %d\n", get_exception_level());

	
	
	/*
	init_vector_table();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
	*/


#if 0
  struct cli command_line; 													// first instance cannibalizes serial io
  cli_start(&command_line, (char *)&__kernel_boundary_end); 	// initialize session
#endif

  return;
}
