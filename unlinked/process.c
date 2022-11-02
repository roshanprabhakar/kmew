#include "process.h"
#include "mm.h"
#include "printf.h"

// struct process* ptable;
// int cur_proc;

struct process* find_proc_space() {
	for (int i = 0; i < PROCESS_CAP; i++) {
		if (!ptable[i].in_use) return ptable + i;
	}
	return (struct process*) 0;
}

int t_init(uint64_t (*fn)(uint64_t, uint64_t), uint64_t argv, uint64_t argc) {
	struct process* p = find_proc_space();
	if (!p) return 1;
	
	p->in_use = 1;
	p->context.x0 = argc;
	p->context.x1 = argv;
	p->context.pc = (uint64_t) fn;
	p->context.sp = (uint64_t) malloc_page();

	printf("argc: %ld\nargv: %ld\npc: %ld\nsp: %ld\n", 
			p->context.x0, p->context.x1, p->context.pc, p->context.sp);
	
	return 0;
}

void schedule() {
	save_proc_state(&ptable[cur_proc].context);
	cur_proc = (cur_proc + 1) % PROCESS_CAP;
	restore_proc_state(&ptable[cur_proc].context);
}
