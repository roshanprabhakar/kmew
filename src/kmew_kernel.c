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

extern uint64_t __kernel_boundary_end;

void el1_entry() {
  printf("In the el1_entry function\n");

  printf("AFTER: Current exception level is: %d\n", get_exception_level());
}

void kmew_main() __attribute__((section(".text.kernel_main")));
void kmew_main() {

  // bare_metal_miniUART_setup();										// use this if deploying to bare metal

  printf("Current exception level is: %d\n", get_exception_level());

#if 0
  struct cli command_line; 													// first instance cannibalizes serial io
  cli_start(&command_line, (char *)&__kernel_boundary_end); 	// initialize session
#endif

  return;
}
