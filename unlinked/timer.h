#ifndef __TIMER_H
#define __TIMER_H

#include "peripherals/timer.h"

void timer_init(void);
void handle_timer_interrupt(void);

#endif /* __TIMER_H */
