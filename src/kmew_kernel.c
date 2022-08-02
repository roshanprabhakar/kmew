void kmew_main() __attribute__((section(".text.kernel")));

#include <stdint.h>
#include "printf.h"
#include "serial_io.h"

extern char* __kernel_boundary_end[];

void kmew_main() {
	
	bare_metal_miniUART_setup();

	/** 
	 * COMMAND LINE INTERFACE
	 * 1. Prompt
	 * 2. Read data to cmd-start* (print to entry, with deletes)
	 * 3. on newline process data, reset wp
	 */

	char* cmd_start = __kernel_boundary_end;

	int wp = 0; // write pointer
	char prompt_sw = 1; // prompt_switch

	for (;;) {

		if (prompt_sw) { 
			_putchar('$'); _putchar(' '); prompt_sw = 0;
		}

		_getchar(cmd_start + wp);

		if (cmd_start[wp] == (char) 127 && wp > 1) {

			_delchar();
			wp--;

		} else {
			printf("[%d]", cmd_start[wp]);
			//_putchar(cmd_start[wp]);
			wp++;
		}
	}
}
