/**
 * Kernel entry function.
 *
 * Launches command line in infinite loop.
 */

#include <stdint.h>
#include "printf.h"
#include "serial_io.h"
#include "cli.h"
#include "interrupts.h"
#include "boot.h"

extern uint64_t __kernel_boundary_end;

void kmew_main() {
	init_el1_vector_table(); // done in el2
	printf("5 current exception level: %ld\n", get_el() >> 2);
	switch_to_el1(); 
	int i = 5;
	i += 5;
	// printf("[%d] current exception level: %ld\n", i, get_el() >> 2);

	/*
	 Enable interrupts from system timer.
	 Set timer compare register.
	 Interrupt handler should execute.
	 */
	/*
	printf("is pending: %d\n", (*( uint32_t* ) IRQ_BASIC_PENDING) & 1);
	enable_timer_IRQ();
	printf("is pending after irq enabled: %d\n", (*( uint32_t* ) IRQ_BASIC_PENDING) & 1);
	printf("value before cmp set: %d\n", *( uint32_t* ) TIMER_CLO);
	inc_timer_cmp(1000);
	printf("value after cmp set: %d\n", *( uint32_t* ) TIMER_CLO);
	block_until_timer_irq();
	*/

#if 0
  struct cli command_line; // first instance cannibalizes serial io
  cli_start(&command_line, (char *)&__kernel_boundary_end); 	// initialize session
#endif

  return;
}

