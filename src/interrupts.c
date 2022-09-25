#include "interrupts.h"
#include "peripherals/irq.h"
#include "printf.h"

const char* exception_ids[] = {
	"sync from cur el t",
	"irq from cur el t",
	"fiq from cur el t",
	"serr from cur el t",

	"sync from cur el h",
	"irq from cur el h",
	"fiq from cur el h",
	"serr from cur el h",

	"sync from lower el at 64",
	"irq from lower el at 64",
	"fiq from lower el at 64",
	"serr from lower el at 64",

	"sync from lower el at 32",
	"irq from lower el at 32",
	"fiq from lower el at 32",
	"serr from lower el at 32"
};

void show_invalid_entry_message(
  uint64_t exception_type,
  uint64_t exception_desc,
  uint64_t src_addr,
	uint64_t el) {

  printf(
    "%s, ESR: %x, address: %x, el: %d\r\n", 
    exception_ids[exception_type], 
    exception_desc, 
    src_addr,
		el);
}

void handle_irq() {
	uint32_t irq_pending = *(uint32_t*) IRQ_PENDING_1;
	if (irq_pending & SYS_TIMER_MATCH_1) {
		*(uint32_t*) TIMER_CS = TIMER_CS_M1;
		*(uint32_t*) TIMER_C1 = (*(uint32_t*) TIMER_CLO) + 200000;
		printf("timer interrupt received!\n");
	}
}


void enable_timer_IRQ() {
	*(uint32_t*) ENABLE_IRQ_1 = 1 << 1;
}

void inc_timer_cmp(uint32_t i) {
	*(uint32_t*) TIMER_C1 = (*(uint32_t*) TIMER_CLO) + i;
}

/*
void inc_timer_cmp(uint32_t i) {
	*(uint32_t*) TIMER_C1 = *( uint32_t* ) TIMER_CLO + i;
}

void ack_timer_irq() {
	*(uint32_t*) TIMER_CS = TIMER_CS_M1;
	printf("timer interrupt received\n");
}

void block_until_timer_irq() {
	printf("waiting on timer interrupt...\n");
	for (;;) {
		if ((*(uint32_t*) IRQ_BASIC_PENDING) & 1) break;
	}
	printf("...received!\n");
}
*/
