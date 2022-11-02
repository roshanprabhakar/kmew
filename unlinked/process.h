#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <stdint.h>

struct cpu_context {
	uint64_t x0;
	uint64_t x1;
	uint64_t x2;
	uint64_t x3;
	uint64_t x4;
	uint64_t x5;
	uint64_t x6;
	uint64_t x7;
	uint64_t x8;
	uint64_t x9;
	uint64_t x10;
	uint64_t x11;
	uint64_t x12;
	uint64_t x13;
	uint64_t x14;
	uint64_t x15;
	uint64_t x16;
	uint64_t x17;
	uint64_t x18;
	uint64_t x19;
	uint64_t x20;
	uint64_t x21;
	uint64_t x22;
	uint64_t x23;
	uint64_t x24;
	uint64_t x25;
	uint64_t x26;
	uint64_t x27;
	uint64_t x28;
	uint64_t fp; // fp
	uint64_t pc; // pc
	uint64_t sp;
	uint64_t cpsr;
};

struct process {
	uint8_t in_use;
	struct cpu_context context;
};

#define PROCESS_CAP 10 // ptable length
extern struct process* ptable;
extern uint8_t cur_proc;

struct process* find_proc_space();
int t_init(uint64_t (*)(uint64_t, uint64_t), uint64_t, uint64_t);

#define T_QUANTA 1200000
void schedule();
void save_proc_state(struct cpu_context*);
void restore_proc_state(struct cpu_context*);

#endif // _PROCESS_H_
