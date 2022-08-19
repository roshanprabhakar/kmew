/**
 * Kernel entry function.
 *
 * Launches command line in infinite loop.
 */

#include <stdint.h>
#include "printf.h"
#include "serial_io.h"
#include "cli.h"

extern char* __kernel_boundary_end[];

void kmew_main() __attribute__((section(".text.kernel_main")));
void kmew_main() {
	
	// bare_metal_miniUART_setup();										// use this if deploying to bare metal

	struct cli command_line; 													// first instance cannibalizes serial io
	cli_start(&command_line, __kernel_boundary_end); 	// initialize session

	return;
}
