#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include <stdint.h>

#include "peripherals/arm_interrupts.h"
#include "peripherals/timer.h"

void enable_timer_IRQ(void);
void inc_timer_cmp(uint32_t);
void block_until_timer_irq(void);
void ack_timer_irq(void);

void show_invalid_entry_message(uint64_t, uint64_t, uint64_t, uint64_t);
void handle_irq(void);

#endif // _INTERRUPTS_H_
