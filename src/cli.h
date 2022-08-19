
/**
 * Keep track of serial console status
 * - writable area
 * - current position
 */

#include <stdint.h>

#define CMD_POS 0x80				// start at bottom of stack

struct cli_pos { uint32_t x; }; // byte offset from console start

struct cli {
	struct cli_pos cur;				// current cursor position
	struct cli_pos cmd_end; 	// end of explorable field
	char* data_start;					// command stored here
};

void cli_start(struct cli*) __attribute__((section(".text.serial_cli")));
void cli_start(struct cli*);
