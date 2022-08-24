/**
 * Kmew command line api. 
 * Integral structures and types.
 */

#ifndef _CLI
#define _CLI

#include <stdint.h>

/* Could just use int32, this exists because it started off with 
 * more members.
 */
struct cli_pos { uint32_t x; }; // byte offset from console start

/* Holds all necessary information for managing a CLI on top of 
 * emulated terminal. Only one struct cli should be used per emulator.
 */
struct cli {
  struct cli_pos cur;				// current cursor position
  struct cli_pos cmd_end; 	// end of explorable field (explorable with <,>)
  char* data_start;					// command stored here
};

void cli_start(struct cli*, char*) __attribute__((section(".text.serial_cli")));
void cli_start(struct cli*, char*);

#endif /* _CLI */
