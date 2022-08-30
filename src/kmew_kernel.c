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

extern uint64_t __kernel_boundary_end;

/* This function runs in exception level 1 */
void kmew_main() {
	init_el1_vector_table();
  printf("Current exception level is: %d\n", get_exception_level());
	switch_to_el1();
  printf("Current exception level is: %d\n", get_exception_level());

	/*
	 enable all IRQ interrupts including system timer.
	 set timer compare register.
	 interrupt handler should execute.
	 */



	printf("is pending: %d\n", (*( uint32_t* ) IRQ_BASIC_PENDING) & 1);
	enable_timer_IRQ();
	printf("is pending after irq enabled: %d\n", (*( uint32_t* ) IRQ_BASIC_PENDING) & 1);
	printf("value before cmp set: %d\n", *( uint32_t* ) TIMER_CLO);
	inc_timer_cmp(1000);
	printf("value after cmp set: %d\n", *( uint32_t* ) TIMER_CLO);
	block_until_timer_irq();
	
	/*
	init_vector_table();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
	*/


#if 0
  struct cli command_line; // first instance cannibalizes serial io
  cli_start(&command_line, (char *)&__kernel_boundary_end); 	// initialize session
#endif

  return;
}
