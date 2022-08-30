#include <stdint.h>

#include "printf.h"
#include "timer.h"

const unsigned int interval = 200000;
unsigned int cur = 0;

void timer_init(void) {
	cur = *(uint32_t*) TIMER_CLO;
	cur += interval;
	*(uint32_t*) TIMER_C1 = cur;
}

void handle_timer_interrupt(void) {
	cur += interval;
	*(uint32_t*) TIMER_C1 = cur;
	*(uint32_t*) TIMER_CS = TIMER_CS_M1;
	printf("received timer interrupt");
}
